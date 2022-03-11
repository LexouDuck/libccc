#! This file define an emscripten-* rule as a `emmake make *` wrapper to every relevant rule


#
# All of the commented rules are still TODO, or 'figure out wether using the rule with emscripten makes sense'
#

EMMAKE = emmake

.PHONY: \
emscripten #! Emscripten wrapper for "make" (same as `emmake make`)
emscripten:
	$(EMMAKE) $(MAKE)

.PHONY: \
all #! Emscripten wrapper for "make all" (same as `emmake make all`): Builds all targets (this is the default rule)
emscripten-all:
	$(EMMAKE) $(MAKE) all

.PHONY: \
re #! Emscripten wrapper for "make re" (same as `emmake make re`): Deletes all generated files and rebuilds `all`
emscripten-re:
	$(EMMAKE) $(MAKE) re

#
# prereq.mk
#

# .PHONY: \
# emscripten-prereq #! Emscripten wrapper for "make prereq" (same as `emmake make prereq`): Checks all prerequisite tools/programs and their versions
# emscripten-prereq:
# 	$(EMMAKE) $(MAKE) prereq

#
# packages.mk
#

# .PHONY: \
# emscripten-packages #! Emscripten wrapper for "make packages" (same as `emmake make packages`): This rule builds/prepares the dependency external packages
# emscripten-packages:
# 	$(EMMAKE) $(MAKE) packages

# .PHONY: \
# emscripten-update-all #! Emscripten wrapper for "make update-all" (same as `emmake make update-all`): This rule update the dependency external packages to their latest versions
# emscripten-update-all:
# 	$(EMMAKE) $(MAKE) update-all


#
# lists.mk
#

# .PHONY: \
# emscripten-lists #! Emscripten wrapper for "make lists" (same as `emmake make lists`): Create/update the list of source/header files
# emscripten-lists:
# 	$(EMMAKE) $(MAKE) lists

# .PHONY: \
# emscripten-show-lists #! Emscripten wrapper for "make show-lists" (same as `emmake make show-lists`): Display the list of source/header files
# emscripten-show-lists:
# 	$(EMMAKE) $(MAKE) show-lists


#
# build.mk
#

.PHONY: \
emscripten-build-debug #! Emscripten wrapper for "make build-debug" (same as `emmake make build-debug`): Builds the library, in 'debug' mode (with debug flags and symbol-info)
emscripten-build-debug:
	$(EMMAKE) $(MAKE) build-debug

.PHONY: \
emscripten-build-release #! Emscripten wrapper for "make build-release" (same as `emmake make build-release`): Builds the library, in 'release' mode (with optimization flags)
emscripten-build-release:
	$(EMMAKE) $(MAKE) build-release

.PHONY: \
emscripten-prereq-build #! Emscripten wrapper for "make prereq-build" (same as `emmake make prereq-build`): Checks prerequisite installed tools to build a library
emscripten-prereq-build:
	$(EMMAKE) $(MAKE) prereq-build


#
# lists-tests.mk
#

# .PHONY: \
# emscripten-lists-tests #! Emscripten wrapper for "make lists-tests" (same as `emmake make lists-tests`): Create/update the list of source/header files for the test suite program
# emscripten-lists-tests:
# 	$(EMMAKE) $(MAKE) lists-tests

# .PHONY: \
# emscripten-show-lists-tests #! Emscripten wrapper for "make show-lists-tests" (same as `emmake make show-lists-tests`): Display the list of source/header files
# emscripten-show-lists-tests:
# 	$(EMMAKE) $(MAKE) show-lists-tests


#
# build-tests.mk
#

# .PHONY: \
# emscripten-build-tests-debug #! Emscripten wrapper for "make build-tests-debug" (same as `emmake make build-tests-debug`): Builds the library, in 'debug' mode (with debug flags and symbol-info)
# emscripten-build-tests-debug:
# 	$(EMMAKE) $(MAKE) build-tests-debug

# .PHONY: \
# emscripten-build-tests-release #! Emscripten wrapper for "make build-tests-release" (same as `emmake make build-tests-release`): Builds the library, in 'release' mode (with optimization flags)
# emscripten-build-tests-release:
# 	$(EMMAKE) $(MAKE) build-tests-release

