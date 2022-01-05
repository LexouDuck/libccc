#! This is the root-level Makefile, which includes all the others



# NOTE: the two following variables are to stay at the very top of this Makefile and never move

#! The complete absolute path of the root-level makefile
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
#! The directory of the root-level makefile
CURRENT_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH)))
#! The sub-directory in which makefile scripts are stored
MKFILES_DIR := ./mkfile/



#######################################
#          Project variables          #
#######################################

#! Output filename for the project
NAME = 



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
LISTSDIR = ./$(MKFILES_DIR)/lists/

# generated folders

#! The directory for temporary files of any kind, should be regularly deleted
TEMPDIR = ./temp/
#! The directory for output logs (stores `.txt` output logs)
LOGDIR = ./log/
#! The directory for object assembly files (stores `.o` files)
OBJDIR = ./obj/
#! The directory for built binary files (stores programs/libraries built by this project)
BINDIR = ./bin/
#! The directory for distribution archives (stores `.zip` distributable builds)
DISTDIR = ./dist/




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



#######################################
#      Included Makefile Rules        #
#######################################

# project-specific rules
include $(MKFILES_DIR)rules/all.mk
include $(MKFILES_DIR)rules/lists.mk
include $(MKFILES_DIR)rules/build.mk
include $(MKFILES_DIR)rules/install.mk

include $(MKFILES_DIR)rules/init.mk
include $(MKFILES_DIR)rules/prereq.mk
include $(MKFILES_DIR)rules/packages.mk
include $(MKFILES_DIR)rules/version.mk
include $(MKFILES_DIR)rules/dist.mk
include $(MKFILES_DIR)rules/clean.mk

# general rules
include $(MKFILES_DIR)utils/refactor.mk
include $(MKFILES_DIR)utils/help.mk
