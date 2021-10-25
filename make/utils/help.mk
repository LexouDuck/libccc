#! This file holds the various rules which provide documentation of the build system itself



#! The list of files included by the root-level makefile
MKFILES := $(MKFILE_PATH) $(shell cat $(MKFILE_PATH) | grep include | cut -d' ' -f 2-)

#! The char column at which the doc comments should show up
COLUMN_DOC = 30



.PHONY:\
help # Displays list of any targets which are documented
help:
	@for i in $(MKFILES) ; do \
		awk -f "make/utils/help-targets.awk" $$i | expand -t$(COLUMN_DOC) ; \
	done



.PHONY:\
help-makefiles # Displays list of all makefiles (with brief description, if available)
help-makefiles:
	@for i in $(MKFILES) ; do \
		printf "$$i""\t" | expand -t40 ; \
		awk -f "make/utils/help-makefiles.awk" $$i ; \
	done

.PHONY:\
help-variables # Displays list of variables in the makefile which are documented
help-variables:
	@for i in $(MKFILES) ; do \
		awk -f "make/utils/help-variables.awk" $$i | expand -t$(COLUMN_DOC) ; \
	done

.PHONY:\
help-targets # Displays list of "PHONY" targets, with description if available
help-targets:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk -f "make/utils/help-targets.awk" $$i | expand -t$(COLUMN_DOC) ; \
	done



.PHONY:\
help-all # Displays all makefiles, variables and targets, with any available documentation
help-all:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk -f "make/utils/help-makefiles.awk" $$i | expand -t$(COLUMN_DOC) ; \
		awk -f "make/utils/help-variables.awk" $$i | expand -t$(COLUMN_DOC) ; \
		awk -f "make/utils/help-targets.awk"   $$i | expand -t$(COLUMN_DOC) ; \
	done



.PHONY:\
help-debug # Displays the entire makefile database
help-debug:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \

.PHONY:\
help-debug-variables # Displays list of all variables in the makefile, with their respective values
help-debug-variables:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| grep '=' \
		| grep -v '^#' \
		| grep -v '^\t' \
		| sort

# see https://stackoverflow.com/questions/4219255/how-do-you-get-the-list-of-targets-in-a-makefile
.PHONY:\
help-debug-targets # Displays list of all available targets in this Makefile, sorted in alphabetical order
help-debug-targets:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ /^[#.]/) {print $$1}}' \
		| sort \
		| egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
