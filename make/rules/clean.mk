#! This file holds rules to clean up the project folder, deleting generated files, etc



.PHONY:\
clean #! Deletes all intermediary build files
clean:
	@printf $(IO_CYAN)"Deleting all .o files..."$(IO_RESET)"\n"
	@rm -f $(OBJS)
	@rm -f $(TEST_OBJS)
	@printf $(IO_CYAN)"Deleting all .d files..."$(IO_RESET)"\n"
	@rm -f $(DEPS)
	@rm -f $(TEST_DEPS)
	@rm -f *.d



.PHONY:\
clean-exe #! Deletes any libraries/executables
clean-exe:
	@rm -f $(NAME)
	@rm -f $(NAME).*
	@printf $(IO_CYAN)"Deleting library: "$(NAME_STATIC)""$(IO_RESET)"\n"
	@rm -f $(NAME_STATIC)
	@printf $(IO_CYAN)"Deleting library: "$(NAME_DYNAMIC)""$(IO_RESET)"\n"
	@rm -f $(NAME_DYNAMIC)
	@printf $(IO_CYAN)"Deleting test program: "$(NAME_TEST)""$(IO_RESET)"\n"
	@rm -f $(NAME_TEST)
	@rm -f $(NAME_TEST).d

.PHONY:\
clean-obj #! Deletes the ./obj folder
clean-obj:
	@printf $(IO_CYAN)"Deleting "$(OBJDIR)" folder..."$(IO_RESET)"\n"
	@rm -rf $(OBJDIR)

.PHONY:\
clean-bin #! Deletes the ./bin folder
clean-bin:
	@printf $(IO_CYAN)"Deleting "$(BINDIR)" folder..."$(IO_RESET)"\n"
	@rm -rf $(BINDIR)

.PHONY:\
clean-logs #! Deletes the ./log folder
clean-logs:
	@printf $(IO_CYAN)"Deleting "$(LOGDIR)" folder..."$(IO_RESET)"\n"
	@rm -rf $(LOGDIR)

.PHONY:\
clean-lint #! Deletes the ./lint folder
clean-lint:
	@printf $(IO_CYAN)"Deleting "$(LINTDIR)" folder..."$(IO_RESET)"\n"
	@rm -rf $(LINTDIR)



.PHONY:\
clean-full #! Deletes every generated file
clean-full: clean clean-exe
