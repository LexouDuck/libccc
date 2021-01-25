#include <libccc_string.h>
#include <libccc_list.h>
#include <libccc_io.h>

#include <stdio.h>

#define COUNT 8
int main()
{
	static char* lines[COUNT] =
	{
		"Yo my boi",
		"What's up dog",
		"Not much, you ?",
		"...",
		"Yo spit it out",
		"What's the deal ?",
		"You got the dope ?",
		"I ask the questions.",
	};

	// s_array
	{
		s_array* str_array = &(s_array)
		{
			.item_count = COUNT,
			.item_size = sizeof(char*),
			.items = lines,
		};
		foreach (char*, str, s_array, str_array)
		{
			IO_Output_Format("i:%zu,ptr:%p,\tstr:%p -> \"%s\"\n", str_i, str_ptr, str, str);
		}
	}

	// s_list
	{
		s_list* str_list = NULL;
		for (int i = 0; i < COUNT; ++i)
		{
			List_Append(&str_list, List_New(lines[i], lines[i] ? String_Length(lines[i]) : 0));
		}
		foreach (char*, str, s_list, str_list)
		{
			IO_Output_Format("i:%zu,lst:%p, size: %llu,\tstr:%p -> \"%s\"\n", str_i, str_lst, str_lst->item_size, str, str);
		}
	}
	return (OK);
}

/*

REMOVE #include <libccc/convert.h> split it up into the type headers: int.h, float.h, etc

<libccc.h>
<libccc/int.h>
<libccc/fixed.h>	// TODO fixed-point arithmetic (with macros, such that you can choose where the decimal point is)
<libccc/float.h>
<libccc/bool.h>
<libccc/char.h>		// TODO t_char and t_utf8, with relevant 'wchar_t' functions
<libccc/string.h>
<libccc/object.h>	// TODO anonymous, dynamic, extensible objects (json library - wjelement)
<libccc/time.h>
<libccc/regex.h>	// TODO functions for regular expressions pattern matching/replacing
<libccc/mem/memory.h>
<libccc/mem/pointerarray.h>
<libccc/mem/stringarray.h>
<libccc/mem/compression.h>	// TODO compress/decompress functions (RLE, LZ77, LZW, Huffman)
<libccc/mem/cryptography.h>	// TODO ???
<libccc/array/array.h>	// TODO s_array = contiguous array: { t_size item_count, t_size item_size, (void*) items }
<libccc/array/tuple.h>	// TODO s_tuple = ???
<libccc/array/dict.h>	// TODO s_dict = key/value dictionary: { t_size count, { char* key, char* type, t_size size, (void*) value }* items }
<libccc/array/list.h>	// TODO s_list = singlely-linked list: { s_list* next, t_size item_size, (void*) item }
<libccc/sys/io.h>
<libccc/sys/asm.h>		// TODO collection of cross-platform inline assembly __asm__ macros, like 'INCBIN(varname, "filepath")'
<libccc/sys/thread.h>	// TODO POSIX-thread (pthread) cross-platform interface/wrappers
<libccc/sys/signal.h>	// TODO system signal handling: SIGSEGV, SIGFPE, SIGTRAP, SIGABORT, etc
<libccc/sys/socket.h>	// TODO network socket functions - send(), recv(), etc
<libccc/sys/network.h>	// TODO utility functions for common network protocols: TCP/IP, UDP (maybe DELTA-T?)
<libccc/math/math.h>
<libccc/math/random.h>	// TODO several RNG methods (use function pointer, so others can implement custom RNG logic ?)
<libccc/math/vlq.h>		// TODO variable-length-quantites (VLQ) arbitrary-precision math
<libccc/math/stat.h>
<libccc/math/algebra.h>
<libccc/math/complex.h>
*/
