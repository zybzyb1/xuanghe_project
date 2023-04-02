#if  0
/*******************��������*******************
��������

1����һ�δ����̵���1 (PCB�����������̵���)��ͨ220V��Դ��

2���ڶ��δ����̵���1 (PCB�����������̵���)�Ͽ����̵���2 (PCB���м�̵���)��ͨ220V��Դ��

3�������δ����̵���1 �����̵���2 ����ͨ220V��Դ��

4�����Ĵδ����ֻص���һ�δ���ʵ�ֵĹ��ܣ�ֻ��(PCB�����������̵���)��ͨ220V��Դ��
************************************************/

#include  "stc8g1k_code.h"		
#include  "STC8xxxx.h"	
#include  "STC8G_H_GPIO.h"
#include  "STC8G_H_ADC.h"
#include  "STC8G_H_NVIC.h"
#include  "string.h"
#include  "global.h"

#define   IR_ONOFF_BUTTON     0x1B    //����ҡ�ذ忪�ؼ�ֵ
#define   IR_LIGHT_BUTTON     0xBB    //����ҡ�ذ����˿��λ������ֵ

#define   DELAY1_OFF     P37=0    
#define   DELAY2_OFF     P10=0 
#define   DELAY1_ON      P37=1
#define   DELAY2_ON      P10=1 
#define   TOUCH_PIN      P34

#define   BUTTON_VALUE_MAX   4    //���λ, ��ʵֻ��3��
#define   TIMER_LENGTH_MAX   16   //��ʱ��ʱ8Сʱ������0.5Сʱ

#define  IR_DATA_BUFFER_SIZE  10

#ifdef    UART_ENABLE
#include  "uart.h"
#endif


 

//���ݶ���
bit IR_Flag=0;		//�������ݽ�����ɱ�־λ
u8 IR_time=0;		//�½���֮���ʱ�����ֵ
u8 IR_data[9];		//������+8��λ���ݸ���ռ�õ�ʱ��

//bit IR_TimeFlag;            //���ⷢ����ʱ����־
//unsigned char count;        //280us

u16 Touch_time;     //������ʱ��
bit Touch_flag=0;     //����IC�����־
bit touch_preFlag=0; //�ϴδ���IC�����־
bit timeFunFlag;    //��ʱ���ܱ�־
bit sysFunFlag;     //ϵͳ���ܱ�־

bit edgeFlag = 0;   //����ܽ��սű��ر�ʶ
bit IR_data_deal_flag=0; //����ܽ��յ����ݴ������־
static u8 IR_bit;		//����IR_bit����ָʾ�������ݵ�λ��
static u8 btn_value=0; //���ⰴ����ֵ�Ĵ���
u32 time_cnt=0;     //��ʱ������ ������λ1s
u8 secFlag=0;       //���־
u8 IR_count = 0;    //����ܽ��յ����ݺ���ʱ������--250ms
u8 IRdata_len = 0; //����ܽ��յ����ݳ���
u8 IRdata[IR_DATA_BUFFER_SIZE];

 
//��������
void delay(u16 count);		//��ʱ��������
static void Timer0Init(void);		//��ʱ������0��ʼ������
static void Timer1Init(void);		//��ʱ������1��ʼ������
static void Int0_init(void);		//�ⲿ�ж�0��ʼ������
static u8 IR_decode(void);			//������뺯��
static void gpio_config(void);
static void IR_Data_deal(void);
static void rdelay_acton_fun(u8 action_value);
static  u8 touch_check(void);    //�������
static void touch_deal(void);    //��������
static u8  calculate_timer(u16 adValue);
static u8  time_unit_compare(u8 delayTime);
static void	ADC_config(void);
static void  timer_deal(void);
static void Int1_init(void);

