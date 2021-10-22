
# TODO list

```c
#include <libccc.h>
#include <libccc/bool.h>
#include <libccc/char.h>
#include <libccc/int.h>
#include <libccc/fixed.h>	// TODO fixed-point arithmetic (with macros, such that you can choose where the decimal point is)
#include <libccc/float.h>
#include <libccc/pointer.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/regex.h>	// TODO all: functions for regular expressions pattern matching/replacing
#include <libccc/color.h>
#include <libccc/array/array.h>	// TODO s_array = contiguous array: { t_size item_count, t_size item_size, (void*) items }
#include <libccc/array/tuple.h>	// TODO s_tuple = ???
#include <libccc/array/pointerarray.h>// TODO split up memory.h
#include <libccc/array/stringarray.h>
#include <libccc/array/list.h>	// TODO s_list = singlely-linked list: { s_list* next, t_size item_size, (void*) item }
#include <libccc/array/dict.h>	// TODO s_dict = key/value dictionary: { t_size count, { char* key, char* type, t_size size, (void*) value }* items }
#include <libccc/array/tree.h>	// TODO s_tree = iterable binary tree structure
#include <libccc/array/object.h>// TODO s_object = anonymous, dynamic, extensible objects (json library: wjelement)
#include <libccc/sys/io.h>
#include <libccc/sys/time.h>	// TODO system clock 'timespec' functions: clock_gettime(), etc
#include <libccc/sys/logger.h>	// TODO all: 
#include <libccc/sys/async.h>	// TODO all: libuv ?
#include <libccc/sys/thread.h>	// TODO all: POSIX-thread (pthread) cross-platform interface/wrappers
#include <libccc/sys/signal.h>	// TODO all: system signal handling: SIGSEGV, SIGFPE, SIGTRAP, SIGABORT, etc
#include <libccc/sys/socket.h>	// TODO all: network socket functions - send(), recv(), etc
#include <libccc/sys/compression.h>	// TODO all: compress/decompress functions (RLE, LZ77, LZW, Huffman)
#include <libccc/sys/cryptography.h>// TODO all: ???
#include <libccc/sys/network.h>	// TODO all: utility functions for common network protocols: TCP/IP, UDP (maybe DELTA-T?)
#include <libccc/math/math.h>
#include <libccc/math/float.h>
#include <libccc/math/fixed.h>	// TODO
#include <libccc/math/random.h>	// TODO several RNG methods (use function pointer, so others can implement custom RNG logic ?)
#include <libccc/math/vlq.h>	// TODO all: variable-length-quantites (VLQ) arbitrary-precision math
#include <libccc/math/stat.h>
#include <libccc/math/algebra.h>// TODO add 's_tensor' type
#include <libccc/math/complex.h>// TODO add 's_quaternion' type
```
- TODO: reorganize test suite to reflect new header file folder tree + add empty files for tests
- TODO: add option #define LIBCONFIG_PRINT_ENCODING	(ANSI,ASCII,UTF8) which changes printf behavior ?
- TODO: for each compound type in 'monad' folder: implement functions _New, _Delete, _Equals, _Duplicate, _Sub, _Insert, _Replace, _Filter, _Map
- TODO: add printf format specifier flags to String_Format wrapper for the following:
	- specifier: unsigned binary integer: `%b`
	- specifier: boolean (TRUE or FALSE): `%B`
	- specifier: char	(escape-sequence): `%C`
	- specifier: string (escape-sequence): `%S`
	- specifier: fixed-point `%q` (and `%k`/`%K` for hex)
	- specifier: data/memory bytes hex display: `%m`, doing `%.5m` will print at most 5 bytes of memory
	- specifier: array (void\*, null-term): `%[s]` for a string array for example:
		- `%.5[s]` will show only the 5 first strings
		- `%[.5s]` will show the first 5 chars of each string
		- `%.5[.5s]` will show the first 5 chars of the 5 first strings



### Other stdlibs to take ideas from
- https://github.com/oz123/awesome-c#game-programming
- [libcork](https://libcork.io/), [git](https://github.com/dcreager/libcork)
- [glib](https://docs.gtk.org/glib), [git](https://gitlab.gnome.org/GNOME/glib/)
- [apr](https://apr.apache.org/), [git](https://svn.apache.org/viewvc/apr/apr/tags/1.7.0/)
