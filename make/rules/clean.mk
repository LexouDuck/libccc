#! This file holds rules to clean up the project folder, deleting generated files, etc



.PHONY:\
clean # Deletes all intermediary build files
clean:
	@printf "Deleting all .o files...\n"
	@rm -f $(OBJS)
	@rm -f $(OBJS_TEST)
	@printf "Deleting all .d files...\n"
	@rm -f $(DEPS)
	@rm -f $(DEPS_TEST)
	@rm -f *.d



.PHONY:\
clean-exe # Deletes any libraries/executables
clean-exe:
	@rm -f $(NAME).*
	@printf "Deleting library: "$(NAME_STATIC)"\n"
	@rm -f $(NAME_STATIC)
	@printf "Deleting library: "$(NAME_DYNAMIC)"\n"
	@rm -f $(NAME_DYNAMIC)
	@printf "Deleting program: "$(NAME_TEST)"\n"
	@rm -f $(NAME_TEST)
	@rm -f $(NAME_TEST).d

.PHONY:\
clean-obj # Deletes the ./obj folder
clean-obj:
	@printf "Deleting "$(OBJDIR)" folder...\n"
	@rm -rf $(OBJDIR)

.PHONY:\
clean-bin # Deletes the ./bin folder
clean-bin:
	@printf "Deleting "$(BINDIR)" folder...\n"
	@rm -rf $(BINDIR)

.PHONY:\
clean-logs # Deletes the ./log folder
clean-logs:
	@printf "Deleting "$(LOGDIR)" folder...\n"
	@rm -rf $(LOGDIR)

.PHONY:\
clean-lint # Deletes the ./lint folder
clean-lint:
	@printf "Deleting "$(LINTDIR)" folder...\n"
	@rm -rf $(LINTDIR)



.PHONY:\
clean-full # Deletes every generated file
clean-full: clean clean-exe
