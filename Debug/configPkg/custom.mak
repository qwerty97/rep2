## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em3 linker.cmd package/cfg/rfExamples_pem3.oem3

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/rfExamples_pem3.xdl
	$(SED) 's"^\"\(package/cfg/rfExamples_pem3cfg.cmd\)\"$""\"D:/Work/bcon/dev-arm/workspace_ti_ccs/1rfPacketTx_CC1310_widacos/Debug/configPkg/\1\""' package/cfg/rfExamples_pem3.xdl > $@
	-$(SETDATE) -r:max package/cfg/rfExamples_pem3.h compiler.opt compiler.opt.defs
