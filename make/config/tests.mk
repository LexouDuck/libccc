# This file holds configuration variables for the test suite compilation

# C compiler config flags
TEST_CFLAGS = -O2 -g -ggdb \
	-Wno-format-extra-args \
	-fno-inline \
#	-fanalyzer

# C linker config flags
TEST_LDFLAGS = $(LDFLAGS)



# C header file paths
TEST_INCLUDEDIRS = \
	-I$(HDRDIR) \
	-I$(TEST_DIR) \



# C libraries to link with
TEST_LIBS = -L./ \
	-lccc \
	-lpthread \
	-lm \

ifneq ($(OSMODE),macos)
	TEST_LIBS := -static $(TEST_LIBS)
endif
