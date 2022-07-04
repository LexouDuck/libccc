#! This file holds rules which perform some initial project/repo setup



.PHONY:\
init #! Performs initial project setup (should be executed once, after cloning the repo)
init:
	@$(call print_message,"Setting up project...")
	@mkdir -p $(LIBDIR)
	@mkdir -p $(DOCDIR)
	@mkdir -p $(TESTDIR)
	@mkdir -p $(GITHOOKSDIR)
	@mkdir -p $(LISTSDIR)
	@$(GIT) submodule update --init --recursive
	@$(GIT) config core.hooksPath $(GITHOOKSDIR)

# TODO 'configure' rule, for easier cross-platform setup ?
