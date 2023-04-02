#if  0
/*******************功能描述*******************
触摸功能

1、第一次触摸继电器1 (PCB板最边上这个继电器)接通220V电源。

2、第二次触摸继电器1 (PCB板最边上这个继电器)断开，继电器2 (PCB板中间继电器)接通220V电源。

3、第三次触摸继电器1 、摸继电器2 都接通220V电源。

4、第四次触摸又回到第一次触摸实现的功能，只有(PCB板最边上这个继电器)接通220V电源。
************************************************/

#include  "stc8g1k_code.h"		
#include  "STC8xxxx.h"	
#include  "STC8G_H_GPIO.h"
#include  "STC8G_H_ADC.h"
#include  "STC8G_H_NVIC.h"
#include  "string.h"
#include  "global.h"

#define   IR_ONOFF_BUTTON     0x1B    //红外摇控板开关键值
#define   IR_LIGHT_BUTTON     0xBB    //红外摇控板加热丝档位调整键值

#define   DELAY1_OFF     P37=0    
#define   DELAY2_OFF     P10=0 
#define   DELAY1_ON      P37=1
#define   DELAY2_ON      P10=1 
#define   TOUCH_PIN      P34

#define   BUTTON_VALUE_MAX   4    //最大档位, 其实只有3档
#define   TIMER_LENGTH_MAX   16   //这时定时8小时，步长0.5小时

#define  IR_DATA_BUFFER_SIZE  10

#ifdef    UART_ENABLE
#include  "uart.h"
#endif


 

//数据定义
bit IR_Flag=0;		//红外数据接收完成标志位
u8 IR_time=0;		//下降沿之间的时间计数值
u8 IR_data[9];		//引导码+8个位数据各自占用的时间

//bit IR_TimeFlag;            //红外发射延时到标志
//unsigned char count;        //280us

u16 Touch_time;     //触摸计时器
bit Touch_flag=0;     //触摸IC输出标志
bit touch_preFlag=0; //上次触摸IC输出标志
bit timeFunFlag;    //定时功能标志
bit sysFunFlag;     //系统功能标志

bit edgeFlag = 0;   //红外管接收脚边沿标识
bit IR_data_deal_flag=0; //红外管接收到数据待处理标志
static u8 IR_bit;		//变量IR_bit用于指示红外数据的位数
static u8 btn_value=0; //红外按键键值寄存器
u32 time_cnt=0;     //定时计数器 计数单位1s
u8 secFlag=0;       //秒标志
u8 IR_count = 0;    //红外管接收到数据后延时计数器--250ms
u8 IRdata_len = 0; //红外管接收到数据长度
u8 IRdata[IR_DATA_BUFFER_SIZE];

 
//函数声明
void delay(u16 count);		//延时函数声明
static void Timer0Init(void);		//定时计数器0初始化函数
static void Timer1Init(void);		//定时计数器1初始化函数
static void Int0_init(void);		//外部中断0初始化函数
static u8 IR_decode(void);			//红外解码函数
static void gpio_config(void);
static void IR_Data_deal(void);
static void rdelay_acton_fun(u8 action_value);
static  u8 touch_check(void);    //触摸检测
static void touch_deal(void);    //触摸处理
static u8  calculate_timer(u16 adValue);
static u8  time_unit_compare(u8 delayTime);
static void	ADC_config(void);
static void  timer_deal(void);
static void Int1_init(void);

