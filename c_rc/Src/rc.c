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
//========================================================
//�޸�����: 2016.X.X
//�޸�����:
//========================================================
//********************************************************
//========================================================
#include <SN8P2501B.h>          // ͷ�ļ�
#include "global.h"             //

//========================================================
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
sbit      Time1s_bz = Funflag0:0;             //
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

//uchar    KeyCnt1;               //
//uchar    KeyCnt2;               //               
//uchar    KeyCnt3;               //

//***** <�Լ�> *******************************************
sbit      ZiJian_bz = Funflag0:7;             //  

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
        //--- T0  Config--------------------------------------
    T0M=0x10;                   // 1M/16/63=500uS
        T0C=0;                      //
        FT0IEN=1;                   //
        //--- TC0 Config--------------------------------------
    TC0M=0x40;                  // 16MHz/16=  Fcpu/4/125
    TC0R=6;                     //
        TC0C=6;                     //  
        FALOAD0=1;                  //   
    FTC0IEN=1;                  // Enable TC0 Interrput
         FTC0ENB=1;                  // ��ʱ������
    //----Start Run---------------------------------------
    FGIE = 1;                   // Enable all Interrput
        //----------------------------------------------------
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
}

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
    //----------------------------------------------------
    if(Bagle_bz|Defrost_bz)                    //
        {  
	   	#if 0 
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
			#endif                      
        }
        else
        {     
		    #if 0 
			 if(SDian_Cnt==1)
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
				#endif
        }
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

//********************************************************
//������
//********************************************************
void main(void)                   // ������
{                                            
        Sys_Init();                   // ϵͳ��ʼ��
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
}                                 //

//********************************************************
//�жϴ���                                       
//********************************************************
void __interrupt[0x8] ISR(void)   // 1024us
{      

        //4MS----------------------------------------
        if(FTC0IRQ)                   // TC0 interrput
    {        FTC0IRQ=0;                // Clr  flag
        
            JS1++;                    // ����ⲻ���ߵ�ƽ��ʱ>250,�͹ػ�  
                TimerCnt++;               //
                if(TimerCnt > 249)        //
                {   TimerCnt=0;           // 1s
                    WorkBuff++;           //                        
                }                 
        //---END-----------------------------------------        
    }                             //
}                                 //

//********************************************************
// ---------end------------------------------------------
//********************************************************

