#! This file holds rules to generate .txt files of lists of files used in the build



#! Path of the file which stores the list of header code files
HDRSFILE = $(LISTSDIR)hdrs.txt
#! The shell command which outputs the list of header code files
echo_HDRSFILE = find $(HDRDIR) -name "*.h" | LC_ALL=C sort | sed 's|//|/|g' | grep -v '^$(HDRDIR)libccc/compatibility/'
#! The shell command which generates the list of header code files
make_HDRSFILE = $(call echo_HDRSFILE) > $(HDRSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(HDRSFILE) ; echo $$?),1)
_:=$(shell $(call print_warning,"header code list file '$(HDRSFILE)' doesn't exist - creating now..."))
_:=$(shell mkdir -p $(LISTSDIR))
_:=$(shell $(call make_HDRSFILE))
endif
#! List of all C header code files
HDRS := $(shell cat $(HDRSFILE))



#! Path of the file which stores the list of source code files
SRCSFILE = $(LISTSDIR)srcs.txt
#! The shell command which generates the list of source code files
echo_SRCSFILE = find $(SRCDIR) -name "*.c" | LC_ALL=C sort | sed 's|//|/|g'
#! The shell command which generates the list of source code files
make_SRCSFILE = $(call echo_SRCSFILE) > $(SRCSFILE)
# if file doesn't exist, create it
ifeq ($(shell test -f $(SRCSFILE) ; echo $$?),1)
_:=$(shell $(call print_warning,"source code list file '$(SRCSFILE)' doesn't exist - creating now..."))
_:=$(shell mkdir -p $(LISTSDIR))
_:=$(shell $(call make_SRCSFILE))
endif
#! List of all C source code files
SRCS := $(shell cat $(SRCSFILE))



.PHONY:\
lists #! Create/update the list of source/header files
lists:
	@$(call make_HDRSFILE)
	@$(call make_SRCSFILE)

.PHONY:\
show-lists #! Display the list of source/header files
show-lists:
	@$(call echo_HDRSFILE)
	@$(call echo_SRCSFILE)
