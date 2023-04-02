#include  "encryptionDecryption.h"
#include  "global.h"
#include  "py32f0xx_hal.h"
#include  "user_flash.h"
#include  "string.h"
/*********************************
�����洢��FLASH�еĵ�ַͳ�ƣ�
���в�����            0x80004000  -���ڱ�����Ƕ�ʱʱ��
��һ�����б�־������   0x80004080
UID����1�����ַ��    0x80004100
UID����2�����ַ1��    0x80004180
UID����2�����ַ2��    0x80004200
************************************/
//ID���ܷ���1��+11 ^85 -62  <<2     �洢��ַ��0x0280
//ID���ܷ���2��-0 +0 -0 +0     �洢��ַ��0x0200

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
	  uid[0] = HAL_GetUIDw0();  //UID��Ϊ96��bitλ
	  uid[1] = HAL_GetUIDw1();
	  uid[2] = HAL_GetUIDw2();
}

static void readCodeId(u8 method,u32 addr,u32 *idpt)
{ 
    //u32 adr;
	  u8 i,j,dat[12];
	  NewDataType srcD;
	
	  //flash��ַ0x80001000+addr��
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
			   encryption1(dat,sizeof(dat));  //������ȡ������ԭ
		}
		memcpy((u8 *)&idpt[0],&dat[0],sizeof(u32));
		memcpy((u8 *)&idpt[1],&dat[4],sizeof(u32));
		memcpy((u8 *)&idpt[2],&dat[8],sizeof(u32));
		
} 

//���ܷ���1��+11 ^85 -62  <<2
static void encryption(u32 *idpt,u8 len)
{   //���ܷ��������Ǵ洢ID����������ȡ��ID��ַ����ID���ݰ�����1�ķ������м������㣬��ͬ�洢��ַ0x02000ֵ�Ƚ��Ƿ���ͬ
      u8 i;
	  
			for(i=0;i<len;i++)
			{
					idpt[i] += 11;
					idpt[i] ^= 85; 
					idpt[i] -= 62; 
					idpt[i] <<= 2;  
			}
		
}
//���ܷ���2���ֽ�ȡ��
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
	
	  encryption(codeId2,3); //���ܷ���1��+11 ^85 -62  <<2

}

//ID����ȣ�����0������ȷ���1
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


//ID����ȣ�����0������ȷ���1
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

//FLASH��ַ��� ��λ�̶���0x80001000
static u32 comb_addr(u16 adr)
{
     u32 addr= 0x80;
		 
    addr <<= 12;
	  addr +=  0x10;
	  addr <<= 8;
	
	  addr += adr;
    return addr;
}
//��FLASH�ж�ȡ����
static void get_flash_data(u32 adr,NewDataType *data)
{
    u32 addr;
		 
    addr = comb_addr(adr);
	
	  memcpy((u8 *)data,(u8 *)(addr),sizeof(NewDataType)); //��flash��ַ0x08001000  �������ݵ�������

}
//��ȡ�����flash 0x80004083�е����ݱ�־
static u32 read_one_run(void)
{
	  u32  *dirDat;
	  u32 var,addr=0x3080;
	  
	  addr = comb_addr(addr);

	  dirDat = ((u32 *)(addr)); //��flash��ַ0x80004080��ȡ����
	
	  var = dirDat[6];//ƫ����6
	
	  return var;
}
//�洢���ݱ�־ֵ0x55aa33cc �� flash 0x80004083��ַ�е�
static void save_one_run(void)
{
	  u32 wordVal=0x55;
	  u32 addr;
		NewDataType srcD;
	
    //addr = comb_addr(0);
	  //memcpy((u8 *)(&srcD),(u8 *)(addr),(sizeof(NewDataType))); 
	  get_flash_data(0,&srcD);//��flash��ַ0x80001000  �������ݵ�������
	
	  addr = comb_addr(0x3080);

	  wordVal  <<=8;  wordVal +=0xaa;
	  wordVal  <<=8;  wordVal +=0x33;
	  wordVal  <<=8;  wordVal +=0xcc;
	  srcD.arrA[6] = wordVal;  //ƫ����0
	  //DATA[5] = wordVal;
	  //data_save_flash(DATA,sizeof(DATA),addr); //�洢��flash��ַ0x80004080��
	  data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //�洢��flash��ַ0x80004080��
	  
}
u8 code_run(void)
{
    u32  var,addr;
	  u8   i;
	
	  var = read_one_run();
	
	  if(var==0x55aa33cc)  //��ȡ�����һ�����б�־ ���ж������Ƿ�������������ǵ�һ������
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
					   while(1); //�ȴ����Ź���λ
					
				}
		 }
			 //���Ǳ�����one_run(void) ����FLASH������
       addr = comb_addr(0x3300);		
		   data_save_flash(DATA,sizeof(NewDataType),addr); //�洢��flash��ַ0x80004300�� 		
		}
		return 1;
}

