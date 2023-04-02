#include  "infrared.h"
#include  "stc8g1k_code.h"
#include  "STC8xxxx.h"
#include  "global.h"
#include  "uart.h"
#include  "string.h"
//���ݶ���

bit edgeFlag = 0;   //����ܽ��սű��ر�ʶ
bit sysFunFlag;      //ϵͳ���ܱ�־
bit IR_Flag=0;		//�������ݽ�����ɱ�־λ
u8 IR_time=0;		  //�½���֮���ʱ�����ֵ
u8 IR_data[9];		//������+8��λ���ݸ���ռ�õ�ʱ��
u8 IR_bit;		//����IR_bit����ָʾ�������ݵ�λ��
u8 btn_value=0; //���ⰴ����ֵ�Ĵ���
u8 IRdata_len = 0; //����ܽ��յ����ݳ���
u8 IRdata[IR_DATA_BUFFER_SIZE];
u32 time_cnt=0;     //��ʱ������ ������λ1s


static void IR_Data_deal(void);
static u8 IR_decode(void);	
static void Int1_init(void);

void infrared_init(void)
{
    btn_value = 0;
	  edgeFlag = 1;
	  //����������
	  Int1_init();		//�ⲿ�ж�1��ʼ������  ���������  //����IC�����	
	
}
void infrared_check_deal(void)
{
		if(IR_Flag)				//�������ݽ������
		{
				//��������
				if(IR_time >0xf0)
				{		
					  IR_time =0; 
						IR_Flag =0; 				
						IR_Data_deal();
				}
		}
}


//-------------------����������ݴ���-------------------------------
static void IR_Data_deal(void)
{
		u8 dat=0,i,light=0,onoff=0;

		for(i=0;i<IRdata_len;i++) 
		{
				if(IRdata[i]==IR_LIGHT_BUTTON)
					 light++;
				else  if(IRdata[i]==IR_ONOFF_BUTTON)
					 onoff++;
		}
		if(IRdata_len == 0)
			 return;
		if(light > onoff)
			 dat = IR_LIGHT_BUTTON;
		else if(light < onoff)
			 dat = IR_ONOFF_BUTTON;

		IRdata_len = 0;
		
		switch(dat)//���������ȷ
		{
			case  IR_LIGHT_BUTTON:   //�Ƶ�λ���ڼ�
						 if(sysFunFlag==1)
						 {
							 btn_value++;
							 if(btn_value > BUTTON_VALUE_MAX)
							 {
									btn_value = 1;
							 }

						 }
						 else
							 return;	
			break;
			case  IR_ONOFF_BUTTON:  //��Դ���ؼ�
					 if(sysFunFlag==1)
					 {
							 sysFunFlag = 0;
							 btn_value = 0;
					 }
					 else
					 {
							 sysFunFlag = 1;
							 btn_value = 1;
					 }							 
			break;	
			default:
						return;			
		}
    rdelay_acton_fun(btn_value);
}

//-------------------------������ս���-------------------------
static u8 IR_decode(void)
{
	u8 j;//,k;								
	u8 IR_Value = 0; 
	//k=0;							//���ñ���k����1����ΪkΪ0ʱȡ���Ľ����ǡ��������ʱ������
 
	for(j=0;j<=7;j++)				//�ڲ�ѭ��8��Ϊ��ƴ��8������λΪ1���ֽ�
	{
		if(IR_data[j]>=5)			//����ʱ��������5���ǿ϶��ǡ�1�롱��֮Ϊ��0�롱
			IR_Value|=0x80;			//ͨ����λ�������λ��1
		if(j<7)						    //������û��ƴ����8��
			IR_Value>>=1;			  //ͨ���������㡰�ڳ���λ��׼����һλ�ж�
		//k++;						      //�±��������
	}
	
	return IR_Value;				//���غ�����յ�����
}

//-------------------------�ⲿ�ж�1������������ų�ʼ��-------------------------
static void Int1_init(void)
{
	IT1 = 1;	//������ʽΪ�½��ش���
	EX1 = 1;	//ʹ��INT1�ж�
}
void INT1_ISR() interrupt INT1_VECTOR	 //���Ӻ���ܽ��ս�
{
	static u8 isRec=0; 

	if(edgeFlag) //�����ж�
	{   //�ߵ�ƽ�ﵽ9msΪ��ʼ λ
		  IT1 = 0;	//������ʽΪ���ش���
		  EX1 = 1;	//ʹ��INT1�ж�
		  edgeFlag = 0; 
		  if(IR_time>50)	//�ж�������(9ms+1.12ms)��0.56ms+1.12ms��
			{
				    isRec = 1;
				    IR_bit = 0;
			}
			
	}
	else
	{   //�����ж�
		IT1 = 1;	//������ʽΪ�½��ش���
		EX1 = 1;	//ʹ��INT1�ж�
		edgeFlag = 1;

		if(isRec)
		{
						IR_data[IR_bit]=IR_time;		//�洢��Ӧλʱ����
						IR_time=0;						//����ʱ���ȼ���ֵ
						IR_bit++;						  //λ����������
						if(IR_bit==8)				  //����ﵽ��9λ��������+8������λ��
						{
							IR_Flag=1;				  //�������ݽ�����ɱ�־λ��1
							IR_bit=0;					  //λ����������
							isRec =0;
							
							IRdata[IRdata_len] = IR_decode();
							++IRdata_len;
							if(IRdata_len >= IR_DATA_BUFFER_SIZE)	
									IRdata_len=0;
						}
		}
	}
	IR_time =0;  //����ʱ���ȼ���ֵ
}