//-------------------------������----------------------------
void main(void)
{
	u8 num=0;			

	gpio_config();
	EA = 1;				  //���ж�

	Timer0Init();		//��ʱ������0��ʼ������
	Timer1Init();		//��ʱ������1��ʼ������
	Int1_init();		//�ⲿ�ж�1��ʼ������  ���������  //����IC�����

	delay(1000);			//�ȴ������ȶ�


	while(1)
	{	
	
		if(IR_Flag)				//�������ݽ������
		{
			IR_Flag=0; 
			IR_count =0;
			IR_data_deal_flag=1;
      IRdata[IRdata_len++] = IR_decode();
      if(IRdata_len >= IR_DATA_BUFFER_SIZE)	
          IRdata_len=0;				
		}
		else
		{
			//250ms ��������
			if(IR_count > 1 && IR_data_deal_flag)	//250ms 
			{		
        IR_data_deal_flag=0;
				
				#ifdef UART_ENABLE
				for(num=0;num<IRdata_len ;num++)
			    TX1_write2buff(IRdata[num]);
				#endif
				
				IR_Data_deal();
			}
		}
		if(touch_check())  //�������
		{
			 sysFunFlag = 1;
		}
		touch_deal();
	
	}
}
static void gpio_config(void)
{

	 P3_PULL_UP_ENABLE(GPIO_Pin_0 | GPIO_Pin_1);//			
	 //P3_PULL_UP_ENABLE(GPIO_Pin_1);//
	
   P1_MODE_OUT_PP(GPIO_Pin_0);   //�������P1.0 �����м�ڶ����̵���
	 P3_MODE_OUT_PP(GPIO_Pin_6 |GPIO_Pin_7);   //�������P3.7 ���Ʊ��ϵ�һ���̵���  //�������P3.6 ����ܴ���IC С���Դ����
	
	 //P3_MODE_OUT_PP(GPIO_Pin_6);   //�������P3.6 ����ܴ���IC С���Դ����
	 P3_MODE_IN_HIZ(GPIO_Pin_3 | GPIO_Pin_4);   //ʩ���ش���ʹ��P3.3 ���Ӵ���IC�����
	 //P3_MODE_IN_HIZ(GPIO_Pin_4);   //ʩ���ش���ʹ��P3.4 ���Ӻ���ܽ��ս�
	
	 DELAY1_OFF;   
   DELAY2_OFF; 
	 P36 = 0; 
}

/*************��������*********************/
static  u8 touch_check(void)
{   //����������   �޴���ʱ�ߵ�ƽ���д���ʱ�͵�ƽʱ������300ms
    if(TOUCH_PIN == 0)
    {
			   if(Touch_flag) 
					 Touch_time = 0;
         else if(Touch_time > 500)  //139΢�� *500 = 69.5ms
				 {
					    Touch_time = 0;
				      Touch_flag = 1; 
					    
					    return 1;
				 } 
    }
		else 
		{
				if(Touch_flag)
				{
						if(Touch_time > 2000)  //139΢�� *2000 = 279.5ms
						{
							 Touch_time=0;
							 Touch_flag = 0;
							
						}
				}
				else Touch_time=0;
				    
		}
		return 0;
}

static void touch_deal(void)
{
	 if(Touch_flag)
	 {
			if(!touch_preFlag)
			{
					touch_preFlag = 1;
				  btn_value++;
				  
					if(btn_value >= BUTTON_VALUE_MAX)
							btn_value = 1;				
				  rdelay_acton_fun(btn_value);	
			}
	 }
	 else 
	 {
			touch_preFlag = 0;	
	 }
}

//-------------------------��ʱ����----------------------------
void delay(u16 count)
{
	while(count--)
	{
		_nop_();
	}
}
	
//-------------------����������ݴ���-------------------------------
static void IR_Data_deal(void)
{
	u8 dat,i,light=0,onoff=0;

	for(i=0;i<IRdata_len;i++) 
	{
			if(IRdata[i]==IR_LIGHT_BUTTON)
				 light++;
			else  if(IRdata[i]==IR_ONOFF_BUTTON)
				 onoff++;
	}
	if(light > IRdata_len/2)
		 dat = IR_LIGHT_BUTTON;
	else if(onoff > IRdata_len/2)
		 dat = IR_ONOFF_BUTTON;
	memset(IRdata,0,IR_DATA_BUFFER_SIZE);
	IRdata_len = 0;
	
	switch(dat)//���������ȷ
	{
		case  IR_LIGHT_BUTTON:   //�Ƶ�λ���ڼ�
				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= BUTTON_VALUE_MAX)
						 btn_value = 1;
				}
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
         time_cnt=0;    //��Դ�����������㶨ʱ������				 
    break;	
    default:
          return;			
	}
	
  rdelay_acton_fun(btn_value);

}

static void rdelay_acton_fun(u8 action_value)
{
	#ifdef UART_ENABLE
		TX1_write2buff(action_value);
	#endif
    switch(action_value)
		{
		    case 0:  // �Ͽ����м̵���
            DELAY1_OFF; 
						DELAY2_OFF;  
        break;
				case 1:   //
            DELAY1_ON; 
						DELAY2_OFF;  
        break;
				case 2:
            DELAY1_OFF; 
						DELAY2_ON;  
        break;
				case 3:
            DELAY1_ON; 
						DELAY2_ON;  
        break;
		    default:
					
				break;
		}
}
//-------------------------��ʱ����ʼ��----------------------------
void Timer0Init(void)		//139΢��@6.000MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x02;		//���ö�ʱ��ģʽ
	TL0 = 0xBA;		//���ö�ʱ��ֵ
	TH0 = 0xBA;		//���ö�ʱ����ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;		//ʹ��T0�ж�
}
void Timer1Init(void)		//125����@6.000MHz
{
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xDC;		//���ö�ʱ��ֵ
	TH1 = 0x0B;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	
	ET1 = 1;		//ʹ��T1�ж�
}

