#! This file holds rules to clean up the project folder, deleting generated files, etc



.PHONY:\
clean #! Deletes any intermediary build files
clean: \
	clean-all-obj \
	clean-all-dep \



.PHONY:\
clean-all #! Deletes every generated file
clean-all: \
	clean-build \
%%if tracked(mkfile/rules/_if_flag_testsuite/build-tests.mk):	clean-tests \
	clean-obj \
	clean-bin \



.PHONY:\
clean-all-obj #! Deletes all .o files
clean-all-obj: \
	clean-build-obj \
%%if tracked(mkfile/rules/_if_flag_testsuite/build-tests.mk):	clean-tests-obj \

.PHONY:\
clean-all-dep #! Deletes all .d files
clean-all-dep: \
	clean-build-dep \
%%if tracked(mkfile/rules/_if_flag_testsuite/build-tests.mk):	clean-tests-dep \

.PHONY:\
clean-all-bin #! Deletes any built libraries/executables
clean-all-bin: \
	clean-build-bin \
%%if tracked(mkfile/rules/_if_flag_testsuite/build-tests.mk):	clean-tests-bin \



.PHONY:\
clean-obj #! Deletes the ./obj folder
clean-obj:
	@$(call print_message,"Deleting "$(OBJDIR)" folder...")
	@rm -rf $(OBJDIR)

.PHONY:\
clean-bin #! Deletes the ./bin folder
clean-bin:
	@$(call print_message,"Deleting "$(BINDIR)" folder...")
	@rm -rf $(BINDIR)

.PHONY:\
clean-log #! Deletes the ./log folder
clean-log:
	@$(call print_message,"Deleting "$(LOGDIR)" folder...")
	@rm -rf $(LOGDIR)
