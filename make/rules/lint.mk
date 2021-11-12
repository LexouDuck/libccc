#! This file holds project-specific rules and logic to run static analyzers/linters on the code



#! Derive the list of linter warnings output files, from the the of sources
LINT = $(SRCS:%.c=$(LINTDIR)%.html)



$(LINTDIR)%.html: $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Linting file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) 2> $@
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



.PHONY:\
lint #! Runs a linter on all source files, giving useful additional warnings
lint: MODE = debug
ifeq (gcc,$(findstring gcc,$(CC)))
lint: CFLAGS += -fanalyzer
else ifeq (clang,$(findstring clang,$(CC)))
lint: CFLAGS += -Wthread-safety --analyze --analyzer-output text
else
$(error Unknown compiler "$(CC)", cannot estimate static analyzer linting options)
endif
lint: $(LINT)
	@find $(LINTDIR) -size 0 -print -delete
	@echo "Linting finished."



# CCPcheck: http://cppcheck.sourceforge.net/
lint-cppcheck:
	@cppcheck $(SRCDIR) $(HDRDIR) --quiet --std=c99 --enable=all \
		-DTRUE=1 -DFALSE=0 -DERROR=1 -DOK=0 -D__GNUC__ \
		--suppress=variableScope \
		--suppress=unusedFunction \
		--suppress=memleak \
		--template="-[{severity}]\t{file}:{line}\t->\t{id}: {message}" \
		--template-location="  -> from:\t{file}:{line}\t->\t{info}"



# splint: http://splint.org/
#	@splint
