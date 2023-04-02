

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
#include <SN8P2501D.h>          // 头文件
#include "global.h"             //

#define   IR_ONOFF_BUTTON     0x1B    //红外摇控板开关键值
#define   IR_LIGHT_BUTTON     0xBB    //红外摇控板加热丝档位调整键值

#define   DELAY1_OFF     FP13=0    
#define   DELAY2_OFF     FP12=0 
#define   DELAY1_ON      FP13=1
#define   DELAY2_ON      FP12=1 
#define   TOUCH_PIN      FP23
#define   BUZZER_OFF     FP54=1
#define   BUZZER_ON      FP54=0

#define   BUTTON_VALUE_MAX   4    //最大档位, 其实只有3档
#define   IR_DATA_BUFFER_SIZE  5

#define  R_POWER_LED_ON      FP24=0
#define  B_BTOUCH_LED_ON     FP10=0
#define  B_BTOUCH_LED_OFF    FP10=1
//********************************************************
//#pragma 上电不清0
//********************************************************

//数据定义
u8  sysFlag;
u8  sysFlag1;

sbit IR_Flag        =  sysFlag:0;		//红外数据接收完成标志位
sbit Touch_flag     =  sysFlag:1;       //触摸IC输出标志
sbit touch_preFlag  =  sysFlag:2;       //上次触摸IC输出标志
sbit timeFunFlag    =  sysFlag:3;       //定时功能标志
sbit sysFunFlag     =  sysFlag:4;       //系统功能标志
sbit isRec          =  sysFlag:5;
sbit buzzerFlag     =  sysFlag:6;
sbit buzzerEnableFlag= sysFlag:7;

sbit edgeFlag       = sysFlag1:0;   //红外管接收脚边沿标识
//sbit IR_data_deal_flag=sysFlag:1;   //红外管接收到数据待处理标志


u8 IR_time=0;		//下降沿之间的时间计数值
//u8 IR_data[9];		//引导码+8个位数据各自占用的时间
u8 IR_data;

u16 Touch_time;     //触摸计时器

u8 IR_bit;		//变量IR_bit用于指示红外数据的位数
u8 btn_value=0; //红外按键键值寄存器

u8 IR_count = 0;    //红外管接收到数据后延时计数器--250ms
//u8 IRdata_len = 0; //红外管接收到数据长度
//u8 IRdata[IR_DATA_BUFFER_SIZE];
u8 IRdata;


//函数声明
//static u8 IR_decode(void);			//红外解码函数
//static void IR_Data_deal(void);
static void rdelay_acton_fun(u8 action_value);
static void touch_check(void);    //触摸检测
//static void touch_deal(void);    //触摸处理



