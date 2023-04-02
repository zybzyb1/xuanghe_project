#include  "encryptionDecryption.h"
#include  "global.h"
#include  "py32f0xx_hal.h"
#include  "user_flash.h"
#include  "string.h"
/*********************************
参数存储在FLASH中的地址统计：
运行参数：            0x80004000  -现在保存的是定时时长
第一次运行标志参数：   0x80004080
UID加密1保存地址：    0x80004100
UID加密2保存地址1：    0x80004180
UID加密2保存地址2：    0x80004200
************************************/
//ID加密方法1、+11 ^85 -62  <<2     存储地址：0x0280
//ID加密方法2、-0 +0 -0 +0     存储地址：0x0200

u32  codeId1[3];
u32  codeId2[3];

static void get_flash_data(u32 adr,NewDataType *data);
static u32 comb_addr(u16 adr);
static void encryption1(u8* uid_byt,u8 len);
void one_run(void)  __attribute__ ((section(".ARM.__at_0x08004300")));

extern IWDG_HandleTypeDef   IwdgHandle;

static void getUid(u32 *uid)
{
    if(uid == NULL)
	     return;
	  uid[0] = HAL_GetUIDw0();  //UID长为96个bit位
	  uid[1] = HAL_GetUIDw1();
	  uid[2] = HAL_GetUIDw2();
}

static void readCodeId(u8 method,u32 addr,u32 *idpt)
{ 
    //u32 adr;
	  u8 i,j,dat[12];
	  NewDataType srcD;
	
	  //flash地址0x80001000+addr起
	  //adr = comb_addr(addr);
	  //srcD = (READ_REG(*((NewDataType *)(adr & 0xffffffff))));
    get_flash_data(addr,&srcD);
  
	  if(method == 1)
	  {
			  for(i=0,j=0;i<sizeof(dat);i++)
				{
						 dat[j++] = (u8)(srcD.arrA[i*2]); 
				}
		}
	  if(method == 2)
	  {
			   for(i=0,j=0;i<sizeof(dat);i++)
				{
						 dat[j++] = (u8)(srcD.arrA[i*2]>>24); 
				}
			   encryption1(dat,sizeof(dat));  //把数据取反，还原
		}
		memcpy((u8 *)&idpt[0],&dat[0],sizeof(u32));
		memcpy((u8 *)&idpt[1],&dat[4],sizeof(u32));
		memcpy((u8 *)&idpt[2],&dat[8],sizeof(u32));
		
} 

//加密方法1、+11 ^85 -62  <<2
static void encryption(u32 *idpt,u8 len)
{   //加密方法二就是存储ID参数，这里取出ID地址，把ID数据按加密1的方法进行加密运算，再同存储地址0x02000值比较是否相同
      u8 i;
	  
			for(i=0;i<len;i++)
			{
					idpt[i] += 11;
					idpt[i] ^= 85; 
					idpt[i] -= 62; 
					idpt[i] <<= 2;  
			}
		
}
//加密方法2将字节取反
static void encryption1(u8* uid_byt,u8 len)
{
    u8 i;
	 
	 for(i=0;i<len;i++)
	 {
	     uid_byt[i] = ~uid_byt[i];
	 }
	
}
static void id_method1(void)
{  //UID0:0x1FFF0E00UL UID1:0x1FFF0E04UL UID2:0x1FFF0E08UL
	  u32 baseAdr;
		
	 	baseAdr = 0x31;
    baseAdr <<=8;	
		readCodeId(1,0x3100,codeId1);
		
}

static void id_method2(void)
{
    u32 baseAdr;
		
		baseAdr = 0x31;
	  baseAdr <<= 8;
	  baseAdr += 0x80;
		readCodeId(2,baseAdr,codeId2);
	
	  encryption(codeId2,3); //加密方法1、+11 ^85 -62  <<2

}

//ID号相等，返回0，不相等返回1
u8 method_res_compare(void)
{
	  u8  i,res=0;

    id_method1();
	  id_method2();
    
    for(i=0;i<3;i++)
	  {
		   if(codeId1[i] != codeId2[i])
			 {
				 res =1;
			   break;
			 }
		}
		return res;
}


