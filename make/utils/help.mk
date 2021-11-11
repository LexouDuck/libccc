#! This file holds the various rules which provide documentation of the build system itself



ifeq ($(MKFILE_PATH),)
$(error To use the 'help.mk' utils, you must set the 'MKFILE_PATH' variable)
endif

#! The list of files included by the root-level makefile (and any sub-included)
MKFILES :=            $(shell cat $(MKFILE_PATH) | grep '^include\b' | cut -d' ' -f 2-)
MKFILES := $(MKFILES) $(shell cat $(MKFILES)     | grep '^include\b' | cut -d' ' -f 2-)
$(eval MKFILES := $(MKFILE_PATH) $(MKFILES))

#! The char column at which the doc comments should show up
COLUMN_DOC = 30



.PHONY:\
help #! Displays list of any targets which are documented
help:
	@for i in $(MKFILES) ; do \
		awk -f "make/utils/help-targets.awk" $$i | expand -t $(COLUMN_DOC) ; \
	done



.PHONY:\
help-makefiles #! Displays list of all makefiles (with brief description, if available)
help-makefiles:
	@for i in $(MKFILES) ; do \
		printf "$$i""\t" | expand -t 40 ; \
		awk -f "make/utils/help-makefiles.awk" $$i ; \
	done

.PHONY:\
help-variables #! Displays list of variables in the makefile which are documented
help-variables:
	@for i in $(MKFILES) ; do \
		awk -f "make/utils/help-variables.awk" $$i | expand -t $(COLUMN_DOC) ; \
	done

.PHONY:\
help-targets #! Displays list of "PHONY" targets, with description if available
help-targets:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk -f "make/utils/help-targets.awk" $$i | expand -t $(COLUMN_DOC) ; \
	done



.PHONY:\
help-all #! Displays all makefiles, variables and targets, with any available documentation
help-all:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk -v color=$(C_DARK) -v reset=$(C_RESET) -f "make/utils/help-makefiles.awk" $$i | expand -t $(COLUMN_DOC) ; \
		printf $(C_DARK)"# Documented variables:"$(C_RESET)"\n" ; \
		awk -v color=$(C_DARK) -v reset=$(C_RESET) -f "make/utils/help-variables.awk" $$i | expand -t $(COLUMN_DOC) ; \
		printf $(C_DARK)"# Documented targets:"$(C_RESET)"\n" ; \
		awk -v color=$(C_DARK) -v reset=$(C_RESET) -f "make/utils/help-targets.awk"   $$i | expand -t $(COLUMN_DOC) ; \
	done



.PHONY:\
help-debug #! Displays the entire makefile database
help-debug:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \

.PHONY:\
help-debug-makefiles #! Displays list of all variables used each included makefile
help-debug-makefiles:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk -v RS=" " '\
		{ \
			remaining = $$0; \
			while (length(remaining) > 0) \
			{ \
				if (match(remaining, /\$$\([a-zA-Z0-9_]+\)/) != 0) \
				{ \
					print "uses " substr(remaining, RSTART, RLENGTH); \
					remaining = substr(remaining, RSTART + RLENGTH); \
				} \
				else remaining = ""; \
			} \
		} \
		' $$i \
		| sort \
		| uniq ; \
	done

.PHONY:\
help-debug-variables #! Displays list of all variables in the makefile, with their respective values
help-debug-variables:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| grep '=' \
		| grep -v '^#' \
		| grep -v '^\t' \
		| sort

# see https://stackoverflow.com/questions/4219255/how-do-you-get-the-list-of-targets-in-a-makefile
.PHONY:\
help-debug-targets #! Displays list of all available targets in this Makefile, sorted in alphabetical order
help-debug-targets:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ /^[#.]/) {print $$1}}' \
		| sort \
		| egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
