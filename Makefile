#! This is the root-level Makefile, which includes all the others



# NOTE: the two following variables are to stay at the very top of this Makefile and never move

#! The complete absolute path of the root-level makefile
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
#! The directory of the root-level makefile
CURRENT_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH)))



#######################################
#          Project variables          #
#######################################

#! Output filename for the library
NAME = libccc

#! Output filename for the test suite program
NAME_TEST = libccc-test



#######################################
#      Project folder structure       #
#######################################

# repository folders

#! The directory for header code files (stores `.h` files)
HDRDIR = ./hdr/
#! The directory for source code files (stores `.c` files)
SRCDIR = ./src/
#! The directory for dependency library files (stores libs - static:`.a` or dynamic:`.dll`/`.dylib`/`.so`)
LIBDIR = ./lib/
#! The directory for documentation (stores config and scripts to generate doc)
DOCDIR = ./doc/
#! The directory for testing programs (stores source/header code for the various testing programs)
TESTDIR = ./test/
#! The directory for git hooks scripts
GITHOOKSDIR = ./.githooks/
#! The directory for important list files (source files, packages)
LISTSDIR = ./make/lists/

# generated folders

#! The directory for object assembly files (stores `.o` files)
OBJDIR = ./obj/
#! The directory for built binary files (stores programs/libraries built by this project)
BINDIR = ./bin/
#! The directory for distribution archives (stores `.zip` distributable builds)
DISTDIR = ./dist/
#! The directory for output logs (stores `.txt` outputs of the test suite program)
LOGDIR = ./log/
#! The directory for linter/static analyzer output logs (stores warnings logs)
LINTDIR = ./lint/
#! The directory for temporary (can be used for several things - should always be deleted after use)
TEMPDIR = ./temp/




#######################################
#     Included Makefile Variables     #
#######################################

# general variables
include make/utils/print.mk
include make/utils/ansi.mk
include make/utils/sudo.mk
include make/utils/ext.mk
include make/utils/install.mk

# project-specific rules
include make/config/modes.mk
include make/config/build.mk
include make/config/build-tests.mk



#######################################
#      Included Makefile Rules        #
#######################################

# project-specific rules
include make/rules/all.mk
include make/rules/lists.mk
include make/rules/build.mk
include make/rules/lists-tests.mk
include make/rules/build-tests.mk
include make/rules/install.mk

include make/rules/init.mk
include make/rules/prereq.mk
include make/rules/packages.mk
include make/rules/version.mk
include make/rules/dist.mk
include make/rules/clean.mk

include make/rules/debugging.mk
include make/rules/test.mk
include make/rules/test-helloworld.mk
include make/rules/test-foreach.mk
include make/rules/test-kvt.mk
include make/rules/test-env.mk
include make/rules/lint.mk
include make/rules/format.mk
include make/rules/doc.mk

# general rules
include make/utils/refactor.mk
include make/utils/help.mk
include make/rules/help-doc.mk
