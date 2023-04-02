#include  "led2_digital_tube.h"
#include  "global.h"
#include  "user_gpio.h"
#include  "py32f0xx_hal.h"
#include  "temperature.h"
#include  "led.h"

typedef struct{
    u8  vol;
    u8  percent;
}VOL_PERCENT_STRUCT; 
const static VOL_PERCENT_STRUCT dig_vol[]={
   {128,100},
	 {127,100},
   {126,95},
	 {125,80},
	 {124,75},
   {123,70},
	 {122,60},
	 {121,55},
   {120,50},
	 {119,40},
	 {118,30},
   {117,25},
	 {116,20},
	 {115,10},
   {114,10},
	 {113,10},
	 {112,255},
   {111,255},
	 {89,255}  
}; 

u8  digital_value[3];
u8  display_second;   //显示秒计时器
u8  percentage_reg;   //百分比
u8  page,pageV;
/*************    功能说明        *************

驱动3个共阴数码管自动扫描显示.

******************************************/
static void digital_display_unit(uint8 displayV,uint8 page);
static void digital_display(void);
static void digital_display_percentage(void);
static void vol_deal(u16 vol_value);
void  digital_display_init(void)
{
	  display_second = 0;
	  percentage_reg = 0;
	  page=1;
	  pageV = 1;
}

void digital_run(void)
{
	  
	 
    if(display_second < 18)  //单位104ms 电压显示时长1.872s
		{   
			  vol_deal(vol_value);
		    digital_display();
			  page = 1;vol_enable = 0;
		 
		}
    else  if(display_second < 36)  //单位104ms 电压比例显示时长1.872s
		{
			  vol_deal(vol_value);
		    digital_display_percentage();
			  pageV = 1;
		
		}
		else  if(display_second < 186)  //15s不显示 单位104ms
		{
			 vol_enable = 1; 
			 DIG1_OFF;
			 DIG2_OFF;
			 DIG3_OFF;
			 DP_OFF();
			 led_mode = 0;   //LED指示灯全灭
			 
		}
		else  
		{
		    display_second = 0;
		} 

}

static void vol_deal(u16 vol_value)
{
    u16 vol;
	  u8 i,v;

	  vol = vol_value; 
    //获取显示百分比值
	  //1、高于等于15V以上百分比值显示H1 
	  //2、高于12.6V且小于15V，百分比值显示100
	  //3、高于11.2V且小于12.7V，百分比值显示实际比例值 
	  //4、低于11.3V，百分比值显示SOS
		v = sizeof(dig_vol)/sizeof(VOL_PERCENT_STRUCT);
	  if(vol >= 150) 
		{
			  percentage_reg = 254;	//高于15V以上百分比值显示H1 1--c=1
		}
		else if(vol > dig_vol[1].vol && vol < 150) 
		{
			  percentage_reg = dig_vol[1].percent;	//高于12.8V且小于15V，百分比值显示100
		}
		else if(vol < dig_vol[v-4].vol) 
		{
			  percentage_reg = dig_vol[v-3].percent;	//低于11.3V，百分比值显示SOS 
		}
		else
		{
				for(i=0;i<v;i++)
				{
					if(vol == dig_vol[i].vol)
					{
							percentage_reg = dig_vol[i].percent;	  
					
					}
				}
		}
	
		//获取显示电压值
		//1、电压高于16V电压显示16-上划线a=1 
	  //2、电压高于8.9V且小于16V，电压显示实际值
	  //3、电压小于9V，电压显示-9
	  if(vol > 160)
		{
				digital_value[0] =	1;//vol/100;  //显示16- 上划线a=1
				//vol = vol%100;
				digital_value[1] =	6;//vol/10;
				digital_value[2] =	0x13;
		}
	  else if(vol <= dig_vol[v-1].vol)
		{
				digital_value[0] =	0x14;  //显示-号  -90
				digital_value[1] =	9;
				digital_value[2] =	0;
		}
		else
		{
				digital_value[0] =	vol/100;
				vol = vol%100;
				digital_value[1] =	vol/10;
				digital_value[2] =	vol%10;
		}

#if LED_ENABLE			
		//led双色指示灯
		if(vol_value > 125)
		{
		     led_mode = 2;  //绿色亮
		}
		else if(vol_value == 124 || vol_value == 125)
		{
		     led_mode = 3;   //双色亮
		}
		else if(vol_value < 124 )
		{
		     led_mode = 1;   //红色亮
		}
#endif			
}

static void  digital_display_percentage(void)
{
    u8  tmp = percentage_reg;
	  u8  dat;

		if(page == 1)
		{
			  if(tmp == 100)
           dat = 1;
				else if(tmp == 255)
           dat = 0x10;  //'s'
				else if(tmp == 254)
				{     //不显示
				   page = 2;
					 return;
				}
				else
				    dat = 0;  					
				digital_display_unit(dat,page);
				page = 2;	  
		}
		else if(page == 2)
		{
			  if(tmp == 100)
           dat = 0;
				else if(tmp == 255)
           dat = 0x11;  //'0'
				else if(tmp == 254)
				   dat = 0x12; //H
				else
				{
				    dat = tmp%100; 
					  dat = dat/10;
			  }
				digital_display_unit(dat,page);
				page = 3;	  
		}
		else if(page == 3)
		{
			  if(tmp == 100)
           dat = 0;
				else if(tmp == 255)
           dat = 0x10;  //'s'
				else if(tmp == 254)
				   dat = 0x15; //1
				else
				{ 
				    dat = tmp%10; 
				}
				digital_display_unit(dat,page);
				page = 1;	  
		}
	 

}
static void  digital_display(void)  //5ms执行一次
{
	 
    u8 dat;

		if(pageV == 1)
		{
			  dat = digital_value[0];
				digital_display_unit(dat,pageV);
				pageV = 2;	  
		}
		else if(pageV == 2)
		{
			  dat = digital_value[1];
			  if(digital_value[2]!=0x13)
			     DP_ON();
				digital_display_unit(dat,pageV);
			  
				pageV = 3;	  
		}
		else if(pageV == 3)
		{
			  dat = digital_value[2];
				digital_display_unit(dat,pageV);
				pageV = 1;	  
		}
}	

