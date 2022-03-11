#! This file holds rules which perform some initial project/repo setup



.PHONY:\
init #! Performs initial project setup (should be executed once, after cloning the repo)
init:
	@$(call print_message,"Setting up project...")
	@git submodule update --init --recursive
	@git config core.hooksPath $(GITHOOKSDIR)

# TODO 'configure' rule, for easier cross-platform setup ?
