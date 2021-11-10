#! This file holds configuration variables for the test suite compilation

#! C compiler config flags
TEST_CFLAGS = \
	-O2 \
	-g -ggdb \
	-Wall \
	-Wextra \
	-Wno-format-extra-args \
	-fno-inline \
#	-fanalyzer

#! C linker config flags
TEST_LDFLAGS = $(LDFLAGS)



#! C header file paths
TEST_INCLUDES = \
	-I$(HDRDIR) \
	-I$(TEST_DIR) \



#! C libraries to link with
TEST_LDLIBS = -L./ \
	-lccc \
	-lpthread \
	-lm \

ifneq ($(OSMODE),macos)
	TEST_LDLIBS := -static $(TEST_LDLIBS)
endif
