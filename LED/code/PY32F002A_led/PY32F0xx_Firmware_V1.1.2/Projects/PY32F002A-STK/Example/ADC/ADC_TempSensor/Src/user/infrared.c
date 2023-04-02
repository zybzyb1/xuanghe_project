#include  "infrared.h"
#include  "stc8g1k_code.h"
#include  "global.h"
#include  "led2_digital_tube.h"
#include  "timing.h"
#include  "string.h"
//数据定义

#define   IR_HIGH_TIMER   3// 5

u8 sysFunFlag;      //系统功能标志
u8 IR_Flag;		    //红外数据接收完成标志位
u8 IR_time;		    //下降沿之间的时间计数值
u8 IR_data[9];		//引导码+8个位数据各自占用的时间
u8 IR_bit;	    	//变量IR_bit用于指示红外数据的位数
u8 btn_value;     //红外按键键值寄存器
u8 IRdata_len;     //红外管接收到数据长度
u8 IRdata[IR_DATA_BUFFER_SIZE];
u32 time_cnt;     //定时计数器 计数单位1s
u8 ir_int_flag;    //红外中断边沿类型
u8 si_level;
u8 timing_enableFlag;

static void IR_Data_deal(void);
static u8 IR_decode(void);	
//static void Int1_init(void);

void infrared_init(void)
{
    btn_value = 0;
    IR_Flag=0;		    //红外数据接收完成标志位
    IR_time=0;		    //下降沿之间的时间计数值
	  IRdata_len = 0;   //红外管接收到数据长度
	  btn_value=0;      //红外按键键值寄存器
	  time_cnt=0;       //定时计数器 计数单位1s
	  si_level =0;
	  timing_enableFlag=0;
}
void infrared_check_deal(void)
{
		if(IR_Flag)				//红外数据接收完成
		{
				//后处理数据
				if(IR_time >0xf0)
				{		
					  IR_time =0; 
						IR_Flag =0; 				
						IR_Data_deal();
				}
		}
}
extern void timing_action_fun(u8 timing);

//-------------------红外接收数据处理-------------------------------
static void IR_Data_deal(void)
{
		u8 dat=0,i,light=0,onoff=0;
	
		for(i=0;i<IRdata_len;i++) 
		{
				if(IRdata[i]==IR_LIGHT_BUTTON)
					 light++;
				else  if(IRdata[i]==IR_ONOFF_BUTTON)
					 onoff++;
		}
		if(IRdata_len == 0)
			 return;
		if(light > onoff)
			 dat = IR_LIGHT_BUTTON;
		else if(light < onoff)
			 dat = IR_ONOFF_BUTTON;
		
		IRdata_len = 0;
		
		switch(dat)//红外接收正确
		{
			case   IR_ONOFF_BUTTON:  //电源开关键（摇控器面板，上面红色丝印开关键）
            timing_enableFlag = 0;	
            shine_enable =0;
            if(led_display_chang == 0)			
						    btn_value++;
						if(timing_enable==0)
		          timing_duration =0;
						led_display_chang=0;  //显示通道1
					  if(btn_value > BUTTON_VALUE_MAX)
						{
									btn_value = 0;								
					  }
						rdelay_acton_fun(btn_value);
			break;
			case   IR_LIGHT_BUTTON:   //定时调节键（摇控器面板，下面白丝印灯控键）
					 led_display_chang=1;  //显示通道1
			     display_second=0;   //通道2显示秒计时器
			     if(timing_enableFlag != 1)
					 {
					     timing_enableFlag = 1;    
						   shine_enable = 0;
					 }
					 else
					 {
						   timing_enable= 0; 
						   if(shine_enable!=1)
							 {
									shine_enable = 1;
							 }
							 else
							 {
								 if(si_level > 0)
								     timing_duration++;
								 else 
									   timing_duration=0;
								 if(timing_duration > TIMING_VALUE_MAX)
								 {
											timing_duration = 0;								
								 }
							 }
					 }
			     timing_action_fun(timing_duration);
			break;	
			default:
						return;			
		}
    
}

//-------------------------红外接收解码-------------------------
static u8 IR_decode(void)
{
	u8 j;//,k;								
	u8 IR_Value = 0; 
	//k=0;							//先让变量k等于1，因为k为0时取出的将会是“引导码的时间间隔”
 
	for(j=0;j<=7;j++)				//内层循环8次为了拼合8个数据位为1个字节
	{
		if(IR_data[j]>=IR_HIGH_TIMER)			//若“时间间隔”比5大那肯定是“1码”反之为“0码”
			IR_Value|=0x80;			//通过按位或运算高位填1
		if(j<7)						    //若数据没有拼合完8次
			IR_Value>>=1;			  //通过右移运算“腾出”位置准备下一位判定
		//k++;						      //下标变量自增
	}
	
	return IR_Value;				//返回红外接收的数据
}

//-------------------------外部中断1红外线输出引脚初始化-------------------------
u8 isRec=0;
void ir_falling(void)  //红外下沿处理 
{
	 //下沿中断
	 //高电平达到9ms为开始 位	 
	  if( IR_time > 34)	//50判断引导码(9ms+1.12ms)（0.56ms+1.12ms）
		{
					isRec = 1;
					IR_bit = 0;
		}
		IR_time =0;  //清零时间宽度计数值
}

void ir_rising(void)  //红外上沿处理
{   //上沿中断	
		if(isRec)
		{
						IR_data[IR_bit]=IR_time;		//存储相应位时间宽度
						IR_time=0;						//清零时间宽度计数值
						IR_bit++;						  //位数变量自增
						if(IR_bit==8)				  //如果达到了9位（引导码+8个数据位）
						{
							IR_Flag=1;				  //红外数据接收完成标志位置1
							IR_bit=0;					  //位数变量清零
							isRec =0;
							
							IRdata[IRdata_len] = IR_decode();
							++IRdata_len;
							if(IRdata_len >= IR_DATA_BUFFER_SIZE)	
									IRdata_len=0;
						}
		}
	  IR_time =0;  //清零时间宽度计数值
}
