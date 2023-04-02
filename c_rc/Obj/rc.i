#line 1 ".\Src\rc.c"
#line 1 "C:\Sonix\SN8_C_~1.297\C\include\SonixDef.h"



unsigned long GetRollingCode(unsigned int offset);








struct _intrinsicbitfield
{
	unsigned bit0:1;
	unsigned bit1:1;
	unsigned bit2:1;
	unsigned bit3:1;
	unsigned bit4:1;
	unsigned bit5:1;
	unsigned bit6:1;
	unsigned bit7:1;
};













#line 1 ".\Src\rc.c"



























#line 1 "C:\Sonix\SN8_C_~1.297\C\include\SN8P2501B.h"



void _ClearWatchDogTimer(void);
void _ClrRAM(void);



sfr	R = 0x82;
sfr	Z = 0x83;
sfr	Y = 0x84;
sfr	PFLAG = 0x86;
sbit	FZ = 0x86:0;
sbit	FDC = 0x86:1;
sbit	FC = 0x86:2;
sbit	FLVD24 = 0x86:4;
sbit	FLVD36 = 0x86:5;
sbit	FNPD = 0x86:6;
sbit	FNT0 = 0x86:7;
sfr	P0M = 0xb8;
sbit	FP00M = 0xb8:0;
sfr	PEDGE = 0xbf;
sbit	FP00G1 = 0xbf:4;
sbit	FP00G0 = 0xbf:3;
sfr	P1W = 0xc0;
sfr	P1M = 0xc1;
sbit	FP10M = 0xc1:0;
sbit	FP12M = 0xc1:2;
sbit	FP13M = 0xc1:3;
sfr	P2M = 0xc2;
sbit	FP20M = 0xc2:0;
sbit	FP21M = 0xc2:1;
sbit	FP22M = 0xc2:2;
sbit	FP23M = 0xc2:3;
sbit	FP24M = 0xc2:4;
sbit	FP25M = 0xc2:5;
sfr	P5M = 0xc5;
sbit	FP54M = 0xc5:4;
sfr	INTRQ = 0xc8;
sbit	FP00IRQ = 0xc8:0;
sbit	FT0IRQ = 0xc8:4;
sbit	FTC0IRQ = 0xc8:5;
sfr	INTEN = 0xc9;
sbit	FP00IEN = 0xc9:0;
sbit	FT0IEN = 0xc9:4;
sbit	FTC0IEN = 0xc9:5;
sfr	OSCM = 0xca;
sbit	FCPUM1 = 0xca:4;
sbit	FCPUM0 = 0xca:3;
sbit	FCLKMD = 0xca:2;
sbit	FSTPHX = 0xca:1;
sfr	WDTR = 0xcc;
sfr	TC0R = 0xcd;
sfr	PCL = 0xce;
sfr	PCH = 0xcf;
sfr	P0 = 0xd0;
sbit	FP00 = 0xd0:0;
sfr	P1 = 0xd1;
sbit	FP10 = 0xd1:0;
sbit	FP11 = 0xd1:1;
sbit	FP12 = 0xd1:2;
sbit	FP13 = 0xd1:3;
sfr	P2 = 0xd2;
sbit	FP20 = 0xd2:0;
sbit	FP21 = 0xd2:1;
sbit	FP22 = 0xd2:2;
sbit	FP23 = 0xd2:3;
sbit	FP24 = 0xd2:4;
sbit	FP25 = 0xd2:5;
sfr	P5 = 0xd5;
sbit	FP54 = 0xd5:4;
sfr	T0M = 0xd8;
sbit	FT0TB = 0xd8:0;
sbit	FT0RATE0 = 0xd8:4;
sbit	FT0RATE1 = 0xd8:5;
sbit	FT0RATE2 = 0xd8:6;
sbit	FT0ENB = 0xd8:7;
sfr	T0C = 0xd9;
sfr	TC0M = 0xda;
sbit	FTC0ENB = 0xda:7;
sbit	FTC0RATE2 = 0xda:6;
sbit	FTC0RATE1 = 0xda:5;
sbit	FTC0RATE0 = 0xda:4;
sbit	FTC0CKS = 0xda:3;
sbit	FALOAD0 = 0xda:2;
sbit	FTC0OUT = 0xda:1;
sbit	FPWM0OUT = 0xda:0;
sfr	TC0C = 0xdb;
sfr	STKP = 0xdf;
sbit	FGIE = 0xdf:7;
sbit	FSTKPB1 = 0xdf:1;
sbit	FSTKPB0 = 0xdf:0;
sfr	P0UR = 0xe0;
sbit	FP00R = 0xe0:0;
sfr	P1UR = 0xe1;
sbit	FP10R = 0xe1:0;
sbit	FP12R = 0xe1:2;
sbit	FP13R = 0xe1:3;
sfr	P2UR = 0xe2;
sbit	FP20R = 0xe2:0;
sbit	FP21R = 0xe2:1;
sbit	FP22R = 0xe2:2;
sbit	FP23R = 0xe2:3;
sbit	FP24R = 0xe2:4;
sbit	FP25R = 0xe2:5;
sfr	P5UR = 0xe5;
sbit	FP54R = 0xe5:4;
sfr	_YZ = 0xe7;
sfr	P1OC = 0xe9;
sfr	STK3L = 0xf8;
sfr	STK3H = 0xf9;
sfr	STK2L = 0xfa;
sfr	STK2H = 0xfb;
sfr	STK1L = 0xfc;
sfr	STK1H = 0xfd;
sfr	STK0L = 0xfe;
sfr	STK0H = 0xff;





