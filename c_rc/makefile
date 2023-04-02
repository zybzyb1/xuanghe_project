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
COMPILER_FLAGS = -target=SN8P2501B -INI="C:\Sonix\SN8_C_~1.297\Bin\Build\SN8P2600.ini" -PROJECTNAME=".\c_rc.prj" -WL=3 -Chip_Series=2 -A -I.\Include -IC:\Sonix\SN8_C_~1.297\C\include -NoCALLHL -NoMUL -NoHL -NoX -PUSH2 -NoGlobalOpt -tempdir="$(OBJ_PATH)"  -cpp_skip_asm -DICE_Mode=0
GMA_FLAGS = /INI:"SN8P2600.ini" /ID1:0 /ID2:0  /NODEBUG /MACHINE:SN8P2501B  /Chip_Series:2 /NOPeephole: /PATH:".\Include" /PROJECTNAME:".\c_rc.prj" /WL:3 /DEFINE:ICE_Mode=0 /DEFINE:SN8P2501B=1  /OutputPath:"$(OBJ_PATH)" 
LINK_FLAGS = /MACHINE:SN8P2501B /Chip_Series:2 /INI:"SN8P2600.ini" /WL:3 /OutputFile:"$(OUT_PATH)/c_rc.out"  /MAP:"$(OBJ_PATH)\c_rc.map"   /LISTFILE:  /STDLIB:".\Obj"    /PATH:"$(LIB_PATH)" /STACK: /PROJECTNAME:".\c_rc.prj"
CONV_FLAGS = /MACHINE:SN8P2501B /INI:"SN8P2600.ini" /WL:3 /OutputFile:"$(OUT_PATH)/c_rc.sn8"  /PROJECTNAME:".\c_rc.prj" /IDSVersion:V1.20.219.297n /Chip_Series:2 /OSLIB:".\Obj"  
LINK_DEP_FILES = $(OBJ_PATH)\rc.o   \

# Define Rule
$(OBJ_PATH)\rc.asm: .\Src\rc.c $(C_INC_PATH)\SN8P2501B.h $(PRJ_PATH)\c_rc.cfg .\Include\global.h
	@$(COMPILER) $(COMPILER_FLAGS) -o $@ $^ 

$(OBJ_PATH)\rc.o: $(OBJ_PATH)\rc.asm $(PRJ_PATH)\c_rc.cfg
	@$(GMA) $(GMA_FLAGS) /CSource: /CASE: $< 

$(OUT_PATH)\c_rc.out: $(LINK_DEP_FILES) $(PRJ_PATH)\c_rc.cop
	@$(LINKER) $(LINK_FLAGS) /CSource: /CASE: $(LINK_DEP_FILES) 

$(OUT_PATH)\c_rc.sn8: $(OUT_PATH)\c_rc.out $(PRJ_PATH)\c_rc.cop
	@$(CONVERT) $(CONV_FLAGS) $^ 


# Define Clean Rule
Clean:
	@del /F /Q $(OBJ_PATH)\*.*;
	@if EXIST .\c_rc.prj.stb del .\c_rc.prj.stb;
	@if EXIST .\c_rc.out del .\c_rc.out;
	@if EXIST .\c_rc.sn8 del .\c_rc.sn8;
	@if EXIST .\c_rc.sn8.dep del .\c_rc.sn8.dep;
	@if EXIST $(OUT_PATH)\c_rc.out del $(OUT_PATH)\c_rc.out;
	@if EXIST $(OUT_PATH)\c_rc.sn8 del $(OUT_PATH)\c_rc.sn8;
	@if EXIST $(OUT_PATH)\c_rc.sn8.dep del $(OUT_PATH)\c_rc.sn8.dep;

# Don't keep invalid files, command line must return non-zero(1 or 2) value 
# to validate delete on error mechanism 
# else return 0 for success

.DELETE_ON_ERROR:

Begin: 

Build: Begin All 

Rebuild: Clean Build 

All:$(OUT_PATH)\c_rc.out $(OUT_PATH)\c_rc.sn8
