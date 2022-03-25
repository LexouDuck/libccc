#! This file holds the variables which configure the code compilation



#! GNU conventional variable: C compiler options
TEST_CFLAGS = \
	-Wall \
	-Wextra \
	-Winline \
	-Wno-unused-variable \
	-Wno-unused-parameter \
	-Wno-format-extra-args \
	-fno-inline \
	-fstrict-aliasing \
	$(TEST_CFLAGS_MODE) \
	$(TEST_CFLAGS_OS) \
	$(TEST_CFLAGS_EXTRA)

#! C compiler options which are specific to the current build mode, according to $(MODE)
TEST_CFLAGS_MODE = $(TEST_CFLAGS_MODE_$(MODE))
#! C compiler flags which are only present in "debug" build mode
TEST_CFLAGS_MODE_debug = \
	-g \
	-ggdb \
	-D DEBUG=1
#! C compiler flags which are only present in "release" build mode
TEST_CFLAGS_MODE_release = \
	-O3 \
	-D RELEASE=1

#! C compiler options which are platform-specific, according to $(OSMODE)
TEST_CFLAGS_OS = $(TEST_CFLAGS_OS_$(OSMODE))
TEST_CFLAGS_OS_win32 = -D__USE_MINGW_ANSI_STDIO=1 # -fno-ms-compatibility
TEST_CFLAGS_OS_win64 = -D__USE_MINGW_ANSI_STDIO=1 # -fno-ms-compatibility
TEST_CFLAGS_OS_macos = -Wno-language-extension-token
TEST_CFLAGS_OS_linux = -Wno-unused-result -fPIC
TEST_CFLAGS_OS_other = 
TEST_CFLAGS_OS_emscripten = 
ifneq ($(findstring clang,$(CC)),)
	TEST_CFLAGS_OS += -Wno-missing-braces
endif

#! This variable is intentionally empty, to specify additional C compiler options from the commandline
TEST_CFLAGS_EXTRA ?= \
#	-flto \
#	-fanalyzer \
#	-fsanitize=address \
#	-fsanitize=thread \
#	-std=ansi -pedantic \
#	-D __NOSTD__=1 \



#! GNU conventional variable: C linker options
TEST_LDFLAGS = \
	$(TEST_LDFLAGS_MODE) \
	$(TEST_LDFLAGS_OS) \
	$(TEST_LDFLAGS_EXTRA)

#! C linker options which are specific to the current build mode, according to $(MODE)
TEST_LDFLAGS_MODE = $(TEST_LDFLAGS_MODE_$(MODE))
TEST_LDFLAGS_debug = 
TEST_LDFLAGS_release = 

#! C linker options which are platform-specific, according to $(OSMODE)
TEST_LDFLAGS_OS = $(TEST_LDFLAGS_OS_$(OSMODE))
TEST_LDFLAGS_OS_win32 =
TEST_LDFLAGS_OS_win64 =
TEST_LDFLAGS_OS_macos = 
TEST_LDFLAGS_OS_linux = 
TEST_LDFLAGS_OS_other = 
TEST_LDFLAGS_OS_emscripten = 

#! This variable is intentionally empty, to specify additional C linker options from the commandline
TEST_LDFLAGS_EXTRA ?= \



#! GNU conventional variable: C libraries to link against
TEST_LDLIBS = \
	$(NAME_LIBMODE) \
	$(TEST_LDLIBS_MODE) \
	$(TEST_LDLIBS_OS) \
	$(TEST_LDLIBS_EXTRA)

#! Linked libraries which are specific to the current build mode, according to $(MODE)
TEST_LDLIBS_MODE = $(TEST_LDLIBS_MODE_$(MODE))
TEST_LDLIBS_MODE_debug = 
TEST_LDLIBS_MODE_release = 

#! Linked libraries which are platform-specific, according to $(OSMODE)
TEST_LDLIBS_OS = $(TEST_LDLIBS_OS_$(OSMODE))
TEST_LDLIBS_OS_win32 = 
TEST_LDLIBS_OS_win64 = 
TEST_LDLIBS_OS_macos = 
TEST_LDLIBS_OS_linux = -lm
TEST_LDLIBS_OS_other = 
TEST_LDLIBS_OS_emscripten = -lm
ifneq ($(findstring mingw,$(CC)),)
TEST_LDLIBS_OS += -L./ -static-libgcc
endif

#! This variable is intentionally empty, to specify additional linked libraries from the commandline
TEST_LDLIBS_EXTRA ?= \
#	-L/usr/local/lib -ltsan \



#! GNU conventional variable: List of included folders, which store header code files
TEST_INCLUDES = \
	-I$(HDRDIR) \
	-I$(TESTDIR) \
	$(TEST_INCLUDES_MODE) \
	$(TEST_INCLUDES_OS) \
	$(TEST_INCLUDES_EXTRA)

#! Header directories which are specific to the current build mode, according to $(MODE)
TEST_INCLUDES_MODE = $(TEST_INCLUDES_MODE_$(MODE))
TEST_INCLUDES_MODE_debug = 
TEST_INCLUDES_MODE_release = 

#! Header directories which are platform-specific, according to $(OSMODE)
TEST_INCLUDES_OS = $(TEST_INCLUDES_OS_$(OSMODE))
TEST_INCLUDES_OS_win32 = 
TEST_INCLUDES_OS_win64 = 
TEST_INCLUDES_OS_macos = 
TEST_INCLUDES_OS_linux = 
TEST_INCLUDES_OS_other = 
TEST_INCLUDES_OS_emscripten = 

#! This variable is intentionally empty, to specify additional header directories from the commandline
TEST_INCLUDES_EXTRA ?= \



#! The directory in which to store text logs of the test suite output
TEST_LOGDIR = $(LOGDIR)test/
