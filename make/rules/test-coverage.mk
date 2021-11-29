#! This file holds project-specific rules to check if the test suite covers all functions/edge cases



#! The directory in which to store code-coverage output reports
COVDIR = $(LOGDIR)coverage/

#! This is the tracefile which is output by lcov, to generate HTML code-coverage report
LCOVFILE      = $(COVDIR)coverage.info
LCOVFILE_BASE = $(COVDIR)coverage-base.info
LCOVFILE_TEST = $(COVDIR)coverage-test.info



#! Shell command: used to read code-coverage files (.gcda and .gcno files next to the corresponding .o file)
GCOV = gcov
#! Shell command options: for code-coverage file reader tool
GCOV_FLAGS = \
	--function-summaries \
	--branch-probabilities \
	--branch-counts \

#! Shell command: used to make HTML summary of all code-coverage files
LCOV = lcov
#! Shell command options: for code-coverage file reader tool
LCOV_FLAGS = \
	--directory . \
	--base-directory . \



#! List of code-coverage files generated when compiling with the `--coverage` flag
GCOVFILES_GCNO = $(OBJS:%.o=%.gcno)
#! List of code-coverage files generated when running code which was compiled with `--coverage`
GCOVFILES_GCDA = $(OBJS:%.o=%.gcda)
#! List of files which store code-coverage results
GCOVFILES_GCOV = $(OBJS:%.o=%.gcov)



.PHONY:\
test-coverage #! Generates human-readable HTML output reports for code-coverage tests
test-coverage: CFLAGS       += --coverage
test-coverage: TEST_LDFLAGS += --coverage
test-coverage: # clean test



#! Generates text output reports by calling gcov
%.gcov: %.o
	@$(call print_message,"Generating code coverage report for file: "$(IO_RESET)"$@")
	@if [ ! -f `echo $@ | sed 's/.gcov$$/.gcda/' | sed 's/.gcov$$/.gcda/'` ] ; then \
		$(call print_warning,"source file does not have a .gcda file (code was never run): $<") ; \
		touch $@ ; \
	else \
		mkdir -p $(@D) ; \
		$(GCOV) $(GCOV_FLAGS) $< ; \
		mv `basename $@ | sed 's/.gcov$$/.c.gcov/'` $@ || exit 0 ; \
	fi



.PHONY:\
coverage #! Generates human-readable HTML output reports for code-coverage tests
coverage: test-coverage $(GCOVFILES_GCOV)
	@mkdir -p $(COVDIR)
	@if $(LCOV) --version ; then \
		$(call print_message,"$(LCOV) is installed: generating HTML output...") ; \
		$(LCOV) $(LCOV_FLAGS) \
			--initial \
			--capture \
			-o $(LCOVFILE_BASE) ; \
		$(LCOV) $(LCOV_FLAGS) \
			--capture \
			-o $(LCOVFILE_TEST) ; \
		$(LCOV) $(LCOV_FLAGS) \
			--add-tracefile $(LCOVFILE_BASE) \
			--add-tracefile $(LCOVFILE_TEST) \
			-o $(LCOVFILE) ; \
		genhtml $(LCOVFILE) \
			-o $(COVDIR) ; \
	fi
	@$(call print_success,"Generated all code coverage reports: open $(COVDIR)index.html")
