################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../rfExamples.cfg 

CMD_SRCS += \
../CC1310_SL_BASE.cmd 

C_SRCS += \
../CC1310_SL_BASE.c \
../ccfg.c \
../rfPacketTx.c 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_MISC_DIRS += \
./configPkg/ 

C_DEPS += \
./CC1310_SL_BASE.d \
./ccfg.d \
./rfPacketTx.d 

GEN_OPTS += \
./configPkg/compiler.opt 

OBJS += \
./CC1310_SL_BASE.obj \
./ccfg.obj \
./rfPacketTx.obj 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

OBJS__QUOTED += \
"CC1310_SL_BASE.obj" \
"ccfg.obj" \
"rfPacketTx.obj" 

C_DEPS__QUOTED += \
"CC1310_SL_BASE.d" \
"ccfg.d" \
"rfPacketTx.d" 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

C_SRCS__QUOTED += \
"../CC1310_SL_BASE.c" \
"../ccfg.c" \
"../rfPacketTx.c" 


