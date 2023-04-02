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
#include  "led2_digital_tube.h"
#include  "uart.h"
#include  "infrared.h"
#include  "touch.h"
#include  "temperature.h"
#include  "buzzer.h"

#ifdef    UART_ENABLE
#include  "uart.h"
#endif

#define ET2 0x04
 
//数据定义
u8 si_level;        //可控硅控制级数 0关闭 最大3档

//函数声明
static void Timer0Init(void);		//定时计数器0初始化函数
static void Timer1Init(void);		//定时计数器1初始化函数
static void Timer2Init(void);		//10毫秒@6.000MHz
static void gpio_config(void);
static void Int1_init(void);
static void Int0_init(void);
void rdelay_acton_fun(u8 action_value);
void delay(u16 count);		//延时函数声明

//-------------------------主函数----------------------------
void main(void)
{
	gpio_config();

	Timer0Init();		//定时计数器0初始化函数
	Timer1Init();		//定时计数器1初始化函数
	Timer2Init();		//10毫秒@6.000MHz
	//过零检测
	Int0_init();		//外部中断0初始化函数  过零检测脚
	//Int3_init();		//外部中断3初始化函数  
  infrared_init(); //红外初始化函数
	touch_init();    //触摸初始化函数
	buzzer_init();
	
	#ifdef UART_ENABLE
	UartInit();
	#endif
	EA = 1;				  //开中断
	delay(500);			//等待配置稳定
	#ifdef UART_ENABLE
	PrintString1("STC8:\r\n");    //UART1发送一个字符串
  #endif
	
	WDT_CONTR = 0x23; //使能看门狗,溢出时间约为 0.5s
  //WDT_CONTR = 0x24; //使能看门狗,溢出时间约为 1s
  // WDT_CONTR = 0x27; //使能看门狗,溢出时间约为 8s

	temperature_init();
	
  rdelay_acton_fun(0);
	si_level =0;
	led_display_enable=0;
	buzzerEnableFlag =1;

	while(1)
	{		
		 WDT_CONTR |= 0x10; //清看门狗,否则系统复位
     temperature_get_deal();		
		 if(overtemperature_check())
			  continue;
		 infrared_check_deal(); 
		 touch_check_deal();//触摸检测
     buzzer_run();
		
	}
}