//-------------------------主函数----------------------------
void main(void)
{
	u8 num=0;			

	gpio_config();
	EA = 1;				  //开中断

	Timer0Init();		//定时计数器0初始化函数
	Timer1Init();		//定时计数器1初始化函数
	Int1_init();		//外部中断1初始化函数  红外输出脚  //触摸IC输出脚

	delay(1000);			//等待配置稳定


	while(1)
	{	
	
		if(IR_Flag)				//红外数据接收完成
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
			//250ms 后处理数据
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
		if(touch_check())  //触摸检测
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
	
   P1_MODE_OUT_PP(GPIO_Pin_0);   //推挽输出P1.0 控制中间第二个继电器
	 P3_MODE_OUT_PP(GPIO_Pin_6 |GPIO_Pin_7);   //推挽输出P3.7 控制边上第一个继电器  //推挽输出P3.6 红外管触摸IC 小板电源控制
	
	 //P3_MODE_OUT_PP(GPIO_Pin_6);   //推挽输出P3.6 红外管触摸IC 小板电源控制
	 P3_MODE_IN_HIZ(GPIO_Pin_3 | GPIO_Pin_4);   //施密特触发使能P3.3 连接触摸IC输出脚
	 //P3_MODE_IN_HIZ(GPIO_Pin_4);   //施密特触发使能P3.4 连接红外管接收脚
	
	 DELAY1_OFF;   
   DELAY2_OFF; 
	 P36 = 0; 
}

/*************触摸功能*********************/
static  u8 touch_check(void)
{   //触摸输出检测   无触摸时高电平，有触摸时低电平时长大于300ms
    if(TOUCH_PIN == 0)
    {
			   if(Touch_flag) 
					 Touch_time = 0;
         else if(Touch_time > 500)  //139微秒 *500 = 69.5ms
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
						if(Touch_time > 2000)  //139微秒 *2000 = 279.5ms
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

//-------------------------延时函数----------------------------
void delay(u16 count)
{
	while(count--)
	{
		_nop_();
	}
}
	
//-------------------红外接收数据处理-------------------------------
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
	
	switch(dat)//红外接收正确
	{
		case  IR_LIGHT_BUTTON:   //灯档位调节键
				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= BUTTON_VALUE_MAX)
						 btn_value = 1;
				}
		break;
	  case  IR_ONOFF_BUTTON:  //电源开关键
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
         time_cnt=0;    //电源键动作则清零定时计数器				 
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
		    case 0:  // 断开所有继电器
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
//-------------------------定时器初始化----------------------------
void Timer0Init(void)		//139微秒@6.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x02;		//设置定时器模式
	TL0 = 0xBA;		//设置定时初值
	TH0 = 0xBA;		//设置定时重载值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;		//使能T0中断
}
void Timer1Init(void)		//125毫秒@6.000MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xDC;		//设置定时初值
	TH1 = 0x0B;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	
	ET1 = 1;		//使能T1中断
}

//-------------------------外部中断1初始化-------------------------
static void Int1_init(void)
{
	IT1 = 1;	//触发方式为下降沿触发
	EX1 = 1;	//使能INT1中断
	edgeFlag = 1;
}


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

void INT1_ISR() interrupt 2	 //连接红外管接收脚
{
	static u8 isRec=0; 

	if(edgeFlag) //下沿中断
	{   //高电平达到9ms为开始 位
		  IT1 = 0;	//触发方式为上沿触发
		  EX1 = 1;	//使能INT1中断
		  edgeFlag = 0; 
		  if(IR_time>60)	//判断引导码(9ms+1.12ms)（0.56ms+1.12ms）
			{
				IR_data[0]=IR_time;		//存储相应位时间宽度 
			  IR_bit=1;						  //位数变量自增
				isRec = 1;
			}
			IR_time =0;  //清零时间宽度计数值
	}
	else
	{   //上沿中断
		IT1 = 1;	//触发方式为下降沿触发
		EX1 = 1;	//使能INT1中断
		edgeFlag = 1;

		if(isRec)
		{
			IR_data[IR_bit]=IR_time;		//存储相应位时间宽度
			IR_time=0;						//清零时间宽度计数值
			IR_bit++;						  //位数变量自增
			if(IR_bit==9)				  //如果达到了9位（引导码+8个数据位）
			{
				IR_Flag=1;				  //红外数据接收完成标志位置1
				IR_bit=0;					  //位数变量清零
				isRec =0;
			}
		}
	}
}

