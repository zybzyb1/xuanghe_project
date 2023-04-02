#include  "infrared.h"
#include  "global.h"
#include "user_gpio.h"
#include "buzzer.h"
#include  "py32f0xx_hal.h"
#include  "string.h"
//���ݶ���

#define   IR_HIGH_TIMER   3// 5

u8 sysFunFlag;      //ϵͳ���ܱ�־
u8 IR_Flag;		    //�������ݽ�����ɱ�־λ
u8 IR_time;		    //�½���֮���ʱ�����ֵ
u8 IR_data[9];		//������+8��λ���ݸ���ռ�õ�ʱ��
u8 IR_bit;		//����IR_bit����ָʾ�������ݵ�λ��
u8 btn_value; //���ⰴ����ֵ�Ĵ���
u8 IRdata_len; //����ܽ��յ����ݳ���
u8 IRdata[IR_DATA_BUFFER_SIZE];
u32 time_cnt;     //��ʱ������ ������λ1s
u8 ir_int_flag;    //�����жϱ�������
u8 si_level;

static void IR_Data_deal(void);
static u8 IR_decode(void);	
extern void rdelay_acton_fun(u8 btn_value);

void infrared_init(void)
{
    btn_value = 0;
    IR_Flag=0;		    //�������ݽ�����ɱ�־λ
    IR_time=0;		    //�½���֮���ʱ�����ֵ
	  IRdata_len = 0;   //����ܽ��յ����ݳ���
	  btn_value=0;      //���ⰴ����ֵ�Ĵ���
	  time_cnt=0;       //��ʱ������ ������λ1s
	  si_level =0;
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
			case  IR_ONOFF_BUTTON:  //��Դ���ؼ���ҡ��������ϣ������ɫ˿ӡ����
							 btn_value++;
							 if(btn_value >= BUTTON_VALUE_MAX)
							 {
									btn_value = 0;								
							 }						 
			break;
			case  IR_LIGHT_BUTTON:   //�Ƶ�λ���ڼ���ҡ��������ϣ������˿ӡ�ƿؿ��ؼ���
					 if(btn_value==0)
					 {
							 if(sysFunFlag)
							 {
								  LIGHT_OFF();
								  sysFunFlag=0;
							 }
							 else
							 {
								  LIGHT_ON();
								  sysFunFlag=1;
							 }
					 }
					 buzzerEnableFlag = 1;					 
			return;	
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
		if(IR_data[j]>=IR_HIGH_TIMER)			//����ʱ��������5���ǿ϶��ǡ�1�롱��֮Ϊ��0�롱
			IR_Value|=0x80;			//ͨ����λ�������λ��1
		if(j<7)						    //������û��ƴ����8��
			IR_Value>>=1;			  //ͨ���������㡰�ڳ���λ��׼����һλ�ж�
		//k++;						      //�±��������
	}
	
	return IR_Value;				//���غ�����յ�����
}

//-------------------------�ⲿ�ж�1������������ų�ʼ��-------------------------
u8 isRec=0;
void ir_falling(void)  //�������ش��� 
{
	 //�����ж�
	 //�ߵ�ƽ�ﵽ9msΪ��ʼ λ	 
	  if( IR_time > 34)	//50�ж�������(9ms+1.12ms)��0.56ms+1.12ms��
		{
					isRec = 1;
					IR_bit = 0;
		}
		IR_time =0;  //����ʱ���ȼ���ֵ
}

void ir_rising(void)  //�������ش���
{   //�����ж�	
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
	  IR_time =0;  //����ʱ���ȼ���ֵ
}
