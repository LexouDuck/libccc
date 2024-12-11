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
	$(TEST_CFLAGS_BUILDMODE) \
	$(TEST_CFLAGS_OS) \
	$(TEST_CFLAGS_EXTRA)

#! C compiler options which are specific to the current build mode, according to $(BUILDMODE)
TEST_CFLAGS_BUILDMODE = $(TEST_CFLAGS_BUILDMODE_$(BUILDMODE))
#! C compiler flags which are only present in "debug" build mode
TEST_CFLAGS_BUILDMODE_debug = \
	-g \
	-ggdb \
	-D DEBUG=1
#! C compiler flags which are only present in "release" build mode
TEST_CFLAGS_BUILDMODE_release = \
	-O3 \
	-D RELEASE=1

#! C compiler options which are platform-specific, according to $(OSMODE)
TEST_CFLAGS_OS = $(TEST_CFLAGS_OS_$(OSMODE))
TEST_CFLAGS_OS_windows = -fvisibility=default # -fno-ms-compatibility
TEST_CFLAGS_OS_macos = -Wno-language-extension-token
TEST_CFLAGS_OS_linux = -Wno-unused-result -fPIC
TEST_CFLAGS_OS_other = 
TEST_CFLAGS_OS_emscripten = 
ifneq ($(findstring clang,$(CC)),)
	TEST_CFLAGS_OS += -Wno-missing-braces
	TEST_CFLAGS_OS_windows += -target x86_64-pc-windows-msvc
else
	TEST_CFLAGS_OS += -Wno-unused-value
endif
ifneq ($(findstring mingw,$(CC)),)
	TEST_CFLAGS_OS += -D__USE_MINGW_ANSI_STDIO=1
endif

#! This variable is intentionally empty, to specify additional C compiler options from the commandline
TEST_CFLAGS_EXTRA ?= \
#	-std=c99 \
#	-std=c11 \
#	-std=c23 \
#	-flto \
#	-fanalyzer \
#	-fsanitize=address \
#	-fsanitize=thread \
#	-std=ansi -pedantic \
#	-D __NOSTD__=1 \

# these fixes allow libccc to be compiled using a C++ compiler
ifneq ($(findstring ++,$(CC)),)
TEST_CFLAGS_EXTRA += \
	-Wno-deprecated \
	-Wno-variadic-macros \
	-Wno-c99-extensions \
	-Wno-c++11-extensions \
	-Wno-c++17-extensions \
	-Wno-return-type-c-linkage \

endif

# this fix allows libccc to build on iOS platforms
ifneq ($(findstring iPhone,$(UNAME_M)),)
TEST_CFLAGS_EXTRA += -D__IOS__
endif



#! GNU conventional variable: C linker options
TEST_LDFLAGS = \
	$(TEST_LDFLAGS_BUILDMODE) \
	$(TEST_LDFLAGS_OS) \
	$(TEST_LDFLAGS_EXTRA)

#! C linker options which are specific to the current build mode, according to $(BUILDMODE)
TEST_LDFLAGS_BUILDMODE = $(TEST_LDFLAGS_BUILDMODE_$(BUILDMODE))
TEST_LDFLAGS_BUILDMODE_debug = 
TEST_LDFLAGS_BUILDMODE_release = 

#! C linker options which are platform-specific, according to $(OSMODE)
TEST_LDFLAGS_OS = $(TEST_LDFLAGS_OS_$(OSMODE))
TEST_LDFLAGS_OS_windows = 
TEST_LDFLAGS_OS_macos = 
TEST_LDFLAGS_OS_linux = 
TEST_LDFLAGS_OS_other = 
TEST_LDFLAGS_OS_emscripten = 

#! This variable is intentionally empty, to specify additional C linker options from the commandline
TEST_LDFLAGS_EXTRA ?= \



#! GNU conventional variable: C libraries to link against
TEST_LDLIBS = \
	$(BINPATH)$(LIBMODE)/$(NAME_LIBMODE) \
	$(TEST_LDLIBS_BUILDMODE) \
	$(TEST_LDLIBS_OS) \
	$(TEST_LDLIBS_EXTRA)

#! Linked libraries which are specific to the current build mode, according to $(BUILDMODE)
TEST_LDLIBS_BUILDMODE = $(TEST_LDLIBS_BUILDMODE_$(BUILDMODE))
TEST_LDLIBS_BUILDMODE_debug = 
TEST_LDLIBS_BUILDMODE_release = 

#! Linked libraries which are platform-specific, according to $(OSMODE)
TEST_LDLIBS_OS = $(TEST_LDLIBS_OS_$(OSMODE))
TEST_LDLIBS_OS_windows = -L./
TEST_LDLIBS_OS_macos = 
TEST_LDLIBS_OS_linux = -lm
TEST_LDLIBS_OS_other = 
TEST_LDLIBS_OS_emscripten = -lm
ifneq ($(findstring mingw,$(CC)),)
	TEST_LDLIBS_OS_windows += -static-libgcc -lpthread
endif
ifneq ($(findstring clang,$(CC)),)
endif

#! This variable is intentionally empty, to specify additional linked libraries from the commandline
TEST_LDLIBS_EXTRA ?= \
#	-L/usr/local/lib -ltsan \



#! GNU conventional variable: List of included folders, which store header code files
TEST_INCLUDES = \
	-I$(HDRDIR) \
	-I$(TESTDIR) \
	$(TEST_INCLUDES_BUILDMODE) \
	$(TEST_INCLUDES_OS) \
	$(TEST_INCLUDES_EXTRA)

#! Header directories which are specific to the current build mode, according to $(BUILDMODE)
TEST_INCLUDES_BUILDMODE = $(TEST_INCLUDES_BUILDMODE_$(BUILDMODE))
TEST_INCLUDES_BUILDMODE_debug = 
TEST_INCLUDES_BUILDMODE_release = 

#! Header directories which are platform-specific, according to $(OSMODE)
TEST_INCLUDES_OS = $(TEST_INCLUDES_OS_$(OSMODE))
TEST_INCLUDES_OS_windows = 
TEST_INCLUDES_OS_macos = 
TEST_INCLUDES_OS_linux = 
TEST_INCLUDES_OS_other = 
TEST_INCLUDES_OS_emscripten = 

#! This variable is intentionally empty, to specify additional header directories from the commandline
TEST_INCLUDES_EXTRA ?= \



#! The directory in which to store text logs of the test suite output
TEST_LOGDIR = $(LOGDIR)test/
