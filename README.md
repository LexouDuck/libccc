libccc
---
A comprehensive, cross-platform, customizable standard library for C

<a href="https://github.com/LexouDuck/libccc/actions">
	<img src="https://github.com/LexouDuck/libccc/workflows/CI+CD/badge.svg" />
</a>



The Project
---
The objective is to have one simple, well-documented, efficient open-source implementation of the C standard library, but with easier to use functions and types than what is offered by the ISO standards - mostly by consistently handling undefined behaviors, and handling edge cases in a consistent, coherent way, so as to have code that is as little machine-specific as possible.

The first step to accomplishing this is to avoid using the native int/long/short types, which can have different storage size depending on the platform
('int' is defined as the fastest integer type for the given machine, typically this will be the CPU register size - so on a 64-bit machine, that'd be int64, on a 32-bit machine int32, and some old embedded systems you come across might have 16-bit ints as the machine's default storage size). So first of all, using the integer types defined in "stdint.h" ('int32_t', 'uint64_t', etc) is essential for any cross-platform C code, as it ensures consistent cross-platform overflow behaviors (Note that these aren't present on every platform though - sometimes we will have to settle for the 'uint_fastX_t' types, but macros have been provided to make this switch simply). Of course, many times a platform-dependent "fast int" is the best thing to use, and this is made easy using libccc.

The following categories/headers include the ISO standard library (types, functions, macros):
* `bool.h`       : primitive boolean type (usually `_Bool`), and strtobool, booltostr, etc
* `char.h`       : functions to handle ANSI/ASCII characters (islower, isalpha, toupper, etc - but also `wchar_t` and UTF8 char handling)
* `int.h`        : integer number types, functions to replace the wonky STD C atoi/itoa functions with better type-specific conversion functions
* `float.h`      : floating-point types, functions to replace the wonky STD C atof/strtol functions with better type-specific conversion functions
* `pointer.h`    : important system types for pointer arithmetic (`size_t`, `ptrdiff_t`) and the functions associated with them
* `memory.h`     : functions to manipulate memory directly (memcpy, memset, memchr, etc - but also extras like memdup, memrep, getbits)
* `string.h`     : functions to manipulate strings (strcpy,strchr,strsub,etc but also extras such as strformat,strsplit,strmap)
* `math/float.h` : common mathematical functions operating on floating-point numbers (the implementations in this lib are fast-approximate versions, though by default LIBCONFIG_FAST_APPROX_MATH is defined as 0, so the functions are actually simple wrappers over the builtin FPU math functions)
* `sys/time.h`   : functions for handling times/dates/timezones/timespecs (handling of timezones is different from the stdlib 'global variable' tzset call)
* `sys/io.h`     : functions for reading and writing (from/to terminal, or from/to file(s) - wrapper functions over `unistd.h` and `stdio.h`)

Furthermore, there are other functions here that are not found in the ISO standard, particularly in the following categories:
* `libccc/fixed.h`        : fixed-point arithmetic, with a configurable fixed-point number type (regarding what portion is dedicated to the fractional part)
* `libccc/color.h`        : functions manipulating several common color encodings, as well as other useful color-related functions (like RGB_to_HSL, etc)
* `libccc/pointerarray.h` : a set of functions used to manipulate pointer arrays (`void **`, where the array is terminated by a NULL pointer)
* `libccc/stringarray.h`  : a set of functions used to manipulate string arrays (`char **`, where the array is terminated by a NULL pointer)
* `libccc/math/algebra.h` : math functions for 2D/3D/4D vectors and matrices, as well as integrals and more
* `libccc/math/random.h`  : functions for simple pseudo-random number generation (many more functions than just the ISO rand/srand/rand_r functions)
* `libccc/math/complex.h` : math functions for complex number operations, as well as quaternions
* `libccc/math/stat.h`    : statistics & probabilities functions: int/float number array sort functions, median, standard deviation, etc
* `libccc/math/vlq.h`     : Variable-Length Quantity math functions, for variable-size "big ints", "big fixed", and "big float" types.
* `libccc/monad/array.h`  : generic-type array functions (simply stores a contiguous memory buffer `.items` and a `.length`)
* `libccc/monad/list.h`   : generic-type linked-list functions (which can be configured to be singly-linked or doubly-linked)
* `libccc/monad/stack.h`  : generic-type stack functions (mainly push/pop, made to act like a FIFO/LILO type)
* `libccc/monad/queue.h`  : generic-type queue functions (mainly push/pop, made to act like a LIFO/FILO type)
* `libccc/monad/dict.h`   : generic-type dictionary (key/value pair) functions (access items via their string `key` rather than their index)
* `libccc/monad/tree.h`   : generic-type tree functions (each `struct tree` stores a value of type `T`)
* `libccc/monad/object.h` : generic-type nestable object, works similar to a JSON data structure (stores key/value pairs).
* `libccc/sys/regex.h`    : Regular Expression type and functions, based on the all-encompassing [Oniguruma](https://github.com/kkos/oniguruma) regex engine



Why does this exist ?
---
What started as a necessary exercise for the 42 school (called `libft`, as in "lib-forty-two") quickly became a much more expansive project, now dubbed `libccc` (for comprehensive, customizable, cross-platform). Whereas the 42 libft project only requires students to code a certain set of important memory/string/io functions, we decided to take this idea much further. The `libft` project is originally meant as an educational exercise, in which a student learns a lot by "reinventing the wheel" many times over. Here, the goal is to have a standard C library which is: fully cross-platform, uniformized, configurable and customizable, obviously being open source (MIT license) and which offers more than the "bare minimum" that is the C ISO standard library (not to mention, making edge case behaviors far more consistent across various platforms).



How to use this library
---
The Makefile simply builds a `libccc.a` library to link to your project. (eg: you can link it with something like `gcc main.c -I./libccc/hdr/ -L./libccc/ -lccc`)

Alternatively, you may add this git repo as a "git submodule" to your own. This allows you to be up to date to the latest version at all times, by simply `cd`-ing over to the submodule folder and doing a `git pull`.

In general though, we recommend having the source code and compiling it yourself (as there are important customization flags in `./hdr/libccc_config.h` which change how the library is compiled). You are encouraged to take a look at this file ([libccc_config.h](https://github.com/LexouDuck/libccc/blob/master/hdr/libccc_config.h)), and decide on how you wish to configure the library when using it in your project. In particular:
- `LIBCONFIG_HANDLE_NULLPOINTERS`
	If 0, then libccc functions will always try to dereference (and usually do a segmentation fault) when given NULL pointer arguments (this is useful for debug).
	If 1 (this is the default), then all NULL pointer accesses will be avoided, and an appropriate return value (eg:`NULL`, `0`, sometimes `-1`) will be returned by any libccc function when given a NULL pointer.
- `LIBCONFIG_FAST_APPROX_MATH`
	If 0 (this is the default), the builtin FPU-call libc math functions will be used (eg: `__builtin_powf()`, etc)
	If 1, the libccc fast approximate math functions will be used (these can be quite unreliable, their purpose is to be faster in terms of execution time - the general precision error margin they are tested for is 0.0001)
- `LIBCONFIG_INTTYPES_...` `EXACT`/`FAST`/`LEAST`:
	If `LIBCONFIG_INTTYPES_EXACT` is true, default `int` types are set to with the standard `(u)intSIZE_t` type specifiers.
	If `LIBCONFIG_INTTYPES_FAST ` is true, default `int` types are set to with the standard `(u)int_fastSIZE_t` type specifiers.
	If `LIBCONFIG_INTTYPES_LEAST` is true, default `int` types are set to with the standard `(u)int_leastSIZE_t` type specifiers.
	If multiple of these macros are simultaneously true, EXACT takes precedence over FAST, which itself takes precedence over LEAST. If none are true, resolves to EXACT.



Documentation
---
The documentation for libccc is available at the following address: https://lexouduck.github.io/libccc/doc/html/index.html
This documentation website is generated from special comments written directly within the code, so, as usual in C, it is recommended that you take a look at the .h header files located in the `hdr` folder of this repo.
Thank you to Doxygen, Doxyrest, Sphinx, and GitHub Pages to make this auto-generated documentation work.




Build system
---
This library is built using a cross-platform Makefile, which can build it on most platforms, in both static and dynamic library form.

There a couple of important custom Makefile variables used, which you should keep in mind:
- MODE: the kind of compiler flags used (can be `debug` or `release`)
- OSMODE: the target operating system (can be `win32`, `win64`, `macos`, `linux`, or `other`)
- LIBMODE: the type of library build (can be `static` or `dynamic`)
Depending on your particular machine/environment/needs, you may need to set a custom value for one of these (eg: `make OSMODE=win32`)

To learn more about what make scripts are provided, do `make help`, which will give a list of all rules and a brief description for each.



Testing
---
To ensure proper functionality of all these important functions in every edge case, a rather exhaustive testing suite program was implemented, which compares libccc functions to their stdlib ISO equivalent, wherever applicable (otherwise tests expect results that are manually written out and asserted).
This test suite program features segfault/signal handling and execution time comparison, among other things.
You can test the `libccc` by running `make test`: this will compile and run the test suite program from the files found in the `./test` folder.



Continuous Integration
---
Every time a new commit/push is done, the automated CI testing job is run, as defined in `.github/workflows/ci.yml` (see the [official github documentation for Actions and Workflows to learn more](https://help.github.com/en/actions/reference/workflow-syntax-for-github-actions)).

This CI job builds everything with a `make`, and runs the testing suite with a `make test`. It runs with all of the following configurations:
- Ubuntu (gcc and clang)
- MacOS (gcc and clang)
- Windows (mingw-gcc and clang)

You can check the latest CI/CD run of libccc over on the [GitHub Actions](https://github.com/LexouDuck/libccc/actions) page of this repo.



Contributing
---
Check `CONTRIBUTING.md`, this file serves as a "contributions style guide". This style was chosen because it allows for more efficient version control and code review.

- TODO add description of coding style to `CONTRIBUTING.md`