static void digital_display_unit(u8 displayV,u8 page)
{
     
		 DIG1_OFF;
		 DIG2_OFF;
	   DIG3_OFF;
	   if(page != 2)//digital_value[2]!=0x13)
	       DP_OFF();
	   DIGITAL_VALUE_PORT &= 0xFFFFFFF0;
		 switch(displayV)
		 {
			 case 0: 
			 DIGITAL_VALUE_PORT |= 0x0000000f; //0x3F		
       GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_OFF();
			 break;
			 case 1: 	 
			 DIGITAL_VALUE_PORT |= 0x00000006; //0x06
       GPIO4_OFF();
			 GPIO5_OFF();
			 GPIO6_OFF();
			 break;
			 case 2:	 
			 DIGITAL_VALUE_PORT |= 0x000000b;  //0x5B 
       GPIO4_ON();
			 GPIO5_OFF();
			 GPIO6_ON();
			 break;
			 case 3: 
			 DIGITAL_VALUE_PORT |= 0x0000000f; //0x4F	
       GPIO4_OFF();
			 GPIO5_OFF();
			 GPIO6_ON();
			 break;
			 case 4:
			 DIGITAL_VALUE_PORT |= 0x0000006; //0x66
       GPIO4_OFF();
			 GPIO5_ON();
			 GPIO6_ON();			 
			 break;
			 case 5:
			 DIGITAL_VALUE_PORT |= 0x0000000d; //0x6D
			 GPIO4_OFF();
			 GPIO5_ON();
			 GPIO6_ON();
			 break;
			 case 6:
			 DIGITAL_VALUE_PORT |= 0x0000000d; //0x7D
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_ON();  
			 break;
			 case 7:
			 DIGITAL_VALUE_PORT |= 0x00000007; //0x07
			 GPIO4_OFF();
			 GPIO5_OFF();
			 GPIO6_OFF();	 
			 break;
			 case 8:
			 DIGITAL_VALUE_PORT |= 0x000000f; //0x7F
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_ON();   
			 break;
			 case 9:			 
			 DIGITAL_VALUE_PORT |= 0x000000f; //0x6F
			 GPIO4_OFF();
			 GPIO5_ON();
			 GPIO6_ON(); 
			 break;
			 case 0x0A:		
			 DIGITAL_VALUE_PORT |= 0x0000007; //0x77
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_ON(); 
			 break;
			 case 0x0B:
			 DIGITAL_VALUE_PORT |= 0x000000c; //0x7C
			 
			 break;
			 case 0x0C:
			 DIGITAL_VALUE_PORT |= 0x0000009; //0x39
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_OFF(); 
			 break;
			 case 0x0D:
			 DIGITAL_VALUE_PORT |= 0x0000000e; //0x6E
			 GPIO4_OFF();
			 GPIO5_ON();
			 GPIO6_ON(); 
			 break;
			 case 0x0E:
			 DIGITAL_VALUE_PORT = 0x00000079; //0x79
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_ON();  
			 break;
			 case 0x0F:
			 DIGITAL_VALUE_PORT |= 0x00000001; //0x71
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_ON();   
			 break;
			 case 0x10: //'s'
			 DIGITAL_VALUE_PORT |= 0x0000000d; //0x6d 
			 GPIO4_OFF();
			 GPIO5_ON();
			 GPIO6_ON();
			 break; 
			 case 0x11: //'O'
			 DIGITAL_VALUE_PORT |= 0x0000000c; //0x5c      cde g
			 GPIO4_ON();
			 GPIO5_OFF();
			 GPIO6_ON(); 
			 break; 
			 case 0x12: //'H'
			 DIGITAL_VALUE_PORT |= 0x00000006; //0x76    BC EF 
			 GPIO4_ON();
			 GPIO5_ON();
			 GPIO6_ON(); 
			 break; 
			 case 0x13: //'-' //上划线--a=1
			 DIGITAL_VALUE_PORT |= 0x00000001; //0x01    
			 GPIO4_OFF();
			 GPIO5_OFF();
			 GPIO6_OFF(); 
			  break; 
			 case 0x14:  //'-' //下划线=--d=1
			 DIGITAL_VALUE_PORT |= 0x00000008; //0x08
			 GPIO4_OFF();
			 GPIO5_OFF();
			 GPIO6_OFF(); 
			 break; 
			 case 0x15:  //'1' //1=--c=1
			 DIGITAL_VALUE_PORT |= 0x00000004; //0x04
			 GPIO4_OFF();
			 GPIO5_OFF();
			 GPIO6_OFF(); 
			 break; 
			 default:  
			 
			 break;
		 }
 
		 if(page==1)     {DIG1_ON;}
		 else if(page==2){DIG2_ON;}
		 else            {DIG3_ON;}
}