//ID号相等，返回0，不相等返回1
u8 id_compare(void)
{
	  u8  i,res=0;
	  u32 baseAdr;
	  u32 uid[3];
		
    getUid(uid);
	  baseAdr = 0x32;
    baseAdr <<= 8;	
		readCodeId(2,baseAdr,codeId2);
	
    for(i=0;i<3;i++)
	  {
			  
		   if(uid[i] != codeId2[i])
			 {
				 res =1;
			   break;
			 }
		}
		return res; 
}

//FLASH地址组合 高位固定是0x80001000
static u32 comb_addr(u16 adr)
{
     u32 addr= 0x80;
		 
    addr <<= 12;
	  addr +=  0x10;
	  addr <<= 8;
	
	  addr += adr;
    return addr;
}
//从FLASH中读取数据
static void get_flash_data(u32 adr,NewDataType *data)
{
    u32 addr;
		 
    addr = comb_addr(adr);
	
	  memcpy((u8 *)data,(u8 *)(addr),sizeof(NewDataType)); //从flash地址0x08001000  读出数据到缓冲区

}
//读取存放在flash 0x80004083中的数据标志
static u32 read_one_run(void)
{
	  u32  *dirDat;
	  u32 var,addr=0x3080;
	  
	  addr = comb_addr(addr);

	  dirDat = ((u32 *)(addr)); //从flash地址0x80004080读取数据
	
	  var = dirDat[6];//偏移量6
	
	  return var;
}
//存储数据标志值0x55aa33cc 到 flash 0x80004083地址中的
static void save_one_run(void)
{
	  u32 wordVal=0x55;
	  u32 addr;
		NewDataType srcD;
	
    //addr = comb_addr(0);
	  //memcpy((u8 *)(&srcD),(u8 *)(addr),(sizeof(NewDataType))); 
	  get_flash_data(0,&srcD);//从flash地址0x80001000  读出数据到缓冲区
	
	  addr = comb_addr(0x3080);

	  wordVal  <<=8;  wordVal +=0xaa;
	  wordVal  <<=8;  wordVal +=0x33;
	  wordVal  <<=8;  wordVal +=0xcc;
	  srcD.arrA[6] = wordVal;  //偏移量0
	  //DATA[5] = wordVal;
	  //data_save_flash(DATA,sizeof(DATA),addr); //存储到flash地址0x80004080中
	  data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //存储到flash地址0x80004080中
	  
}
u8 code_run(void)
{
    u32  var,addr;
	  u8   i;
	
	  var = read_one_run();
	
	  if(var==0x55aa33cc)  //读取程序第一次运行标志 并判断条件是否成立，成立则不是第一次运行
			return 0;
    else  //save_one_run();
		{
			 for(i=0;i<5;i++)
			{
				HAL_Delay(10);
				one_run();
				HAL_Delay(10);
				if(id_compare() && method_res_compare())
					continue;
				else
				{
					   while(1); //等待看门狗复位
					
				}
		 }
			 //覆盖本函数one_run(void) 代码FLASH区数据
       addr = comb_addr(0x3300);		
		   data_save_flash(DATA,sizeof(NewDataType),addr); //存储到flash地址0x80004300中 		
		}
		return 1;
}

