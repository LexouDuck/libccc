# This file holds some convenience variables which are useful in any project



# The escape sequences for colored terminal output (ANSI)
C_RESET  = "\033[0m"
C_RED    = "\033[0;31m"
C_GREEN  = "\033[0;32m"
C_YELLOW = "\033[0;33m"
C_BLUE   = "\033[0;34m"
C_MAGENTA= "\033[0;35m"
C_CYAN   = "\033[0;36m"



# This allows us to use 'sudo' for certain operations while remaining cross-platform
ifeq ($(OSMODE),win32)
	SUDO =
endif
ifeq ($(OSMODE),win64)
	SUDO =
endif
ifeq ($(OSMODE),linux)
	SUDO = sudo
endif
ifeq ($(OSMODE),macos)
	SUDO = sudo
endif



# The file extension used for static library files
LIBEXT_STATIC=a

# The file extension used for dynamic library files
ifeq ($(OSMODE),other)
	LIBEXT_DYNAMIC=
else ifeq ($(OSMODE),win32)
	LIBEXT_DYNAMIC=dll
else ifeq ($(OSMODE),win64)
	LIBEXT_DYNAMIC=dll
else ifeq ($(OSMODE),linux)
	LIBEXT_DYNAMIC=so
else ifeq ($(OSMODE),macos)
	LIBEXT_DYNAMIC=dylib
else
	$(error Unsupported platform: you must configure the dynamic library file extension your machine uses)
endif
