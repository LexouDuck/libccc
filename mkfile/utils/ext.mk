#! This file holds cross-platform convenience variables to abstract-away file extensions



#! This allows us to refer to executables, across any platform
ifeq ($(OS),Windows_NT)
	EXT_EXE=.exe
else
	EXT_EXE=
endif



#! The file extension used for static library files
EXT_LIB_STATIC=.a

#! The file extension used for dynamic library files
EXT_LIB_DYNAMIC=
ifeq ($(OS),Windows_NT)
	EXT_LIB_DYNAMIC=.dll
else
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		EXT_LIB_DYNAMIC=.dylib
	else
		ifeq ($(UNAME_S),Linux)
			EXT_LIB_DYNAMIC=.so
		else
			$(error Unsupported platform: you must configure the dynamic library file extension your machine uses)
		endif
	endif
endif
