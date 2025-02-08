#! This file holds project-specific rules and logic to run static analyzers/linters on the code



#! Derive the list of linter warnings output files, from the the of sources
LINT = $(SRCS:$(SRCDIR)%.c=$(LINTDIR)%.html)



$(LINTDIR)%.html: $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Linting file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR)
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"
ifneq ($(findstring clang,$(CC)),)
	@mv ./*.plist $(@D) 2> /dev/null || exit 0
endif



.PHONY:\
lint #! Runs a linter on all source files, giving useful additional warnings
lint: BUILDMODE = debug
ifeq ($(CC),)
$(warning C compiler '$$CC' environment variable has not been set, cannot estimate static analyzer linting options)
#$(error Unknown compiler "$(CC)", cannot estimate static analyzer linting options)
endif
ifneq ($(findstring gcc,$(CC)),)
lint: CFLAGS += -fanalyzer
endif
ifneq ($(findstring clang,$(CC)),)
lint: CFLAGS += -Wthread-safety --analyze --analyzer-output html
endif
lint: $(LINT)
	@find $(LINTDIR) -size 0 -print -delete
	@$(call print_success,"Linting finished.")



CPPCHECK = cppcheck
CPPCHECK_FLAGS = 

.PHONY:\
lint-cppcheck #! Runs code linter on source code: cppcheck (http://cppcheck.sourceforge.net/)
lint-cppcheck:
	@$(CPPCHECK) $(SRCDIR) $(HDRDIR) $(CPPCHECK_FLAGS) \
		--quiet --std=c11 --enable=all \
		-DTRUE=1 -DFALSE=0 -DERROR=-1 -DOK=0 -D__GNUC__ \
		--suppress=variableScope \
		--suppress=unusedFunction \
		--suppress=memleak \
		--template="-[{severity}]\t{file}:{line}\t->\t{id}: {message}" \
		--template-location="  -> from:\t{file}:{line}\t->\t{info}"



SPLINT = splint
SPLINT_FLAGS = 

.PHONY:\
lint-splint #! Runs code linter on source code: splint (http://splint.org/)
lint-splint:
	@$(call print_error,"splint not configured yet") # $(SPLINT) $(SPLINT_FLAGS)



.PHONY:\
clean-lint #! Deletes the ./lint folder
clean-lint:
	@$(call print_message,"Deleting "$(LINTDIR)" folder...")
	@rm -rf $(LINTDIR)



.PHONY:\
prereq-lint #! Checks prerequisite installs to run the linters/static analyzers
prereq-lint:
	@-$(call check_prereq,'(lint) cppcheck',\
		cppcheck --version,\
		$(call install_prereq,cppcheck))
	@-$(call check_prereq,'(lint) splint',\
		splint --help version,\
		$(call install_prereq,splint))
