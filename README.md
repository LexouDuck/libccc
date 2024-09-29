libccc
---
A comprehensive, cross-platform, customizable standard library for C

<a href="https://github.com/LexouDuck/libccc/actions">
	<img src="https://github.com/LexouDuck/libccc/workflows/CI+CD/badge.svg" />
</a>



The Project
---
The objective is to have one simple, well-documented, efficient open-source implementation of the C standard library,
but with easier to use functions and types than what is offered by the ISO standards -
mostly by minimising occurence of undefined behaviors, and handling edge cases in a consistent, coherent way,
so as to have code that is as little machine-specific as possible.

Here is a more in-depth description of what this standard library contains.

The following categories/headers include the ISO standard library (types, functions, macros):

| C header file         | Types                         | Description
|-----------------------|-------------------------------|----------
| `libccc/bool.h`       | `t_bool`                      | primitive boolean type (usually `_Bool`), and strtobool, booltostr, etc |
| `libccc/char.h`       | `t_char`, `t_ascii`, `t_utf8` | functions to handle ANSI/ASCII characters (islower, isalpha, toupper, etc - but also `wchar_t` and UTF8 char handling) |
| `libccc/int.h`        | `t_uint`, `t_sint`, etc...    | integer number types, functions to replace the wonky STD C atoi/itoa functions with better type-specific conversion functions |
| `libccc/float.h`      | `t_float`, etc...             | floating-point types, functions to replace the wonky STD C atof/strtol functions with better type-specific conversion functions |
| `libccc/pointer.h`    | `t_size`, `t_ptrdiff`, etc... | important system types for pointer arithmetic (`size_t`, `ptrdiff_t`) and the functions associated with them |
| `libccc/memory.h`     | `void*`                       | functions to manipulate memory directly (memcpy, memset, memchr, etc - but also extras like memdup, memrep, getbits) |
| `libccc/string.h`     | `t_char*`                     | functions to manipulate strings (strcpy,strchr,strsub,etc but also extras such as strformat,strsplit,strmap) |
| `libccc/math.h`       | N/A                           | common mathematical functions operating on floating-point numbers (the implementations in this lib are fast-approximate versions, though by default LIBCONFIG_FAST_APPROX_MATH is defined as 0, so the functions are actually simple wrappers over the builtin FPU math functions) |
| `libccc/sys/time.h`   | `t_time`, `s_date`, etc...    | functions for handling times/dates/timezones/timespecs (handling of timezones is different from the stdlib 'global variable' tzset call) |
| `libccc/sys/io.h`     | N/A                           | functions for reading and writing (from/to terminal, or from/to file(s) - wrapper functions over `unistd.h` and `stdio.h`) |


Furthermore, there are other functions here that are not found in the ISO standard, particularly in the following categories:

