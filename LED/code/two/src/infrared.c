#include  "infrared.h"
#include  "stc8g1k_code.h"
#include  "STC8xxxx.h"
#include  "global.h"
#include  "uart.h"
#include  "string.h"
//数据定义

bit edgeFlag = 0;   //红外管接收脚边沿标识
bit sysFunFlag;      //系统功能标志
bit IR_Flag=0;		//红外数据接收完成标志位
u8 IR_time=0;		  //下降沿之间的时间计数值
u8 IR_data[9];		//引导码+8个位数据各自占用的时间
u8 IR_bit;		//变量IR_bit用于指示红外数据的位数
u8 btn_value=0; //红外按键键值寄存器
u8 IRdata_len = 0; //红外管接收到数据长度
u8 IRdata[IR_DATA_BUFFER_SIZE];
u32 time_cnt=0;     //定时计数器 计数单位1s


static void IR_Data_deal(void);
static u8 IR_decode(void);	
static void Int1_init(void);

void infrared_init(void)
{
    btn_value = 0;
	  edgeFlag = 1;
	  //红外输出检测
	  Int1_init();		//外部中断1初始化函数  红外输出脚  //触摸IC输出脚	
	
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
			case  IR_LIGHT_BUTTON:   //灯档位调节键
						 if(sysFunFlag==1)
						 {
							 btn_value++;
							 if(btn_value > BUTTON_VALUE_MAX)
							 {
									btn_value = 1;
							 }

						 }
						 else
							 return;	
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
			break;	
			default:
						return;			
		}
    rdelay_acton_fun(btn_value);
}

//-------------------------红外接收解码-------------------------
static u8 IR_decode(void)
{
	u8 j;//,k;								
	u8 IR_Value = 0; 
	//k=0;							//先让变量k等于1，因为k为0时取出的将会是“引导码的时间间隔”
 
	for(j=0;j<=7;j++)				//内层循环8次为了拼合8个数据位为1个字节
	{
		if(IR_data[j]>=5)			//若“时间间隔”比5大那肯定是“1码”反之为“0码”
			IR_Value|=0x80;			//通过按位或运算高位填1
		if(j<7)						    //若数据没有拼合完8次
			IR_Value>>=1;			  //通过右移运算“腾出”位置准备下一位判定
		//k++;						      //下标变量自增
	}
	
	return IR_Value;				//返回红外接收的数据
}

//-------------------------外部中断1红外线输出引脚初始化-------------------------
static void Int1_init(void)
{
	IT1 = 1;	//触发方式为下降沿触发
	EX1 = 1;	//使能INT1中断
}
void INT1_ISR() interrupt INT1_VECTOR	 //连接红外管接收脚
{
	static u8 isRec=0; 

	if(edgeFlag) //下沿中断
	{   //高电平达到9ms为开始 位
		  IT1 = 0;	//触发方式为上沿触发
		  EX1 = 1;	//使能INT1中断
		  edgeFlag = 0; 
		  if(IR_time>50)	//判断引导码(9ms+1.12ms)（0.56ms+1.12ms）
			{
				    isRec = 1;
				    IR_bit = 0;
			}
			
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
	}
	IR_time =0;  //清零时间宽度计数值
}
