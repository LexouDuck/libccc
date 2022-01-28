#! This is the root-level Makefile, which includes all the others



# NOTE: the two following variables are to stay at the very top of this Makefile and never move

#! The complete absolute path of the root-level makefile
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
#! The directory of the root-level makefile
CURRENT_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH)))
#! The sub-directory in which makefile scripts are stored
MKFILES_DIR := ./%[mkpath]%/



#######################################
#          Project variables          #
#######################################

#! Output filename for the %[type]%
NAME = %[name]%
%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)       :
%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)       :#! Output filename for the test suite program
%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)       :NAME_TEST = %[name]%-test



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
%%if tracked(mkfile/rules/_if_multiselect/doc.mk)          :#! The directory for documentation (stores config and scripts to generate doc)
%%if tracked(mkfile/rules/_if_multiselect/doc.mk)          :DOCDIR = ./doc/
%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)       :#! The directory for testing programs (stores source/header code for the various testing programs)
%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)       :TESTDIR = ./test/
%%if tracked(.githooks/_if_ask_autoversion/pre-commit)     :#! The directory for git hooks scripts
%%if tracked(.githooks/_if_ask_autoversion/pre-commit)     :GITHOOKSDIR = ./.githooks/
%%if tracked(mkfile/rules/lists.mk)                        :#! The directory for important list files (source files, packages)
%%if tracked(mkfile/rules/lists.mk)                        :LISTSDIR = $(MKFILES_DIR)lists/

# generated folders

#! The directory for object assembly files (stores `.o` files)
OBJDIR = ./obj/
#! The directory for built binary files (stores programs/libraries built by this project)
BINDIR = ./bin/
#! The directory for distribution archives (stores `.zip` distributable builds)
DISTDIR = ./dist/
#! The directory for temporary (can be used for several things - should always be deleted after use)
TEMPDIR = ./temp/
#! The directory for output logs (stores `.txt` outputs of the test suite program)
LOGDIR = ./log/
%%if tracked(mkfile/rules/_if_multiselect/coverage.mk)     :#! The directory for test-suite code-coverage output reports
%%if tracked(mkfile/rules/_if_multiselect/coverage.mk)     :COVDIR = $(LOGDIR)coverage/
%%if tracked(mkfile/rules/_if_multiselect/lint.mk)         :#! The directory for linter/static analyzer output logs (stores warnings logs)
%%if tracked(mkfile/rules/_if_multiselect/lint.mk)         :LINTDIR = $(LOGDIR)lint/




#######################################
#     Included Makefile Variables     #
#######################################

# general variables
include $(MKFILES_DIR)utils/print.mk
include $(MKFILES_DIR)utils/ansi.mk
include $(MKFILES_DIR)utils/sudo.mk
include $(MKFILES_DIR)utils/ext.mk
include $(MKFILES_DIR)utils/install.mk

# project-specific rules
include $(MKFILES_DIR)config/modes.mk
include $(MKFILES_DIR)config/build.mk
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):include $(MKFILES_DIR)config/build-tests.mk



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
%%if tracked(mkfile/rules/_if_ask_testsuite/lists-tests.mk):include $(MKFILES_DIR)rules/lists-tests.mk
%%if tracked(mkfile/rules/_if_ask_testsuite/build-tests.mk):include $(MKFILES_DIR)rules/build-tests.mk
include $(MKFILES_DIR)rules/install.mk
include $(MKFILES_DIR)rules/dist.mk
include $(MKFILES_DIR)rules/clean.mk

%%if tracked(mkfile/rules/_if_ask_testsuite/test.mk)       :include $(MKFILES_DIR)rules/test.mk
%%if tracked(mkfile/rules/_if_multiselect/coverage.mk)     :include $(MKFILES_DIR)rules/coverage.mk
%%if tracked(mkfile/rules/_if_multiselect/debugging.mk)    :include $(MKFILES_DIR)rules/debugging.mk
%%if tracked(mkfile/rules/_if_multiselect/format.mk)       :include $(MKFILES_DIR)rules/format.mk
%%if tracked(mkfile/rules/_if_multiselect/lint.mk)         :include $(MKFILES_DIR)rules/lint.mk
%%if tracked(mkfile/rules/_if_multiselect/doc.mk)          :include $(MKFILES_DIR)rules/doc.mk
%%if tracked(mkfile/rules/_if_multiselect/doc-help.mk)     :include $(MKFILES_DIR)rules/doc-help.mk

# general rules
include $(MKFILES_DIR)utils/refactor.mk
include $(MKFILES_DIR)utils/help.mk