//-------------------------�ⲿ�ж�1��ʼ��-------------------------
static void Int1_init(void)
{
	IT1 = 1;	//������ʽΪ�½��ش���
	EX1 = 1;	//ʹ��INT1�ж�
	edgeFlag = 1;
}


//-------------------------������ս���-------------------------
static u8 IR_decode(void)
{
	u8 j,k;								
	u8 IR_Value = 0; 
	k=1;							//���ñ���k����1����ΪkΪ0ʱȡ���Ľ����ǡ��������ʱ������
 
	for(j=0;j<=7;j++)				//�ڲ�ѭ��8��Ϊ��ƴ��8������λΪ1���ֽ�
	{
		if(IR_data[k]>5)			//����ʱ��������5���ǿ϶��ǡ�1�롱��֮Ϊ��0�롱
			IR_Value|=0x80;			//ͨ����λ�������λ��1
		if(j<7)						    //������û��ƴ����8��
			IR_Value>>=1;			  //ͨ���������㡰�ڳ���λ��׼����һλ�ж�
		k++;						      //�±��������
	}
	
	return IR_Value;				//���غ�����յ�����
}

void INT1_ISR() interrupt 2	 //���Ӻ���ܽ��ս�
{
	static u8 isRec=0; 

	if(edgeFlag) //�����ж�
	{   //�ߵ�ƽ�ﵽ9msΪ��ʼ λ
		  IT1 = 0;	//������ʽΪ���ش���
		  EX1 = 1;	//ʹ��INT1�ж�
		  edgeFlag = 0; 
		  if(IR_time>60)	//�ж�������(9ms+1.12ms)��0.56ms+1.12ms��
			{
				IR_data[0]=IR_time;		//�洢��Ӧλʱ���� 
			  IR_bit=1;						  //λ����������
				isRec = 1;
			}
			IR_time =0;  //����ʱ���ȼ���ֵ
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
			if(IR_bit==9)				  //����ﵽ��9λ��������+8������λ��
			{
				IR_Flag=1;				  //�������ݽ�����ɱ�־λ��1
				IR_bit=0;					  //λ����������
				isRec =0;
			}
		}
	}
}

void Time0_Handler_Callback(void) 	interrupt TIMER0_VECTOR		//���ж�ʱ�Ѿ������־//�����ǻص�����
{
	if(IR_time < 0xf0)IR_time++;
	Touch_time++;
}
void Time1_Handler_Callback(void)	interrupt TIMER1_VECTOR		//���ж�ʱ�Ѿ������־//�����ǻص�����
{
	static u8 secCount=0;
	
	if(IR_data_deal_flag)	//125ms 	
      IR_count++;
	
  
	if(++secCount >= 8)
	{
	   secCount = 0;
		 secFlag=1;
		 if(timeFunFlag)   //��ʱ���ܿ����ż���
		     time_cnt++;   //8Сʱ��ʱ������ 1s�ۼ�һ�� 
	}		
	
}

#endif

//SN8P2501BP��Ƭ��RC��ŵ�Դ���루ϣ���ܸ�λ��������������
//��·ԭ��ͼ���:http://www.51hei.com/bbs/dpj-212635-1.html
//********************************************************
//����  RC: �ڲ�16MHz          ��ǰ�汾: V0
//Ŀ�� MCU: SN8P2501BP,SOP14   
//��������: SL                 ��¼У��:  
//��ʼ����: 2016.3.16          �������: 2016.X.X

//********************************************************
//;               _____________  ____________
//;              |             \/            |
//;             -|P2.2                   P2.3|-
//;             -|P2.1                   P2.4|-
//;             -|P2.0                   P2.5|-
//;          +5V-|VDD                     VSS|-GND
//;  DEFRST/LED1-|P1.3/XIN          INT0/P0.0|-AN1
//;  REHEAT/LED2-|P1.2/XOUT              P1.0|-AD
//;             -|P1.1/RET/VPP   PWM/BZ0/P5.4|-CEACEL/LED3
//;              |___________________________|
//;                   SN8P2511P,DIP8
//********************************************************
#include <SN8P2501B.h>          // ͷ�ļ�
#include "global.h"             //

//********************************************************
//#pragma �ϵ粻��0
//********************************************************
#pragma data_address 0x2f       //
uchar    SDian_Cnt;             //
#pragma data_address 0x2e       //
bit      SDian_bz;              //
//**** ʱ��������� **************************************   
uchar    TimerCnt;              //                                                                                                                                 
ulong    Worktime;              //
ulong    WorkBuff;              //
uchar    WorkGear;              //  

