#include  "encryptionDecryption.h"
#include  "global.h"
#include  "uart.h"
//ID���ܷ���1��+11 ^85 -62  <<2     �洢��ַ��0x0280
//ID���ܷ���2��-0 +0 -0 +0     �洢��ַ��0x0200

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

//��ԭID���ܷ���1��+11 ^85 -62  <<2    �洢��ַ��0x0280
void decryption(u8 *idpt)
{   //���ܷ��������Ǵ洢ID����������ȡ��ID��ַ����ID���ݰ�����1�ķ������м������㣬��ͬ�洢��ַ0x02000ֵ�Ƚ��Ƿ���ͬ
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
