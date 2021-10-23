# NOTE: the two following lines are to stay at the very top of this Makefile and never move
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH)))

#######################################
#          Project variables          #
#######################################

# The complete project version number
VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_BUILD)-$(COMMIT_REF)
VERSION_MAJOR := 0
VERSION_MINOR := 8
VERSION_BUILD := 1
# The current commit's revision hash code
COMMIT_REF = $(shell git rev-parse HEAD)



# Output filename for the library
NAME = libccc

# Output filename for the test suite program
NAME_TEST = libccc-test



#######################################
#      Project folder structure       #
#######################################

# The header code files directory (stores `.h` files)
HDRDIR = ./hdr/
# The source code files directory (stores `.c` files)
SRCDIR = ./src/
# The object assembly files directory (stores `.o` files)
OBJDIR = ./obj/
# The built binary files directory (stores programs/libraries built by this project)
BINDIR = ./bin/
# The dependency library files directory (stores libs - static:`.a` or dynamic:`.dll`/`.dylib`/`.so`)
LIBDIR = ./lib/
# The documentation directory (stores config and scripts to generate doc)
DOCDIR = ./doc/
# The distribution archives directory (stores `.zip` distributable builds)
DISTDIR = ./dist/
# The output logs directory (stores `.txt` outputs of the test suite program)
LOGDIR = ./log/
# The linter/static analyzer output logs directory (stores warnings logs)
LINTDIR = ./lint/
# The testing programs directory (stores source/header code for the various testing programs)
TEST_DIR = ./test/
# The temporary directory (can be used for several things - should always be deleted after use)
TEMPDIR = ./temp/



#######################################
#          Project variables          #
#######################################

HDRSFILE = make/lists/hdrs.txt
# List of all C header code files
HDRS := $(shell cat $(HDRSFILE))

SRCSFILE = make/lists/srcs.txt
# List of all C source code files
SRCS := $(shell cat $(SRCSFILE))

# define object files list (.o) from source list
OBJS = ${SRCS:%.c=$(OBJDIR)%.o}

# define dependency files list (.d)
DEPS = ${OBJS:.o=.d}



HDRSFILE_TEST = make/lists/hdrs-test.txt
# List of all C header code files
HDRS_TEST := $(shell cat $(HDRSFILE_TEST))

SRCSFILE_TEST = make/lists/srcs-test.txt
# List of all C source code files
SRCS_TEST := $(shell cat $(SRCSFILE_TEST))

# define object files list (.o) from source list
OBJS_TEST = ${SRCS_TEST:%.c=$(OBJDIR)%.o}

# define dependency files list (.d)
DEPS_TEST = ${OBJS_TEST:.o=.d}



#######################################
#           Main build rules          #
#######################################

.PHONY:\
all # Builds all targets (this is the default rule)
all: $(MODE)

.PHONY:\
debug # Builds the library, in 'debug' mode (with debug flags and symbol-info)
debug: MODE = debug
debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(NAME_STATIC) $(NAME_DYNAMIC)

.PHONY:\
release # Builds the library, in 'release' mode (with debug flags and symbol-info)
release: MODE = release
release: CFLAGS += $(CFLAGS_RELEASE)
release: $(NAME_STATIC) $(NAME_DYNAMIC)



.PHONY:\
re # Deletes all generated files and rebuilds `all`
re: clean-full all



#######################################
#     Included Makefile Variables     #
#######################################

include make/config/modes.mk
include make/config/build.mk
include make/config/tests.mk

include make/utils.mk



#######################################
#      Included Makefile Rules        #
#######################################

# general rules
include make/rules/help.mk
include make/rules/list.mk
include make/rules/init.mk
include make/rules/dist.mk
include make/rules/clean.mk
include make/rules/install.mk

# language-specific rules
include make/rules/build-library.mk
include make/rules/build-tests.mk
include make/rules/debugging.mk
include make/rules/prereq.mk
include make/rules/update.mk
include make/rules/version.mk

# project-specific rules
include make/rules/test.mk
include make/rules/test-foreach.mk
include make/rules/test-helloworld.mk
include make/rules/test-kvt.mk
include make/rules/doc.mk
include make/rules/lint.mk
include make/rules/format.mk
