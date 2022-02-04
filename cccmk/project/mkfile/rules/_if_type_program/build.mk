#! This file holds C-specific rules to build a program



#! Derive list of compiled object files (.o) from list of srcs
OBJS := $(SRCS:%.c=$(OBJDIR)%.o)

#! Derive list of dependency files (.d) from list of srcs
DEPS := $(OBJS:.o=.d)

# here we add dependency library linking flags for each package
LDLIBS := $(LDLIBS) \
	$(foreach i,$(PACKAGES), $(PACKAGE_$(i)_LINK))

# here we add include header folders for each package
INCLUDES := $(INCLUDES) \
	$(foreach i,$(PACKAGES), -I$(PACKAGE_$(i)_INCLUDE))



.PHONY:\
build-debug #! Builds the program, in 'debug' mode (with debug flags and symbol-info)
build-debug: MODE = debug
build-debug: CFLAGS += $(CFLAGS_DEBUG)
build-debug: $(NAME)

.PHONY:\
build-release #! Builds the program, in 'release' mode (with optimization flags)
build-release: MODE = release
build-release: CFLAGS += $(CFLAGS_RELEASE)
build-release: $(NAME)



#! Compiles object files from source files
$(OBJDIR)%.o : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file: $@ -> "
	@$(CC) -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Compiles the project executable
$(NAME): $(OBJS)
	@printf "Compiling program: $@ -> "
	@$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
	@mkdir -p $(BINDIR)$(OSMODE)/
	@cp -f $(NAME) $(BINDIR)$(OSMODE)/
	@$(foreach i,$(PACKAGES), cp -f $(PACKAGE_$(i)_BIN)* $(BINDIR)$(OSMODE)/ ;)



# The following line is for `.d` dependency file handling
-include $(DEPS)



.PHONY:\
mkdir-build #! Creates all the build folders in the ./bin folder (according to `OSMODES`)
mkdir-build:
	@$(call print_message,"Creating build folders...")
	@$(foreach i,$(OSMODES), mkdir -p $(BINDIR)$(i) ;)



.PHONY:\
clean-build #! Deletes all intermediary build-related files
clean-build: \
clean-build-obj \
clean-build-dep \
clean-build-bin \

.PHONY:\
clean-build-obj #! Deletes all .o build object files
clean-build-obj:
	@$(call print_message,"Deleting all build .o files...")
	@rm -f $(OBJS)

.PHONY:\
clean-build-dep #! Deletes all .d build dependency files
clean-build-dep:
	@$(call print_message,"Deleting all build .d files...")
	@rm -f $(DEPS)

.PHONY:\
clean-build-bin #! Deletes all build binaries
clean-build-bin:
	@$(call print_message,"Deleting program: $(NAME)")
	@rm -f $(NAME)



.PHONY:\
prereq-build #! Checks prerequisite installs to build the program
prereq-build:
	@-$(call check_prereq,'(build) C compiler: $(CC)',\
		$(CC) --version,\
		$(call install_prereq,$(CC)))