uchar   Funflag0;
uchar   Funflag1;
sbit    Time1s_bz = Funflag0:0;             //
//**** AD�������� ****************************************
uchar    JS1;                   //
uchar    AD_Cnt;                //
uchar    AD_value;              //
ulong    RT_Cnt;                //
ulong    RS_Cnt;                //


sbit      ChongDian1_bz = Funflag0:1;         //
sbit      ChongDian2_bz = Funflag0:2;         //
sbit      ChongDian3_bz = Funflag0:3;         //
sbit      ChongDian4_bz = Funflag0:4;         //

//***** <KEY> ********************************************
sbit      Defrost_bz = Funflag1:0;             //
sbit      Reheat_bz = Funflag1:1;             //
sbit      Cancel_bz = Funflag1:2;             //

sbit      Bagle_bz = Funflag0:5;              //
sbit      Key_bz = Funflag0:6;                //


//***** <�Լ�> *******************************************
sbit      ZiJian_bz = Funflag0:7;             //  



#define   IR_ONOFF_BUTTON     0x1B    //����ҡ�ذ忪�ؼ�ֵ
#define   IR_LIGHT_BUTTON     0xBB    //����ҡ�ذ����˿��λ������ֵ

#define   DELAY1_OFF     P37=0    
#define   DELAY2_OFF     P10=0 
#define   DELAY1_ON      P37=1
#define   DELAY2_ON      P10=1 
#define   TOUCH_PIN      P34

#define   BUTTON_VALUE_MAX   4    //���λ, ��ʵֻ��3��
#define   TIMER_LENGTH_MAX   16   //��ʱ��ʱ8Сʱ������0.5Сʱ
#define  IR_DATA_BUFFER_SIZE  10
//���ݶ���
bit IR_Flag=0;		//�������ݽ�����ɱ�־λ
u8 IR_time=0;		//�½���֮���ʱ�����ֵ
u8 IR_data[9];		//������+8��λ���ݸ���ռ�õ�ʱ��

u16 Touch_time;     //������ʱ��
bit Touch_flag=0;    //����IC�����־
bit touch_preFlag=0; //�ϴδ���IC�����־
bit timeFunFlag;     //��ʱ���ܱ�־
bit sysFunFlag;      //ϵͳ���ܱ�־

bit edgeFlag = 0;   //����ܽ��սű��ر�ʶ
bit IR_data_deal_flag=0; //����ܽ��յ����ݴ������־
static u8 IR_bit;		//����IR_bit����ָʾ�������ݵ�λ��
static u8 btn_value=0; //���ⰴ����ֵ�Ĵ���
u32 time_cnt=0;     //��ʱ������ ������λ1s
u8 secFlag=0;       //���־
u8 IR_count = 0;    //����ܽ��յ����ݺ���ʱ������--250ms
u8 IRdata_len = 0; //����ܽ��յ����ݳ���
u8 IRdata[IR_DATA_BUFFER_SIZE];

 
//��������
static u8 IR_decode(void);			//������뺯��
static void IR_Data_deal(void);
static void rdelay_acton_fun(u8 action_value);
static  u8 touch_check(void);    //�������
static void touch_deal(void);    //��������




//********************************************************
//��������
//********************************************************
void Sys_Init(void);            // ϵͳ��ʼ��
void AdccDeal(void);            // ��λ������
void KeyeDeal(void);            // ��������
void Defrost(void);             //
void Reheat(void);              // ��������
void Bagle(void);               //
void Cancel(void);