#line 29 ".\Src\rc.c"
#line 1 ".\Include\global.h"














#line 30 ".\Src\rc.c"





#pragma data_address 0x2f
 unsigned char    SDian_Cnt;
#pragma data_address 0x2e
bit      SDian_bz;

 unsigned char    TimerCnt;
 unsigned int    Worktime;
 unsigned int    WorkBuff;
 unsigned char    WorkGear;

 unsigned char   Funflag0;
 unsigned char   Funflag1;
sbit      Time1s_bz = Funflag0:0;

 unsigned char    JS1;
 unsigned char    AD_Cnt;
 unsigned char    AD_value;
 unsigned int    RT_Cnt;
 unsigned int    RS_Cnt;


sbit      ChongDian1_bz = Funflag0:1;
sbit      ChongDian2_bz = Funflag0:2;
sbit      ChongDian3_bz = Funflag0:3;
sbit      ChongDian4_bz = Funflag0:4;


sbit      Defrost_bz = Funflag1:0;
sbit      Reheat_bz = Funflag1:1;
sbit      Cancel_bz = Funflag1:2;

sbit      Bagle_bz = Funflag0:5;
sbit      Key_bz = Funflag0:6;






sbit      ZiJian_bz = Funflag0:7;




void Sys_Init(void);
void AdccDeal(void);
void KeyeDeal(void);
void Defrost(void);
void Reheat(void);
void Bagle(void);
void Cancel(void);

void ZhiJDeal(void);
void DataDeal(void);
void TimeDeal(void);
void Delayms(unsigned char k);



void Sys_Init(void)
{
        OSCM = 0x00;
        INTEN= 0x00;
        INTRQ= 0x00;


        P0M  = 0xFF;
        P2M  = 0xFF;
        P1M  = 0xF1;
        P5M  = 0xFF;

        P0UR = 0x00;
        P2UR = 0x00;
        P1UR = 0x0C;
        P5UR = 0x00;

        FP12=1;
        FP13=1;
        FP54=1;

    T0M=0x10;
        T0C=0;
        FT0IEN=1;

    TC0M=0x40;
    TC0R=6;
        TC0C=6;
        FALOAD0=1;
    FTC0IEN=1;
         FTC0ENB=1;

    FGIE = 1;

        ZhiJDeal();
        Worktime=100;
        WorkBuff=0;

        if(SDian_Cnt==2)
        {   if(SDian_bz) SDian_Cnt=2;
            else SDian_Cnt=1;
        }
        else if(SDian_Cnt==3)
        {   if(SDian_bz) SDian_Cnt=3;
            else SDian_Cnt=1;
        }
        else if(SDian_Cnt==4)
        {   if(SDian_bz) SDian_Cnt=4;
            else SDian_Cnt=1;
        }
    else
   {    SDian_Cnt=1;
                SDian_bz=1;
        }
}




void Delayms(unsigned char k)
{unsigned char x,y;
    for(x=0;x<k;x++)
        {  for(y=100;y>0;y--);}
}



void TimeDeal(void)
{
        if(WorkBuff>=40)
        {   if(Reheat_bz) Cancel_bz=1;
        }

    if(WorkBuff>=Worktime)
        {   SDian_Cnt++;
                if(SDian_Cnt>=4) SDian_Cnt=4;
        Cancel_bz=1;
        }

}




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