static void gpio_config(void)
{
	
   //数码管引脚初始化
	 P3_MODE_OUT_PP(GPIO_Pin_5 | GPIO_Pin_7 |GPIO_Pin_4);   //推挽输出A F G       
	 P1_MODE_OUT_PP(GPIO_Pin_6 | GPIO_Pin_4 | GPIO_Pin_2 |GPIO_Pin_3);//推挽输出B C D E  
	 P1_MODE_OUT_PP(GPIO_Pin_0);   //推挽输出DIG2  
	 P5_MODE_OUT_PP(GPIO_Pin_4);   //推挽输出DIG1 
	 P54 = 0; P16=0;  //数码管不显示
// ||GPIO_Pin_7
	 //P5_MODE_OUT_PP(GPIO_Pin_5);   //推挽输出AH
	 //P55 = 1;
	
	 //触摸IC引脚初始化 
	 P3_ST_ENABLE(GPIO_Pin_3);     //施密特触发使能
	 P3_MODE_IN_HIZ(GPIO_Pin_3);   //高阻输入	
	 //Int2_init();  //P3.6/INT2下降沿中断

	 //可控硅控制IO初始化
	 P1_MODE_OUT_PP(GPIO_Pin_7);   //推挽输出 
	 SI_OFF();   //关断可控硅
	 
   //蜂鸣器IO初始化
	 P1_MODE_OUT_PP(GPIO_Pin_1);   //推挽输出 
	 P11=1;
	
/*
		#if   0
	//STC8G系列单片机除P3.0和P3.1外，所有I/O上电均为高阻输入状态，需先配置再使用
	P3M0 |=0x08;		//P3.3引脚为推挽输出模式
	P3M1 &=0xF7;		//P3.3引脚为推挽输出模式
	RSTCFG &=0xEF;		//复位引脚P5.4当做普通I/O引脚
	P5M0 |=0x10;		//P5.4引脚为推挽输出模式
	P5M1 &=0xEF;		//P5.4引脚为推挽输出模式
	P5M0 &=0xDF;		//P5.5引脚为准双向口模式
	P5M1 &=0xDF;		//P5.5引脚为准双向口模式
	#endif
		GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

		GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
		GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
		GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//初始化
	
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
*/
}
//-------------------------延时函数----------------------------
void delay(u16 count)
{
	while(count--)
	{
		_nop_();
	}
}
//函数功能：备份与还原参数
void display_para(u8 bak)
{
   static u8 btn_value_bak=0xff;
	 if(1 == bak)
	    btn_value_bak = btn_value;
	 else
	 {
	     btn_value = btn_value_bak;
	     rdelay_acton_fun(btn_value);
	 }

}
void rdelay_acton_fun(u8 action_value)
{
    switch(action_value)
		{
		    case 0:  // 断开所有继电器
					led_display_enable=0;  //上电LED数码管不显示
				  si_level = 0; 
        break;
				case 1:   //数码管显示--
            led_display_enable=1; 
				    digital_value[0]=0xff;
				    digital_value[1]=0xff;
				    buzzerEnableFlag = 1;
				    si_level = 0;
        break;
				case 2:  //数码管显示L1
            led_display_enable=1; 
				    digital_value[0]=0x10;
				    digital_value[1]=0x01;
				    //buzzerEnableFlag = 1;
				    si_level = 1;
        break;
				case 3:
            led_display_enable=1; 
				    digital_value[0]=0x10;
				    digital_value[1]=0x02;
				    //buzzer_enable = 1;
				    si_level = 2;
        break;
				case 4:
            led_display_enable=1; 
				    digital_value[0]=0x10;
				    digital_value[1]=0x03;
				    //buzzer_enable = 1;
				    si_level = 3;
        break;
				case 5:
            led_display_enable=1; 
				    digital_value[0]=0x0e;
				    digital_value[1]=0x01;
				    //buzzer_enable = 0;
				    si_level = 0;
        break;
		    default:
					
				break;
		}
}

//-------------------------定时器初始化----------------------------
static void Timer0Init(void)		//139微秒@6.000MHz
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
static void Timer1Init(void)		//125毫秒@6.000MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xDC;		//设置定时初值
	TH1 = 0x0B;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	
	ET1 = 1;		//使能T1中断
}
static void Timer2Init(void)		//10毫秒@6.000MHz
{
	AUXINTIF &= ~T2IF; //清中断标志
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0x78;		//设置定时初值
	T2H = 0xEC;		//设置定时初值
	AUXR &= ~0x10;//定时器2不计时
	IE2 = ET2;    //使能定时器中断
}

//-------------------------外部中断0过零检测中断初始化-------------------------
static void Int0_init(void)
{
	IT0 = 1;	//触发方式为下降沿触发
	EX0 = 1;	//使能INT0中断
}


//-------------------------外部中断0服务函数-------------------------
void INT0_ISR() interrupt INT0_VECTOR   //过零检测中断
{
	//可控硅控制方法：过零点后可控硅在没有外部触发条件下，自动关闭.
	//用time2作延时，time2最长延时长为10ms，把10ms分成3份，即每份时长为3.3ms
	//第一档延时时长为10-3.3ms=6.7ms，第二档延时时长为10-3.3ms*2=3.4ms，第三档全波形工作不延时.过零点时直接触发可控硅导通
	//所以一二档定时器初始值计算如下：
	//incrementV=(0xffff-0xEC78)/4=0x0662; ---incrementV变量值：把10ms分成3份每一份的初始值的增量值
	//timeVal=0xEC78 + incrementV * si_level;---preTimeVal变量值：即是一二档定时器初始值
	
     u16  timeVal;// 0x0662; // 0x04c9; //0x1327;
	   AUXR &= ~0x10;		//定时器2停止计时
     
		 switch(si_level)
     {
			 case 0:
          SI_OFF();  //关断可控硅 
			    return;
       case 1:
				   SI_OFF();  //关断可控硅 
				   //timeVal = 0xEC78 + 0x0662; //定时器初始值越大延时时长越短,定时器工作方式是增量溢出产生中断.
           TH2=242;//timeVal/256;  62170/256;
           TL2=218;//timeVal%256;  62170-61952
        break;
			 case 2:
				   SI_OFF();  //关断可控硅 
				   //timeVal = 0xEC78 + 0x0662 *2;
           TH2=249;//timeVal/256;   63804/256
           TL2=60;//timeVal%256;   63804-63744
        break;
		   case 3:
           SI_ON();   //开启可控硅
			     return;
        break;
		 } 
        
     AUXR |= 0x10;		//定时器2开始计时;
		
}



