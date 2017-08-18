################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
CC1310_SL_BASE.obj: ../CC1310_SL_BASE.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos" --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos" --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos/smartrf_settings" --include_path="C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="CC1310_SL_BASE.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ccfg.obj: ../ccfg.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos" --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos" --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos/smartrf_settings" --include_path="C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="ccfg.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

build-1765267903:
	@$(MAKE) -Onone -f subdir_rules.mk build-1765267903-inproc

build-1765267903-inproc: ../rfExamples.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/01.tirex-content/xdctools_3_32_00_06_core/xs" --xdcpath="C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/packages;C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/tidrivers_cc13xx_cc26xx_2_21_00_04/packages;C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/bios_6_46_01_37/packages;C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/uia_2_01_00_01/packages;C:/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M3 -p ti.platforms.simplelink:CC1310F128 -r release -c "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS" --compileOptions "-mv7M3 --code_state=16 --float_support=vfplib -me --include_path=\"D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos\" --include_path=\"D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos\" --include_path=\"D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos/smartrf_settings\" --include_path=\"C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272\" --include_path=\"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include\" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-1765267903 ../rfExamples.cfg
configPkg/compiler.opt: build-1765267903
configPkg/: build-1765267903

rfPacketTx.obj: ../rfPacketTx.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos" --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos" --include_path="D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos/smartrf_settings" --include_path="C:/ti/01.tirex-content/tirtos_cc13xx_cc26xx_2_21_00_06/products/cc13xxware_2_04_03_17272" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.3.LTS/include" --define=ccs -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="rfPacketTx.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