/*оƬ��д����󣬵�һ������ִ�к���
���ܣ�1����ȡоƬID��-96bit�������ܣ��Ӽ��ܺ��96bit�дӵ͵��ߣ���8bit��ʽΪһ�飬��ϳ��ֽں󣬷ֱ�������鲻ͬ��λ���У�
      2���������鲻ͬλ�÷��䷽������96bit��ȡ����4bitȡ����˳�����δ��������λ�á�
      3�����ڴ�������鵥Ԫ���֣�32λ������������ÿ���ֽڴ�������鵥Ԫ���еĵ��ֽڣ�ÿ��һ���֣���һ���ֽڡ�
 ���磺 96bitID��ȡ�������� u32 id[0]=0x12345678,id[1]=9abcdef0,id[2]=11223344�����У� 
      ��һ��ȡ8bit�����Ǵ�id[0]ֵ��0x78,����һ���֣�32bit����4�μ���ȡ�ꡣ�����4����Ԫ�ֽڵ����飬
      ����ID�����24����Ԫ�ֽڵ����飬�����������鶨��Ϊ u8 uid[12]�������FLASH���ڴ滺����u32 DATA[32]��
      ��ôuid[0] ����� DATA[0]������ֽڣ�uid[1] ����� DATA[1]�Ĵε��ֽڡ�    
*/
void one_run(void) 
{
	  u32  uid[3];
	  u32  addr;
	  u8   uid_byt[12];
	  u8   i;
	  NewDataType srcD;
			
		save_one_run();
		//�����Ƕ�ȡ UID ���ܺ�ֱ���뵽ָ����ַ��FLASH��
		getUid(uid); //��ȡUID
		
		//���м���1
		encryption(uid,3);
		//��96bit��ϳ�12���ֽڳ��ȵ�����
		memcpy(&uid_byt[0],(u8 *)(&uid[0]),sizeof(u32));
		memcpy(&uid_byt[4],(u8 *)(&uid[1]),sizeof(u32));
		memcpy(&uid_byt[8],(u8 *)(&uid[2]),sizeof(u32));
	  //������uid_byte ���䵽�ڴ���
    get_flash_data(0,&srcD); //��flash��ַ0x80001000  �������ݵ�srcD������	
		for(i=0;i<sizeof(uid_byt);i++)
		{
		   srcD.arrA[i*2] &= 0xffffff00;
			 srcD.arrA[i*2] += uid_byt[i];
		}
    //�����������1��FLASH	
    addr = comb_addr(0x3100);   
		data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //�洢��flash��ַ0x80004100��
    /*ι��*/
		if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
		{
				Error_Handler();
		}
		//uid�ż���2
		getUid(uid); //��ȡUID
		//��96bit��ϳ�24��Ԫ�ֽ�����
		memcpy(&uid_byt[0],(u8 *)(&uid[0]),sizeof(u32));
		memcpy(&uid_byt[4],(u8 *)(&uid[1]),sizeof(u32));
		memcpy(&uid_byt[8],(u8 *)(&uid[2]),sizeof(u32));
		//���ֽڽ��м���2
		encryption1(uid_byt,12);
		 //������uid_byte ���䵽�ڴ���
		for(i=0;i<sizeof(uid_byt);i++)
		{
		   srcD.arrA[i*2] &= 0x00ffffff;
			 srcD.arrA[i*2] += (u32)uid_byt[i]<<24;
		}
		 //�����������2��FLASH	
    addr = comb_addr(0x3180);		
		data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //�洢��flash��ַ0x80004180��
		/*ι��*/
		if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
		{
				Error_Handler();
		}
		 //�����������3��FLASH	
    addr = comb_addr(0x3200);		
		data_save_flash(srcD.arrA,sizeof(NewDataType),addr); //�洢��flash��ַ0x80004200��

}


#if 0  //������������������������������ͬ
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
	perm1=~(perm1|refer);//�ų�perm1��λ����Чbit�ĸ��ţ����ų�0001 1111��ǰ��3��0
	perm2=~(perm2|refer);//ͬ��
	value=perm1&perm2;
	return value|tmp;
}
#endif
