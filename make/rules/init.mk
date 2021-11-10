#! This file holds rules which perform some initial project/repo setup



.PHONY:\
init # Should be executed once, after cloning the repo
init:
	@git submodule update --init --recursive
	@git config core.hooksPath $(GITHOOKSDIR)

# TODO 'configure' rule, for easier cross-platform setup ?