void ZhiJDeal(void);            //   
void DataDeal(void);            // ���ݴ���
void TimeDeal(void);            //
void Delayms(uchar k);          //
//********************************************************
//ϵͳ��ʼ��
//********************************************************
void Sys_Init(void)             //
{               
        OSCM = 0x00;                // ��ͨģʽ(˫ʱ��)         
        INTEN= 0x00;                //
        INTRQ= 0x00;                //

        //--- I0 Config --------------------------------------
	 P3_PULL_UP_ENABLE(GPIO_Pin_0 | GPIO_Pin_1);//			
	 //P3_PULL_UP_ENABLE(GPIO_Pin_1);//
	
   P1_MODE_OUT_PP(GPIO_Pin_0);   //�������P1.0 �����м�ڶ����̵���
	 P3_MODE_OUT_PP(GPIO_Pin_6 |GPIO_Pin_7);   //�������P3.7 ���Ʊ��ϵ�һ���̵���  //�������P3.6 ����ܴ���IC С���Դ����
	
	 //P3_MODE_OUT_PP(GPIO_Pin_6);   //�������P3.6 ����ܴ���IC С���Դ����
	 P3_MODE_IN_HIZ(GPIO_Pin_3 | GPIO_Pin_4);   //ʩ���ش���ʹ��P3.3 ���Ӵ���IC�����
	 //P3_MODE_IN_HIZ(GPIO_Pin_4);   //ʩ���ش���ʹ��P3.4 ���Ӻ���ܽ��ս�
	
	 DELAY1_OFF;   
   DELAY2_OFF; 
	 P36 = 0; 

        P0M  = 0xFF;                // 0=����   1=���
        P2M  = 0xFF;                //
        P1M  = 0xF1;                // 0xF3
        P5M  = 0xFF;                //
        
        P0UR = 0x00;                // 0=������ 1=����
        P2UR = 0x00;                //
        P1UR = 0x0C;                // 0x0C
        P5UR = 0x00;                //

        FP12=1;                     // 0=�͵�ƽ 1=�ߵ�ƽ
        FP13=1;                     // (����ָʾ�� �򿪵����)
        FP54=1;                     // bit ����д��ʡROM�ռ�
        //--- P00 Config-------------------------------------
        PEDGE = 0x10;               //�½��ش����ж�
        //PEDGE = 0x08;               //�����ش����ж�
		FP00IRQ  = 0;               //����жϱ�־
        FP00IEN  = 1;               //P0.0 �ⲿ�ж�(INT0)ʹ��
        edgeFlag = 1;
        //--- T0  Config--��ʱ��T0����------------------------------------
		//FT0TB = 0;                  //��ֹ RTC
        T0M=0x70;                   // 16M/16/2= 2uS   Fcpu��2��Ƶ 
        //T0M=0x10;                   // 1M/16/128=500uS   Fcpu��128��Ƶ
        T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 ÿ139us�ж�һ��      
		FT0IRQ=0;                   // T0 �ж������־���㡣
		FT0IEN=1;                   //������Ӧ T0 �жϡ�
        FT0ENB=1;                   //������ʱ��T0���� 
        //--- TC0 PWM Config  ���������� 2KƵ��-�ߵ�ƽ�͵͵�ƽ��ʱ���ȶ�Ϊ 250��s--------------------------------------
        TC0M=0x70;                  // 16MHz/16=  Fcpu/2   2us  256-250/2=
        TC0R=131;                   //ÿ��125*2 =250us�ж�һ��
        TC0C=131;                   //  
        FALOAD0=1;                  // 
		FTC0OUT=1;                  //����P5.4����PWM���
		FPWM0OUT = 1;               //����PWM/BUZZER����  
        FTC0IEN=0;                  //�������ж�// Enable TC0 Interrput
        FTC0ENB=1;                  // ��ʱ������
        //----Start Run---------------------------------------
        FGIE = 1;                   // Enable all Interrput
        //----------------------------------------------------
#if 0
        ZhiJDeal();                 //  
        Worktime=100;
        WorkBuff=0;
        //----------------------------------------------------
        if(SDian_Cnt==2)                // ����������ϵ紦��
        {   if(SDian_bz) SDian_Cnt=2;   //
            else SDian_Cnt=1;           //
        }
        else if(SDian_Cnt==3)           //
        {   if(SDian_bz) SDian_Cnt=3;   //
            else SDian_Cnt=1;           //
        }
        else if(SDian_Cnt==4)           //
        {   if(SDian_bz) SDian_Cnt=4;   //
            else SDian_Cnt=1;           //
        }
	    else                            //
	    {    SDian_Cnt=1;                //
	                SDian_bz=1;                 //  
	    }
	     
#endif
}
#if 0
//********************************************************
//��ʱ����
//********************************************************
void Delayms(uchar k)
{   uchar x,y;
    for(x=0;x<k;x++)
        {  for(y=100;y>0;y--);}//100
}
//********************************************************
//ʱ�䴦��
//********************************************************
void TimeDeal(void)                            //
{   //---------------------------------------
        if(WorkBuff>=40)                       // ������ؼ��ȱ�־
        {   if(Reheat_bz) Cancel_bz=1;                   // 50S�ػ�   
        }               
    //---------------------------------------        
    if(WorkBuff>=Worktime)                 // ʱ�䵽�ػ�
        {   SDian_Cnt++;                       //
                if(SDian_Cnt>=4) SDian_Cnt=4;      //
        Cancel_bz=1;                               //
        }
        //---------------------------------------                                             //
}                                             

//********************************************************
//�Լ������
//********************************************************
void ZhiJDeal(void)
{   
    Delayms(1);
        while(1)
        {   
            if(FP12);
                if(FP13);
        Delayms(1);
            if(FP12)break;
                if(FP13)break;
                ZiJian_bz=1;
                FP12M=1;
                FP13M=1;
                break;
        }
}

