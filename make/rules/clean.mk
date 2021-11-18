#! This file holds rules to clean up the project folder, deleting generated files, etc



.PHONY:\
clean #! Deletes all intermediary build files
clean:
	@$(call print_message,"Deleting all .o files...")
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@$(call print_message,"Deleting all .d files...")
	@rm -f $(DEPS)
	@rm -f $(TEST_DEPS)
	@rm -f *.d



.PHONY:\
clean-exe #! Deletes any libraries/executables
clean-exe:
	@rm -f $(NAME)
	@rm -f $(NAME).*
	@$(call print_message,"Deleting library: "$(NAME_STATIC)"")
	@rm -f $(NAME_STATIC)
	@$(call print_message,"Deleting library: "$(NAME_DYNAMIC)"")
	@rm -f $(NAME_DYNAMIC)
	@$(call print_message,"Deleting test program: "$(NAME_TEST)"")
	@rm -f $(NAME_TEST)
	@rm -f $(NAME_TEST).d

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
clean-logs #! Deletes the ./log folder
clean-logs:
	@$(call print_message,"Deleting "$(LOGDIR)" folder...")
	@rm -rf $(LOGDIR)

.PHONY:\
clean-lint #! Deletes the ./lint folder
clean-lint:
	@$(call print_message,"Deleting "$(LINTDIR)" folder...")
	@rm -rf $(LINTDIR)



.PHONY:\
clean-full #! Deletes every generated file
clean-full: clean clean-exe
