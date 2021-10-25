#! This file holds project-specific rules and logic to run static analyzers/linters on the code



#! Derive the list of linter warnings output files, from the the of sources
LINT = ${SRCS:%.c=$(LINTDIR)%.html}



$(LINTDIR)%.html: $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Linting file: "$@" -> "
	@$(CC) $(CFLAGS) -c $< -I$(HDRDIR) 2> $@
	@printf $(C_GREEN)"OK!"$(C_RESET)"\n"



.PHONY:\
lint # Runs a linter on all source files, giving useful additional warnings
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



PCLP				= /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/pclp32.exe
PCLP_SETUP =python3.8 /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/config/pclp_config.py
PCLP_IMPOSTER		= /cygdrive/d/Lexou/Projects/_C/pc-lint/windows/config/imposter
PCLP_IMPOSTER_LOG	= pclint_imposter_log.txt
PCLP_LOG			= pclint_log.txt
PCLP_CONFIG			= pclint_config
PCLP_PROJECT		= pclint_project

lint-pclint-setup:
	$(PCLP_SETUP) \
		--compiler=$(CC) \
		--compiler-bin=/usr/bin/$(CC) \
		--compiler-options="$(CFLAGS)" \
		--config-output-lnt-file=$(PCLP_CONFIG).lnt \
		--config-output-header-file=$(PCLP_CONFIG).h \
		--generate-compiler-config
	@export IMPOSTER_LOG=$(PCLP_IMPOSTER_LOG)
	@$(CC) $(CFLAGS) $(PCLP_IMPOSTER).c -o $(PCLP_IMPOSTER)
	@$(PCLP_IMPOSTER) $(CFLAGS) $(SRCS) -o $@ $(HDRDIR) $(LIBS)
	$(PCLP_SETUP) \
		--compiler=$(CC) \
		--imposter-file=$(PCLP_IMPOSTER_LOG) \
		--config-output-lnt-file=$(PCLP_PROJECT).lnt \
		--generate-project-config
	@rm $(PCLP_IMPOSTER_LOG)

# pc-lint: https://gimpel.com/
lint-pclint:
	@printf "Running linter: "
	@$(PCLP) -width"(120,4)" -format="%(%f:%l%):\n[%n]->%t: %m" -w2 \
		-e438 -e534 -e641 -e655 -e695 -e835 -e2445 \
		$(PCLP_CONFIG).lnt $(PCLP_PROJECT).lnt > $(PCLP_LOG)
	@printf $(C_GREEN)"SUCCESS"$(C_RESET)": output file is "$(PCLP_LOG)"\n"



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