//********************************************************
//��λ������
//********************************************************
void KeyeDeal(void)
{   
#if 0
    //----------------------------------------------------
        if(Bagle_bz|Defrost_bz)                    //
        {   
		        if(SDian_Cnt==1)
                {   Worktime=Defrost_TAB1[WorkGear];                    
                }
                else if(SDian_Cnt==2)
                {   Worktime=Defrost_TAB2[WorkGear];                                       
                }        
                else if(SDian_Cnt==3)
                {   Worktime=Defrost_TAB3[WorkGear];                    
                }
                else if(SDian_Cnt==4)
                {   Worktime=Defrost_TAB4[WorkGear];                    
                }                        
        }
        else
        {       if(SDian_Cnt==1)
                {  Worktime=Noranl_TAB1[WorkGear];                    
                }
                else if(SDian_Cnt==2)
                {  Worktime=Noranl_TAB2[WorkGear];                                       
                }        
                else if(SDian_Cnt==3)
                {  Worktime=Noranl_TAB3[WorkGear];                    
                }
                else if(SDian_Cnt==4)
                {  Worktime=Noranl_TAB4[WorkGear];                    
                }
        }
#endif
        //----------------------------------------------------
        //----------------------------------------------------
        
        //if(FP11)KeyCnt3=0;
    //else Cancel();
/*
    if(Reheat_bz|Defrost_bz|ZiJian_bz){}
        else
        {
                if(FP12)KeyCnt1=0;
                else Reheat();

                if(FP13)KeyCnt2=0;
                else Defrost();   
        }*/
}
//********************************************************
//�������ܴ���
//********************************************************
/*void Cancel(void) //ȡ��
{   KeyCnt3++;
        if(KeyCnt3>5)
        {   KeyCnt3=0;
                FP12M=1;
                FP13M=1;
                FP54=0;
        Cancel_bz=1;
     }
}*/
/*
//------------------------------
void Reheat(void)  //�ؼ���
{
     KeyCnt1++;
         if(KeyCnt1>2)
         {   KeyCnt1=0;

         Reheat_bz=1;
                 FP12M=1;
                 FP13M=1;
                 FP12=0;
     }         
}
//-----------------------------
void Defrost(void) //�ⶳ
{
     KeyCnt2++;
         if(KeyCnt2>2)
         {   KeyCnt2=0;

         Defrost_bz=1;
                 FP12M=1;
                 FP13M=1;
                 FP13=0;
     }
}
*/
//********************************************************
//��λ������
//********************************************************
void AdccDeal(void)             //
{   if(Reheat_bz)return;

    if( !ChongDian1_bz )        // ��һ�ηŵ�
        {    ChongDian1_bz=1;       // �˿����
             FP00M=0;               // ��Ϊ����FP00
                 FP10M=1;               // ��Ϊ���
                 FP10=0;                // ���0
                 Delayms(2);            // Ҫ���㹻ʱ��ŵ�
        }
        else if( !ChongDian2_bz )   //
        {     
             T0C=0;                 // �嶨ʱ��0                     
         FP10M=0;               //0 ����
                 FP00M=1;               //
                 FP00=1;                // *��һ�γ��               
         FT0ENB=1;              // �򿪶�ʱ��
                 NOP(1);
                 NOP(1);
                 while(1)               //
                 {    WDTR=0x5A;        //
                      if(JS1>20)break;//FP54=0;                                       
                          if( FP10 )break;        // ������Ϊ�߾��˳�                  
                 }        
                 FT0ENB=0;              // �ض�ʱ��
         RS_Cnt+=T0C;           //
                 T0C=0;                 //
                 JS1=0;
         FP00M=0;               //0
                 FP10M=1;               // ��Ϊ���
                 FP10=0;                // ���0�ŵ�
                 ChongDian2_bz=1;       //
        }
        else if( !ChongDian3_bz )   //  
        {    ChongDian3_bz=1;       //
         FP00M=0;               // 0
                 FP10M=1;               // ��Ϊ���
                 FP10=0;                // ���0�ŵ�
                 Delayms(2);            // Ҫ���㹻ʱ��ŵ�
        }
        else if( !ChongDian4_bz )   //
        {
             T0C=0;                 // �嶨ʱ��0                       
         FP10M=0;               //
                 FP00M=0;               // *�ڶ��γ��
         FT0ENB=1;              // �򿪶�ʱ��        
                 NOP(1);
                 NOP(1);
                 while(1)               //
                 {    WDTR=0x5A;        //
                      if(JS1>20)break;//FP54=0;         
                          if( FP10 )break;  // ������Ϊ�߾��˳�                           
                 }

                 FT0ENB=0;              // �ض�ʱ��
                 RT_Cnt+=T0C;           //
                 JS1=0;
                 T0C=0;                 //
         FP00M=0;               //0 ��Ϊ���
                 FP10M=1;               //
                 FP10=0;                //
                 ChongDian4_bz=1;       //
                 
        }
    else
        {   AD_Cnt++;               //
            if(AD_Cnt==8)         // ��128������ƽ��ֵ
        {   AD_Cnt=0;           //
                    RT_Cnt>>=3;         // RT���ʱ��ƽ��ֵ
                        RS_Cnt>>=3;         // RS��׼ʱ��ƽ��ֵ
                        
                        //----------------------------------------------------                                      
                AD_value=(RS_Cnt*230)/RT_Cnt;      // �Ŵ�230�� *���������ᳬ��256*
                        //-------------------------------------------
                        //11����ֵ[225-200-170-148-123-103-76-53-28-9] 104
                        //----------------------------------------------------               
             if(AD_value>=227)         //1
                        {   WorkGear=1;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }                        
                        else if(AD_value>=206 )   //1.5
                        {   WorkGear=2;
                            if(ZiJian_bz){FP13=1;FP12=0;}
                        }
                        else if(AD_value>=173 )   //2
                        {   WorkGear=3;
                            if(ZiJian_bz){FP13=0;FP12=0;}
                        }
                        else if(AD_value>=155 )   //2.5
                        {   WorkGear=4;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else if(AD_value>=125 )   //3
                        {   WorkGear=5;
                            if(ZiJian_bz){FP13=1;FP12=0;}
                        }
                        else if(AD_value>=103)    //3.5
                        {   WorkGear=6;
                            if(ZiJian_bz){FP13=0;FP12=0;}
                        }
                        else if(AD_value>=75)     //4
                        {   WorkGear=7;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else if(AD_value>=56 )    //4.5
                        {   WorkGear=8;
                            if(ZiJian_bz){FP13=1;FP12=0;}
                        }
                        else if(AD_value>=22 )    //5
                        {   WorkGear=9;
                            if(ZiJian_bz){FP13=0;FP12=0;}
                        }
                        else if(AD_value>=5 )    //5.5
                        {   WorkGear=10;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else
                        {   if(AD_value<5)      //6
                                {   WorkGear=11;
                                    if(ZiJian_bz){FP13=1;FP12=0;}
                                }         
                        }        
            //-----------------------------------------------------
                }
                ChongDian1_bz=0;                       //
                ChongDian2_bz=0;                       //
                ChongDian3_bz=0;                       //
                ChongDian4_bz=0;                       //               
        }
}
#endif

/*************��������*********************/
static  u8 touch_check(void)
{   //����������   �޴���ʱ�ߵ�ƽ���д���ʱ�͵�ƽʱ������300ms
    if(TOUCH_PIN == 0)
    {
			   if(Touch_flag) 
					 Touch_time = 0;
         else if(Touch_time > 500)  //139΢�� *500 = 69.5ms
				 {
					    Touch_time = 0;
				      Touch_flag = 1; 
					    
					    return 1;
				 } 
    }
		else 
		{
				if(Touch_flag)
				{
						if(Touch_time > 2000)  //139΢�� *2000 = 279.5ms
						{
							 Touch_time=0;
							 Touch_flag = 0;
							
						}
				}
				else Touch_time=0;
				    
		}
		return 0;
}

static void touch_deal(void)
{
	 if(Touch_flag)
	 {
			if(!touch_preFlag)
			{
					touch_preFlag = 1;
				  btn_value++;
				  
					if(btn_value >= BUTTON_VALUE_MAX)
							btn_value = 1;				
				  rdelay_acton_fun(btn_value);	
			}
	 }
	 else 
	 {
			touch_preFlag = 0;	
	 }
}


//-------------------����������ݴ���-------------------------------
static void IR_Data_deal(void)
{
	u8 dat,i,light=0,onoff=0;

	for(i=0;i<IRdata_len;i++) 
	{
			if(IRdata[i]==IR_LIGHT_BUTTON)
				 light++;
			else  if(IRdata[i]==IR_ONOFF_BUTTON)
				 onoff++;
	}
	if(light > IRdata_len/2)
		 dat = IR_LIGHT_BUTTON;
	else if(onoff > IRdata_len/2)
		 dat = IR_ONOFF_BUTTON;
	memset(IRdata,0,IR_DATA_BUFFER_SIZE);
	IRdata_len = 0;
	
	switch(dat)//���������ȷ
	{
		case  IR_LIGHT_BUTTON:   //�Ƶ�λ���ڼ�
				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= BUTTON_VALUE_MAX)
						 btn_value = 1;
				}
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
         time_cnt=0;    //��Դ�����������㶨ʱ������				 
    break;	
    default:
          return;			
	}
	
  rdelay_acton_fun(btn_value);

}
//-------------------------������ս���-------------------------
static u8 IR_decode(void)
{
	u8 j,k;								
	u8 IR_Value = 0; 
	k=1;							//���ñ���k����1����ΪkΪ0ʱȡ���Ľ����ǡ��������ʱ������
 
	for(j=0;j<=7;j++)				//�ڲ�ѭ��8��Ϊ��ƴ��8������λΪ1���ֽ�
	{
		if(IR_data[k]>5)			//����ʱ��������5���ǿ϶��ǡ�1�롱��֮Ϊ��0�롱
			IR_Value|=0x80;			//ͨ����λ�������λ��1
		if(j<7)						    //������û��ƴ����8��
			IR_Value>>=1;			  //ͨ���������㡰�ڳ���λ��׼����һλ�ж�
		k++;						      //�±��������
	}
	
	return IR_Value;				//���غ�����յ�����
}

//********************************************************
//������
//********************************************************
void main(void)                   // ������
{                                            
    
	Sys_Init();                   // ϵͳ��ʼ��
		
	while(1)
	{	
	
		if(IR_Flag)				//�������ݽ������
		{
			IR_Flag=0; 
			IR_count =0;
			IR_data_deal_flag=1;
		    IRdata[IRdata_len++] = IR_decode();
		    if(IRdata_len >= IR_DATA_BUFFER_SIZE)	
          		IRdata_len=0;				
		}
		else
		{
			//250ms ��������
			if(IR_count > 1 && IR_data_deal_flag)	//250ms 
			{		
        		IR_data_deal_flag=0;
				
				#ifdef UART_ENABLE
				for(num=0;num<IRdata_len ;num++)
			    TX1_write2buff(IRdata[num]);
				#endif
				
				IR_Data_deal();
			}
		}
		if(touch_check())  //�������
		{
			 sysFunFlag = 1;
		}
		touch_deal();
	
	}

		#if 0
        while(1)                      // ��ѭ������
        {   WDTR=0x5A;                // ���Ź�
        if(Cancel_bz)
                {   FP54=0;               // �ػ�ţ
                        FP13=1;               // ��LED
                    FP12=1;               // ��LED            
                }
                else
                {   TimeDeal();           //                    
                    AdccDeal();           // ��λ������                       
                    //KeyeDeal();           // ��������
                        FP54=1;               // ����ţ
                }                              //
        }                             //
		#endif
}                                 //

//********************************************************
//�жϴ���                                       
//********************************************************
void __interrupt[0x8] ISR(void)   // 1024us
{   
    static u8 isRec=0;   
	  
    //INT0�жϴ���
	if(FP00IRQ)
	{             //P00 interrput//P0.0 �ⲿ�ж�(INT0)

			if(edgeFlag) //�����ж�
			{     //�ߵ�ƽ�ﵽ9msΪ��ʼ λ
				  PEDGE = 0x08;               //������ʽΪ���ش���
				  edgeFlag = 0; 
				  if(IR_time>60)	//�ж�������(9ms+1.12ms)��0.56ms+1.12ms��
				  {
						IR_data[0]=IR_time;		//�洢��Ӧλʱ���� 
					    IR_bit=1;						  //λ����������
						isRec = 1;
				   }
				   IR_time =0;  //����ʱ���ȼ���ֵ
			}
			else
			{   //�����ж�
				PEDGE = 0x10;  //������ʽΪ�½��ش���
				edgeFlag = 1;

				if(isRec)
				{
					IR_data[IR_bit]=IR_time;		//�洢��Ӧλʱ����
					IR_time=0;						//����ʱ���ȼ���ֵ
					IR_bit++;						  //λ����������
					if(IR_bit==9)				  //����ﵽ��9λ��������+8������λ��
					{
						IR_Flag=1;				  //�������ݽ�����ɱ�־λ��1
						IR_bit=0;					  //λ����������
						isRec =0;
					}
				}
			}   
	        FP00IRQ  = 0;               //����жϱ�־
	        FP00IEN  = 1;               //P0.0 �ⲿ�ж�(INT0)ʹ��
	}
	else if(FT0IRQ)   //��ʱ��T0�ж� 139us�ж�һ��
	{
		if(IR_time < 0xf0)IR_time++;
	        Touch_time++;
        
		T0M=0x70;                   // 16M/16/2= 2uS   Fcpu��2��Ƶ  
        T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 ÿ139us�ж�һ��      
		FT0IRQ=0;                   // T0 �ж������־���㡣
		FT0IEN=1;                   //������Ӧ T0 �жϡ�
        FT0ENB=1;                   //������ʱ��T0���� 
	
	}
	#if 0
    //4MS----------------------------------------
    else if(FTC0IRQ)                   // TC0 interrput
    {        FTC0IRQ=0;                // Clr  flag
        
            JS1++;                    // ����ⲻ���ߵ�ƽ��ʱ>250,�͹ػ�  
                TimerCnt++;               //
                if(TimerCnt > 249)        //
                {   TimerCnt=0;           // 1s
                    WorkBuff++;           //                        
                }                 
        //---END-----------------------------------------        
    }                             //
	#endif
}                                 //

//********************************************************
// ---------end------------------------------------------
//********************************************************