void Time0_Handler_Callback(void) 	interrupt TIMER0_VECTOR		//进中断时已经清除标志//任务标记回调函数
{
	if(IR_time < 0xf0)IR_time++;
	Touch_time++;
}
void Time1_Handler_Callback(void)	interrupt TIMER1_VECTOR		//进中断时已经清除标志//任务标记回调函数
{
	static u8 secCount=0;
	
	if(IR_data_deal_flag)	//125ms 	
      IR_count++;
	
  
	if(++secCount >= 8)
	{
	   secCount = 0;
		 secFlag=1;
		 if(timeFunFlag)   //定时功能开启才计数
		     time_cnt++;   //8小时定时计数器 1s累加一次 
	}		
	
}

#endif

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
#include <SN8P2501B.h>          // 头文件
#include "global.h"             //

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
sbit    Time1s_bz = Funflag0:0;             //
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


//***** <自检> *******************************************
sbit      ZiJian_bz = Funflag0:7;             //  



#define   IR_ONOFF_BUTTON     0x1B    //红外摇控板开关键值
#define   IR_LIGHT_BUTTON     0xBB    //红外摇控板加热丝档位调整键值

#define   DELAY1_OFF     P37=0    
#define   DELAY2_OFF     P10=0 
#define   DELAY1_ON      P37=1
#define   DELAY2_ON      P10=1 
#define   TOUCH_PIN      P34

#define   BUTTON_VALUE_MAX   4    //最大档位, 其实只有3档
#define   TIMER_LENGTH_MAX   16   //这时定时8小时，步长0.5小时
#define  IR_DATA_BUFFER_SIZE  10
//数据定义
bit IR_Flag=0;		//红外数据接收完成标志位
u8 IR_time=0;		//下降沿之间的时间计数值
u8 IR_data[9];		//引导码+8个位数据各自占用的时间

u16 Touch_time;     //触摸计时器
bit Touch_flag=0;    //触摸IC输出标志
bit touch_preFlag=0; //上次触摸IC输出标志
bit timeFunFlag;     //定时功能标志
bit sysFunFlag;      //系统功能标志

bit edgeFlag = 0;   //红外管接收脚边沿标识
bit IR_data_deal_flag=0; //红外管接收到数据待处理标志
static u8 IR_bit;		//变量IR_bit用于指示红外数据的位数
static u8 btn_value=0; //红外按键键值寄存器
u32 time_cnt=0;     //定时计数器 计数单位1s
u8 secFlag=0;       //秒标志
u8 IR_count = 0;    //红外管接收到数据后延时计数器--250ms
u8 IRdata_len = 0; //红外管接收到数据长度
u8 IRdata[IR_DATA_BUFFER_SIZE];

 
//函数声明
static u8 IR_decode(void);			//红外解码函数
static void IR_Data_deal(void);
static void rdelay_acton_fun(u8 action_value);
static  u8 touch_check(void);    //触摸检测
static void touch_deal(void);    //触摸处理




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
	 P3_PULL_UP_ENABLE(GPIO_Pin_0 | GPIO_Pin_1);//			
	 //P3_PULL_UP_ENABLE(GPIO_Pin_1);//
	
   P1_MODE_OUT_PP(GPIO_Pin_0);   //推挽输出P1.0 控制中间第二个继电器
	 P3_MODE_OUT_PP(GPIO_Pin_6 |GPIO_Pin_7);   //推挽输出P3.7 控制边上第一个继电器  //推挽输出P3.6 红外管触摸IC 小板电源控制
	
	 //P3_MODE_OUT_PP(GPIO_Pin_6);   //推挽输出P3.6 红外管触摸IC 小板电源控制
	 P3_MODE_IN_HIZ(GPIO_Pin_3 | GPIO_Pin_4);   //施密特触发使能P3.3 连接触摸IC输出脚
	 //P3_MODE_IN_HIZ(GPIO_Pin_4);   //施密特触发使能P3.4 连接红外管接收脚
	
	 DELAY1_OFF;   
   DELAY2_OFF; 
	 P36 = 0; 

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
        FALOAD0=1;                  // 
		FTC0OUT=1;                  //允许P5.4口作PWM输出
		FPWM0OUT = 1;               //允许PWM/BUZZER功能  
        FTC0IEN=0;                  //不允许中断// Enable TC0 Interrput
        FTC0ENB=1;                  // 定时器开启
        //----Start Run---------------------------------------
        FGIE = 1;                   // Enable all Interrput
        //----------------------------------------------------