void KeyeDeal(void)
{

    if(Bagle_bz|Defrost_bz)
        {














        }
        else
        {














        }






#line 250 ".\Src\rc.c"
}




#line 264 ".\Src\rc.c"

#line 292 ".\Src\rc.c"



void AdccDeal(void)
{   if(Reheat_bz)return;

    if( !ChongDian1_bz )
        {    ChongDian1_bz=1;
             FP00M=0;
                 FP10M=1;
                 FP10=0;
                 Delayms(2);
        }
        else if( !ChongDian2_bz )
        {
             T0C=0;
         FP10M=0;
                 FP00M=1;
                 FP00=1;
         FT0ENB=1;
 __asm{ _NOP 1 };
 __asm{ _NOP 1 };
                 while(1)
                 {    WDTR=0x5A;
                      if(JS1>20)break;
                          if( FP10 )break;
                 }
                 FT0ENB=0;
         RS_Cnt+=T0C;
                 T0C=0;
                 JS1=0;
         FP00M=0;
                 FP10M=1;
                 FP10=0;
                 ChongDian2_bz=1;
        }
        else if( !ChongDian3_bz )
        {    ChongDian3_bz=1;
         FP00M=0;
                 FP10M=1;
                 FP10=0;
                 Delayms(2);
        }
        else if( !ChongDian4_bz )
        {
             T0C=0;
         FP10M=0;
                 FP00M=0;
         FT0ENB=1;
 __asm{ _NOP 1 };
 __asm{ _NOP 1 };
                 while(1)
                 {    WDTR=0x5A;
                      if(JS1>20)break;
                          if( FP10 )break;
                 }

                 FT0ENB=0;
                 RT_Cnt+=T0C;
                 JS1=0;
                 T0C=0;
         FP00M=0;
                 FP10M=1;
                 FP10=0;
                 ChongDian4_bz=1;

        }
    else
        {   AD_Cnt++;
            if(AD_Cnt==8)
        {   AD_Cnt=0;
                    RT_Cnt>>=3;
                        RS_Cnt>>=3;


                AD_value=(RS_Cnt*230)/RT_Cnt;



             if(AD_value>=227)
                        {   WorkGear=1;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else if(AD_value>=206 )
                        {   WorkGear=2;
                            if(ZiJian_bz){FP13=1;FP12=0;}
                        }
                        else if(AD_value>=173 )
                        {   WorkGear=3;
                            if(ZiJian_bz){FP13=0;FP12=0;}
                        }
                        else if(AD_value>=155 )
                        {   WorkGear=4;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else if(AD_value>=125 )
                        {   WorkGear=5;
                            if(ZiJian_bz){FP13=1;FP12=0;}
                        }
                        else if(AD_value>=103)
                        {   WorkGear=6;
                            if(ZiJian_bz){FP13=0;FP12=0;}
                        }
                        else if(AD_value>=75)
                        {   WorkGear=7;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else if(AD_value>=56 )
                        {   WorkGear=8;
                            if(ZiJian_bz){FP13=1;FP12=0;}
                        }
                        else if(AD_value>=22 )
                        {   WorkGear=9;
                            if(ZiJian_bz){FP13=0;FP12=0;}
                        }
                        else if(AD_value>=5 )
                        {   WorkGear=10;
                            if(ZiJian_bz){FP13=1;FP12=1;}
                        }
                        else
                        {   if(AD_value<5)
                                {   WorkGear=11;
                                    if(ZiJian_bz){FP13=1;FP12=0;}
                                }
                        }

                }
                ChongDian1_bz=0;
                ChongDian2_bz=0;
                ChongDian3_bz=0;
                ChongDian4_bz=0;
        }
}




void main(void)
{
        Sys_Init();
        while(1)
        {   WDTR=0x5A;
        if(Cancel_bz)
                {   FP54=0;
                        FP13=1;
                    FP12=1;
                }
                else
                {   TimeDeal();
                    AdccDeal();

                        FP54=1;
                }
        }
}




void __interrupt[0x8] ISR(void)
{


        if(FTC0IRQ)
    {        FTC0IRQ=0;

            JS1++;
                TimerCnt++;
                if(TimerCnt > 249)
                {   TimerCnt=0;
                    WorkBuff++;
                }

    }
}





