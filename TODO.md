
# TODO list

```c
#include <libccc.h>
#include <libccc/bool.h>
#include <libccc/char.h>
#include <libccc/int.h>
#include <libccc/fixed.h>
#include <libccc/float.h>
#include <libccc/pointer.h>
#include <libccc/memory.h>
#include <libccc/string.h>
#include <libccc/pointerarray.h>
#include <libccc/stringarray.h>
#include <libccc/enum.h>
#include <libccc/text/char/ascii.h>
#include <libccc/text/char/unicode.h>
#include <libccc/text/string/ascii.h>
#include <libccc/text/string/utf32.h>
#include <libccc/text/string/utf8.h>
#include <libccc/text/stringarray/ascii.h>
#include <libccc/text/stringarray/utf32.h>
#include <libccc/text/stringarray/utf8.h>
#include <libccc/text/regexp.h>	// TODO all: functions for regular expressions pattern matching/replacing
#include <libccc/math/math.h>
#include <libccc/math/int.h>
#include <libccc/math/fixed.h>	// TODO advanced math functions
#include <libccc/math/float.h>
#include <libccc/math/vlq.h>	// TODO all: variable-length-quantites (VLQ) arbitrary-precision math
#include <libccc/math/sort.h>
#include <libccc/math/stat.h>
#include <libccc/math/algebra.h>
#include <libccc/math/algebra/interval.h>
#include <libccc/math/algebra/vector.h>
#include <libccc/math/algebra/matrix.h>
#include <libccc/math/algebra/tensor.h>// TODO
#include <libccc/math/complex.h>
#include <libccc/math/quaternion.h>	// TODO
#include <libccc/math/octonion.h>	// TODO
#include <libccc/random.h>	// TODO several RNG methods (use function pointer, so others can implement custom RNG logic ?)
#include <libccc/random/prng.h>
#include <libccc/random/csprng.h>
#include <libccc/generic/array.h>
#include <libccc/generic/list.h>
#include <libccc/generic/dict.h>
#include <libccc/generic/tree.h>
#include <libccc/generic/set.h>	// TODO s_set = unordered set, containing only unique values
#include <libccc/generic/object.h>	// TODO s_object = anonymous, dynamic, extensible objects (json library: wjelement)
#include <libccc/sys/io.h>
#include <libccc/sys/time.h>	// TODO system clock 'timespec' functions: clock_gettime(), etc
#include <libccc/sys/logger.h>
#include <libccc/sys/async.h>	// TODO all: libuv ?
#include <libccc/sys/thread.h>	// TODO all: POSIX-thread (pthread) cross-platform interface/wrappers
#include <libccc/sys/signal.h>	// TODO all: system signal handling: SIGSEGV, SIGFPE, SIGTRAP, SIGABORT, etc
#include <libccc/sys/socket.h>	// TODO all: network socket functions - send(), recv(), etc
#include <libccc/sys/network.h>	// TODO all: utility functions for common network protocols: TCP/IP, UDP (maybe DELTA-T?)
#include <libccc/encode/common.h>
#include <libccc/encode/json.h>
#include <libccc/encode/xml.h>	// TODO
#include <libccc/encode/yaml.h>	// TODO
#include <libccc/encode/toml.h>
#include <libccc/hash/crc.h>	// TODO CRC-[8|16|32|64]
#include <libccc/hash/checksum.h>	// TODO fletcher-[4|8|16|32], BSD, SYSV, IPv4, xor8
#include <libccc/hash/universal.h>	// TODO Rabin, Zobrist
#include <libccc/hash/hash.h>	// TODO Rabin, Zobrist
#include <libccc/hash/keyed.h>	// TODO BLAKE[1|2|3], HMAC, MD6, SipHash
#include <libccc/hash/crypto.h>	// TODO MD[2|4|5], BLAKE[256|512], SHA-[1|256|512]
#include <libccc/compress/rle.h>
#include <libccc/compress/huffman.h>
#include <libccc/compress/lz77.h>
#include <libccc/compress/lzw.h>
#include <libccc/compress/lzss.h>
#include <libccc/compress/lzma.h>
#include <libccc/image/color.h>
```
- add option #define LIBCONFIG_PRINT_ENCODING	(ANSI,ASCII,UTF8) which changes printf behavior ?
- add printf format specifier flags to String_Format wrapper for the following:
	- specifier: unsigned binary integer: `%b`
	- specifier: boolean (TRUE or FALSE): `%B`
	- specifier: char	(escape-sequence): `%C`
	- specifier: string (escape-sequence): `%S`
	- specifier: fixed-point `%q` (and `%k`/`%K` for fixed-point hex)
	- specifier: data/memory bytes hex display: `%m`, doing `%.5m` will print at most 5 bytes of memory
	- specifier: pointer array (void\*, null-pointer-terminated): `%[s]` for a string array for example:
		- `%.5[s]` will show only the 5 first strings
		- `%[.5s]` will show the first 5 chars of each string
		- `%.5[.5s]` will show the first 5 chars of the 5 first strings
- add profiler / speed indicator documentation for each function
	- shows execution time for 0 elems
	- shows execution time for 1 elems
	- shows execution time for 100 elems
	- shows big O notation?



### Other stdlibs to take ideas from
- https://github.com/oz123/awesome-c#game-programming
- [libcork](https://libcork.io/), [git](https://github.com/dcreager/libcork)
- [glib](https://docs.gtk.org/glib), [git](https://gitlab.gnome.org/GNOME/glib/)
- [apr](https://apr.apache.org/), [git](https://svn.apache.org/viewvc/apr/apr/tags/1.7.0/)
