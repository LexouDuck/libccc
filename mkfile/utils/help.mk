#! This file holds the various rules which provide documentation of the build system itself



ifeq ($(MKFILE_PATH),)
$(error To use the 'help.mk' utils, you must set the 'MKFILE_PATH' variable)
endif

#! The list of files included by the root-level makefile (and any sub-included)
MKFILES :=            $(shell cat $(MKFILE_PATH) | grep '^include\b' | cut -d' ' -f 2-)
$(eval MKFILES :=  $(MKFILE_PATH) $(MKFILES))
MKFILES := $(MKFILES) $(shell cat $(MKFILES)     | grep '^include\b' | cut -d' ' -f 2-)
$(eval MKFILES := $(MKFILES))
MKFILES := $(shell echo "$(MKFILES)" | tr '[:space:]' '\n' | awk '!x[$$0]++')
# make all paths be relative to project root folder
MKFILES := $(patsubst $(CURRENT_DIR)/%,./%, $(MKFILES))


#! Set the root project directory, if not yet set (ROOTDIR is necessary for complex projects)
ROOTDIR ?= ./

#! The char column at which the doc comments should show up
COLUMN_DOC = 30



.PHONY:\
help #! Displays list of included makefiles, with any targets that are documented
help:
	@for i in $(MKFILES) ; do \
		printf "\n"$(IO_CYAN)"$$i"$(IO_RESET)"\n" ; \
		awk -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-targets.awk" $$i | expand -t $(COLUMN_DOC) ; \
	done



.PHONY:\
help-all #! Displays all makefiles, variables and targets, with any available documentation
help-all:
	@for i in $(MKFILES) ; do \
		printf "\n"$(IO_CYAN)"$$i"$(IO_RESET)"\n" ; \
		awk -v color=$(IO_DARK) -v reset=$(IO_RESET) -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-makefiles.awk" $$i | expand -t $(COLUMN_DOC) ; \
		printf $(IO_DARK)"# Documented variables:"$(IO_RESET)"\n" ; \
		awk -v color=$(IO_DARK) -v reset=$(IO_RESET) -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-variables.awk" $$i | expand -t $(COLUMN_DOC) ; \
		printf $(IO_DARK)"# Documented targets:"$(IO_RESET)"\n" ; \
		awk -v color=$(IO_DARK) -v reset=$(IO_RESET) -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-targets.awk"   $$i | expand -t $(COLUMN_DOC) ; \
	done



.PHONY:\
help-makefiles #! Displays list of all makefiles (with brief description, if available)
help-makefiles:
	@for i in $(MKFILES) ; do \
		printf "$$i""\t" | expand -t $(COLUMN_DOC) ; awk -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-makefiles.awk" $$i | head -1 ; \
	done

.PHONY:\
help-variables #! Displays list of makefile variables (with brief description, if available)
help-variables:
	@for i in $(MKFILES) ; do \
		awk -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-variables.awk" $$i | expand -t $(COLUMN_DOC) ; \
	done

.PHONY:\
help-targets #! Displays list of ".PHONY" targets (with brief description, if available)
help-targets:
	@for i in $(MKFILES) ; do \
		awk -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-targets.awk" $$i | expand -t $(COLUMN_DOC) ; \
	done



# Makefile debugging utils



.PHONY:\
help-debug #! Displays useful debugging info for each makefile
help-debug:
	@for i in $(MKFILES) ; do \
		printf "\n"$(IO_CYAN)"$$i"$(IO_RESET)"\n" ; \
		awk -f "$(ROOTDIR)$(MKFILES_DIR)utils/help-debug.awk" $$i ; \
	done



# see https://stackoverflow.com/questions/4219255/how-do-you-get-the-list-of-targets-in-a-makefile
print_makefile_database = LC_ALL=C \
	$(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null



.PHONY:\
help-debug-all #! Displays the entire makefile database
help-debug-all:
	@$(call print_makefile_database)



.PHONY:\
help-debug-makefiles #! Displays list of all included makefiles (even .d files)
help-debug-makefiles:
	@$(call print_makefile_database) \
	| awk -v prev="" '{ if (/# Not a target/) { prev = $$0; } else if (prev != "") { prev = ""; print; } }' \
	| egrep -e '.(mk|d):' \
	| sed 's/://g' \
	| sort \

.PHONY:\
help-debug-variables #! Displays list of all variables in the makefile, with their respective values
help-debug-variables:
	@$(call print_makefile_database) \
	| grep '=' \
	| grep -v '^#' \
	| grep -v '^\t' \
	| sort \

.PHONY:\
help-debug-targets #! Displays list of all available targets in this Makefile, sorted in alphabetical order
help-debug-targets:
	@$(call print_makefile_database) \
	| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ /^[#.]/) {print $$1}}' \
	| egrep -v -e '^[^[:alnum:]]' -e '^$@$$' \
	| sort \
