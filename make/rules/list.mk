#! This file holds rules to list/debug the contents of the build system



.PHONY:\
update-lists # Updates the lists of source/header files
update-lists:
	@$(MAKE) update-lists-build
	@$(MAKE) update-lists-tests



.PHONY:\
update-lists-build # Create/update the list of source/header files
update-lists-build:
	@find $(HDRDIR) -name "*.h" | sort | sed "s|$(HDRDIR)/||g" > $(HDRSFILE)
	@find $(SRCDIR) -name "*.c" | sort | sed "s|$(SRCDIR)/||g" > $(SRCSFILE)

.PHONY:\
update-lists-tests # Create/update the list of source/header files for the test suite program
update-lists-tests:
	@find $(TEST_DIR) -name "*.h" | sort | sed "s|//|/|g" | grep -v "/_" > $(HDRSFILE_TEST)
	@find $(TEST_DIR) -name "*.c" | sort | sed "s|//|/|g" | grep -v "/_" > $(SRCSFILE_TEST)
