# This file holds C-specific rules for auto-updating the build system, or its dependencies



.PHONY:\
update-lists # Updates the lists of source/header files
update-lists:
	@find $(HDRDIR)   -name "*.h" | sort | sed "s|$(HDRDIR)/||g"         > $(HDRSFILE)
	@find $(SRCDIR)   -name "*.c" | sort | sed "s|$(SRCDIR)/||g"         > $(SRCSFILE)
	@find $(TEST_DIR) -name "*.h" | sort | sed "s|//|/|g" | grep -v "/_" > $(HDRSFILE_TEST)
	@find $(TEST_DIR) -name "*.c" | sort | sed "s|//|/|g" | grep -v "/_" > $(SRCSFILE_TEST)



# TODO: package manager update logic (for submodules, and wget/curl packages)
#
#GIT_SUBMODULES = $(shell cat .gitmodules | grep "\[submodule" | cut -d'"' -f 2)
#
#.PHONY:\
#update-submodules # Updates git submodules
#update-submodules:
#	@for i in $(GIT_SUBMODULES) ; do \
#		cd $$i ; \
#		if git status | grep -q "HEAD detached" ; then \
#			printf $(C_YELLOW)"WARNING"$(C_RESET)": Your git submodule "$$i" is in detached HEAD state""\n" ; \
#			printf "You need to manually go into the submodule folder and do 'git checkout master',""\n" ; \
#			printf "after making sure that you have no uncommitted/unpushed local working changes.""\n" ; \
#		fi ; \
#		git pull ; \
#		cd - ; \
#	done