#if 0
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
	     
#endif
}
#if 0
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
#endif

/*************触摸功能*********************/
static  u8 touch_check(void)
{   //触摸输出检测   无触摸时高电平，有触摸时低电平时长大于300ms
    if(TOUCH_PIN == 0)
    {
			   if(Touch_flag) 
					 Touch_time = 0;
         else if(Touch_time > 500)  //139微秒 *500 = 69.5ms
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
						if(Touch_time > 2000)  //139微秒 *2000 = 279.5ms
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


//-------------------红外接收数据处理-------------------------------
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
	
	switch(dat)//红外接收正确
	{
		case  IR_LIGHT_BUTTON:   //灯档位调节键
				if(sysFunFlag==1)
				{
					 btn_value++;
					 if(btn_value >= BUTTON_VALUE_MAX)
						 btn_value = 1;
				}
		break;
	  case  IR_ONOFF_BUTTON:  //电源开关键
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
         time_cnt=0;    //电源键动作则清零定时计数器				 
    break;	
    default:
          return;			
	}
	
  rdelay_acton_fun(btn_value);

}
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

//********************************************************
//主程序
//********************************************************
void main(void)                   // 主程序
{                                            
    
	Sys_Init();                   // 系统初始化
		
	while(1)
	{	
	
		if(IR_Flag)				//红外数据接收完成
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
			//250ms 后处理数据
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
		if(touch_check())  //触摸检测
		{
			 sysFunFlag = 1;
		}
		touch_deal();
	
	}

		#if 0
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
		#endif
}                                 //

//********************************************************
//中断处理                                       
//********************************************************
void __interrupt[0x8] ISR(void)   // 1024us
{   
    static u8 isRec=0;   
	  
    //INT0中断处理
	if(FP00IRQ)
	{             //P00 interrput//P0.0 外部中断(INT0)

			if(edgeFlag) //下沿中断
			{     //高电平达到9ms为开始 位
				  PEDGE = 0x08;               //触发方式为上沿触发
				  edgeFlag = 0; 
				  if(IR_time>60)	//判断引导码(9ms+1.12ms)（0.56ms+1.12ms）
				  {
						IR_data[0]=IR_time;		//存储相应位时间宽度 
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
					IR_data[IR_bit]=IR_time;		//存储相应位时间宽度
					IR_time=0;						//清零时间宽度计数值
					IR_bit++;						  //位数变量自增
					if(IR_bit==9)				  //如果达到了9位（引导码+8个数据位）
					{
						IR_Flag=1;				  //红外数据接收完成标志位置1
						IR_bit=0;					  //位数变量清零
						isRec =0;
					}
				}
			}   
	        FP00IRQ  = 0;               //清除中断标志
	        FP00IEN  = 1;               //P0.0 外部中断(INT0)使能
	}
	else if(FT0IRQ)   //定时器T0中断 139us中断一次
	{
		if(IR_time < 0xf0)IR_time++;
	        Touch_time++;
        
		T0M=0x70;                   // 16M/16/2= 2uS   Fcpu的2分频  
        T0C=186;                    //256-139/2 = 256- 69.5 = 186.5 每139us中断一次      
		FT0IRQ=0;                   // T0 中断请求标志清零。
		FT0IEN=1;                   //允许响应 T0 中断。
        FT0ENB=1;                   //启动定时器T0运行 
	
	}
	#if 0
    //4MS----------------------------------------
    else if(FTC0IRQ)                   // TC0 interrput
    {        FTC0IRQ=0;                // Clr  flag
        
            JS1++;                    // 充电检测不到高电平计时>250,就关机  
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