//********************************************************
//系统初始化
//********************************************************
void Sys_Init(void)             //
{               
        OSCM = 0x00;                // 普通模式(双时钟)         
        INTEN= 0x00;                //
        INTRQ= 0x00;                //

        //--- I0 Config --------------------------------------
        P0M  = 0xFE;                // P00输入  0=输入   1=输出
        P2M  = 0xEF;                // P2.3输入 P2.4输出驱动LED红色电源指示灯 P2.1输出驱动8个LED灯 高电平有效

        P1M  = 0xFB;                // P1.0输出驱动LED 蓝色触摸灯    P1.3P1.2输出驱动两组继电器
        P5M  = 0xFF;                // P5.4输出 蜂鸣器输出保持高电平
        
        P0UR = 0x01;                // 0=不上拉 1=上拉 P0.0拉
        P2UR = 0x00;                //
        P1UR = 0x00;                // 0x0C
        P5UR = 0x00;                //

        DELAY1_OFF;   
        DELAY2_OFF; 
	    R_POWER_LED_ON;
        B_BTOUCH_LED_OFF;
        BUZZER_OFF;
     
        //--- P00 Config-------------------------------------
        PEDGE = 0x10;               //下降沿触发中断
        //PEDGE = 0x08;               //上升沿触发中断
		FP00IRQ  = 0;               //清除中断标志
        FP00IEN  = 1;               //P0.0 外部中断(INT0)使能
        edgeFlag = 1;
        //--- T0  Config--定时器T0配置------------------------------------
		//FT0TB = 0;                  //禁止 RTC
        T0M=0x70;                   // 16M/16/2= 2uS   Fcpu的2分频 
        //T0M=0x10;                   // 1M/16/128=500uS   Fcpu的128分频
        T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 每139us中断一次      
		FT0IRQ=0;                   // T0 中断请求标志清零。
		FT0IEN=1;                   //允许响应 T0 中断。
        FT0ENB=1;                   //启动定时器T0运行 
        //--- TC0 PWM Config  蜂鸣器驱动 2K频率-高电平和低电平的时间宽度都为 250μs--------------------------------------
        TC0M=0x70;                  // 16MHz/16=  Fcpu/2   2us  256-250/2=
        TC0R=131;                   //每隔125*2 =250us中断一次
        TC0C=131;                   //  
        FALOAD0=1;                  //使能 TC0 自动装载
		FTC0OUT=0;                  //允许P5.4口作PWM输出
		FPWM0OUT = 0;               //允许PWM/BUZZER功能  
        FTC0IEN=1;                  //允许中断Enable TC0 Interrput
        FTC0ENB=1;                  // 定时器开启
        //----Start Run---------------------------------------
        FGIE = 1;                   // Enable all Interrput
}