| C header file            | Types                                  | Description
|--------------------------|----------------------------------------|-----------------
| `libccc/fixed.h`         | `t_fixed`, etc...                      | fixed-point arithmetic, with a configurable fixed-point number type (regarding what portion is dedicated to the fractional part)
| `libccc/color.h`         | `t_argb32`, `s_argb`, `s_ahsl`, etc... | functions manipulating several common color encodings, as well as other useful color-related functions (like RGB_to_HSL, etc)
| `libccc/pointerarray.h`  | `void**`                               | a set of functions used to manipulate pointer arrays (`void **`, where the array is terminated by a NULL pointer)
| `libccc/stringarray.h`   | `t_char**`                             | a set of functions used to manipulate string arrays (`char **`, where the array is terminated by a NULL pointer)
| `libccc/math/algebra.h`  | `s_vector2d`, `s_matrix2x2`, etc...    | math functions for 2D/3D/4D vectors and matrices, as well as integrals and more
| `libccc/random/random.h` | `t_prng`, `t_csprng`, etc...           | functions for simple pseudo-random number generation (many more functions than just the ISO rand/srand/rand_r functions)
| `libccc/math/complex.h`  | `s_complex`                            | math functions for complex number operations, as well as quaternions
| `libccc/math/stat.h`     | N/A                                    | statistics & probabilities functions: int/float number array sort functions, median, standard deviation, etc
| `libccc/math/vlq.h`      | `t_bigint`, `t_bigfloat`, etc...       | Variable-Length Quantity math functions, for variable-size "big ints", "big fixed", and "big float" types.
| `libccc/monad/array.h`   | `s_array<T>`                           | generic-type array functions (simply stores a contiguous memory buffer `.items` and a `.length`)
| `libccc/monad/list.h`    | `s_list<T>`                            | generic-type linked-list functions (which can be configured to be singly-linked or doubly-linked)
| `libccc/monad/stack.h`   | `s_stack<T>`                           | generic-type stack functions (mainly push/pop, made to act like a FIFO/LILO type)
| `libccc/monad/queue.h`   | `s_queue<T>`                           | generic-type queue functions (mainly push/pop, made to act like a LIFO/FILO type)
| `libccc/monad/dict.h`    | `s_dict<T>`                            | generic-type dictionary (key/value pair) functions (access items via their string `key` rather than their index)
| `libccc/monad/tree.h`    | `s_tree<T>`                            | generic-type tree functions (each `struct tree` stores a value of type `T`)
| `libccc/encode/common.h` | `s_kvt*`                               | key-value pair nestable object, supports printing/parsing to several common data formats (JSON, YAML, XML, TOML).
| `libccc/sys/regex.h`     | `s_regex`                              | Regular Expression type and functions, based on the all-encompassing [Oniguruma](https://github.com/kkos/oniguruma) regex engine



Why does this exist ?
---
What started as a necessary exercise for the 42 school (called `libft`, as in "lib-forty-two") quickly became a much more expansive project, now dubbed `libccc` (for comprehensive, customizable, cross-platform).
Whereas the 42 libft project only requires students to code a certain set of important memory/string/io functions, we decided to take this idea much further.
The `libft` project is originally meant as an educational exercise, in which a student learns a lot by "reinventing the wheel" many times over.
Here, the goal is to have a standard C library which is:

- **fully cross-platform**: libccc should be able to compile on as many compilers/machines as possible.
- **uniformized**: libccc should allow the developer to not worry so much about "undefined behavior" or platform-specific edge cases when using standard functions.
- **configurable**: libccc should be compield from source, and linked statically to your project, so that configuration variables can be set directly on the commandline, when compiling it (see `libccc_config.h`).
- **customizable**: libccc being open source (MIT license), allows and encourages all developers to use, add and contribute to this standard library.
- **comprehensive**: libccc offers much more than the minimalist set of utility functions that is the C ISO standard library, to hopefully alleviate having too many dependencies, or too many "util.c" files, which really should be part of the standard library.

The first step to accomplishing fully cross-platform code, is to avoid using the native int/long/short types,
which can have different storage size depending on the platform (the C native `int` type is defined as
the fastest integer type for the given machine, typically this will be the CPU register size -
so on a 64-bit machine, that'd be int64, on a 32-bit machine int32,
and some old embedded systems you come across might have 16-bit ints as the machine's default storage size).
So first of all, using the integer types defined in "stdint.h" (`int32_t`, `uint64_t`, etc) is essential
to write cross-platform C code, as it ensures that integer overflow behaviors are consistent across platforms.
Note however that these integer types aren't present on every platform though - sometimes, you will have to
settle for the `uint_fastX_t` types, but libccc provides configuration macros to make this switch a simple affair).
Of course, there are also many times where a platform-dependent "fast int" is the logical, correct, best thing to use,
and this is also made easy using libccc.



How to use this library
---

To speak in simple terms: the make simply builds a `libccc.a` library to link to your project.
(eg: you can link it with something like `gcc main.c -I./libccc/hdr/ -L./libccc/ -lccc`)

Alternatively, you may add this git repo as a "git submodule" to your own.
This allows you to be up to date to the latest version at all times,
by simply `cd`-ing over to the submodule folder and doing a `git pull`.

In general though, we recommend having the source code and compiling it yourself, because
there are important customization flags in `./hdr/libccc_config.h` which change how the library is compiled).
You are encouraged to take a look at this file ([libccc_config.h](https://github.com/LexouDuck/libccc/blob/master/hdr/libccc_config.h)),
and decide on how you wish to configure the library when using it in your project.

In particular:

- `LIBCONFIG_HANDLE_NULLPOINTERS`
	- If 0, then libccc functions will always try to dereference (and usually do a segmentation fault) when given NULL pointer arguments (this is useful for debug).
	- If 1 (this is the default), then all NULL pointer accesses will be avoided, and an appropriate return value (eg:`NULL`, `0`, sometimes `-1`) will be returned by any libccc function when given a NULL pointer.
- `LIBCONFIG_FAST_APPROX_MATH`
	- If 0 (this is the default), the builtin FPU-call libc math functions will be used (eg: `__builtin_powf()`, etc)
	- If 1, the libccc fast approximate math functions will be used (these can be quite unreliable, their purpose is to be faster in terms of execution time - the general precision error margin they are tested for is 0.0001)
- `LIBCONFIG_INTTYPES_...` `EXACT`/`FAST`/`LEAST`:
	- If `LIBCONFIG_INTTYPES_EXACT` is true, default `int` types are set to with the standard `(u)intSIZE_t` type specifiers.
	- If `LIBCONFIG_INTTYPES_FAST ` is true, default `int` types are set to with the standard `(u)int_fastSIZE_t` type specifiers.
	- If `LIBCONFIG_INTTYPES_LEAST` is true, default `int` types are set to with the standard `(u)int_leastSIZE_t` type specifiers.
	- If multiple of these macros are simultaneously true, EXACT takes precedence over FAST, which itself takes precedence over LEAST. If none are true, resolves to EXACT.



Documentation
---

The documentation for libccc is available [here](https://lexouduck.github.io/libccc/doc/html/index.html).

This documentation website is generated from special comments written directly within the code, so, as usual in C,
it is recommended that you take a look at the .h header files located in the `hdr` folder of this repo.

Thanks to [Doxygen](#), [Doxyrest](#), [Sphinx](#), and GitHub Pages to make this auto-generated documentation work.




Build system
---

This project uses a cross-platform Makefile-based build system, via [cccmk](https://github.com/LexouDuck/cccmk.git).
libccc should be able to build on most all common platforms, in both static and dynamic library form.

The default `make` rule will simply build libccc (both static and dynamic libraries).
There are many `make` commands which make up the build system (you can do `make test` to run the test suite, for example).
Run `make help` in the project folder, to get a full list of all possible `make` rules.
To learn more about what make scripts are provided, do `make help`, which will give a list of all rules and a brief description for each.

There a couple of important custom Makefile variables used, which you should keep in mind.
Here are some common options which will change how the Makefile build is done:

`make <target-name> [BUILDMODE=?] [OSMODE=?] [CPUMODE=?] [LIBMODE=?]`

Here is an explantion of these optional makefile variables (in brackets) which can be specified:

- `BUILDMODE`: can be `debug` or `release`
	Use this to specify the type of build to perform, which will alter the `CFLAGS` accordingly
	By default, for most rules, the value will be `debug`, unless you call `make release`.
	Example usage: `$ make cli MODE=release` (to build the CLI executable without debug flags, with optimization etc)

- `OSMODE`: can be `windows`, `macos`, `linux`, or `other`
	Use this to specify the target platform/operating system, for cross-compiling.
	By default, the Makefile will use the current platform (it will guess using `uname -s`).
	Example usage: `$ make release OSMODE=macos` (to cross-compile for the MacOS platform)

- `CPUMODE`: this string, by default, is the result of the `uname -m` shell command for your machine.
	There is no complete list of possible return values for the standard `uname` shell command, but here is a spreadsheet which gives an idea of some common values: https://en.wikipedia.org/wiki/Uname#Examples
	This variable is used to disambiguate builds of various CPU architectures, specifically in the `./bin` and `./obj` folders.

- `LIBMODE`: can be `static` or `dynamic`
	Use this to specify the type of library to build (to the output `./bin/` folder)
	If `static`, only the statically-linked `libavesterra.a` library archive will be built.
	If `dynamic`, the appropriate dynamically-linked library files will be built using `CC` (`.dll`/`.dylib`/`.so`)
	By default, the value is `static` - but if you call `make release`, both static and dynamic libs will be built.
	Example usage: `$ make LIBMODE=dynamic` (to only build dynamic libs, without creating static `.a` files)



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
