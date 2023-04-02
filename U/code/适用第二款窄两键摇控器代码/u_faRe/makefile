# SONIX DSP Makefile Version:1.0.0.2
# Defination
COMPILER = "c:\sonix\SN8_C_~1.297\bin\build\sn8pc.exe"
GMA = "C:\Sonix\SN8_C_~1.297\Bin\Build\gma.exe"
LINKER = "C:\Sonix\SN8_C_~1.297\Bin\Build\slib.exe"

# Define Path Macro
PRJ_PATH=.
OBJ_PATH=.\Obj
INC_PATH=.\Include
LIB_PATH=.\Lib
C_INC_PATH=C:\Sonix\SN8_C_~1.297\C\include
OUT_PATH=.\Lib
VPATH=.\:$(OBJ_PATH):$(LIB_PATH):$(INC_PATH):$(C_INC_PATH):$(OUT_PATH)

# Define Option Flags
COMPILER_FLAGS = -target=SN8P2501D -INI="C:\Sonix\SN8_C_~1.297\Bin\Build\SN8P2600.ini" -PROJECTNAME=".\u_faRe.prj" -WL=0 -Chip_Series=2 -A -g -I.\Include -IC:\Sonix\SN8_C_~1.297\C\include -NoCALLHL -NoMUL -NoHL -NoX -PUSH2 -NoGlobalOpt -tempdir="$(OBJ_PATH)"  -cpp_skip_asm -DICE_Mode=0
GMA_FLAGS = /INI:"SN8P2600.ini"  /MACHINE:SN8P2501D  /Chip_Series:2 /NOPeephole: /PATH:".\Include" /PROJECTNAME:".\u_faRe.prj" /WL:0 /DEFINE:ICE_Mode=0 /DEFINE:SN8P2501D=1  /OutputPath:"$(OBJ_PATH)" 
LINK_FLAGS = /MACHINE:SN8P2501D /INI:"SN8P2600.ini"    /OutputFile:"$(OUT_PATH)\u_faRe.lib" /PROJECTNAME:".\u_faRe.prj"
LINK_DEP_FILES =  .\Obj\u_board.o  \

# Define Rule
$(OBJ_PATH)\u_board.asm: .\Src\u_board.c $(C_INC_PATH)\SN8P2501D.h $(PRJ_PATH)\u_faRe.cfg .\Src\global.h
	@$(COMPILER) $(COMPILER_FLAGS) -o $@ $^ 

$(OBJ_PATH)\u_board.o: $(OBJ_PATH)\u_board.asm $(PRJ_PATH)\u_faRe.cfg
	@$(GMA) $(GMA_FLAGS) /CSource: /CASE: $< 

$(OUT_PATH)\u_faRe.lib: $(LINK_DEP_FILES)
	@$(LINKER) $(LINK_FLAGS) $(LINK_DEP_FILES) 

# Define Clean Rule
Clean:
	@del /F /Q $(OBJ_PATH)\*.*;
	@if EXIST .\u_faRe.prj.stb del .\u_faRe.prj.stb;
	@if EXIST .\u_faRe.lib del .\u_faRe.lib;
	@if EXIST $(OUT_PATH)\u_faRe.lib del $(OUT_PATH)\u_faRe.lib;

# Don't keep invalid files, command line must return non-zero(1 or 2) value 
# to validate delete on error mechanism 
# else return 0 for success

.DELETE_ON_ERROR:

Begin: 

Build: Begin All 

Rebuild: Clean Build 

All:$(OUT_PATH)\u_faRe.lib
