#! This file holds the variables which configure the code compilation



#! GNU conventional variable: archiver program (for static libraries)
AR = ar
#! GNU conventional variable: archiver program options
ARFLAGS = \
	-r \
	-c \

#! GNU conventional variable: archive symbol table tool (for static libraries)
RANLIB = ranlib
#! GNU conventional variable: archive symbol table tool options
RANLIB_FLAGS = \

ifdef __EMSCRIPTEN__
AR = emar
RANLIB = emranlib
endif



#! GNU conventional variable: C compiler
CC = $(CC_OS)
#! C compiler platform-specific variable, according to $(OSMODE)
CC_OS = $(CC_OS_$(OSMODE))
CC_OS_windows = $(if $(findstring 64,$(CPUMODE)),x86_64-w64-mingw32-gcc,i686-w64-mingw32-gcc)
CC_OS_macos = clang
CC_OS_linux = gcc
CC_OS_other = cc
CC_OS_emscripten = emcc



#! GNU conventional variable: C compiler options
CFLAGS = \
	-Werror \
	-Wall \
	-Wextra \
	-Winline \
	-Wpedantic \
	-fstrict-aliasing \
	$(CFLAGS_BUILDMODE) \
	$(CFLAGS_OS) \
	$(CFLAGS_EXTRA)

#! C compiler options which are specific to the current build mode, according to $(BUILDMODE)
CFLAGS_BUILDMODE = $(CFLAGS_BUILDMODE_$(BUILDMODE))
#! C compiler flags which are only present in "debug" build mode
CFLAGS_BUILDMODE_debug = \
	-g \
	-ggdb \
	-D DEBUG=1
#! C compiler flags which are only present in "release" build mode
CFLAGS_BUILDMODE_release = \
	-O3 \
	-D RELEASE=1

#! C compiler options which are platform-specific, according to $(OSMODE)
CFLAGS_OS = $(CFLAGS_OS_$(OSMODE))
CFLAGS_OS_windows = -fvisibility=default # -fno-ms-compatibility
CFLAGS_OS_macos = -Wno-language-extension-token
CFLAGS_OS_linux = -Wno-unused-result -fPIC
CFLAGS_OS_other = 
CFLAGS_OS_emscripten = -Wno-unused-result -fPIC -pedantic
ifneq ($(findstring mingw,$(CC)),)
	CFLAGS_OS += -D__USE_MINGW_ANSI_STDIO=1
endif
ifneq ($(findstring clang,$(CC)),)
	CFLAGS_OS += -Wno-missing-braces
	CFLAGS_OS_windows += -target x86_64-pc-windows-msvc # -Wl,-lldmingw -Wl,-dll -Wl,-export-all-symbols
else
	CFLAGS_OS += -Wno-unused-value
endif

#! This variable is intentionally empty, to specify additional C compiler options from the commandline
CFLAGS_EXTRA ?= \
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
CFLAGS_EXTRA += \
	-std=c++20 \
	-Wno-pedantic \
	-Wno-deprecated \
	-Wno-variadic-macros \
	-Wno-c99-extensions \
	-Wno-c++11-extensions \
	-Wno-c++17-extensions \
	-Wno-return-type-c-linkage \
	-Wno-missing-field-initializers \

else
CFLAGS_EXTRA += \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wold-style-definition \

endif

# this fix allows libccc to build on iOS platforms
ifneq ($(findstring iPhone,$(UNAME_M)),)
CFLAGS_EXTRA += -D__IOS__
endif



#! GNU conventional variable: C linker options
LDFLAGS = \
	$(LDFLAGS_BUILDMODE) \
	$(LDFLAGS_OS) \
	$(LDFLAGS_EXTRA)

#! C linker options which are specific to the current build mode, according to $(BUILDMODE)
LDFLAGS_BUILDMODE = $(LDFLAGS_BUILDMODE_$(BUILDMODE))
LDFLAGS_BUILDMODE_debug = 
LDFLAGS_BUILDMODE_release = 

#! C linker options which are platform-specific, according to $(OSMODE)
LDFLAGS_OS = $(LDFLAGS_OS_$(OSMODE))
LDFLAGS_OS_windows = 
LDFLAGS_OS_macos = 
LDFLAGS_OS_linux = 
LDFLAGS_OS_other = 
LDFLAGS_OS_emscripten = 
ifneq ($(findstring clang,$(CC)),)
	LDFLAGS_OS_macos += -current_version       $(VERSION)
	LDFLAGS_OS_macos += -compatibility_version $(VERSION)
	LDFLAGS_OS_windows += -lclang_rt.builtins.x86_64
endif

#! This variable is intentionally empty, to specify additional C linker options from the commandline
LDFLAGS_EXTRA ?= \

ifdef __EMSCRIPTEN__
LDFLAGS_BUILDMODE_debug += \
	-s ASSERTIONS=2 \
	-s SAFE_HEAP=1 \
	-s STACK_OVERFLOW_CHECK=1 \

endif



#! GNU conventional variable: C libraries to link against
LDLIBS = \
	$(LDLIBS_BUILDMODE) \
	$(LDLIBS_OS) \
	$(LDLIBS_EXTRA)

#! Linked libraries which are specific to the current build mode, according to $(BUILDMODE)
LDLIBS_BUILDMODE = $(LDLIBS_BUILDMODE_$(BUILDMODE))
LDLIBS_BUILDMODE_debug = 
LDLIBS_BUILDMODE_release = 

#! Linked libraries which are platform-specific, according to $(OSMODE)
LDLIBS_OS = $(LDLIBS_OS_$(OSMODE))
LDLIBS_OS_windows = -L./
LDLIBS_OS_macos = 
LDLIBS_OS_linux = 
LDLIBS_OS_other = 
LDLIBS_OS_emscripten = 
ifneq ($(findstring mingw,$(CC)),)
	LDLIBS_OS_windows += -static-libgcc
endif

#! This variable is intentionally empty, to specify additional linked libraries from the commandline
LDLIBS_EXTRA ?= \
# -L/usr/local/lib -ltsan \



#! GNU conventional variable: List of included folders, which store header code files
INCLUDES = \
	-I$(HDRDIR) \
	$(INCLUDES_BUILDMODE) \
	$(INCLUDES_OS) \
	$(INCLUDES_EXTRA)

#! Header directories which are specific to the current build mode, according to $(BUILDMODE)
INCLUDES_BUILDMODE = $(INCLUDES_BUILDMODE_$(BUILDMODE))
INCLUDES_BUILDMODE_debug = 
INCLUDES_BUILDMODE_release = 

#! Header directories which are platform-specific, according to $(OSMODE)
INCLUDES_OS = $(INCLUDES_OS_$(OSMODE))
INCLUDES_OS_windows = 
INCLUDES_OS_macos = 
INCLUDES_OS_linux = 
INCLUDES_OS_other = 
INCLUDES_OS_emscripten = 

#! This variable is intentionally empty, to specify additional header directories from the commandline
INCLUDES_EXTRA ?= \



# do not compile with stdlib if user called `make STDLIBMODE=none`
ifeq ($(STDLIBMODE),none)
CFLAGS += -D __NOSTD__=1
TARGETDIR = $(BUILDMODE)_$(OSMODE)_$(CPUMODE)_nostdlib
endif
