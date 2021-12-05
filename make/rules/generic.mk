#! This file holds scripts to generate importable .c code files from .h files which use libccc generic types


#! If not explicitly specified, use full of list of all generic headers
ifeq ($(GENERIC_HEADERS),)
GENERIC_HEADERS = $(wildcard $(HDRDIR)libccc/monad/*.h)
endif

#! The file which holds the template of C code to make an importable generic-type code header
GENERIC_TEMPLATE = make/rules/generic.template.c



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

define AWKSCRIPT_FILEFROMTEMPLATE
function print_error(message)\
{ print $(IO_RED)"Template error"$(IO_RESET)"($(GENERIC_TEMPLATE)): " message > "/dev/stderr"; }\
BEGIN {\
	vars["header"]       = header;\
	vars["header_guard"] = header_guard;\
	vars["sources"]      = sources;\
	vars["symbols"]      = symbols;\
	split(symbols, symbol_array, /[ \t\n]/);\
}\
{\
	if (match($$0, /^%%([a-zA-Z_]+):/, matched))\
	{\
		if (matched[1] in vars)\
		{\
			split(vars[matched[1]], array, /[ \t\n]/);\
			for (i in array)\
			{\
				line = substr($$0, length(matched[0]) + 1);\
				gsub(/%/, array[i], line);\
				print line;\
			}\
		}\
		else { print_error("unknown variable in loop directive: " matched[0]); }\
	}\
	else if (/^%%(.*):/)\
	{ print_error("expected variable name after '%%_:' loop directive"); }\
	else if (/^%%/)\
	{ print_error("expected variable name and colon for '%%_:' loop directive"); }\
	else if (/%%/)\
	{ print_error("bad syntax - '%%_:' loop directive should be at the beginning of the line"); }\
	else if (match($$0, /%([a-zA-Z_]+)%/, matched))\
	{\
		if (matched[1] in vars)\
		{\
			line = $$0;\
			sub(/%([a-zA-Z_]+)%/, vars[matched[1]], line);\
			print line;\
		}\
		else { print_error("unknown variable used: " matched[0]); }\
	}\
	else print;\
}
endef



.PHONY:\
generic #! Creates a generic import file for any files given as `GENERIC_HEADERS`
generic:
	@for i in $(GENERIC_HEADERS) ; do \
		folder="`echo $${i} | sed 's|\.h$$|/|' | sed 's|^$(HDRDIR)libccc/||' `" ; \
		output="`echo $${i} | sed 's|\.h$$|\.c|' `" ; \
		$(call print_message,"Generating generic import file:"$(IO_RESET)" $${output}") ; \
		awk \
			-v header="`echo $${i} | sed 's|\./hdr/||' `" \
			-v header_guard="`awk '$(AWKSCRIPT_GETHEADERGUARD)' $${i}`" \
			-v sources="`grep "$${folder}" $(SRCSFILE)`" \
			-v symbols="`awk '$(AWKSCRIPT_GETSYMBOLS)' $${i} | uniq`" \
			'$(AWKSCRIPT_FILEFROMTEMPLATE)' \
			"$(GENERIC_TEMPLATE)" \
			> $${output} ; \
	done

.PHONY:\
clean-generic #! Deletes any generated C importable generic code files (uses `GENERIC_HEADERS`)
clean-generic:
	@$(call print_message,"Deleting all generic import files...")
	@for i in $(GENERIC_HEADERS) ; do \
		output="`echo $${i} | sed 's|\.h$$|\.c|' `" ; \
		rm -f $${output}
	done
