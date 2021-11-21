#! This file holds rules to generate .txt files of lists of files used in the build



#! Path of the file which stores the list of header code files
TEST_HDRSFILE = $(LISTSDIR)hdrs-test.txt
#! The shell command which outputs the list of header code files
echo_TEST_HDRSFILE = find $(TESTDIR) -name "*.h" | sort | sed 's|//|/|g' | grep -v '/_'
#! The shell command which generates the list of header code files
make_TEST_HDRSFILE = $(call echo_TEST_HDRSFILE) > $(TEST_HDRSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(TEST_HDRSFILE) ; echo $$?),1)
$(shell $(call print_warning,"test suite header code list file '$(TEST_HDRSFILE)' doesn't exist - creating now..."))
$(shell mkdir -p $(LISTSDIR))
$(shell $(call make_TEST_HDRSFILE))
endif
#! List of all C header code files
TEST_HDRS := $(shell cat $(TEST_HDRSFILE))



#! Path of the file which stores the list of source code files
TEST_SRCSFILE = $(LISTSDIR)srcs-test.txt
#! The shell command which outputs the list of source code files
echo_TEST_SRCSFILE = find $(TESTDIR) -name "*.c" | sort | sed 's|//|/|g' | grep -v '/_'
#! The shell command which generates the list of source code files
make_TEST_SRCSFILE = $(call echo_TEST_SRCSFILE) > $(TEST_SRCSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(TEST_SRCSFILE) ; echo $$?),1)
$(shell $(call print_warning,"test suite source code list file '$(TEST_SRCSFILE)' doesn't exist - creating now..."))
$(shell mkdir -p $(LISTSDIR))
$(shell $(call make_TEST_SRCSFILE))
endif
#! List of all C source code files
TEST_SRCS := $(shell cat $(TEST_SRCSFILE))



.PHONY:\
lists-tests #! Create/update the list of source/header files for the test suite program
lists-tests:
	@$(call make_TEST_HDRSFILE)
	@$(call make_TEST_SRCSFILE)

.PHONY:\
show-lists-tests #! Display the list of source/header files
show-lists-tests:
	@$(call echo_TEST_HDRSFILE)
	@$(call echo_TEST_SRCSFILE)