# .PHONY: \
# emscripten-clean-tests #! Emscripten wrapper for "make clean-tests" (same as `emmake make clean-tests`): Deletes all intermediary tests-related files
# emscripten-clean-tests:
# 	$(EMMAKE) $(MAKE) clean-tests

# .PHONY: \
# emscripten-clean-tests-obj #! Emscripten wrapper for "make clean-tests-obj" (same as `emmake make clean-tests-obj`): Deletes all .o tests object files
# emscripten-clean-tests-obj:
# 	$(EMMAKE) $(MAKE) clean-tests-obj

# .PHONY: \
# emscripten-clean-tests-dep #! Emscripten wrapper for "make clean-tests-dep" (same as `emmake make clean-tests-dep`): Deletes all .d tests dependency files
# emscripten-clean-tests-dep:
# 	$(EMMAKE) $(MAKE) clean-tests-dep

.PHONY: \
# emscripten-clean-tests-exe #! Emscripten wrapper for "make clean-tests-exe" (same as `emmake make clean-tests-exe`): Deletes the built test program in the root project folder
# emscripten-clean-tests-exe:
# 	$(EMMAKE) $(MAKE) clean-tests-exe


#
# dist.mk
#

# .PHONY: \
# emscripten-dist-all #! Emscripten wrapper for "make dist-all" (same as `emmake make dist-all`): Prepares .zip archives in ./dist for each platform from the contents of the ./bin folder
# emscripten-dist-all:
# 	$(EMMAKE) $(MAKE) dist-all

# .PHONY: \
# emscripten-dist #! Emscripten wrapper for "make dist" (same as `emmake make dist`): Creates a .zip distributable according to the current 'OSMODE' and 'LIBMODE'
# emscripten-dist:
# 	$(EMMAKE) $(MAKE) dist

# .PHONY: \
# emscripten-mkdir-dist #! Emscripten wrapper for "make mkdir-dist" (same as `emmake make mkdir-dist`): Creates the distributable builds folder
# emscripten-mkdir-dist:
# 	$(EMMAKE) $(MAKE) mkdir-dist

# .PHONY: \
# emscripten-clean-dist #! Emscripten wrapper for "make clean-dist" (same as `emmake make clean-dist`): Deletes the distributable builds folder
# emscripten-clean-dist:
# 	$(EMMAKE) $(MAKE) clean-dist


#
# clean.mk
#

.PHONY: \
emscripten-clean #! Emscripten wrapper for "make clean" (same as `emmake make clean`): Deletes files generated by the `make all` default rule
emscripten-clean:
	$(EMMAKE) $(MAKE) clean

.PHONY: \
emscripten-clean-all #! Emscripten wrapper for "make clean-all" (same as `emmake make clean-all`): Deletes every generated file/folder
emscripten-clean-all:
	$(EMMAKE) $(MAKE) clean-all


#
# test.mk
#

.PHONY: \
emscripten-test #! Emscripten wrapper for "make test" (same as `emmake make test`): Runs the test suite program, with the given 'ARGS'
emscripten-test:
	$(EMMAKE) $(MAKE) test

# .PHONY: \
# emscripten-test-logs #! Emscripten wrapper for "make test-logs" (same as `emmake make test-logs`): Builds and runs the test suite program with the given 'ARGS', logging all results to files
# emscripten-test-logs:
# 	$(EMMAKE) $(MAKE) test-logs

# .PHONY: \
# emscripten-clean-test-logs #! Emscripten wrapper for "make clean-test-logs" (same as `emmake make clean-test-logs`): Deletes any test suite logs
# emscripten-clean-test-logs:
# 	$(EMMAKE) $(MAKE) clean-test-logs

# .PHONY: \
# emscripten-test-memory #! Emscripten wrapper for "make test-memory" (same as `emmake make test-memory`): Builds and runs the test suite program with the given 'ARGS', checking for memory leaks
# emscripten-test-memory:
# 	$(EMMAKE) $(MAKE) test-memory

# .PHONY: \
# emscripten-prereq-tests #! Emscripten wrapper for "make prereq-tests" (same as `emmake make prereq-tests`): Checks prerequisite installs to run the various tests
# emscripten-prereq-tests:
# 	$(EMMAKE) $(MAKE) prereq-tests


#
# coverage.mk
#