void INT2_ISR() interrupt INT2_VECTOR	 //触摸按键
{
	
}
u8 display_cnt=0;
void Time0_Handler_Callback(void) 	interrupt TIMER0_VECTOR		//139us 进中断时已经清除标志//任务标记回调函数
{
	 if(IR_time < 0xfc)
		 IR_time++;
	
	 Touch_time++;

	 if(display_cnt++ > 40)
	 {
		   display_cnt = 0;
	     led_display();
	 }
		 
}
void Time1_Handler_Callback(void)	interrupt TIMER1_VECTOR		//125ms 进中断时已经清除标志//任务标记回调函数
{
	static u8 secCount=0;

	buzzer_timer++;
	
	if(++secCount >= 8)
	{
	   secCount = 0;
		 secFlag=1;
	}
	
	
	#if 0
  count--;
	if(count == 0)
	{
		 IR_TimeFlag = 1;
		 ET1 = 1;//
	}
	#endif
	
}

void Time2_Handler_Callback(void)	interrupt TIMER2_VECTOR	
{
	  AUXINTIF &= ~T2IF; //清中断标志
    SI_ON();   //开启可控硅
    //delay(10);  //延时2us
    //SI_OFF();  //关断可控硅 
	  
}








//-------------------------定时器0初始化----------------------------
#if 0
static void Time0_init(void)	//139微秒@11.0592MHz
{
	AUXR &= 0x7F;	//定时器时钟12T模式，工作方式2
	TMOD &= 0xF0;	
	TMOD |= 0x02;	
	TL0 = 0x80;		
	TH0 = 0x80;		
	TF0 = 0;		//清除标志
	ET0 = 1;		//使能T0中断
	TR0 = 1;		//启动T0
}
//-------------------------定时器1初始化---------------------------

static void Time1_init(void)	//278微秒@11.0592MHz
{	
    AUXR |= 0x40;//模式2 1T
    TMOD &= 0x0F;	
}
#endif









#if 0
//-------------------------红外发送高电平----------------------------
void Wait_High(a)//a*280uS 
{
	unsigned char k;
	IR_TimeFlag = 0;
	count = a;
	T1_START();
	while(!IR_TimeFlag)  //38khz载波
	{
		_nop_();
		_nop_();
		k = 23;
		while (--k);
		IR_IO = ~IR_IO;
	}
	IR_IO = 1;
}
//-------------------------红外发送低电平----------------------------
void Wait_Low(a)//a*280uS 
{
	IR_IO = 1;
	IR_TimeFlag = 0;
	count = a;
	T1_START();
	while(!IR_TimeFlag);
}
//-------------------------红外发送单字节数据----------------------------
void Send_IR(u8 dat)
{
	unsigned char i,j;
	Wait_High(2);//0.56ms 
	Wait_Low(4);//1.12ms  
 
	for(j=0;j<8;j++)
	{
		Wait_High(1);//0.28ms 
		if(dat&0x01)
		{
			Wait_Low(2);// 0.56ms 
		}
		else
		{
			Wait_Low(1);//0.28ms
		}
		dat = dat>>1;    
	}
  
	Wait_High(1);//0.28ms 
}
#endif


