#! This file holds C-specific rules to build a library



#! Derive list of compiled object files (.o) from list of srcs
OBJS := $(SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS := $(OBJS:.o=.d)

# here we add linked library flags for each package
LDLIBS := $(LDLIBS) \
	$(foreach i,$(PACKAGES_LINK),$($(i)))

# here we add include header folders for each package
INCLUDES := $(INCLUDES) \
	$(foreach i,$(PACKAGES_INCLUDE),-I$($(i)))



.PHONY:\
build-debug #! Builds the library, in 'debug' mode (with debug flags and symbol-info)
build-debug: MODE = debug
build-debug: CFLAGS += $(CFLAGS_DEBUG)
build-debug: $(NAME)

.PHONY:\
build-release #! Builds the library, in 'release' mode (with optimization flags)
build-release: MODE = release
build-release: CFLAGS += $(CFLAGS_RELEASE)
build-release: $(NAME)



#! Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: "$@" -> "
	@$(CC) -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Compiles the project executable
$(NAME): $(OBJS)
	@printf "Compiling program: "$(NAME)" -> "
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) $^ $(LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



# The following line is for `.d` dependency file handling
-include $(DEPS)
