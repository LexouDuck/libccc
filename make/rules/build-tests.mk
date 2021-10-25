#! This file holds C-specific rules to build a test suite program



#! Compiles object files from source files
$(OBJDIR)$(TEST_DIR)%.o: $(TEST_DIR)%.c $(HDRS_TEST)
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -c $< -o $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



#! Builds the testing/CI program
$(NAME_TEST): $(NAME_STATIC) $(NAME_DYNAMIC) $(OBJS_TEST)
	@printf "Compiling testing program: "$@" -> "
	@$(CC) $(TEST_CFLAGS) $(TEST_INCLUDEDIRS) -o $@ $(OBJS_TEST) $(TEST_LIBS)
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



# The following line is for `.d` dependency file handling
-include ${DEPS_TEST}
