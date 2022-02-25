#! This file holds the variables which configure the code compilation



#! GNU conventional variable: C Compiler
CC = $(CC_OS)

CC_OS = _
CC_OS_WIN32 =   i686-w64-mingw32-gcc
CC_OS_WIN64 = x86_64-w64-mingw32-gcc
CC_OS_LINUX = gcc
CC_OS_MACOS = clang
CC_OS_OTHER = cc



#! GNU conventional variable: C Compiler flags & settings
CFLAGS = \
	-Werror \
	-Wall \
	-Wextra \
	-Winline \
	-Wpedantic \
	-Wstrict-prototypes \
	-Wmissing-prototypes \
	-Wold-style-definition \
	-Wno-format-extra-args \
	-fstrict-aliasing \
	$(CFLAGS_OS) $(CFLAGS_EXTRA)

#! Compiler flags which are only present in "debug" build mode
CFLAGS_DEBUG = \
	-g \
	-ggdb \
	-D DEBUG=1 \
#	-D __NOSTD__=1 \

#! Compiler flags which are only present in "release" build mode
CFLAGS_RELEASE = \
	-O3 \

CFLAGS_OS = _
CFLAGS_OS_WIN32 = -D__USE_MINGW_ANSI_STDIO=1
CFLAGS_OS_WIN64 = -D__USE_MINGW_ANSI_STDIO=1
CFLAGS_OS_LINUX = -Wno-unused-result -fPIC -pedantic
CFLAGS_OS_MACOS = -Wno-missing-braces -Wno-language-extension-token
CFLAGS_OS_OTHER = 

#! This variable is intentionally empty, to specify additional CFLAGS from the commandline
CFLAGS_EXTRA ?= 
#	-fsanitize=address \
#	-fsanitize=thread \
#	-fanalyzer \

ifeq ($(CC),clang)
	CFLAGS_OS_WIN += -Wno-missing-braces -fno-ms-compatibility -fgnuc-version=4.2.1
endif



#! GNU conventional variable: C Linker flags & settings
LDFLAGS = \
	$(LDFLAGS_OS) $(LDFLAGS_EXTRA)

LDFLAGS_DEBUG   = 
LDFLAGS_RELEASE = 

LDFLAGS_OS = _
LDFLAGS_OS_WIN32 = 
LDFLAGS_OS_WIN64 = 
LDFLAGS_OS_LINUX = 
LDFLAGS_OS_MACOS = 
LDFLAGS_OS_OTHER = 

LDFLAGS_EXTRA ?= 
#	-flto \



#! GNU conventional variable: List of libraries to link against
LDLIBS = \
	$(LDLIBS_OS) $(LDLIBS_EXTRA)

LDLIBS_DEBUG   = 
LDLIBS_RELEASE = 

LDLIBS_OS = _
LDLIBS_OS_WIN32 = -L./ -static-libgcc
LDLIBS_OS_WIN64 = -L./ -static-libgcc
LDLIBS_OS_LINUX = 
LDLIBS_OS_MACOS = 
LDLIBS_OS_OTHER = 

LDLIBS_EXTRA ?= 
#	-D__NOSTD__=1 \
#	-L/usr/local/lib -ltsan \
#	-Wl,-rpath,bin/linux/dynamic/ \
#	-Wl,-rpath='$$ORIGIN/' \



#! GNU conventional variable: List of folders which store header code files
INCLUDES = \
	-I$(HDRDIR) \
	$(INCLUDES_OS) $(INCLUDES_EXTRA)

INCLUDES_DEBUG   = 
INCLUDES_RELEASE = 

INCLUDES_OS = _
INCLUDES_OS_WIN32 = 
INCLUDES_OS_WIN64 = 
INCLUDES_OS_LINUX = 
INCLUDES_OS_MACOS = 
INCLUDES_OS_OTHER = 



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
	-D \



# Set platform-specific variables
ifeq ($(OSMODE),other)
	CC_OS       =       $(CC_OS_OTHER)
	CFLAGS_OS   =   $(CFLAGS_OS_OTHER)
	LDFLAGS_OS  =  $(LDFLAGS_OS_OTHER)
	LDLIBS_OS   =   $(LDLIBS_OS_OTHER)
	INCLUDES_OS = $(INCLUDES_OS_OTHER)
else ifeq ($(OSMODE),win32)
	CC_OS       =       $(CC_OS_WIN32)
	CFLAGS_OS   =   $(CFLAGS_OS_WIN32)
	LDFLAGS_OS  =  $(LDFLAGS_OS_WIN32)
	LDLIBS_OS   =   $(LDLIBS_OS_WIN32)
	INCLUDES_OS = $(INCLUDES_OS_WIN32)
else ifeq ($(OSMODE),win64)
	CC_OS       =       $(CC_OS_WIN64)
	CFLAGS_OS   =   $(CFLAGS_OS_WIN64)
	LDFLAGS_OS  =  $(LDFLAGS_OS_WIN64)
	LDLIBS_OS   =   $(LDLIBS_OS_WIN64)
	INCLUDES_OS = $(INCLUDES_OS_WIN64)
else ifeq ($(OSMODE),linux)
	CC_OS       =       $(CC_OS_LINUX)
	CFLAGS_OS   =   $(CFLAGS_OS_LINUX)
	LDFLAGS_OS  =  $(LDFLAGS_OS_LINUX)
	LDLIBS_OS   =   $(LDLIBS_OS_LINUX)
	INCLUDES_OS = $(INCLUDES_OS_LINUX)
else ifeq ($(OSMODE),macos)
	CC_OS       =       $(CC_OS_MACOS)
	CFLAGS_OS   =   $(CFLAGS_OS_MACOS)
	LDFLAGS_OS  =  $(LDFLAGS_OS_MACOS)
	LDLIBS_OS   =   $(LDLIBS_OS_MACOS)
	INCLUDES_OS = $(INCLUDES_OS_MACOS)
endif
