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



#ifdef    UART_ENABLE
#include  "uart.h"
#endif

#define  IR_DATA_BUFFER_SIZE  10
 

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
	
	
	gpio_config();
	EA = 1;				  //开中断
	#ifdef  ADC_TIMER_ENABLE	
	ADC_config();
	#endif
	Timer0Init();		//定时计数器0初始化函数
	Timer1Init();		//定时计数器1初始化函数
	Int1_init();		//外部中断1初始化函数  红外输出脚  //触摸IC输出脚
	//Int0_init();		//外部中断0初始化函数 
	//Int3_init();		//外部中断3初始化函数  
	
	#ifdef UART_ENABLE
	UartInit();
	PrintString1("STC8:\r\n");    //UART1发送一个字符串
  #endif	
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
#ifdef  ADC_TIMER_ENABLE	
		if((secFlag==1) && (sysFunFlag==1))  //1秒 ADC一次
		{
			  secFlag = 0;
    		timer_deal();
		}
#endif	
	}
}
static void gpio_config(void)
{
	/*
		GPIO_InitTypeDef	GPIO_InitStructure;		//结构定义

		GPIO_InitStructure.Pin  = GPIO_Pin_0 | GPIO_Pin_1;		//指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
		GPIO_InitStructure.Mode = GPIO_PullUp;	//指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
		GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);	//初始化
	*/

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
#ifdef  ADC_TIMER_ENABLE	
//-------------------------继电器定时关闭-----------------------
static void  timer_deal(void)
{
	  u16  ad_dat;
	  static u16  ad_pre=0xffff;
	  static u8  delay_time=0;
	
		ad_dat = Get_ADCResult(ADC_CH13);  //读取ADC定时值
	
    if(ad_dat == 4096)  return;   //出错
		
    if(ad_dat > 1024 / TIMER_LENGTH_MAX / 2)//定时功能开启
    {			
				if(ad_pre > ad_dat+15 || ad_pre < ad_dat-15)
				{
					ad_pre = ad_dat;
					timeFunFlag = 1;  //定时功能开启
					time_cnt = 0;   //定时计数器清零
					
					delay_time = calculate_timer(ad_dat); //计算出定时时长
					
				}
		}
		else
			  timeFunFlag = 0;   //定时功能关闭
		
	  if(timeFunFlag)
		{	
			if(time_unit_compare(delay_time))  
			{                     //定时时间到了
				  btn_value=0;
					rdelay_acton_fun(0);
					timeFunFlag = 0;  //定时功能关闭
				  sysFunFlag = 0;
			
			}	
		}			  
			  
}
static u8  time_unit_compare(u8 delayTime)
{
		u32 delay_T;
	
	  delay_T = delayTime*30*60;   //delayTime单位为半个小时 这里转化为秒
	   
	  if(time_cnt > delay_T)
		{
				time_cnt = 0; //定时计数清零
		    return 1;
		}
		return 0;
}
static u8  calculate_timer(u16 adValue)
{ 
	u8  timing_time=0;  //定时时长 单位1表小0.5小时
	u16 step_length = 1024 / TIMER_LENGTH_MAX; //这里计算定时步长对应的数值,当ADC值是低半步关闭定时功能,最高半步值时定时时长8个小时
  u16  half_length =  step_length/2;
	if(adValue < half_length)   //ADC数值小于32关闭定时
       timing_time = 0;
	else if(adValue > 1024- half_length) //ADC数值大于1024-32=992定时8小时
       timing_time = 16; //8 小时
	else
		{    // 计算定时时长步长为0.5小时  每一步长对应ADC数值64
			timing_time = adValue/step_length; 
			//ADC数值<=32 故timing_time=0 定时长为0小时，
			//32<ADC数值<=96 故timing_time=1 定时长为半小时，96<ADC数值<160 故timing_time=2 定时长为1小时 .160<ADC数值<224 故timing_time=3 定时长为1.5小时 
			//224<ADC数值<=288 故timing_time=4 定时长为2小时,288<ADC数值<352 故timing_time=5 定时长为2.5小时,352<ADC数值<416 故timing_time=6 定时长为3小时 
			//416<ADC数值<=480 故timing_time=7 定时长为3.5小时480<ADC数值<544 故timing_time=8 定时长为4小时 544<ADC数值<608 故timing_time=9 定时长为4.5小时 
			//608<ADC数值<=672 故timing_time=10 定时长为5小时,672<ADC数值<736 故timing_time=11 定时长为5.5小时,736<ADC数值<800 故timing_time=12 定时长为6小时
      //800<ADC数值<=864 故timing_time=13 定时长为6.5小时，864<ADC数值<928 故timing_time=14 定时长为7小时928<ADC数值<992 故timing_time=15 定时长为7.5小时 
			//992<ADC数值<=1024 故timing_time=16 定时长为8小时.			
	    if(adValue % step_length  > half_length)
				   timing_time++;
	
	}
		return timing_time;
}
//========================================================================
static void	ADC_config(void)
{
	
	ADC_InitTypeDef		ADC_InitStructure;		//结构定义
	ADC_InitStructure.ADC_SMPduty   = 31;		//ADC 模拟信号采样时间控制, 0~31（注意： SMPDUTY 一定不能设置小于 10）
	ADC_InitStructure.ADC_CsSetup   = 0;		//ADC 通道选择时间控制 0(默认),1
	ADC_InitStructure.ADC_CsHold    = 1;		//ADC 通道选择保持时间控制 0,1(默认),2,3
	ADC_InitStructure.ADC_Speed     = ADC_SPEED_2X1T;		//设置 ADC 工作时钟频率	ADC_SPEED_2X1T~ADC_SPEED_2X16T
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	//ADC结果调整,	ADC_LEFT_JUSTIFIED,ADC_RIGHT_JUSTIFIED
	ADC_Inilize(&ADC_InitStructure);		//初始化
	ADC_PowerControl(ENABLE);						//ADC电源开关, ENABLE或DISABLE
	//NVIC_ADC_Init(DISABLE,Polity_0);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Polity_0,Polity_1,Polity_2,Polity_3
	
}
#endif	
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
#if 0
//-------------------------外部中断0初始化-------------------------
static void Int0_init(void)
{
	IT0 = 1;	//触发方式为下降沿触发
	EX0 = 1;	//使能INT0中断
}
//-------------------------外部中断3初始化-------------------------
static void Int3_init(void)
{
	//EX0 = 1;	//使能INT0中断
	//INTCLKO = EX2; //使能 INT2 下降沿中断
  INTCLKO |= EX3; //使能 INT3 下降沿中断//触发方式为下降沿触发
  //INTCLKO |= EX4; //使能 INT4 下降沿中断
}
#endif
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

#if 0
//-------------------------外部中断0服务函数-------------------------
void INT0_ISR() interrupt 0
{

}
#endif
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
void INT3_ISR() interrupt 11	
{
	
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
	
	
	#if 0
  count--;
	if(count == 0)
	{
		 IR_TimeFlag = 1;
		 ET1 = 1;//
	}
	#endif
	
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


