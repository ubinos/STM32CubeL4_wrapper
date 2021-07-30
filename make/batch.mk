###############################################################################

%:
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=stm32cubel4_stm32l475eiot01_baremetal
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../config CONFIG_NAME=stm32cubel4_stm32l476geval_baremetal
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../app CONFIG_NAME=mybsp_stm32l475eiot01
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../app CONFIG_NAME=cli_tester_stm32l276geval_extdtty
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""
	@echo ""
	make -f makefile.mk $@ CONFIG_DIR=../app CONFIG_NAME=cli_tester_nucleol476rg_extdtty
	@echo ""
	@echo ""


	@echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
	@echo ""

###############################################################################


