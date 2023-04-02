#include  "encryptionDecryption.h"
#include  "global.h"
#include  "uart.h"
//ID加密方法1、+11 ^85 -62  <<2     存储地址：0x0280
//ID加密方法2、-0 +0 -0 +0     存储地址：0x0200

u8  codeId1[7];
u8  codeId2[7];

char  *irId1;
void readCodeId(u16 addr,u8 *idpt)
{ 
	  u8 i;
	
	  EA =0;
	  irId1 = (char code *)(addr & 0xffff);
     
	  for(i=0;i<7;i++)
    {  
         idpt[i] = irId1[i]; 
    }	
    EA =1;
}

//还原ID加密方法1、+11 ^85 -62  <<2    存储地址：0x0280
void decryption(u8 *idpt)
{   //加密方法二就是存储ID参数，这里取出ID地址，把ID数据按加密1的方法进行加密运算，再同存储地址0x02000值比较是否相同
    u8 i=0;
	  for(i=0;i<7;i++)
	  {
        idpt[i] += 11;
			  idpt[i] ^= 85; 
        idpt[i] -= 62; 
        idpt[i] <<= 2;  
		}
}
		

static void id_method1(void)
{
	  u16 adr = 0x0002;
	  adr  <<= 8;
	  adr  |= 0x0080;
    readCodeId(adr,codeId1);
}

static void id_method2(void)
{
    u16 adr = 0x0002;
	  adr  <<= 8;
	  
    readCodeId(adr,codeId2);
		decryption(codeId2);

}

u8 method_res_compare(void)
{
	  u8  i,res=0;

    id_method1();
	  id_method2();
    
    for(i=0;i<7;i++)
	  {
			  
		   if(codeId1[i] != codeId2[i])
			 {
				 res =1;
			   break;
			 }
		}
		return res;
}



u8 id_compare(void)
{
	  u8  i,res=0;
	  u16 adr = 0x0002;
	  adr  <<= 8;
	
    readCodeId(adr,codeId1);
	
	  adr = 0x1f; //0x1ff9
	  adr <<= 8;
	  adr |= 0x00f9;
	
	  readCodeId(adr,codeId2);
	
    for(i=0;i<7;i++)
	  {
			  
		   if(codeId1[i] != codeId2[i])
			 {
				 res =1;
			   break;
			 }
		}
		return res; 
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
