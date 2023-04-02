#line 1 ".\Src\u_board.c"
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













#line 1 ".\Src\u_board.c"























#line 1 "C:\Sonix\SN8_C_~1.297\C\include\SN8P2501D.h"



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





#line 25 ".\Src\u_board.c"
#line 1 ".\Src\global.h"














#line 26 ".\Src\u_board.c"























 unsigned char  sysFlag;
 unsigned char  sysFlag1;

sbit IR_Flag        =  sysFlag:0;
sbit Touch_flag     =  sysFlag:1;
sbit touch_preFlag  =  sysFlag:2;
sbit timeFunFlag    =  sysFlag:3;
sbit sysFunFlag     =  sysFlag:4;
sbit isRec          =  sysFlag:5;
sbit buzzerFlag     =  sysFlag:6;
sbit buzzerEnableFlag= sysFlag:7;

sbit edgeFlag       = sysFlag1:0;



 unsigned char IR_time=0;

 unsigned char IR_data;

 unsigned short Touch_time;

 unsigned char IR_bit;
 unsigned char btn_value=0;

 unsigned char IR_count = 0;


 unsigned char IRdata;





static void rdelay_acton_fun(unsigned char action_value);
static void touch_check(void);







void Sys_Init(void)
{
        OSCM = 0x00;
        INTEN= 0x00;
        INTRQ= 0x00;


        P0M  = 0xFE;
        P2M  = 0xEF;

        P1M  = 0xFB;
        P5M  = 0xFF;

        P0UR = 0x01;
        P2UR = 0x00;
        P1UR = 0x00;
        P5UR = 0x00;

 FP13=0;
 FP12=0;
 FP24=0;
 FP10=1;
 FP54=1;


        PEDGE = 0x10;

		FP00IRQ  = 0;
        FP00IEN  = 1;
        edgeFlag = 1;


        T0M=0x70;

        T0C=186;
		FT0IRQ=0;
		FT0IEN=1;
        FT0ENB=1;

        TC0M=0x70;
        TC0R=131;
        TC0C=131;
        FALOAD0=1;
		FTC0OUT=0;
		FPWM0OUT = 0;
        FTC0IEN=1;
        FTC0ENB=1;

        FGIE = 1;
}



static void touch_check(void)
{

    if(FP23 == 0)
    {
			   if(Touch_flag==1)
					 Touch_time = 0;
               else if(Touch_time > 500)
			   {
					  Touch_time = 0;
				      Touch_flag = 1;
					  sysFunFlag = 1;
			   }
      }
	  else
	  {
				if(Touch_flag==1)
				{
						if(Touch_time > 2000)
						{
							 Touch_time=0;
							 Touch_flag = 0;

						}
				}
				else Touch_time=0;

		}

}

static void touch_deal(void)
{
	 if(Touch_flag)
	 {
			if(!touch_preFlag)
			{
					touch_preFlag = 1;
				    btn_value++;

					if(btn_value >= 4)
							btn_value = 1;
				    rdelay_acton_fun(btn_value);
			}
	 }
	 else
	 {
			touch_preFlag = 0;
	 }
}





static void rdelay_acton_fun(unsigned char action_value)
{

      if(action_value == 0)
	  {
 FP13=0;
 FP12=0;
	  }
	  else if(action_value == 1)
	  {
 FP13=1;
 FP12=0;
	  }
	  else if(action_value == 2)
	  {
 FP13=0;
 FP12=1;
	  }
	  else if(action_value == 3)
	  {
 FP13=1;
 FP12=1;
	  }
}





void main(void)
{
 unsigned char  val;
	Sys_Init();

	while(1)
	{

		if(IR_Flag && IR_count > 230)
		{
			IR_Flag=0;
			IR_count =0;

			val = IRdata & 0x0f;
            IRdata = IRdata >> 4;

			if(val > IRdata)
			{


				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= 4)
						 btn_value = 1;
                     rdelay_acton_fun(btn_value);
				}
			}
		    else if(val < IRdata)
			{

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
		    }

		}

        touch_check();
	    touch_deal();

	}

}





void __interrupt[0x8] ISR(void)
{
    static unsigned short buzzerCount=0;


	if(FP00IRQ)
	{

			if(edgeFlag)
			{
				  PEDGE = 0x08;
				  edgeFlag = 0;
				  if(IR_time>60)
				  {

						IR_data = 0;
					    IR_bit=1;
						isRec = 1;
				   }
				   IR_time =0;
			}
			else
			{
				PEDGE = 0x10;
				edgeFlag = 1;

				if(isRec)
				{

				    if(IR_time>5)
			            IR_data|=0x80;

					IR_time=0;
					IR_bit++;
					if(IR_bit==9)
					{
						IR_Flag=1;
						IR_bit=0;
						isRec =0;
                        if(IR_data == 0xBB)
						   IRdata += 1;
                        else  if(IR_data == 0x1B)
                           IRdata += 0x10;

					}
					else
					    IR_data>>=1;
				}
			}
			IR_count=0;
	        FP00IRQ  = 0;
	        FP00IEN  = 1;
	}
	else if(FT0IRQ)
	{
		if(IR_time < 0xf0)IR_time++;
	        Touch_time++;
        if(IR_Flag)
			IR_count++;

		T0M=0x70;
        T0C=186;
		FT0IRQ=0;
		FT0IEN=1;
        FT0ENB=1;

	}


    else if(FTC0IRQ)
    {
	      FTC0IRQ=0;
          if(buzzerEnableFlag == 0)
		  {
 FP54=1;
              return;
		  }
		  if(buzzerCount++ > 3000)
		  {
		      buzzerEnableFlag = 0;
		      buzzerCount = 0;
 FP54=1;
		  }
		  else
		  {
		       if(buzzerFlag)
			   {
			       buzzerFlag = 0;
 FP54=1;
			   }
		        else
				{
			       buzzerFlag = 1;
 FP54=0;
			   }
		  }

    }

}









































































