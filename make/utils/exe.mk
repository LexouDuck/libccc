#! This file holds a cross-platform variables to run/manipulate executables



#! This allows us to refer to executables, across any platform
ifeq ($(OS),Windows_NT)
	EXE = .exe
else
	EXE = 
endif
