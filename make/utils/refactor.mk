#! This file holds useful rules to refactor source code (language-agnostic)



TEMPFILE = refactor.tmp



.PHONY:\
refactor-indent #! On all source files: changes any tab characters which are not at the start of a line into spaces
refactor-indent:
	@if ! echo "    _ " | unexpand -t 4 --first-only > /dev/null  ; then \
		printf $(IO_RED)"ERROR"$(IO_RESET)": 'unexpand' command doesn't support the '--first-only' option.\n" ; \
		exit 1 ; \
	fi
	@for i in $(SRCS) $(HDRS) ; do \
		printf "Editing file: $$i -> " ; \
		LC_ALL=C cat $$i \
		| expand   -t 4 \
		| unexpand -t 4 --first-only \
		> $(TEMPFILE) && mv $(TEMPFILE) $$i ; \
		printf $(IO_GREEN)"OK!"$(IO_RESET)"\n" ; \
	done



.PHONY:\
refactor-replace #! On all source files: performs a regular expression match & replace (using args: `OLD` and `NEW`)
refactor-replace:
	@if [ "$(OLD)" == "" ]; then printf $(IO_RED)"ERROR"$(IO_RESET)": no 'OLD' argument specified.\n" ; exit 1 ; fi
	@if [ "$(NEW)" == "" ]; then printf $(IO_RED)"ERROR"$(IO_RESET)": no 'NEW' argument specified.\n" ; exit 1 ; fi
	@for i in $(SRCS) $(HDRS) ; do \
		printf "Editing file: $$i -> " ; \
		sed -E 's/$(OLD)/$(NEW)/g' $$i \
		> $(TEMPFILE) && mv $(TEMPFILE) $$i ; \
		printf $(IO_GREEN)"OK!"$(IO_RESET)"\n" ; \
	done
