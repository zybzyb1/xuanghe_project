# SONIX DSP Makefile Version:1.0.0.2
# Defination
COMPILER = "c:\sonix\SN8_C_~1.297\bin\build\sn8pc.exe"
GMA = "C:\Sonix\SN8_C_~1.297\Bin\Build\gma.exe"
LINKER = "C:\Sonix\SN8_C_~1.297\Bin\Build\slink.exe"
CONVERT = "C:\Sonix\SN8_C_~1.297\Bin\Build\RcvSN8.exe"

# Define Path Macro
PRJ_PATH=.
OBJ_PATH=.\Obj
INC_PATH=.\Include
LIB_PATH=.\Lib
C_INC_PATH=C:\Sonix\SN8_C_~1.297\C\include
OUT_PATH=.\Bin
VPATH=.\:$(OBJ_PATH):$(LIB_PATH):$(INC_PATH):$(C_INC_PATH):$(OUT_PATH)

# Define Option Flags
COMPILER_FLAGS = -target=SN8P2501D -INI="C:\Sonix\SN8_C_~1.297\Bin\Build\SN8P2600.ini" -PROJECTNAME=".\test.prj" -WL=4 -Chip_Series=2 -A -I.\Include -IC:\Sonix\SN8_C_~1.297\C\include -NoCALLHL -NoMUL -NoHL -NoX -PUSH2 -NoGlobalOpt -tempdir="$(OBJ_PATH)"  -cpp_skip_asm -DICE_Mode=0
GMA_FLAGS = /INI:"SN8P2600.ini" /ID1:0 /ID2:0  /NODEBUG /MACHINE:SN8P2501D  /Chip_Series:2 /NOPeephole: /PATH:".\Include" /PROJECTNAME:".\test.prj" /WL:4 /DEFINE:ICE_Mode=0 /DEFINE:SN8P2501D=1  /OutputPath:"$(OBJ_PATH)" 
LINK_FLAGS = /MACHINE:SN8P2501D /Chip_Series:2 /INI:"SN8P2600.ini" /WL:4 /OutputFile:"$(OUT_PATH)/test.out"  /MAP:"$(OBJ_PATH)\test.map"   /LISTFILE:  /STDLIB:".\Obj"    /PATH:"$(LIB_PATH)" /STACK: /PROJECTNAME:".\test.prj"
CONV_FLAGS = /MACHINE:SN8P2501D /INI:"SN8P2600.ini" /WL:4 /OutputFile:"$(OUT_PATH)/test.sn8"  /PROJECTNAME:".\test.prj" /IDSVersion:V1.20.219.297n /Chip_Series:2 /OSLIB:".\Obj"  
LINK_DEP_FILES = $(OBJ_PATH)\u_board.o   \

# Define Rule
$(OBJ_PATH)\u_board.asm: .\Src\u_board.c $(C_INC_PATH)\SN8P2501D.h $(PRJ_PATH)\test.cfg .\Src\global.h
	@$(COMPILER) $(COMPILER_FLAGS) -o $@ $^ 

$(OBJ_PATH)\u_board.o: $(OBJ_PATH)\u_board.asm $(PRJ_PATH)\test.cfg
	@$(GMA) $(GMA_FLAGS) /CSource: /CASE: $< 

$(OUT_PATH)\test.out: $(LINK_DEP_FILES) $(PRJ_PATH)\test.cop
	@$(LINKER) $(LINK_FLAGS) /CSource: /CASE: $(LINK_DEP_FILES) 

$(OUT_PATH)\test.sn8: $(OUT_PATH)\test.out $(PRJ_PATH)\test.cop
	@$(CONVERT) $(CONV_FLAGS) $^ 


# Define Clean Rule
Clean:
	@del /F /Q $(OBJ_PATH)\*.*;
	@if EXIST .\test.prj.stb del .\test.prj.stb;
	@if EXIST .\test.out del .\test.out;
	@if EXIST .\test.sn8 del .\test.sn8;
	@if EXIST .\test.sn8.dep del .\test.sn8.dep;
	@if EXIST $(OUT_PATH)\test.out del $(OUT_PATH)\test.out;
	@if EXIST $(OUT_PATH)\test.sn8 del $(OUT_PATH)\test.sn8;
	@if EXIST $(OUT_PATH)\test.sn8.dep del $(OUT_PATH)\test.sn8.dep;

# Don't keep invalid files, command line must return non-zero(1 or 2) value 
# to validate delete on error mechanism 
# else return 0 for success

.DELETE_ON_ERROR:

Begin: 

Build: Begin All 

Rebuild: Clean Build 

All:$(OUT_PATH)\test.out $(OUT_PATH)\test.sn8