# .PHONY: \
# emscripten-test-coverage #! Emscripten wrapper for "make test-coverage" (same as `emmake make test-coverage`): Generates simple text file output reports for code-coverage tests
# emscripten-test-coverage:
# 	$(EMMAKE) $(MAKE) test-coverage

# .PHONY: \
# emscripten-coverage #! Emscripten wrapper for "make coverage" (same as `emmake make coverage`): Generates human-readable HTML output reports for code-coverage tests
# emscripten-coverage:
# 	$(EMMAKE) $(MAKE) coverage

# .PHONY: \
# emscripten-clean-coverage #! Emscripten wrapper for "make clean-coverage" (same as `emmake make clean-coverage`): Deletes all files generated by the `make coverage` rule
# emscripten-clean-coverage:
# 	$(EMMAKE) $(MAKE) clean-coverage

# .PHONY: \
# emscripten-prereq-coverage #! Emscripten wrapper for "make prereq-coverage" (same as `emmake make prereq-coverage`): Checks prerequisite installs to run the automatic code style formatter
# emscripten-prereq-coverage:
# 	$(EMMAKE) $(MAKE) prereq-coverage


#
# debugging.mk
#

# .PHONY: \
# emscripten-debug-macros #! Emscripten wrapper for "make debug-macros" (same as `emmake make debug-macros`): Preprocesses all source files and stores them in the obj folder
# emscripten-debug-macros:
# 	$(EMMAKE) $(MAKE) debug-macros

# .PHONY: \
# emscripten-debug-symbols #! Emscripten wrapper for "make debug-symbols" (same as `emmake make debug-symbols`): Outputs the list of symbols found inside the given `ARGS` binary/ies
# emscripten-debug-symbols:
# 	$(EMMAKE) $(MAKE) debug-symbols

# .PHONY: \
# emscripten-debug-linking #! Emscripten wrapper for "make debug-linking" (same as `emmake make debug-linking`): Outputs the list of linking paths to find dynamic libraries for the given `ARGS`
# emscripten-debug-linking:
# 	$(EMMAKE) $(MAKE) debug-linking

#
# test-env.mk
#

# .PHONY: \
# emscripten-test-env-predef #! Emscripten wrapper for "make test-env-predef" (same as `emmake make test-env-predef`): Gets the list of all predefined macros for the current compiler/flags/env/arch
# emscripten-test-env-predef:
# 	$(EMMAKE) $(MAKE) test-env-predef

# .PHONY: \
# emscripten-test-env-errno #! Emscripten wrapper for "make test-env-errno" (same as `emmake make test-env-errno`): Gets the list of all 'errno' values for the current compiler/flags/env/arch
# emscripten-test-env-errno:
# 	$(EMMAKE) $(MAKE) test-env-errno


#
# test-standalone.mk
#

# .PHONY: \
# emscripten-test-helloworld #! Emscripten wrapper for "make test-helloworld" (same as `emmake make test-helloworld`): Builds and runs a simple 'Hello World!' test program
# emscripten-test-helloworld:
# 	$(EMMAKE) $(MAKE) test-helloworld

# .PHONY: \
# emscripten-test-foreach #! Emscripten wrapper for "make test-foreach" (same as `emmake make test-foreach`): Builds and runs a simple test program for the 'foreach ()' macro
# emscripten-test-foreach:
# 	$(EMMAKE) $(MAKE) test-foreach

# .PHONY: \
# emscripten-test-kvt #! Emscripten wrapper for "make test-kvt" (same as `emmake make test-kvt`): Builds and runs a KVT (json,toml,yaml,xml) print/parse test program
# emscripten-test-kvt:
# 	$(EMMAKE) $(MAKE) test-kvt

# .PHONY: \
# emscripten-test-undefined #! Emscripten wrapper for "make test-undefined" (same as `emmake make test-undefined`): Builds and runs a simple test program to check if headers expose any undefined functions
# emscripten-test-undefined:
# 	$(EMMAKE) $(MAKE) test-undefined

# .PHONY: \
# emscripten-$(SRCS_TEST_UNDEFINED) #! Emscripten wrapper for "make $(SRCS_TEST_UNDEFINED)" (same as `emmake make $(SRCS_TEST_UNDEFINED)`): Generates a .c file which calls every function declared from every header in the project
# emscripten-$(SRCS_TEST_UNDEFINED):
# 	$(EMMAKE) $(MAKE) $(SRCS_TEST_UNDEFINED)