/*************触摸功能*********************/
static void touch_check(void)
{   //触摸输出检测   无触摸时高电平，有触摸时低电平时长大于300ms
  
    if(TOUCH_PIN == 0)
    {
			   if(Touch_flag==1) 
					 Touch_time = 0;
               else if(Touch_time > 500)  //139微秒 *500 = 69.5ms
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
						if(Touch_time > 2000)  //139微秒 *2000 = 279.5ms
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





static void rdelay_acton_fun(u8 action_value)
{

      if(action_value == 0)
	  {     // 断开所有继电器
	            DELAY1_OFF; 
				DELAY2_OFF;  
	  }      
	  else if(action_value == 1)
	  {    
	            DELAY1_ON; 
				DELAY2_OFF;  
	  }
	  else if(action_value == 2)
	  {    
	            DELAY1_OFF; 
				DELAY2_ON;  
	  }
	  else if(action_value == 3)
	  {    
	            DELAY1_ON; 
				DELAY2_ON;  
	  }
}


//********************************************************
//主程序
//********************************************************
void main(void)                   // 主程序
{                                            
    u8  val;
	Sys_Init();                   // 系统初始化
		
	while(1)
	{	
   	   
		if(IR_Flag && IR_count > 230)	//红外数据接收完成后 230*139 = 31970us处理数据
		{
			IR_Flag=0; 
			IR_count =0;
		
			val = IRdata & 0x0f;
            IRdata = IRdata >> 4;

			if(val > IRdata)
			{
				//IR_LIGHT_BUTTON 
				//灯档位调节键
				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= BUTTON_VALUE_MAX)
						 btn_value = 1;
                     rdelay_acton_fun(btn_value);
				}
			}
		    else if(val < IRdata)
			{   //电源开关键
			    //IR_ONOFF_BUTTON
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

        touch_check();//触摸检测
	    touch_deal();
    
	}

}                  


//********************************************************
//中断处理                                       
//********************************************************
void __interrupt[0x8] ISR(void)   // 
{   
    static u16 buzzerCount=0;   
#if 1	  
    //INT0中断处理
	if(FP00IRQ)
	{             //P00 interrput//P0.0 外部中断(INT0)

			if(edgeFlag) //下沿中断
			{     //高电平达到9ms为开始 位
				  PEDGE = 0x08;               //触发方式为上沿触发
				  edgeFlag = 0; 
				  if(IR_time>60)	//判断引导码(9ms+1.12ms)（0.56ms+1.12ms）
				  {
						//IR_data[0]=IR_time;		//存储相应位时间宽度 
						IR_data = 0;
					    IR_bit=1;						  //位数变量自增
						isRec = 1;
				   }
				   IR_time =0;  //清零时间宽度计数值
			}
			else
			{   //上沿中断
				PEDGE = 0x10;  //触发方式为下降沿触发
				edgeFlag = 1;

				if(isRec)
				{
					//IR_data[IR_bit]=IR_time;		//存储相应位时间宽度
				    if(IR_time>5)			//若“时间间隔”比5大那肯定是“1码”反之为“0码”
			            IR_data|=0x80;			//通过按位或运算高位填1
		            					    //若数据没有拼合完8次
					IR_time=0;						//清零时间宽度计数值
					IR_bit++;						  //位数变量自增
					if(IR_bit==9)				  //如果达到了9位（引导码+8个数据位）
					{
						IR_Flag=1;				  //红外数据接收完成标志位置1
						IR_bit=0;					  //位数变量清零
						isRec =0;
                        if(IR_data == IR_LIGHT_BUTTON)
						   IRdata += 1;
                        else  if(IR_data == IR_ONOFF_BUTTON)
                           IRdata += 0x10;
						    
					}
					else
					    IR_data>>=1;			  //通过右移运算“腾出”位置准备下一位判定
				}
			}
			IR_count=0;                 //有接收数据则清零延时计数器   
	        FP00IRQ  = 0;               //清除中断标志
	        FP00IEN  = 1;               //P0.0 外部中断(INT0)使能
	}
	else if(FT0IRQ)   //定时器T0中断 139us中断一次
	{
		if(IR_time < 0xf0)IR_time++;
	        Touch_time++;
        if(IR_Flag)				//接收到红外数据
			IR_count++;

		T0M=0x70;                   // 16M/16/2= 2uS   Fcpu的2分频  
        T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 每139us中断一次      
		FT0IRQ=0;                   // T0 中断请求标志清零。
		FT0IEN=1;                   //允许响应 T0 中断。
        FT0ENB=1;                   //启动定时器T0运行 
	
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
#endif 	   
}                                 //

//********************************************************
// ---------end------------------------------------------
//********************************************************	
#if 0
//-------------------------红外接收解码-------------------------
static u8 IR_decode(void)
{
	u8 j,k;								
	u8 IR_Value = 0; 
	k=1;							//先让变量k等于1，因为k为0时取出的将会是“引导码的时间间隔”
 
	for(j=0;j<=7;j++)				//内层循环8次为了拼合8个数据位为1个字节
	{
		if(IR_data[k]>5)			//若“时间间隔”比5大那肯定是“1码”反之为“0码”
			IR_Value|=0x80;			//通过按位或运算高位填1
		if(j<7)						    //若数据没有拼合完8次
			IR_Value>>=1;			  //通过右移运算“腾出”位置准备下一位判定
		k++;						      //下标变量自增
	}
	
	return IR_Value;				//返回红外接收的数据
}

//-------------------红外接收数据处理-------------------------------
static void IR_Data_deal(void)
{
	u8 dat,light=0,onoff=0;

	for(dat=0;dat<IRdata_len;dat++) 
	{
			if(IRdata[dat]==IR_LIGHT_BUTTON)
				 light++;
			else  if(IRdata[dat]==IR_ONOFF_BUTTON)
				 onoff++;
	}
	for(dat=0;dat<IR_DATA_BUFFER_SIZE;dat++)
	   IRdata[dat] = 0;
	IRdata_len = 0;

	if(light > IRdata_len/2)
		 dat = IR_LIGHT_BUTTON;
	else if(onoff > IRdata_len/2)
		 dat = IR_ONOFF_BUTTON;
	
	if(dat == IR_LIGHT_BUTTON)
	{     //灯档位调节键
				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= BUTTON_VALUE_MAX)
						 btn_value = 1;
				}
	}
	if(dat == IR_ONOFF_BUTTON)  //电源开关键
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
	
    rdelay_acton_fun(btn_value);

}

#endif
