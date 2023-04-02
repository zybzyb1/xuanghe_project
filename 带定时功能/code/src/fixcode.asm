//Keil C51 在目标ROM的的指定地址(如 0x10000)写字符A,FF,FF,FF,FF,FF,B 的方法是
//添加一个fixcode.asm到工程， 内容是:
CSEG AT 01000h

CFG_BYTE_0:  DB  '*'
CFG_BYTE_1:  DB  '*'
CFG_BYTE_2:  DB  '*'
	
CFG_BYTE_3:  DB  '%'  //开 %u5F00
CFG_BYTE_4:  DB  'u'
CFG_BYTE_5:  DB  '5'
CFG_BYTE_6:  DB  'F'
CFG_BYTE_7:  DB  '0'
CFG_BYTE_8:  DB  '0'
	
CFG_BYTE_9:  DB  '%'  //发 %u53D1
CFG_BYTE_10:  DB  'u'
CFG_BYTE_11:  DB  '5'
CFG_BYTE_12:  DB  '3'
CFG_BYTE_13:  DB  'D'
CFG_BYTE_14:  DB  'E'
	
CFG_BYTE_15:  DB  '%'  //者 %u8005
CFG_BYTE_16:  DB  'u'
CFG_BYTE_17:  DB  '8'
CFG_BYTE_18:  DB  '0'
CFG_BYTE_19:  DB  '0'
CFG_BYTE_20:  DB  '5'
	
CFG_BYTE_21:  DB  '%'  //: %uFF1A
CFG_BYTE_22:  DB  'u'
CFG_BYTE_23:  DB  'F'
CFG_BYTE_24:  DB  'F'
CFG_BYTE_25:  DB  '1'
CFG_BYTE_26:  DB  'A'
	
CFG_BYTE_27:  DB  '%'  //周 %u5468 
CFG_BYTE_28:  DB  'u'
CFG_BYTE_29:  DB  '5'
CFG_BYTE_30:  DB  '4'
CFG_BYTE_31:  DB  '6'
CFG_BYTE_32:  DB  '8'
	
CFG_BYTE_33:  DB  '%'  //杨  %u6768
CFG_BYTE_34:  DB  'u'
CFG_BYTE_35:  DB  '6'
CFG_BYTE_36:  DB  '7'
CFG_BYTE_37:  DB  '6'
CFG_BYTE_38:  DB  '8'
	
CFG_BYTE_39:  DB  '%'  //波  %u6CE2
CFG_BYTE_40:  DB  'u'
CFG_BYTE_41:  DB  '6'
CFG_BYTE_42:  DB  'C'
CFG_BYTE_43:  DB  'E'
CFG_BYTE_44:  DB  '2'

CFG_BYTE_45:  DB  'U'
CFG_BYTE_46:  DB  'T'
CFG_BYTE_47:  DB  'F'	
CFG_BYTE_48:  DB  '-'
CFG_BYTE_49:  DB  '8'
	
CFG_BYTE_50:  DB  '*'
CFG_BYTE_51:  DB  '*'
CFG_BYTE_52:  DB  '*'	

END