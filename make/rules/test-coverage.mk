#! This file holds project-specific rules to check if the test suite covers all functions/edge cases



#! The directory in which to store code-coverage output reports
COVDIR = $(LOGDIR)coverage/



#! Shell command: used to read code-coverage files (.gcda and .gcno files next to the corresponding .o file)
GCOV = gcov
#! Shell command options: for code-coverage file reader tool
GCOV_FLAGS = -f -b



#! List of code-coverage files generated when compiling with the `--coverage` flag
GCOVFILES_GCNO = $(OBJS:%.o=%.gcno)
#! List of code-coverage files generated when running code which was compiled with `--coverage`
GCOVFILES_GCDA = $(OBJS:%.o=%.gcda)
#! List of files which store code-coverage results
GCOVFILES_GCOV = $(OBJS:%.o=%.gcov)

#! This is the tracefile which is output by lcov, to generate HTML code-coverage report
LCOVFILE = $(COVDIR)coverage.info



#! Compiles object files, with code-coverage metadata files
$(OBJDIR)%.gcno : $(SRCDIR)%.c
	@mkdir -p $(@D)
	@printf "Compiling file for code-coverage test: "$@" -> "
	@$(CC) --coverage -o $@ $(CFLAGS) -MMD $(INCLUDES) -c $<
	@printf $(IO_GREEN)"OK!"$(IO_RESET)"\n"



#! Generates text output reports by calling gcov
%.gcov : %.o %.gcno
	@if [ ! -f `echo $@ | sed 's/.gcov$$/.gcda/' | sed 's/.gcov$$/.gcda/'` ] ; then \
		$(call print_warning,"source file for '$<' does not have a .gcda file - ie: code was never run.") ; \
	else \
		mkdir -p $(@D) ; \
		$(GCOV) $(GCOV_FLAGS) $< ; \
		mv `basename $@ | sed 's/.gcov$$/.c.gcov/'` $@ ; \
	fi



.PHONY:\
test-coverage #! Generates human-readable HTML output reports for code-coverage tests
test-coverage: $(GCOVFILES_GCOV)
	@mkdir -p $(COVDIR)
	@if lcov --version ; then \
		$(call print_message,"lcov is installed: generating HTML output...") ; \
		lcov --capture \
			--directory . \
			--base-directory . \
			-o $(LCOVFILE) ; \
		genhtml $(LCOVFILE) \
			-o $(COVDIR) ; \
	fi
	@$(call print_success,"Generated all code coverage reports.") ; \
