#! This file holds scripts to display documentation summaries of header files



HELPDOC_VARNAME = $(ANSI_TEXT_BOLD)
HELPDOC_TYPEDEF = $(call ANSI_COLOR_FG,39)
HELPDOC_KEYWORD = $(call ANSI_COLOR_FG,198)
HELPDOC_PUNCTOP = $(call ANSI_COLOR_FG,208)
HELPDOC_PREPROC = $(call ANSI,1;38;5;198)
HELPDOC_COMMENT = $(call ANSI_COLOR_FG,244)



HELPDOC_AWK_DECL_SPACING = \
$$0 = gensub(/\<_[A-Z]+\(\)[ \t]*/,                           "",           "g");\
$$0 = gensub(/\<CONCAT\(([a-zA-Z_0-9]+),([A-Z])_NAME\)/,      "\\1<\\2>\t", "1");\
$$0 = gensub(/[ \t]+([a-zA-Z_0-9]+(<.*>)?)[ \t]*(\(.*\);$$)/, "\t\\1\t\\3", "1");\
$$0 = gensub(/[ \t][ \t]+/,                                   "\t",         "g");\
split($$0, line, "\t");\
$$0 = sprintf("%-20s %-40s %s", line[1], line[2], line[3]);\

HELPDOC_AWK_SYNTAXCOLORS = \
$$0 = gensub(/([a-zA-Z_0-9]+(<.*>)?)([ \t]*\(.*\);$$)/,                    $(HELPDOC_VARNAME) "\\1" $(IO_RESET)"\\3", "1");\
$$0 = gensub(/^[ \t]*\#[ \t]*(define|undef|include)[ \t]+([a-zA-Z_0-9]+)/, $(HELPDOC_PREPROC)"\#\\1"$(IO_RESET)"\t"$(HELPDOC_VARNAME)"\\2"$(IO_RESET), "g");\
$$0 = gensub(/\<(const|restrict|typedef|volatile|atomic)\>/,               $(HELPDOC_KEYWORD) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/\<(void|char|short|int|long|float|double)\>/,                $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/\<(struct|union|enum)[ ]+[a-zA-Z_0-9]+\>/,                   $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/\<([ptseuf]_[a-zA-Z_0-9]+)\>/,                               $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/\<([A-Z])\>/,                                                $(HELPDOC_TYPEDEF) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/[*<>.!&@$$]/,                                                $(HELPDOC_PUNCTOP) "\\0" $(IO_RESET), "g");\
$$0 = gensub(/(\/\/(.*)$$)/,                                               $(HELPDOC_COMMENT) "\\0" $(IO_RESET), "1");\



#! The list of files which should be parsed by the `help-doc` rules (by default, all source code headers)
DOC_FILES = $(addprefix $(HDRDIR),$(HDRS))
#! The awk condition to match a line (the default is an expression to match any c function declaration)
DOC_MATCH = \
	/[ \t]+[a-zA-Z_0-9]+[ \t]*\(.*\);$$/ && \
	!/^[ \t]*\#[ \t]*define\>/ && \
	!/\<typedef\>/ && \
	!/^[ \t]*\/\// \



.PHONY:\
help-doc #! Displays a summary of any code declarations (uses `DOC_FILES` and `DOC_MATCH`)
help-doc:
	@for i in $(DOC_FILES) ; do \
		$(call print_message,"$${i}") ; \
		gawk '\
		{\
			if ($(DOC_MATCH))\
			{\
				$(HELPDOC_AWK_DECL_SPACING)\
				$(HELPDOC_AWK_SYNTAXCOLORS)\
				print;\
			}\
		}\
		' "$${i}" ; \
		printf "\n" ; \
	done



.PHONY:\
help-doc-full #! Displays documentation and code for any line matching the symbols given as `ARGS`
help-doc-full:
	@for i in $(DOC_FILES) ; do \
		awk '\
		BEGIN { doc = ""; docblock = 0; output = ""; }\
		{\
			if (docblock == 0)\
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
				else if (/\/\/!/) { doc = (!/@{/ ? $$0 : doc); }\
				else if (/\/\*!/) { doc = doc "\n" $$0; docblock = 1; }\
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
