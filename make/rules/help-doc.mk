#! This file holds scripts to display documentation summaries of header files



HELPDOC_VARNAME = $(ANSI_TEXT_BOLD)
HELPDOC_TYPEDEF = $(call ANSI_COLOR_FG,39)
HELPDOC_KEYWORD = $(call ANSI_COLOR_FG,198)
HELPDOC_PUNCTOP = $(call ANSI_COLOR_FG,208)
HELPDOC_PREPROC = $(call ANSI_COLOR_FG,160)
HELPDOC_COMMENT = $(call ANSI_COLOR_FG,244)

HELPDOC_AWK_SYNTAXCOLORS = \
$$0 = gensub(/\<_[A-Z]+\(\)[ \t]*/, "", "g");\
$$0 = gensub(/\<CONCAT\(([a-zA-Z_0-9]+),([A-Z])_NAME\)/,      "\\1<\\2>\t"                                 , "1");\
$$0 = gensub(/(\/\/(.*)$$)/,                                      $(HELPDOC_COMMENT)"\\0"$(IO_RESET)       , "1");\
$$0 = gensub(/[ \t]+([a-zA-Z_0-9]+(<.*>)?)[ \t]*(\(.*\);$$)/, "\t"$(HELPDOC_VARNAME)"\\1"$(IO_RESET)"\t\\3", "1");\
$$0 = gensub(/^[ \t]*\#[ \t]*(define|undef|include)\>/,       "\#"$(HELPDOC_PREPROC)"\\1"$(IO_RESET)       , "g");\
$$0 = gensub(/\<(const|restrict|typedef|volatile|atomic)\>/,      $(HELPDOC_KEYWORD)"\\0"$(IO_RESET)       , "g");\
$$0 = gensub(/\<(void|char|short|int|long|float|double)\>/,       $(HELPDOC_TYPEDEF)"\\0"$(IO_RESET)       , "g");\
$$0 = gensub(/\<(struct|union|enum)[ ]+[a-zA-Z_0-9]+\>/,          $(HELPDOC_TYPEDEF)"\\0"$(IO_RESET)       , "g");\
$$0 = gensub(/\<([ptseuf]_[a-zA-Z_0-9]+)\>/,                      $(HELPDOC_TYPEDEF)"\\0"$(IO_RESET)       , "g");\
$$0 = gensub(/\<([A-Z])\>/,                                       $(HELPDOC_TYPEDEF)"\\0"$(IO_RESET)       , "g");\
$$0 = gensub(/[*<>.!&@$$]/,                                       $(HELPDOC_PUNCTOP)"\\0"$(IO_RESET)       , "g");\



.PHONY:\
help-doc #! Displays a summary of all functions provided by libccc (`$(HDRS)`)
help-doc:
	@for i in $(addprefix $(HDRDIR),$(HDRS)) ; do \
		$(call print_message,"$${i}") ; \
		gawk '\
		/[ \t]+[a-zA-Z_0-9]+[ \t]*\(.*\);$$/ \
		{\
			if (!/\<typedef\>/ &&\
				!/^[ \t]*#[ \t]*define\>/ &&\
				!/^[ \t]*\/\//)\
			{\
				$(HELPDOC_AWK_SYNTAXCOLORS)\
				$$0 = gensub(/\t+/, "\t", "g");\
				print;\
			}\
		}\
		' "$${i}" ; \
		printf "\n" ; \
	done



.PHONY:\
help-doc-find #! Displays documentation and code for any line matching the symbols given as `ARGS`
help-doc-find:
	@if [ -z "$(ARGS)" ]; then \
		$(call print_error,"This command expects ARGS - call it like this: make $@ ARGS='...'") ; \
	fi
	@for i in $(addprefix $(HDRDIR),$(HDRS)) ; do \
		awk '\
		BEGIN { doc = ""; docblock = 0; output = ""; }\
		{\
			if (docblock == 0)\
			{\
				if (/$(ARGS)/)\
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
		' "$${i}" ; \
	done
