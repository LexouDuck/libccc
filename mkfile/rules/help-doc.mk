#! This file holds scripts to display documentation summaries of header files



#! The list of files which should be parsed by the `help-doc` rules (by default, all source code headers)
DOC_FILES = $(addprefix $(HDRDIR),$(HDRS))
#! The awk condition to match a line (the default is an expression to match any c function declaration)
DOC_MATCH = \
	/[ \t]+[a-zA-Z_0-9]+[ \t]*\(.*\);$$/ && \
	!/^[ \t]*\#[ \t]*define\>/ && \
	!/\<typedef\>/ && \
	!/^[ \t]*\/\// \



#! These are the colors to use for syntax coloring in the doc shell output (ANSI terminal escape sequences)
#{
HELPDOC_VARNAME = $(ANSI_TEXT_BOLD)
HELPDOC_TYPEDEF = $(call ANSI_COLOR_FG,39)
HELPDOC_KEYWORD = $(call ANSI_COLOR_FG,197)
HELPDOC_OPERATOR= $(call ANSI_COLOR_FG,208)
HELPDOC_PREPROC = $(call ANSI,1;38;5;198)
HELPDOC_COMMENT = $(call ANSI_COLOR_FG,244)
#}

#! These are some regular expressions used to syntactically color code shown
#{
REGEXP_C_SYMBOL  =\<([a-zA-Z_][a-zA-Z_0-9]*)\>
REGEXP_C_PREPROC =\<(define|undef|include|ifdef|ifndef|if|elif|endif|line|error|warning|pragma)\>
REGEXP_C_KEYWORD =\<(typedef|const|restrict|volatile|atomic|auto|register|inline|static|noreturn)\>
REGEXP_C_TYPE    =\<(void|char|short|int|long|float|double|signed|unsigned)\>
REGEXP_C_TYPE_KW =\<(struct|union|enum)\>
REGEXP_C_TYPEDEF =\<([tseufpi]_[a-zA-Z_0-9]+)\>
REGEXP_C_TYPEGEN =\<([A-Z])\>
REGEXP_C_GENERIC =($(REGEXP_C_TYPEGEN)(,[ \t]*$(REGEXP_C_TYPEGEN))?)
#}



HELPDOC_AWK_DECL_CLEANUP = \
$$0 = gensub(/\<_[A-Z]+\(\)[ \t]*/,                                  "",         "g");\
$$0 = gensub(/$(REGEXP_C_TYPEDEF)\($(REGEXP_C_GENERIC)\)/,           "\\1<\\2>", "g");\
$$0 = gensub(/$(REGEXP_C_SYMBOL)\($(REGEXP_C_GENERIC)\)/,            "\\1<\\2>", "1");\
$$0 = gensub(/($(REGEXP_C_SYMBOL)(<$(REGEXP_C_GENERIC)>)?)[ \t]*\(/, "\\1\t(",   "1");\
$$0 = gensub(/[ \t][ \t]+/,                                          "\t",       "g");\

HELPDOC_AWK_DECL_SPACING = \
split($$0, line, "\t");\
$$0 = sprintf("%-20s %-40s %s", line[1], line[2], line[3]);\

HELPDOC_AWK_SYNTAXCOLORS = \
$$0 = gensub(/$(REGEXP_C_SYMBOL)(<$(REGEXP_C_GENERIC)>)?([ \t]*)\(/,       $(HELPDOC_VARNAME) "\\1" $(IO_RESET)"\\2\\7(", "1");\
$$0 = gensub(/^[ \t]*\#[ \t]*$(REGEXP_C_PREPROC)[ \t]+$(REGEXP_C_SYMBOL)/, $(HELPDOC_PREPROC)"\#\\1"$(IO_RESET)" "$(HELPDOC_VARNAME)"\\2"$(IO_RESET), "g");\
$$0 = gensub(/$(REGEXP_C_KEYWORD)/,                                        $(HELPDOC_KEYWORD) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/$(REGEXP_C_TYPE)/,                                           $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/$(REGEXP_C_TYPE_KW)[ ]+$(REGEXP_C_SYMBOL)/,                  $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/$(REGEXP_C_TYPEDEF)/,                                        $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/$(REGEXP_C_TYPEGEN)/,                                        $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/[*\/\-+!&@$$]/,                                              $(HELPDOC_OPERATOR)"\\0" $(IO_RESET), "g");\
$$0 = gensub(/(\/\/(.*)$$)/,                                               $(HELPDOC_COMMENT) "\\0" $(IO_RESET), "1");\



.PHONY:\
help-doc #! Displays a summary of any code declarations (uses `DOC_FILES` and `DOC_MATCH`)
help-doc:
	@for i in $(DOC_FILES) ; do \
		$(call print_message,"$${i}") ; \
		gawk '\
		BEGIN {\
			skip = 0;\
			docblock = 0;\
		}\
		{\
			if (skip)\
			{\
				if (/^[ \t]*#[ \t]*(else|endif)/) { skip = 0; }\
				next;\
			}\
			else if (docblock == 0)\
			{\
				if ($(DOC_MATCH))\
				{\
					$(HELPDOC_AWK_DECL_CLEANUP)\
					$(HELPDOC_AWK_DECL_SPACING)\
					$(HELPDOC_AWK_SYNTAXCOLORS)\
					print;\
				}\
				else if (/^[ \t]*#[ \t]*if[ \t]+(0|FALSE|LIBCONFIG)/) { skip = 1; }\
				else if (/\/\//) { next; }\
				else if (/\/\*/) { docblock = 1; }\
			}\
			else if (/\*\//)\
			{\
				docblock = 0;\
			}\
		}\
		' "$${i}" ; \
		printf "\n" ; \
	done



.PHONY:\
help-doc-full #! Displays documentation for any line matching the given regexp (uses `DOC_FILES` and `DOC_MATCH`)
help-doc-full:
	@for i in $(DOC_FILES) ; do \
		gawk '\
		BEGIN {\
			skip = 0;\
			docblock = 0;\
			doc = "";\
			output = "";\
		}\
		{\
			if (skip)\
			{\
				if (/^[ \t]*#[ \t]*(else|endif)/) { skip = 0; }\
				next;\
			}\
			else if (docblock == 0)\
			{\
				if ($(DOC_MATCH))\
				{\
					$(HELPDOC_AWK_SYNTAXCOLORS)\
					output = $(IO_CYAN) FILENAME $(IO_RESET) "\n";\
					output = (length(doc) > 0 ? $(HELPDOC_COMMENT) doc $(IO_RESET) "\n" : "");\
					print output $$0 "\n";\
					doc = "";\
					docblock = 0;\
				}\
				else if (/^[ \t]*#[ \t]*if[ \t]+(0|FALSE|LIBCONFIG)/) { skip = 1; }\
				else if (/\/\/!/ || /\/\/\//) { doc = (!/@{/ ? $$0 : doc); }\
				else if (/\/\*!/ || /\/\*\*/) { doc = doc "\n" $$0; docblock = 1; }\
				else if (/^_[A-Z]+\(\)/) {  }\
				else { doc = ""; }\
			}\
			else\
			{\
				if (/\*\//)\
				{\
					docblock = 0;\
				}\
				doc = doc "\n" $$0;\
			}\
		}\
		' "$${i}" | expand -t 4 ; \
	done
