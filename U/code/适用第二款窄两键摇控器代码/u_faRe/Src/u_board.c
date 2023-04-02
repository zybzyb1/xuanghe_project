

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

#define   IR_ONOFF_BUTTON     0x1B    //����ҡ�ذ忪�ؼ�ֵ
#define   IR_LIGHT_BUTTON     0xBB    //����ҡ�ذ����˿��λ������ֵ

#define   DELAY1_OFF     FP13=0    
#define   DELAY2_OFF     FP12=0 
#define   DELAY1_ON      FP13=1
#define   DELAY2_ON      FP12=1 
#define   TOUCH_PIN      FP23
#define   BUZZER_OFF     FP54= 1
#define   BUZZER_ON      FP54= 0

#define   BUTTON_VALUE_MAX   4    //���λ, ��ʵֻ��3��
#define   TIMER_LENGTH_MAX   16   //��ʱ��ʱ8Сʱ������0.5Сʱ
#define   IR_DATA_BUFFER_SIZE  10

#define  R_POWER_LED_ON      FP24=0
#define  B_BTOUCH_LED_ON     FP10=0
#define  B_BTOUCH_LED_OFF    FP10=1
//********************************************************
//#pragma �ϵ粻��0
//********************************************************
#pragma data_address 0x2f       //
uchar    SDian_Cnt;             //
#pragma data_address 0x2e       //
bit      SDian_bz;              //


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

u8 secFlag=0;       //���־
u8 IR_count = 0;    //����ܽ��յ����ݺ���ʱ������--250ms
u8 IRdata_len = 0; //����ܽ��յ����ݳ���
u8 IRdata[IR_DATA_BUFFER_SIZE];

bit isRec=0;
bit buzzerFlag=0;
bit buzzerEnableFlag = 0;

//��������
static u8 IR_decode(void);			//������뺯��
static void IR_Data_deal(void);
static void rdelay_acton_fun(u8 action_value);
static  u8 touch_check(void);    //�������
static void touch_deal(void);    //��������



//********************************************************
//ϵͳ��ʼ��
//********************************************************
void Sys_Init(void)             //
{               
        OSCM = 0x00;                // ��ͨģʽ(˫ʱ��)         
        INTEN= 0x00;                //
        INTRQ= 0x00;                //

        //--- I0 Config --------------------------------------
        P0M  = 0xFE;                // P00����  0=����   1=���
        P2M  = 0xEF;                // P2.3���� P2.4�������LED��ɫ��Դָʾ�� P2.1�������8��LED�� �ߵ�ƽ��Ч

        P1M  = 0xFB;                // P1.0�������LED ��ɫ������    P1.3P1.2�����������̵���
        P5M  = 0xFF;                // P5.4��� ������������ָߵ�ƽ
        
        P0UR = 0x01;                // 0=������ 1=���� P0.0��
        P2UR = 0x00;                //
        P1UR = 0x00;                // 0x0C
        P5UR = 0x00;                //

        DELAY1_OFF;   
        DELAY2_OFF; 
	    R_POWER_LED_ON;
        B_BTOUCH_LED_OFF;
        BUZZER_OFF;
     
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
        FALOAD0=1;                  //ʹ�� TC0 �Զ�װ��
		FTC0OUT=0;                  //����P5.4����PWM���
		FPWM0OUT = 0;               //����PWM/BUZZER����  
        FTC0IEN=1;                  //�����ж�Enable TC0 Interrput
        FTC0ENB=1;                  // ��ʱ������
        //----Start Run---------------------------------------
        FGIE = 1;                   // Enable all Interrput
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
	//memset(IRdata,0,IR_DATA_BUFFER_SIZE);
    for(i=0;i<IR_DATA_BUFFER_SIZE;i++)
	   IRdata[i] = 0;
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
         //time_cnt=0;    //��Դ�����������㶨ʱ������				 
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

}                  


//********************************************************
//�жϴ���                                       
//********************************************************
void __interrupt[0x8] ISR(void)   // 
{   
    static u16 buzzerCount=0;   
	  
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
   //250uS----------------------------------------
    else if(FTC0IRQ)                   // TC0 interrput
    {        
	      FTC0IRQ=0;                // Clr  flag
          if(buzzerEnableFlag == 0)
		  {
		      BUZZER_OFF;
              return;
		  }
		  if(buzzerCount++ > 3000)
		  {
		      buzzerEnableFlag = 0;
		      buzzerCount = 0;
			  BUZZER_OFF;
		  }
		  else
		  {
		       if(buzzerFlag)
			   {
			       buzzerFlag = 0;
                   BUZZER_OFF;
			   }
		        else
				{
			       buzzerFlag = 1;
                   BUZZER_ON;
			   }
		  }
		  
    }       
}                                 //

//********************************************************
// ---------end------------------------------------------
//********************************************************	
#if 0
                         //
	#endif