#! This file holds rules to clean up the project folder, deleting generated files, etc



.PHONY:\
clean #! Deletes any intermediary build files
clean: \
clean-build-obj \
clean-build-dep \
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):clean-tests-obj \
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):clean-tests-dep \



.PHONY:\
clean-all #! Deletes every generated file
clean-all: \
clean-build \
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):clean-tests \
clean-obj \
clean-bin \



.PHONY:\
clean-obj #! Deletes the ./obj folder
clean-obj: \
clean-build-obj \
clean-build-dep \
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):clean-tests-obj \
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):clean-tests-dep
	@$(call print_message,"Deleting "$(OBJDIR)" folder...")
	@rm -rf $(OBJDIR)

.PHONY:\
clean-bin #! Deletes the ./bin folder
clean-bin: \
clean-build-bin \
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):clean-tests-bin
	@$(call print_message,"Deleting "$(BINDIR)" folder...")
	@rm -rf $(BINDIR)

.PHONY:\
clean-log #! Deletes the ./log folder
clean-log:
	@$(call print_message,"Deleting "$(LOGDIR)" folder...")
	@rm -rf $(LOGDIR)
