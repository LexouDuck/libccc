#! This file holds rules to list/debug the contents of the build system



.PHONY:\
update-lists # Updates the lists of source/header files
update-lists:
	@find $(HDRDIR)   -name "*.h" | sort | sed "s|$(HDRDIR)/||g"         > $(HDRSFILE)
	@find $(SRCDIR)   -name "*.c" | sort | sed "s|$(SRCDIR)/||g"         > $(SRCSFILE)
	@find $(TEST_DIR) -name "*.h" | sort | sed "s|//|/|g" | grep -v "/_" > $(HDRSFILE_TEST)
	@find $(TEST_DIR) -name "*.c" | sort | sed "s|//|/|g" | grep -v "/_" > $(SRCSFILE_TEST)



# Create/update the list of sources
$(SRCSFILE):
