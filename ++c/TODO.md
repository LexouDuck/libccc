
# ++C

- A superset of C -> transpiles to C code (while keeping it as clean and readible as possible)
- You can enforce a certain code style to the resulting transpiled C code
- Automatic header include-guard insertion (and C++ `#ifdef __cplusplus extern "C" { ... }`)
- Includes m4 multi-pass pre-processor (https://www.gnu.org/savannah-checkouts/gnu/m4/manual/m4-1.4.18/m4.html)
- To differentiate ++C code from C or C++, by convention the following file formats are accepted:
	- `++c`, `ppc`, `xxc` (case insensitive), these transpile to `.c` files
	- `++h`, `pph`, `xxh` (case insensitive), these transpile to `.h` files
- Several language features added, mostly in the form of new pre-processor directives, or new alternate syntax.

The ++C language consists of 2 things:
- `ppp`, the ++C pre-processor - this is the transpiler program
- `libccc`, the ++C standard library (which can also be used in plain old C)



# Warnings:

++C also aims to act as a linter - performing additional code checks and giving many useful warnings.
Here are the warnings which are added by default (any warning can be deactivated in the same way you would do with gcc: `-Wno-*`)
- `-Wimplicit-cast` explicit type casting everywhere (float to int, int to float, enum to int, etc)
- `-Wlingering-alloc` local variable 'a' was allocated, and function returned something which isn't 'a', 'a' should be freed
- `-Wunchecked-null` pointer potentially NULL
- `-Winvalid-enum-item` integer value was assigned to enum type, but this integer is outside of the enum
- `-Wmisaligned-pointer` warn of potential pointer alignment issues, which can be platform-specific



# Features:

### Accepted alternate notation:

- dereference: `*` can be written `$` (to avoid synonymy with the multiply operator)
```c
value = *pointer; // pure C
value = $pointer; // ++C
```
- get address: `&` can be written `@` (to avoid synonymy with the bitwise AND operator)
```c
address = &value; // pure C
address = @value; // ++C
```

- binary number literals: instead of just being a GCC extension, any ++C code can have binary number literals, using the prefix `0b`:
```c
value = 0b110;	// pure C (GCC extension only)
value = 0b110;	// ++C
```

- octal number literals: in addition to leading zero notation, a `0o` literal number prefix is also accepted
```c
value = 0644;	// pure C
value = 0o644;	// ++C
```

- static array types: brackets can be written after the type (before the associated token), rather than after the variable name:
```c
char*	strings[9];	// pure C
char*[9] strings;	// ++C
```

- function pointer types: to avoid hard-to-read function pointer types using `(*func)` notation, you can instead use `=>` arrow notation
```c
void	(*f)(int, char*);	// pure C
(int, char*) => void	f;	// ++C

// example nested function (with another function pointer as argument)
void	(*g)(int, char*	(*)(char*));// pure C
(int, (char*)=>char*) => void	g;	// ++C
```



### Compile-time operators:

- `alignof(X)`: Transpiles to the minimum memory alignment requirement of a variable/value/token `X`
- `typeof(X)`: Transpiles to inline code, the type of the variable/value/token `X`
- `nameof(X)`: Transpiles to a string literal, the name of the variable/value/token `X`

Also:
- `asm`: Transpiles to the more cross-platform equivalent: `__asm__`
- `inline`: Transpiles to the more cross-platform equivalent: `__inline__`
- `restrict`: Transpiles to the more cross-platform equivalent: `__restrict__`



### RegExp literals:

regex literal strings are prefixed with an `r` character, and regex mode flags may be placed after the ending double quote:
```c
char const* regex1 = r"\b(My_\w*)\b"g;
char const* regex2 = r"(?x) ( [^)] __damn__ )"i;
char const* regex3 = r"[a-zA-Z_]\w*"sg;
```
When writing a regex literal, the transpiled C output string literal will:
- have double backquotes `\\` wherever necessary
- place the regex mode flags within the string, at the start, using `(?i)` notation (https://www.regular-expressions.info/modifiers.html?wlr=1)

Note that libccc uses the Oniguruma Regex engine, which encompasses the features of many other RegExp engines into one:
https://github.com/kkos/oniguruma
https://raw.githubusercontent.com/kkos/oniguruma/5.9.6/doc/RE
http://www.greenend.org.uk/rjk/tech/regexp.html



### Functions declared in local scopes (prime citizens-ish):

In ++C, you can declare functions in local scopes:
```c
void	WaitAndRunCallback(void (*callback)(void));

int	main()
{
	WaitAndRunCallback(
		void HelloWorld(void)
		{
			printf("Hello World!\n");
		}
	);
}
```
For simplicity, only pure functions and functions with only global-scope side-effects, can be defined locally.
TODO: Perhaps we can implement a variable-capture mechanism which isn't too complex ? This way parent-scoped locals can be used, like in many modern languages.
```c
// NB: when transpiled to C, the 'HelloWorld' local function will be in global scope, named:
void	WaitAndRunCallback(void (*callback)(void));

void	main_HelloWorld(void)
{
	printf("Hello World!\n");
}

int	main()
{
	WaitAndRunCallback(
		&main_HelloWorld
	);
}
```



### Preprocessor directives:

Most of the new additions take the form of new preprocessor directives, of which here is a brief list:
```c
#operator	$	(char* a, char* b) => int	= DoOperation(a, b)		// define a custom operator (optionally with a certain specified `precedence` and `associativity`)
#accessor (struct s var)[int index] => int	= GetFunction(var, index)	// define a custom accessor syntax for a struct/union (custom brackets `get` functions)
#namespace NameSpace.Type<T=(float|int), P>	// works similar to namespaces and templates in C++, but simpler and more powerful (read more about generic types below)
#reflect // type reflection - type stringization , enum stringization, etc ? TODO define this and how it can work
#replace MACRO() <string>	// works like a `#define` macro, but occurs at transpile-time, and uses m4 (which allows us to do much more stuff)
#header __HEADER_H			// insert header include guards at the beginning and end of a header file (and c++ `extern "C" {}`guards)
#incbin myvar "filepath"	// include a binary file into the executable as an extern const global variable
#alias(token)		// shorter way of writing `__attribute__((alias, ...))`
#align(4)			// shorter way of writing `__attribute__((align, ...))` and/or `_Alignas`
#format(func, 1, 2)	// shorter way of writing `__attribute__((format, ...))`
#noreturn			// shorter way of writing `__attribute__((noreturn, ...))` and/or `_Noreturn`
#malloc				// shorter way of writing `__attribute__((malloc, ...))`
#delete				// shorter way of writing `__attribute__((delete, ...))`
#inline				// shorter way of writing `__attribute__((always_inline, ...))` and/or `inline`
#pure				// shorter way of writing `__attribute__((pure, ...))`
#packed				// shorter way of writing `__attribute__((packed, ...))`
```
Also, some changes/fixes to existing preprocessor directives:
```c
#if // compile-time operators like sizeof() can be used in #if directly now, the transpiler will handle it
// TODO (perhaps even use static_assert() where appropriate ?)

#elif defined(MACRO) // 

#endif
```



### Operators:

In ++C, you can define custom operators:
```c
// integer power operator
#operator ** (int left, int right) => int = \
	Math<int>.Power(left, right)

// usage example:
printf("%d", 2 ** 15);
```

A custom operator has a maximum length of 4 characters, and it can use any of the following characters:
`= - + * / % & | ^ ! ~ ? : < > $ @`
Looking at it the other way around, the following ASCII characters cannot be used for a custom operator:
`. , ; ( ) [ ] { } # ' " \`
A custom operator cannot use any token characters (eg: alphanumeric characters `a-z,A-Z,0-9`, or underscore `_`).
Additionnally, some sequences of characters are special and cannot be overridden (even though they only contain legal characters):
- `=` assignment
- `->` deref sub-field access
- `?` and `:` ternary conditional
- `&` / `@` unary get address
- `*` / `$` unary get value (deref)
- `=>` function pointer
- `//`	(comment one-line) or any sequence which contains this string
- `/*`	(comment start) or any sequence which contains this string
- `*/`	(comment end) or any sequence which contains this string

If you wish to define a "word" operator, you can make a `#replace` macro which wraps a custom operator:
```c
// NULL check and return operator
#operator ?? (void const* left, void const* right) => void const* = \
	(left == NULL ? right : left)

// define a 'word' operator wrapper above the actual operator
#replace OTHERWISE	<??>

// usage example:
char* new_str = str ?? "str is NULL";
char* new_str = str OTHERWISE "str is NULL";
```
You can specify operator precedence and associativity:
https://en.cppreference.com/w/c/language/operator_precedence
Simply place these two arguments within parentheses immediately after the `#operator` directive keyword
- the first argument is an integer index of the operator - by default it will be 0 (highest priority)
- the second argument is a boolean (int 0 or 1), 0 (default) for left-to-right associativity, 1 for right-to-left associativity
```c
// fixed-point math
#operator(4, FALSE)	+ (t_fixed a, t_fixed b) => t_fixed = Fixed.Add(a, b)
#operator(4, FALSE)	- (t_fixed a, t_fixed b) => t_fixed = Fixed.Sub(a, b)
#operator(3, FALSE)	* (t_fixed a, t_fixed b) => t_fixed = Fixed.Mul(a, b)
#operator(3, FALSE)	/ (t_fixed a, t_fixed b) => t_fixed = Fixed.Div(a, b)
#operator(3, FALSE)	% (t_fixed a, t_fixed b) => t_fixed = Fixed.Mod(a, b)
```
```c
// string concatenation operators
#operator(5, FALSE) +	(char const* left, char const* right) => char* = String.Join(left, right)
#operator(5, FALSE) :+	(char*       left, char const* right) => char* = String.Append(left, right)
#operator(5, FALSE) +:	(char const* left, char*       right) => char* = String.Prepend(left, right)
#operator(5, FALSE) :+:	(char*       left, char*       right) => char* = String.Merge(left, right)

// usage example:
char* new_str = "Concatenated: " + str;
```
You can also define unary operators (but not ternary operators):
```c
// unary complex number conjugate operator
typedef struct	s_complex_
{
	float re;
	float im;
}				s_complex;

#operator ! (s_complex right) => s_complex = \
	(Complex.Conjugate(right))

// usage example:
s_complex z = { 1.5, 2.2 };
s_complex conjug = !z;
```
```c
// bool exclusive OR (XOR) operator
#operator(12, FALSE) ^^ (bool left, bool right) => bool = \
	((left ? TRUE : FALSE) ^ (right ? TRUE : FALSE))

// usage example:
if (i < 3 ^^ x >= 4) { /* do stuff */}
```
```c
// 3D vector subtraction operator
#operator - (s_vector3d left, s_vector3d right) => s_vector3d = \
	(s_vector3d)				\
	{							\
		.x = left.x - right.x,	\
		.y = left.y - right.y,	\
		.z = left.z - right.z,	\
	}							\

// usage example:
s_vector3d u = (s_vector3d){ 1, 2, 3 };
s_vector3d v = (s_vector3d){ 4, 5, 6 };
s_vector3d diff = (u - v);
```



### Accessors:

Accessors allow one to dereference with brackets `[]` within a struct, with any specified arguments.
The accessor function body must be a simple inline-able `return` statement. Only works with non-pointer types.
```c
// example color type
typedef	uint32_t	t_argb32;
// example palette color array struct
typedef struct	s_palette_
{
	size_t		color_count;
	t_argb32*	colors;
}				s_palette;

// declare an accessor to get colors from the palette
#accessor (s_palette palette)[int index] => t_argb32 = \
	palette.colors[index]

// usage example:
t_argb32 color = palette[3];
```
```c
// example 32-bit color bitmap array
typedef struct	s_bitmap_
{
	t_argb32*	pixels;
	int			width;
	int			height;
}				s_bitmap;

// declare an accessor to get pixels from their coordinates
#accessor (s_bitmap bitmap)[int x, int y] => t_argb32 = \
	bitmap.pixels[y * bitmap.width + x]

// usage example:
for (int x = 0; x < bitmap->width; ++x)
for (int y = 0; y < bitmap->height; ++y)
{
	t_argb32 color = bitmap[x, y];
}
```
```c
typedef struct	s_keyval_
{
	char*		key;
	char*		type;
	void*		value;
}				s_keyval;

typedef struct	s_dict_
{
	t_size		count;
	s_keyval*	items;
}				s_dict;

#namespace Dict

s_dict	New(int items, s_keyval ...)
{
	return ((s_dict)
	{
		.count = items,
		Array<s_keyval>.New(items, va_list),
	});
}

// declare an accessor to get dictionary values from their key names
#accessor (s_dict dict)[char const* key] => void* = \
	Dict.Get(dict, key)

// usage example:
s_dict dict = Dict.New(2,
	(s_keyval){ .key="foo", .value="FOO" },
	(s_keyval){ .key="bar", .value="BAR" },
);

char* bar = (char*)dict["bar"];
```
Perhaps allow replacing/overriding the standard pointer deref brackets, for special behaviors on pointer types ?
It can allow for some cool stuff, but this kind of syntactic sugar may be too "implicit" for C though...
```c
// parse utf8 char smartly in a string
typedef wchar_t	t_utf8;
t_utf8	String_Get_UTF8(t_utf8* str, size_t index)
{
	char* str = (char*)utf8;
	t_utf8 result = str[index];
	if (str[++index] && (result & 0x000080))	result |= (str[index] << 8);
	if (str[++index] && (result & 0x008000))	result |= (str[index] << 16);
	if (str[++index] && (result & 0x800000))	result |= (str[index] << 24);
	return (result);
}

#accessor 	(t_utf8* str)[size_t index] => t_utf8 = \
	String_Get_UTF8(str, index)

// usage example:
char* str = "char ñ";
t_utf8 utf8_char = (t_utf8*)str[5];
```



### Namespaces:

Namespaces sections can be defined, by using the `#namespace` preprocessor directive:
```c
// in .h header file
#namespace String
char*	Duplicate(char* str);
#namespace // using the namespace instruction with nothing after it ends the namespace section

...

// in .c source file
char*	String.Duplicate(char* str)
{
	return (Memory.Duplicate(String.Length(str) + 1));
}

char* str = String.Duplicate("foo");
```
Namespaces can be also be nested:
```c
// in .h header file
#namespace Compression.RLE
t_u8*	Compress(t_u8* data, size_t length);
t_u8*	Decompress(t_u8* data);

#namespace Compression.LZ77	// a new `#namespace` directive replaces the previous one, similar to `.section` in ASM
t_u8*	Compress(t_u8* data, size_t length);
t_u8*	Decompress(t_u8* data);

...

// in .c source file
t_u8* decompressed_data_rle = Compression.RLE.Decompress(file);
t_u8* decompressed_data_lz77 = Compression.LZ77.Decompress(file);
```
Note that there can only be one namespace section active at any point in the code.
Also, there is no `#using` directive to make namespace token usage implicit, names will usually need to be fully explicitly written out.



### Generic types:
A namespace can declare a generic type:
```c
// a generic typed namespace can indicate a default type (which will be used if no <T> is written)
#namespace List<T>
// Functions in this namespace cannot really use the generic type directly, they must treat it as opaque

typedef struct	s_list_<T>
{
	s_list<T>*	next;
	size_t		item_size;
	T			item;
}				s_list<T>;

...

// usage example:
s_list<char*> const*	string_list;
```
Also note, if you do not write out a generic type explicitly, then the transpiler will attempt to infer the type, using the `typeof` operator:
```c
#namespace List<T>
s_list<T>*	NewItem(T value);
#namespace

char*	str = String.Duplicate("hello world");

// in ++c file, this line:
s_list<char*>*	list = List.NewItem(str);
// ppp infers the type:
s_list<char*>*	list = List<typeof(str)>.NewItem(str);
// resolves 'typeof' operator
s_list<char*>*	list = List<char*>.NewItem(str);
// and finally, transpiles to this C code:
s_list_char_p*	list = List_char_p_NewItem(str);
```
There is a maximum of 4 generic types for one namespace.

##### Namespace:
```c
// A generic typed namespace can have a restricted set of types:
#namespace Math<T = (float|double|fixed|int)>
// Functions using this namespace can have different implementations for each child type
// (this is similar to "template specialization" in C++)

T	Cos(T x);
T	Sin(T x);
T	Tan(T x);

// usage example:
float cosine_float = Math<float>.Cos(value);	// specific implementation for 32-bit floating-point type cos()
double cosine_f64 = Math<double>.Cos(value);	// specific implementation for 64-bit floating-point type cos()
fixed cosine_fixed = Math<fixed>.Cos(value);	// specific implementation for fixed-point type cos()
```
A namespace can also take a compile-time constant value, rather than a type:
```c
// in .h header file
#namespace List<T, int N = 10> // example fixed-size linked list generic type, with default size `10`

s_list<T, N>	New(size_t length, T ...);
void			Append(s_list<T, N>* list, s_list<T, N>* element);
s_list<T, N>	Filter(s_list<T, N>* list, (s_list<T, N>* element)=>bool filter);

// usage example:
// in .c source file
s_list<char*, 3> list = List<char*, 3>.New(3, "foo", "bar", "baz");
```
Here's a set of examples of generic type usage with lists:
```c
// in .h header file
#namespace List<T> // by default, 'void*' type will be used

s_list<T>	New(size_t length, T ...);
void		Append(s_list<T> list, s_list<T> element);
s_list<T>	Filter(s_list<T> list, bool (*filter)(s_list<T> element));

// usage example:
// in .c source file
s_list<char*> list = List<char*>.New(3, "foo", "bar", "baz");
```
##### Local Scope function:
```c
// usage example:
void	KeepOnlyEvenNumbers(s_list<int> integers)
{
	s_list<int> only_even = List<int>.Filter(integers,
		bool	filter(s_list<int> element)
		{
			return (element.item % 2 == 0);
		}
	);
}

// NB: when transpiled to C, the 'filter' local function will be in global scope, named:
static bool	KeepOnlyEvenNumbers_filter(s_list<int> element)
{
	return (element.item % 2 == 0);
}
```
##### Operator:
```c
// list concatenation operator
#namespace List<T = void*>
#operator + (s_list<T>* left, s_list<T>* right) => s_list<T> = \
	List<T>.Join(left, right)

// usage example:
s_list<char*> list = List<char*>.New(2, "foo", "bar");
s_list<char*> list = List<char*>.New(2, "bar", "baz");
s_list<char*> concat = list1 + list2; // type inferrence for the operator
```
##### Accessor:
```c
// list index get
#namespace List<T = void*>
#accessor (s_list<T>* list)[size_t index] => T = \
	List<T>.Get(list, index)

// usage example:
s_list<char*> list = List<char*>.New(3, "foo", "bar", "baz");
char* str = list[2]; // type inferrence for the accessor
```
dynamic anonymous 'object' type (JSON-like)
```c
#namespace KeyVal<T>

typedef struct	keyval_<T>
{
	char*	key;
	char*	type;
	T	value;
}				s_keyval<T>;

s_keyval<T>	New(char* key, T value);



#namespace Object<T=void*>

typedef s_keyval<void*>*	t_object;

t_object*	New(size_t items, s_keyval ...);

#accessor (t_object* obj)[char const* key] => T	= \
	Object<T>.Get(obj, key)



t_object* obj = Object.New(3,
	KeyVal<int>.New("index", 1), // = &(s_keyval<int>){ .key="index", .type="int", .value=1 }
	KeyVal<char*>.New("value", "foo"),
	KeyVal<t_object>.New("sub", Object.New(2,
		KeyVal<float>.New("float", 1.5),
		KeyVal<char*>.New("str", "hello")),
);

printf("%s\n", obj<object*>["sub"]<char*>["str"]); // type inferrence cannot be done here
```



### Type reflection:
The `#reflect` preprocessor directive inserts the contents of a type into the code
```c
// ++C
#reflect(uint64_t)	type
// transpiles to C:
unsigned long int
```
```c
// ++C
#reflect(uint64_t)	#type
// transpiles to C:
"unsigned long int"
```
```c
// ++C
#reflect(uint64_t)	#type #name
// transpiles to C:
"unsigned long int" "uint64_t"
```
For a struct or a union, each field is inserted:
```c
// ++C
struct s_test
{
	int x;
	int y;
	char* name;
	void (*f)(void);
};

// ++C
int main()
{
#reflect(struct s_test) \
	printf("\t%s\t%s\n", #type, #name);
}

// transpiles to C:
int main()
{
	printf("\t%s\t%s\n", "int", "x");
	printf("\t%s\t%s\n", "int", "y");
	printf("\t%s\t%s\n", "char*", "name");
	printf("\t%s\t%s\n", "(void)=>void", "f");
}
```
For an enum, each enum value is inserted:
```c
// ++C
enum e_test
{
	NONE = 0, // null
	TEST = 1,
	OTHER = 2, // test comment
	COOL = 3,
};

// ++C
int main()
{
#reflect(enum e_test) \
	printf("\t%s\t%s\n", #type, #name); comment
}

// transpiles to C:
int main()
{
	printf("\t%s\t%s\n", "0", "NONE"); // null
	printf("\t%s\t%s\n", "1", "TEST");
	printf("\t%s\t%s\n", "2", "OTHER"); // test comment
	printf("\t%s\t%s\n", "3", "COOL");
}
```



### Pre-processor instructions:


##### INCBIN
Allows you to include a binary file as a global/extern const byte array.
```c
#incbin myfile	"./path/to/file.dat"
```
In this example, an `extern` variable named `myfile` will be created, with type `unsigned char const[]`:
it holds the contents of the file given by the second argument, the string filepath.
It will also create two other variables: `myfile_end` which points to the end of the binary data array,
and `myfile_size`, which is the filesize (despite its actual type being `unsigned char const[]` as well, you must cast this to (size_t))


##### REPLACE
Creates a replacement token - works just like to the C `#define` pre-processor instruction, but operates when transpiling.
```c
void		MyFunction(void);
#replace f	MyFunction
int main()
{
	f();
}
```
The above example transpiles by replacing `f` directly inline, rather than transpiling to a C pre-processor `#define` statement.
```c
void		MyFunction(void);
int main()
{
	MyFunction();
}
```
This is the difference between `#define` and `#alias` instructions, `#alias` will change the output C code directly.


##### HEADER
Should be placed in a header file (ie: `.++h`,`.pph`,`.xxh`,etc), at the top of the file (before any `#include` directives).
Surrounds the file with include-guards, with the given token argument being the `#define` used for header inclusion guarding.
```c
// ++C code
#header(__HEADER_H)
// this is a simple test header
void HelloWorld(void);
// ...
```
The above example would transpile to the following C code output:
```c
// C code
#ifndef __HEADER_H
#define __HEADER_H

#ifdef __cplusplus
extern "C"
{
#endif

// this is a simple test header
void HelloWorld(void);
// ...

#ifdef __cplusplus
}
#endif

#endif
```
If no argument is supplied, `#header` will generate a header based on the file name (relative to the folder from where `ppp` was invoked), with two leading underscores `__`, and ending with `_H`:
- for example, in a file at path `./src/utils/header.++h`:
```c
// ++C code
#header
// ...

// transpiled output C code
#ifndef __SRC_UTILS_HEADER_H
#define __SRC_UTILS_HEADER_H
// ...
#endif
```



##### ALIAS
Creates an alias for a function/variable (must be globally scoped), using `__attribute__` (or, you can configure it to rather transpile like a `#define`, or a `#replace`).
```c
void			MyFunction(void);
#alias	func	MyFunction
```
The above example transpiles by declaring `f` with the function aliasing attribute, like so:
```c
// transpiles to:
void	MyFunction(void);
#ifdef __GNUC__
void	func(void) __attribute__((weak, alias("MyFunction")));
#else
#define func	MyFunction
#endif
```

If no second argument is supplied, the alias will be applied to the last definition immediately before it:
```c
void		MyFunction(void);
#alias	func	// `func` is an alias for `MyFunction`

extern int my_global_var;
#alias	my_gv	// `my_gv` is an alias for `my_global_var`
```



##### PACKED
Sets the struct declared after it to be packed a tight as possible, removing any and all byte-padding, by using `__attribute__`:
```c
#packed
typedef struct	s_example_
{
	char a;
	int x;
	bool b;
	int y;
}				s_example;
```
```c
// transpiles to:
__attribute__((packed))
typedef struct	s_example_
{
	...
```


##### INLINE
Sets the function declared after it to be always inlined, using `__attribute__`:
```c
#inline
void	MyFunction(void);
```
```c
// transpiles to:
__attribute__((always_inline)) inline
void*	MyFunction(void);
```


##### PURE
Sets the function declared after it to be a "pure function", (ie: a function with no side-effects), using `__attribute__`:
```c
#pure
char	MyFunction(char c);
```
```c
// transpiles to:
__attribute__((pure))
char	MyFunction(char c);
```
This allows your compiler to perform additionnal optimizations (like memoization for instance).


##### MALLOC
Sets the function declared after it to be always inlined, using `__attribute__`:
```c
#malloc
char*	MyFunction(void);
```
```c
// transpiles to:
__attribute__((malloc))
char*	MyFunction(void);
```


##### FORMAT
Sets the function declared after it to variadic argument type-cehcking according to a format string, like `printf` or `strptime`, using `__attribute__`:
```c
#format(printf, 1, 2)
void	MyFunction(char* format, ...);
```
```c
// transpiles to:
__attribute__((format(printf, 1, 2)))
void	MyFunction(char* format, ...);
```


Lastly,
- **/!\ NOT YET DECIDED, PROBABLY A BAD IDEA**: pointer types: * = $ (mutable pointer) or @ (const pointer)
```c
void*		->	void$
void const*	->	void@
```


---

# M4

TODO: write detailed description of the `#replace` directive, which explains how it interfaces with m4

```sh
m4 --synclines --prefix-builtins
```

```m4
m4_changecom(`/*',`*/')m4_dnl
m4_changequote(`<',`>')m4_dnl
```
```c
#replace #incbin	<INCBIN($1,$2)>
#replace #packed	<__attribute__((packed))>
#replace #format	<__attribute__((format($1,$2,$3)))>
#replace #alias		<__attribute__((alias(#$1)))>
#replace #align		<__attribute__((aligned($1)))>
#replace #pure		<__attribute__((pure))>
#replace #inline	<__attribute__((always_inline)) inline>
#replace #malloc	<__attribute__((malloc))>
#replace #delete	<__attribute__((delete))>
#replace #unused	<__attribute__((unused))>
#replace #replace	<define(|[$1]|,|[$2]|)>
#replace #operator	<>
#replace #accessor	<>
#replace #namespace	<>
```

PS: RegExp to get all code block contents here:
```regex
(?<=```c)\n(.*\n)+?(?=```)
```
