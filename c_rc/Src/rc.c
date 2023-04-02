//SN8P2501BP单片机RC充放电源代码（希望能各位新手有所帮助）
//电路原理图详见:http://www.51hei.com/bbs/dpj-212635-1.html
//********************************************************
//晶振  RC: 内部16MHz          当前版本: V0
//目标 MCU: SN8P2501BP,SOP14   
//开发作者: SL                 烧录校验:  
//开始日期: 2016.3.16          完成日期: 2016.X.X

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
//修改日期: 2016.X.X
//修改内容:
//========================================================
//********************************************************
//========================================================
#include <SN8P2501B.h>          // 头文件
#include "global.h"             //

//========================================================
//********************************************************
//#pragma 上电不清0
//********************************************************
#pragma data_address 0x2f       //
uchar    SDian_Cnt;             //
#pragma data_address 0x2e       //
bit      SDian_bz;              //
//**** 时间变量定义 **************************************   
uchar    TimerCnt;              //                                                                                                                                 
ulong    Worktime;              //
ulong    WorkBuff;              //
uchar    WorkGear;              //  

uchar   Funflag0;
uchar   Funflag1;
sbit      Time1s_bz = Funflag0:0;             //
//**** AD变量定义 ****************************************
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

//***** <自检> *******************************************
sbit      ZiJian_bz = Funflag0:7;             //  

//********************************************************
//函数声明
//********************************************************
void Sys_Init(void);            // 系统初始化
void AdccDeal(void);            // 电位器处理
void KeyeDeal(void);            // 按键处理
void Defrost(void);             //
void Reheat(void);              // 按键保护
void Bagle(void);               //
void Cancel(void);

