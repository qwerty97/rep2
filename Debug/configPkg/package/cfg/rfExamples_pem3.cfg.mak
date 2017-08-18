# invoke SourceDir generated makefile for rfExamples.pem3
rfExamples.pem3: .libraries,rfExamples.pem3
.libraries,rfExamples.pem3: package/cfg/rfExamples_pem3.xdl
	$(MAKE) -f D:\Work\bcon\dev-arm\workspace_ti_ccs\1rfPacketTx_CC1310_widacos/src/makefile.libs

clean::
	$(MAKE) -f D:\Work\bcon\dev-arm\workspace_ti_ccs\1rfPacketTx_CC1310_widacos/src/makefile.libs clean

