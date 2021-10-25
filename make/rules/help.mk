#! This file holds the various rules which provide documentation of the build system itself



#! The list of files included by the root-level makefile
MKFILES := $(MKFILE_PATH) $(shell cat $(MKFILE_PATH) | grep include | cut -d' ' -f 2-)

#! The char column at which the doc comments should show up
COLUMN_DOC = 30



.PHONY:\
help # Displays all variables and targets which are documented
help:
	@printf $(C_MAGENTA)"\n|\n|> Documentation: list of makefiles""\n|\n"$(C_RESET)
	@$(MAKE) help-files
	@printf $(C_MAGENTA)"\n|\n|> Documentation: list of variables""\n|\n"$(C_RESET)
	@$(MAKE) help-variables
	@printf $(C_MAGENTA)"\n|\n|> Documentation: list of targets  ""\n|\n"$(C_RESET)
	@$(MAKE) help-targets



.PHONY:\
help-files # Displays list of all makefiles, with description if available
help-files:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk '\
		{\
			if (/^#!/) { print }\
			else if (/^#/) {}\
			else { exit 0 }\
		}' $$i ; \
	done



.PHONY:\
help-variables # Displays list of variables in the makefile which are documented
help-variables:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk \
		-v doc="" \
		-v prevline="" \
		'\
		match($$0, /#!</)    { doc = substr($$0, RSTART + 4); }\
		match($$0, /#![^<]/) { doc = substr($$0, RSTART + 3); }\
		{\
			if (!$$0) { doc = ""; }\
			else if (/=/)\
			{\
				if (doc != "")\
					print $$1 "\t# " doc;\
				doc = "";\
			}\
			prevline = $$0;\
		}' $$i \
		| expand -t$(COLUMN_DOC) ; \
	done

.PHONY:\
help-all-variables # Displays list of all variables in the makefile, with their respective values
help-all-variables:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| grep '=' \
		| grep -v '^#' \
		| grep -v '^\t' \
		| sort



.PHONY:\
help-targets # Displays list of "PHONY" targets, with description if available
help-targets:
	@for i in $(MKFILES) ; do \
		printf "\n"$(C_CYAN)"$$i"$(C_RESET)"\n" ; \
		awk \
		-v phony=0 \
		'\
		{\
			if (phony)\
			{\
				sub(/#/,"\t#");\
				phony = 0;\
				print "make " $$0;\
			}\
			else if (/^\.PHONY:\\/)\
			{\
				phony = 1;\
			}\
		}' $$i \
		| expand -t$(COLUMN_DOC) ; \
	done

# see https://stackoverflow.com/questions/4219255/how-do-you-get-the-list-of-targets-in-a-makefile
.PHONY:\
help-all-targets # Displays list of all available targets in this Makefile, sorted in alphabetical order
help-all-targets:
	@LC_ALL=C $(MAKE) -prRq -f $(MKFILE_PATH) : 2>/dev/null \
		| awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' \
		| sort \
		| egrep -v -e '^[^[:alnum:]]' -e '^$@$$'