void ZhiJDeal(void);            //   
void DataDeal(void);            // 数据处理
void TimeDeal(void);            //
void Delayms(uchar k);          //
//********************************************************
//系统初始化
//********************************************************
void Sys_Init(void)             //
{               
        OSCM = 0x00;                // 普通模式(双时钟)         
        INTEN= 0x00;                //
        INTRQ= 0x00;                //

        //--- I0 Config --------------------------------------
        P0M  = 0xFF;                // 0=输入   1=输出
        P2M  = 0xFF;                //
        P1M  = 0xF1;                // 0xF3
        P5M  = 0xFF;                //
        
        P0UR = 0x00;                // 0=不上拉 1=上拉
        P2UR = 0x00;                //
        P1UR = 0x0C;                // 0x0C
        P5UR = 0x00;                //

        FP12=1;                     // 0=低电平 1=高电平
        FP13=1;                     // (屏蔽指示灯 打开电磁铁)
        FP54=1;                     // bit 这样写节省ROM空间
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
         FTC0ENB=1;                  // 定时器开启
    //----Start Run---------------------------------------
    FGIE = 1;                   // Enable all Interrput
        //----------------------------------------------------
        ZhiJDeal();                 //  
        Worktime=100;
        WorkBuff=0;
        //----------------------------------------------------
        if(SDian_Cnt==2)                // 掉电后重新上电处理
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
//延时处理
//********************************************************
void Delayms(uchar k)
{   uchar x,y;
    for(x=0;x<k;x++)
        {  for(y=100;y>0;y--);}//100
}
//********************************************************
//时间处理
//********************************************************
void TimeDeal(void)                            //
{   //---------------------------------------
        if(WorkBuff>=40)                       // 如果有重加热标志
        {   if(Reheat_bz) Cancel_bz=1;                   // 50S关机   
        }               
    //---------------------------------------        
    if(WorkBuff>=Worktime)                 // 时间到关机
        {   SDian_Cnt++;                       //
                if(SDian_Cnt>=4) SDian_Cnt=4;      //
        Cancel_bz=1;                               //
        }
        //---------------------------------------                                             //
}                                             

//********************************************************
//自检程序处理
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
//电位器处理
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
//按键功能处理
//********************************************************
/*void Cancel(void) //取消
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
void Reheat(void)  //重加热
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
void Defrost(void) //解冻
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
//电位器处理
//********************************************************
void AdccDeal(void)             //
{   if(Reheat_bz)return;

    if( !ChongDian1_bz )        // 第一次放电
        {    ChongDian1_bz=1;       // 端口输出
             FP00M=0;               // 设为输入FP00
                 FP10M=1;               // 设为输出
                 FP10=0;                // 输出0
                 Delayms(2);            // 要有足够时间放电
        }
        else if( !ChongDian2_bz )   //
        {     
             T0C=0;                 // 清定时器0                     
         FP10M=0;               //0 输入
                 FP00M=1;               //
                 FP00=1;                // *第一次充电               
         FT0ENB=1;              // 打开定时器
                 NOP(1);
                 NOP(1);
                 while(1)               //
                 {    WDTR=0x5A;        //
                      if(JS1>20)break;//FP54=0;                                       
                          if( FP10 )break;        // 检测充电口为高就退出                  
                 }        
                 FT0ENB=0;              // 关定时器
         RS_Cnt+=T0C;           //
                 T0C=0;                 //
                 JS1=0;
         FP00M=0;               //0
                 FP10M=1;               // 设为输出
                 FP10=0;                // 输出0放电
                 ChongDian2_bz=1;       //
        }
        else if( !ChongDian3_bz )   //  
        {    ChongDian3_bz=1;       //
         FP00M=0;               // 0
                 FP10M=1;               // 设为输出
                 FP10=0;                // 输出0放电
                 Delayms(2);            // 要有足够时间放电
        }
        else if( !ChongDian4_bz )   //
        {
             T0C=0;                 // 清定时器0                       
         FP10M=0;               //
                 FP00M=0;               // *第二次充电
         FT0ENB=1;              // 打开定时器        
                 NOP(1);
                 NOP(1);
                 while(1)               //
                 {    WDTR=0x5A;        //
                      if(JS1>20)break;//FP54=0;         
                          if( FP10 )break;  // 检测充电口为高就退出                           
                 }

                 FT0ENB=0;              // 关定时器
                 RT_Cnt+=T0C;           //
                 JS1=0;
                 T0C=0;                 //
         FP00M=0;               //0 设为输出
                 FP10M=1;               //
                 FP10=0;                //
                 ChongDian4_bz=1;       //
                 
        }
    else
        {   AD_Cnt++;               //
            if(AD_Cnt==8)         // 求128个数的平均值
        {   AD_Cnt=0;           //
                    RT_Cnt>>=3;         // RT充电时间平均值
                        RS_Cnt>>=3;         // RS标准时间平均值
                        
                        //----------------------------------------------------                                      
                AD_value=(RS_Cnt*230)/RT_Cnt;      // 放大230倍 *控制它不会超出256*
                        //-------------------------------------------
                        //11档分值[225-200-170-148-123-103-76-53-28-9] 104
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
//主程序
//********************************************************
void main(void)                   // 主程序
{                                            
        Sys_Init();                   // 系统初始化
        while(1)                      // 主循环程序
        {   WDTR=0x5A;                // 看门狗
        if(Cancel_bz)
                {   FP54=0;               // 关火牛
                        FP13=1;               // 关LED
                    FP12=1;               // 关LED            
                }
                else
                {   TimeDeal();           //                    
                    AdccDeal();           // 电位器处理                       
                    //KeyeDeal();           // 按键处理
                        FP54=1;               // 开火牛
                }                              //
        }                             //
}                                 //

//********************************************************
//中断处理                                       
//********************************************************
void __interrupt[0x8] ISR(void)   // 1024us
{      

        //4MS----------------------------------------
        if(FTC0IRQ)                   // TC0 interrput
    {        FTC0IRQ=0;                // Clr  flag
        
            JS1++;                    // 充电检测不到高电平计时>250,就关机  
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

