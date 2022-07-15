#! This file holds scripts to generate importable .c code files from .h files which use libccc generic types


#! If not explicitly specified, use full of list of all generic headers
GENERIC_HEADERS ?= $(wildcard $(HDRDIR)libccc/monad/*.h)
GENERIC_OUTPUTS = $(GENERIC_HEADERS:%.h=%.c)

#! The file which holds the template of C code to make an importable generic-type code header
GENERIC_TEMPLATE = $(MKFILES_DIR)rules/generic.template.c

#! The AWK script which creates the final inlude-able header from the `GENERIC_TEMPLATE` file
GENERIC_AWKSCRIPT = $(MKFILES_DIR)rules/generic.template.awk



define AWKSCRIPT_GETHEADERGUARD
match($$0, /^[ \t]*#[ \t]*ifndef ($(REGEXP_C_SYMBOL))/, matched)\
{\
	print matched[1];\
	exit 0;\
}
endef

define AWKSCRIPT_GETSYMBOLS
BEGIN {\
	declaration = 0;\
	symbolcount = 0;\
	split("", symbols);\
}\
{\
	if (/^typedef\>/) declaration = 1;\
	if (/^struct\>/)  declaration = 1;\
	if (/^\}/)        declaration = 1;\
	if (declaration && match($$0, /\<(($(REGEXP_C_SYMBOL))\(($(REGEXP_C_GENERIC))\))[ \t]*(;|\(|$$)/, matched))\
	{\
		symbols[symbolcount++] = matched[1];\
		declaration = 0;\
	}\
	if (/\<_GENERIC\(\)/) declaration = 1;\
}\
END {\
	for (i in symbols)\
	{\
		symbol = substr(symbols[i], 1, index(symbols[i], "(") - 1);\
		print symbol;\
	}\
}
endef



.PHONY:\
generic #! Creates a generic import file for any files given as `GENERIC_HEADERS`
generic: \
clean-generic \
$(GENERIC_OUTPUTS)

$(HDRDIR)%.c: $(HDRDIR)%.h $(GENERIC_TEMPLATE) $(GENERIC_AWKSCRIPT)
	@if [ -z "`command -v gawk`" ]; \
	then \
		$(call print_warning,"gawk command is not installed - cannot update generic header .c include-wrapper: $@") ; \
	else \
		$(call print_message,"Generating generic import file:"$(IO_RESET)" $@") ; \
		folder="`echo './$<' | sed 's|\.h$$|/|' | sed 's|^$(HDRDIR)$(NAME)/||' `" ; \
		gawk \
			-v variables="\
				header=`echo './$<' | sed 's|$(HDRDIR)||' `;\
				header_guard=`gawk '$(AWKSCRIPT_GETHEADERGUARD)' '$<' `;\
				sources=`grep "$${folder}" $(SRCSFILE) `;\
				symbols=`gawk '$(AWKSCRIPT_GETSYMBOLS)' '$<' | uniq `;\
			" \
			-f $(GENERIC_AWKSCRIPT) \
			"$(GENERIC_TEMPLATE)" > $@ ; \
	fi

.PHONY:\
clean-generic #! Deletes any generated C importable generic code files (uses `GENERIC_HEADERS`)
clean-generic:
	@$(call print_message,"Deleting all generic import files...")
	@for i in $(GENERIC_HEADERS) ; do \
		output="`echo $${i} | sed 's|\.h$$|\.c|' `" ; \
		rm -f $${output} ; \
	done
