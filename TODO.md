
# TODO list

- TODO: eorganize the ./hdr/ header folder to have subfolders and better organized/more split-up files:
```c
#include <libccc/convert.h> // REMOVE this file, split it up into several 'type' headers: int.h, float.h, etc
#include <libccc.h>
#include <libccc/int.h>
#include <libccc/fixed.h>	// TODO fixed-point arithmetic (with macros, such that you can choose where the decimal point is)
#include <libccc/float.h>
#include <libccc/bool.h>
#include <libccc/char.h>	// TODO t_char and t_utf8, with relevant 'wchar_t' functions
#include <libccc/string.h>
#include <libccc/regex.h>	// TODO all: functions for regular expressions pattern matching/replacing
#include <libccc/color.h>
#include <libccc/time.h>	// TODO system clock 'timespec' functions: clock_gettime(), etc
#include <libccc/mem/memory.h>
#include <libccc/mem/pointerarray.h>// TODO split up memory.h
#include <libccc/mem/stringarray.h>
#include <libccc/mem/compression.h>	// TODO all: compress/decompress functions (RLE, LZ77, LZW, Huffman)
#include <libccc/mem/cryptography.h>// TODO all: ???
#include <libccc/array/array.h>	// TODO s_array = contiguous array: { t_size item_count, t_size item_size, (void*) items }
#include <libccc/array/tuple.h>	// TODO s_tuple = ???
#include <libccc/array/tree.h>	// TODO s_tree = iterable binary tree structure
#include <libccc/array/object.h>// TODO s_object = anonymous, dynamic, extensible objects (json library: wjelement)
#include <libccc/array/dict.h>	// TODO s_dict = key/value dictionary: { t_size count, { char* key, char* type, t_size size, (void*) value }* items }
#include <libccc/array/list.h>	// TODO s_list = singlely-linked list: { s_list* next, t_size item_size, (void*) item }
#include <libccc/sys/io.h>
#include <libccc/sys/asm.h>		// TODO collection of cross-platform inline assembly __asm__ macros, like INCBIN(varname, filepath)
#include <libccc/sys/logger.h>	// TODO all: 
#include <libccc/sys/async.h>	// TODO all: libuv ?
#include <libccc/sys/thread.h>	// TODO all: POSIX-thread (pthread) cross-platform interface/wrappers
#include <libccc/sys/signal.h>	// TODO all: system signal handling: SIGSEGV, SIGFPE, SIGTRAP, SIGABORT, etc
#include <libccc/sys/socket.h>	// TODO all: network socket functions - send(), recv(), etc
#include <libccc/sys/network.h>	// TODO all: utility functions for common network protocols: TCP/IP, UDP (maybe DELTA-T?)
#include <libccc/math/math.h>
#include <libccc/math/float.h>
#include <libccc/math/fixed.h>	// TODO
#include <libccc/math/random.h>	// TODO several RNG methods (use function pointer, so others can implement custom RNG logic ?)
#include <libccc/math/vlq.h>	// TODO all: variable-length-quantites (VLQ) arbitrary-precision math
#include <libccc/math/stat.h>
#include <libccc/math/algebra.h>// TODO add 's_tensor' type
#include <libccc/math/complex.h>
```
- TODO: reorganize test suite to reflect new header file folder tree + add empty files for tests
- TODO: add option #define LIBCONFIG_PRINT_ENCODING	(ANSI,ASCII,UTF8) which changes printf behavior ?
- TODO: for each compound type in 'array' folder: implement functions _New, _Delete, _Equals, _Duplicate, _Sub, _Insert, _Replace, _Filter, _Map
