# This file holds the variables which configure the code compiler

# Compiler
CC	= _
CC_WIN32 =   i686-w64-mingw32-gcc
CC_WIN64 = x86_64-w64-mingw32-gcc
CC_LINUX = gcc
CC_MACOS = clang



# Compiler flags
CFLAGS = $(CFLAGS_OS) $(CFLAGS_EXTRA) \
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
#	-L/usr/local/lib -ltsan
#	-fsanitize=address
#	-fsanitize=thread
#	-fanalyzer
CFLAGS_DEBUG = -g -ggdb -D DEBUG=1 # -D__NOSTD__=1
CFLAGS_RELEASE = -O3
#	-flto
CFLAGS_OS = _
CFLAGS_OS_WIN32 = -D__USE_MINGW_ANSI_STDIO=1
CFLAGS_OS_WIN64 = -D__USE_MINGW_ANSI_STDIO=1
CFLAGS_OS_LINUX = -Wno-unused-result -fPIC -pedantic
CFLAGS_OS_MACOS = -Wno-missing-braces -Wno-language-extension-token
CFLAGS_OS_OTHER = 
ifeq ($(CC),clang)
	CFLAGS_OS_WIN += -Wno-missing-braces
else
	CFLAGS_OS_WIN += -D__USE_MINGW_ANSI_STDIO=1
endif
CFLAGS_EXTRA = 



# Linker flags
LDFLAGS = $(LDFLAGS_OS) $(CFLAGS_EXTRA)
#	-fsanitize=address
#	-Wl,-rpath,bin/linux/dynamic/
#	-Wl,-rpath='$$ORIGIN/'
LDFLAGS_OS = _
LDFLAGS_OS_WIN32 = 
LDFLAGS_OS_WIN64 = 
LDFLAGS_OS_LINUX = 
LDFLAGS_OS_MACOS = 
LDFLAGS_OS_OTHER = 
ifeq ($(CC),clang)
	LDFLAGS_OS_WIN += -L/lib
else
	LDFLAGS_OS_WIN += -L./ -static-libgcc
endif
LDFLAGS_EXTRA = 



# Set platform-specific variables
ifeq ($(OSMODE),other)
	CC         =         $(CC_OTHER)
	CFLAGS_OS  =  $(CFLAGS_OS_OTHER)
	LDFLAGS_OS = $(LDFLAGS_OS_OTHER)
else ifeq ($(OSMODE),win32)
	CC         =         $(CC_WIN32)
	CFLAGS_OS  =  $(CFLAGS_OS_WIN32)
	LDFLAGS_OS = $(LDFLAGS_OS_WIN32)
else ifeq ($(OSMODE),win64)
	CC         =         $(CC_WIN64)
	CFLAGS_OS  =  $(CFLAGS_OS_WIN64)
	LDFLAGS_OS = $(LDFLAGS_OS_WIN64)
else ifeq ($(OSMODE),linux)
	CC         =         $(CC_LINUX)
	CFLAGS_OS  =  $(CFLAGS_OS_LINUX)
	LDFLAGS_OS = $(LDFLAGS_OS_LINUX)
else ifeq ($(OSMODE),macos)
	CC         =         $(CC_MACOS)
	CFLAGS_OS  =  $(CFLAGS_OS_MACOS)
	LDFLAGS_OS = $(LDFLAGS_OS_MACOS)
endif
