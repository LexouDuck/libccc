#! This file holds rules to clean up the project folder, deleting generated files, etc



.PHONY:\
clean #! Deletes any intermediary build files
clean: \
clean-build-obj \
clean-build-dep \
clean-tests-obj \
clean-tests-dep \



.PHONY:\
clean-all #! Deletes every generated file
clean-all: \
clean-build \
clean-tests \
clean-obj \
clean-bin \



.PHONY:\
clean-obj #! Deletes the ./obj folder
clean-obj: \
clean-build-obj \
clean-build-dep \
clean-tests-obj \
clean-tests-dep
	@$(call print_message,"Deleting "$(OBJDIR)" folder...")
	@rm -rf $(OBJDIR)

.PHONY:\
clean-bin #! Deletes the ./bin folder
clean-bin: \
clean-build-bin \
clean-tests-bin
	@$(call print_message,"Deleting "$(BINDIR)" folder...")
	@rm -rf $(BINDIR)

.PHONY:\
clean-log #! Deletes the ./log folder
clean-log:
	@$(call print_message,"Deleting "$(LOGDIR)" folder...")
	@rm -rf $(LOGDIR)
