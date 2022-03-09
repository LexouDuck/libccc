#! This is the root-level Makefile, which includes all the others

# Custom variable to detect when Makefile is called through `emmake make`
ifdef EMSCRIPTEN
__EMSCRIPTEN__ = 1
$(info 'EMSCRIPTEN' is defined, building for emscripten platform)
else ifeq ($(OSMODE),emscripten)
$(error You need to call 'emmake make' instead of simply 'make' if you want to build with emscripten. \
	see https://emscripten.org/docs/compiling/Building-Projects.html#integrating-with-a-build-system)
endif


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
ifdef __EMSCRIPTEN__
NAME_TEST := $(NAME_TEST).js
endif



#######################################
#      Project folder structure       #
#######################################

#! The sub-directory in which makefile scripts are stored
MKFILES_DIR := ./mkfile/

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
LISTSDIR = $(MKFILES_DIR)lists/

# generated folders

#! The directory for object assembly files (stores `.o` files)
ifdef __EMSCRIPTEN__
OBJDIR = ./obj/emscripten_obj/
else
OBJDIR = ./obj/
endif
#! The directory for built binary files (stores programs/libraries built by this project)
BINDIR = ./bin/
#! The directory for distribution archives (stores `.zip` distributable builds)
DISTDIR = ./dist/
#! The directory for temporary (can be used for several things - should always be deleted after use)
TEMPDIR = ./temp/
#! The directory for output logs (stores `.txt` outputs of the test suite program)
LOGDIR = ./log/
#! The directory for test-suite code-coverage output reports
COVDIR = $(LOGDIR)coverage/
#! The directory for linter/static analyzer output logs (stores warnings logs)
LINTDIR = $(LOGDIR)lint/



#######################################
#     Included Makefile Variables     #
#######################################

# general variables
include $(MKFILES_DIR)utils/make.mk
include $(MKFILES_DIR)utils/shell.mk
include $(MKFILES_DIR)utils/prereq.mk
include $(MKFILES_DIR)utils/print.mk
include $(MKFILES_DIR)utils/ansi.mk
include $(MKFILES_DIR)utils/ext.mk

# project-specific variables
include $(MKFILES_DIR)config/modes.mk
include $(MKFILES_DIR)config/build.mk
include $(MKFILES_DIR)config/build-tests.mk
include $(MKFILES_DIR)config/install.mk



#######################################
#      Included Makefile Rules        #
#######################################

# project-specific rules
include $(MKFILES_DIR)rules/all.mk
include $(MKFILES_DIR)rules/init.mk
include $(MKFILES_DIR)rules/prereq.mk
include $(MKFILES_DIR)rules/version.mk
include $(MKFILES_DIR)rules/packages.mk

include $(MKFILES_DIR)rules/lists.mk
include $(MKFILES_DIR)rules/build.mk
include $(MKFILES_DIR)rules/lists-tests.mk
include $(MKFILES_DIR)rules/build-tests.mk
include $(MKFILES_DIR)rules/install.mk
include $(MKFILES_DIR)rules/dist.mk
include $(MKFILES_DIR)rules/clean.mk

include $(MKFILES_DIR)rules/test.mk
include $(MKFILES_DIR)rules/coverage.mk
include $(MKFILES_DIR)rules/debugging.mk
include $(MKFILES_DIR)rules/format.mk
include $(MKFILES_DIR)rules/lint.mk
include $(MKFILES_DIR)rules/doc.mk
include $(MKFILES_DIR)rules/doc-help.mk

# libccc-specific rules
include $(MKFILES_DIR)rules/generic.mk
include $(MKFILES_DIR)rules/test-env.mk
include $(MKFILES_DIR)rules/test-standalone.mk

# general rules
include $(MKFILES_DIR)utils/refactor.mk
include $(MKFILES_DIR)utils/help.mk