/*芯片烧写代码后，第一次运行执行函数
功能：1、读取芯片ID号-96bit，并加密，从加密后的96bit中从低到高，按8bit方式为一组，组合成字节后，分别存入数组不同的位置中，
      2、存入数组不同位置分配方法，从96bit中取出的4bit取出的顺序依次存入数组的位置。
      3、由于存入的数组单元是字（32位），所以上面每个字节存放在数组单元字中的低字节，每隔一个字，放一个字节。
 例如： 96bitID号取出后存放在 u32 id[0]=0x12345678,id[1]=9abcdef0,id[2]=11223344数组中， 
      第一次取8bit数据是从id[0]值是0x78,所以一个字（32bit）分4次即可取完。可组成4个单元字节的数组，
      所有ID可组成24个单元字节的数组，这里给这个数组定义为 u8 uid[12]，存放至FLASH的内存缓冲区u32 DATA[32]。
      那么uid[0] 存放在 DATA[0]的最低字节，uid[1] 存放在 DATA[1]的次低字节。    
*/
void one_run(void) 
{
	  u32  uid[3];
	  u32  addr;
	  u8   uid_byt[12];
	  u8   i;
	  NewDataType srcD;
			
		save_one_run();
		//下面是读取 UID 加密后分别存入到指定地址的FLASH中
		getUid(uid); //读取UID
		
		//进行加密1
		encryption(uid,3);
		//将96bit组合成12个字节长度的数组
		memcpy(&uid_byt[0],(u8 *)(&uid[0]),sizeof(u32));
		memcpy(&uid_byt[4],(u8 *)(&uid[1]),sizeof(u32));
		memcpy(&uid_byt[8],(u8 *)(&uid[2]),sizeof(u32));
	  //把数组uid_byte 分配到内存中
    get_flash_data(0,&srcD); //从flash地址0x80001000  读出数据到srcD缓冲区	
		for(i=0;i<sizeof(uid_byt);i++)
		{
		   srcD.arrA[i*2] &= 0xffffff00;
			 srcD.arrA[i*2] += uid_byt[i];
		}
    //保存加密数据1到FLASH	
    addr = comb_addr(0x3100);   
		data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //存储到flash地址0x80004100中
    /*喂狗*/
		if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
		{
				Error_Handler();
		}
		//uid号加密2
		getUid(uid); //读取UID
		//将96bit组合成24单元字节数组
		memcpy(&uid_byt[0],(u8 *)(&uid[0]),sizeof(u32));
		memcpy(&uid_byt[4],(u8 *)(&uid[1]),sizeof(u32));
		memcpy(&uid_byt[8],(u8 *)(&uid[2]),sizeof(u32));
		//将字节进行加密2
		encryption1(uid_byt,12);
		 //把数组uid_byte 分配到内存中
		for(i=0;i<sizeof(uid_byt);i++)
		{
		   srcD.arrA[i*2] &= 0x00ffffff;
			 srcD.arrA[i*2] += (u32)uid_byt[i]<<24;
		}
		 //保存加密数据2到FLASH	
    addr = comb_addr(0x3180);		
		data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //存储到flash地址0x80004180中
		/*喂狗*/
		if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
		{
				Error_Handler();
		}
		 //保存加密数据3到FLASH	
    addr = comb_addr(0x3200);		
		data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //存储到flash地址0x80004200中

}


#if 0  //以下两个函数是两个异或的逆运算异同
u8 xnor(u8 a, u8 b) {
	u8 res = 0;
	u8 i;
	u8 arr1[8] = { 0 };
	u8 arr2[8] = { 0 };
	u8 arr3[8] = {0};
	for (i = 0; i < 8; i++) {
		arr1[i] = a % 2;
		arr2[i] = b % 2;
		a = a / 2;
		b = b / 2;
	}
	u8 m = 0;
	for (i = 7; i >= 0; i--) {
		if (arr1[i] == 1 || arr2[i] == 1) {
			m = i + 1;
			break;
		}
	}
	
	for (i = 0; i < m; i++) {
		if (arr1[i] == arr2[i]) arr3[i] = 1;
		else arr3[i] = 0;
		res = res + arr3[i] * pow(2, i);
	}
	return res;
}
u8 same_or(u8 perm1,u8 perm2)
{
	u8 tmp=perm1>perm2 ? perm1:perm2;
	u8 n=0, refer=~0, value;
	while(tmp>>n)
		n++;
	refer<<=n;
	tmp=perm1&perm2;
	perm1=~(perm1|refer);//排除perm1高位上无效bit的干扰，如排除0001 1111的前面3个0
	perm2=~(perm2|refer);//同上
	value=perm1&perm2;
	return value|tmp;
}
#endif
