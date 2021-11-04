#! This file holds rules to build dependencies (libraries, packages, binaries, etc)



.PHONY:\
packages # This rule builds/prepares the dependency external packages
packages: \
	$(addprefix package-, $(PACKAGES))



.PHONY:\
update-all # This rule update the dependency external packages to their latest versions
update-all: \
	$(addprefix update-, $(PACKAGES))



# TODO: package manager update logic (for submodules, and wget/curl packages) ?
#GIT_SUBMODULES = $(shell cat .gitmodules | grep "\[submodule" | cut -d'"' -f 2)
