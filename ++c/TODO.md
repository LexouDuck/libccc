
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

- dereference: `*` can be written `$`:
This is to avoid synonymy with the arithmetic multiplication operator.
```c
value = *pointer; // pure C
value = $pointer; // ++C
```

- get address: `&` can be written `@`:
This is to avoid synonymy with the bitwise AND operator.
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
This is to allow for greater readibility, always having the variable name on the right-most side of a declaration.
```c
char*   strings[9]; // pure C
char*[9]   strings; // ++C
```

- function pointer types: to avoid hard-to-read function pointer types using `(*func)` notation, you can instead use `=>` arrow notation
This is to allow for greater readibility, always having the variable name on the right-most side of a declaration.
```c
void (*f)(int, char*); // pure C
(int, char*)=>void  f; // ++C

// example nested function pointers (takes another function pointer as argument)
void (*g)(int, char* (*)(char*)); // pure C
(int, (char*)=>char*) => void  g; // ++C
```



### String literals:

C supports regular string literals, as well as wide-char string literals - and since the C11 standard,
unicode string literals are also supported:
```c
"hello world!"   // => char[N]     (ANSI C)
L"hello world!"  // => wchar_t[N]  (ANSI C)
u8"hello world!" // => char[N]     (C11)
u"hello world!"  // => char16_t[N] (C11)
U"hello world!"  // => char32_t[N] (C11)
```
In ++C, alternate prefixes are accepted, and any of these syntaxes will work and transpile/compile correctly, regardless of the target C standard chosen:
```c
"hello world!"      // => t_char[N]  (++C)
w"hello world!"     // => t_sint[N]  (++C)
utf8"hello world!"  // => t_utf8[N]  (++C)
utf16"hello world!" // => t_utf16[N] (++C)
utf32"hello world!" // => t_utf32[N] (++C)
```
In the case where a unicode string literal is used, for a target C standard version which predates C11, then its contents will be directly changed in the transpiled output:
```c
// ++C
t_utf8 const* unicode = utf8"Any unicode character directly works: それは本当に作品";
// with target set is C11 or above, transpiles to:
t_utf8 const* unicode = u8"Any unicode character directly works: それは本当に作品";
// with target set is C99, transpiles to:
t_utf8 const* unicode = "Any unicode character directly works: \u305D\u308C\u306F\u672C\u5F53\u306B\u4F5C\u54C1";
// with target set to less than C99, transpiles to:
t_utf8 const* unicode = "Any unicode character directly works: \xE3\x81\x9D\xE3\x82\x8C\xE3\x81\xAF\xE6\x9C\xAC\xE5\xBD\x93\xE3\x81\xAB\xE4\xBD\x9C\xE5\x93\x81";
```

##### String Format literals:

++C allows for formatted literal strings, prefixed with an `f` character:
```c
t_utf8 const* formatted = f"This is a formatted string containing a float: #{sqrt(2.0)}";
t_utf8 const* formatted = f"This is a formatted string containing an escaped hashtag: \#";
```
Only constant expressions are allowed within the `#{}` format field. In ++C, the exact definition of a constant expression is more open-ended than it is in pure C (any pure function may be called in a constant expression - see "Transpile-time expressions" for more info).

##### String RegExp literals:

++C allows for regex literal strings, prefixed with an `r` character, and regex mode flags may be placed immediately after the ending double quote (no spaces between the ending quote and the flag characters):
```c
char const* regex1 = r"\b(My_\w*)\b"g;
char const* regex2 = r"(?x) ( [^)] __damn__ )"i;
char const* regex3 = r"[a-zA-Z_]\w*"sg;
```
When writing a regex literal, the transpiled C output string literal will:
- output errors/warnings if the underlying regular expression is malformed/invalid.
- have double backquotes `\\` wherever necessary.
- place the regex mode flags within the string, at the start, using `(?i)` notation (learn more about this here: https://www.regular-expressions.info/modifiers.html?wlr=1)

Note that libccc uses the Oniguruma Regex engine, which encompasses the features of many other RegExp engines into one:
- https://github.com/kkos/oniguruma
- https://raw.githubusercontent.com/kkos/oniguruma/5.9.6/doc/RE
- http://www.greenend.org.uk/rjk/tech/regexp.html



### Cross-platform keywords:

- `asm`: Transpiles to the more cross-platform equivalent: `__asm__`
- `inline`: Transpiles to the more cross-platform equivalent: `__inline__`
- `restrict`: Transpiles to the more cross-platform equivalent: `__restrict__`

- `alignof(X)`: Transpiles to whatever logic makes sense for the given platform
- `alignas(X)`: Transpiles to whatever logic makes sense for the given platform



### Transpile-time expressions:

Any constant expression (including calls to pure functions) can be executed at transpile-time, using the
constant expression function: `#(expression)`

Here is an example:
```c
#if #(sqrt(4.0) == 2.0)
typedef enum something
{
	SOMEVALUE = #(sqrt(8.0)),
}	e_something;
#endif
```
This will transpile to:
```c
#if 1
typedef enum something
{
	SOMEVALUE = 4.0,
}	e_something;
#endif
```
Note that memory allocation/freeing are non-pure operations, so they cannot be performed at transpile-time.



### Transpile-time operators:

- `typeof(X)`: Transpiles to the fully resolved type of the variable/value/token `X`
- `nullof(X)`: Transpiles to the user-defined default value of the variable/value/token `X`
- `formatof(X)`: Transpiles to the user-defined string literal printf format specifier of the variable/value/token `X`

There is also an `is` operator, which allows for equality checks between types at transpile-time:
```c
#if #(typeof(size_t) is unsigned long)
	#warning "memory size type is unsigned long"
#elif #(!(typeof(size_t) is unsigned long long))
	#warning "memory size type is unsigned long long"
#endif
```
A type equality check returns `1` if both types, when fully resolved (after following any nested `typedef`s), are the same.
Essentially, any 2 types which would issue a warning when implicitly casted will have `is` between them return `0`.
Note that this operator is not symmetrical, ie: `A is B` is not the same as `B is A`, here is a simple example:
```c
#(char* is char const*) // result is `1`, since a mutable pointer implicitly casts to its constant equivalent
#(char const* is char*)	// result is `0`, since a constant pointer cannot be coerced to mutable implicitly
```

You can use transpile-time expressions alongside existing preprocessor directives:
```c
//! compile-time operators like sizeof() can be used in `#if` statements directly now, the transpiler will handle it
#if #(sizeof(char) == 1)
#endif

//! Here is an example of function-call generic type promotion (to use with `va_arg()`)
#if #(typeof(T) is char)
	#define T_VA_ARG	int
#elif #(typeof(T) is short)
	#define T_VA_ARG	int
#elif #(typeof(T) is float)
	#define T_VA_ARG	double
#else
	#define T_VA_ARG	T
#endif
```


### Optional function arguments (named):

In ++C, you can declare functions with optional arguments:
```c
// ++C
void MyFunc(int arg1, int arg2, [ int arg3, int arg4 = 0, int arg5 = 0 ]);
// usage example
MyFunc(1, 1, 1, .arg4=1);
```
Any optional arguments must be placed after the necessary positional arguments, enclosed in square brackets.
You can set a default value for an optional argument, with the `=` assignment operator.

When calling the function, optional arguments can either be provided in their normal positional order,
or they may all be specified in any order, if the argument name is given for each: `.myarg = 1, `.

When transpiled to C, the example above becomes:
```c
void MyFunc_kwargs(int arg1, int arg2, struct MyFunc_kwargs { int _; int arg3; int arg4; } kwargs);
#define MyFunc(ARG1, ARG2, ...) \
	MyFunc_kwargs(ARG1, ARG2, &(struct MyFunc_kwargs { int _; int arg3; int arg4; }) { ._ = 0, __VA_ARGS__ })
// usage example
MyFunc(1, 1, 1, .arg4=1, .arg5=0);
```
This feature works thanks to a neat trick which leverages C99 compound struct initializers to have type-safe optional arguments.
You can learn more about this here: https://snai.pe/posts/varargs



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
When transpiled to C, this becomes:
```c
// NB: when transpiled to C, the 'HelloWorld' local function will be in global scope, named:
void	WaitAndRunCallback(void (*callback)(void));

static
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
For simplicity, only pure functions (no side-effects) and functions with only global-scope side-effects, can be defined locally.

TODO: DEBATE: Perhaps we can implement a variable-capture mechanism which isn't too complex ?
	This way parent-scoped local variables can be used, like in many modern languages.
	Although, this requires some method of storage for the local variables used (like a "closure"),
	and generally is not very idiomatic to C, since it "hides away" some function arguments.

TODO: add example to show how variable capture is complicated


### Preprocessor directives:

Most of the new additions in ++C take the form of new preprocessor directives - this is done for 2 reasons:
- Because they all involve operations that occur at transpile-time (so, they occur before any #ifs or #defines)
- To avoid adding new keywords to the C language which could conflict with existing C code, since one of the goals of ++C is to have full two-way interoperability between both languages.

Here is a list of the preprocessor directives which ++C provides:
```c
//! define a custom operator (optionally with a certain specified `precedence` and `associativity`)
#operator	$	(char* a, char* b) => int	= DoOperation(a, b)

//! define a custom accessor syntax for a struct/union (custom brackets `get` functions)
#accessor (struct s var)[int index] => int	= GetFunction(var, index)

//! works similar to namespaces and templates in C++ (read more about generic namespace types below)
#namespace NameSpace.Type<T=(float|int), P>

//! defines a category of types, which verify certain conditions
#interface i_iterable<T>
	#has #(sizeof(i_iterable<T>) == 1)
	#has Iterate(i_iterable<T> self, (T)=>void f)

//! defines a type with additional info: operators, 
#type t_string = char*
	#has nullof: NULL
	#has formatof: "%s"
	#has i_iterable: { Iterate: String_Iterate; }

//! type reflection - a special kind of macro, for types (inserts contents of a type into the code)
#reflect(struct s)	printf("%s %s;\n", #type, #name)

//! works like a `#define` macro, but occurs at transpile-time, and uses the powerful `m4` macro engine (by K&R)
#replace MACRO() <string>

//! insert header include guards at the beginning and end of a header file (and c++ `extern "C" {}`guards)
#header __HEADER_H

//! include a binary file into the executable as an extern const global variable
#incbin myvar "filepath"

//! cross-platform way to declare function attributes (in GNU C for example: `__attribute__((alias, ...))`)
#is alias(token)
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
- `= - + * / % & | ^ ! ~ ? : < > $ @`

Looking at it the other way around, the following ASCII characters cannot be used for a custom operator:
- `. , ; ( ) [ ] { } # ' " \`

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

If you wish to define a "word" operator which uses regular token characters, you can make a `#replace` macro which wraps a custom operator:
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
- the first argument is `precedence`: an integer index of the operator - by default it will be 0 (highest priority)
- the second argument is `associativity`: a boolean (int 0 or 1), 0 (default) for left-to-right, 1 for right-to-left
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
#operator(5, FALSE) +   (char const* left, char const* right) => char* = String.Join(left, right)
#operator(5, FALSE) :+  (char*       left, char const* right) => char* = String.Append(left, right)
#operator(5, FALSE) +:  (char const* left, char*       right) => char* = String.Prepend(left, right)
#operator(5, FALSE) :+: (char*       left, char*       right) => char* = String.Merge(left, right)

// usage example:
char* new_str = "Concatenated: " + str;
```
You can also define unary operators (but not ternary operators):
```c
// unary complex number conjugate operator
typedef struct complex
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
// boolean exclusive OR (XOR) operator
#operator(12, FALSE) ^^ (bool left, bool right) => bool = \
	((left ? TRUE : FALSE) ^ (right ? TRUE : FALSE))

// usage example:
if (i < 3 ^^ x >= 4) { /* do stuff */}
```
```c
// 3D vector subtraction operator
#operator - (s_vector3d left, s_vector3d right) => s_vector3d = \
	(s_vector3d) \
	{ \
		.x = left.x - right.x, \
		.y = left.y - right.y, \
		.z = left.z - right.z, \
	} \

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
typedef struct palette
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
typedef struct bitmap
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
typedef struct keyval
{
	char*		key;
	char*		type;
	void*		value;
}				s_keyval;

typedef struct dict
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
#namespace

...

// in .c source file
char*	String.Duplicate(char* str)
{
	return (Memory.Duplicate(String.Length(str) + 1));
}

char* str = String.Duplicate("foo");
```
Using the `#namespace` instruction with nothing after it, ends the namespace section.
To be precise, it brings us back to the global-scope namespace, since there is no argument given.

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

typedef struct list<T>
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


### Interfaces
++C supports interfaces (similar to their incarnations in many other languages): an interface defines a category of types, which verify certain conditions
```c
#interface i_iterable<T>
	#has #(sizeof(i_iterable<T>) == 1)
	#has Iterate(i_iterable<T> self, (T) => void f) => void
```
An interface may be followed by any number of `#has` directives, which describe the interface.
To be precise, an interface `#has` directive accepts:
- a function prototype: any type which implements this interface will require a corresponding function to be mapped
- a variable declaration: any type which implements this interface
- a transpile-time conditional expression: this expression will be executed to check that a type does indeed implement the interface in question


### Types

++C supports a `#type` directive, which creates a c typedef, as well as define other additional info which is associated to this type
```c
#type t_string = char*
	#has nullof: NULL
	#has formatof: "%s"
	#has i_iterable: { .Iterate = String_Iterate; }
```
An interface may be followed by any number of `#has` directives, which describe the interface.
To be precise, an interface `#has` directive accepts:



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
struct test
{
	int x;
	int y;
	char* name;
	void (*f)(void);
};

// ++C
int main()
{
	#reflect(struct test) \
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
	printf("\t%s\t%s\n", #value, #type, #name); comment
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



### REPLACE: m4 macros

Creates a replacement token - works similarly to the C `#define` pre-processor instruction, but operates when transpiling.
```c
void		MyFunction(void);
#replace f <MyFunction>
int main()
{
	f();
}
```
The above example transpiles by replacing `f` directly inline, rather than transpiling to a C `#define` statement:
```c
void		MyFunction(void);
int main()
{
	MyFunction();
}
```
The substitute expansion string can be written with either `"` double-quotes, or `<`/`>` chevron quotes, much like the `#include` C pre-processor directive.
The `#replace` directive is performed/transpiled using `m4` - this means that several more powerful features are available, which you can learn more about here: https://www.gnu.org/software/m4/manual/m4.html.
For instance, since `m4` is not single-pass, you can make recursive macros (define a macro from within a macro).
For this to be possible though, you must use different characters to begin and finish the macro string (ie: you must use a `<>` chevron-quoted string in this case).



### INCBIN: include binary file as global constant variable
Allows you to include a binary file as a global/extern const byte array.
```c
#incbin myfile	"./path/to/file.dat"
```
In this example, an `extern` variable named `myfile` will be created, with type `unsigned char const[]`:
it holds the contents of the file given by the second argument, the string filepath.
This directive will create a total of 3 global constant variables:
```c
extern t_u8 const[] myfile;      // this is the binary contents of the included file
extern t_u8 const[] myfile_end;  // this points to the end of the binary data array
extern t_size const myfile_size; // this is the filesize - ie: the result of `(myfile_end - myfile)`
```


### HEADER: guard a header file against double-inclusion

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
#pragma once
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
If no argument is supplied, `#header` will generate a header `#define` name based on the file name (relative to the folder from where `ppp` was invoked), with two leading underscores `__`, and ending with `_H`:
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



### Function attributes:

++C provides the `#is` instruction to associate traits to types/variables/functions.
In particular, there are 9 pre-defined `#is` attributes:
```c
#is inline              //!< cross-platform way to use `__attribute__((always_inline, ...))` and/or `inline`
#is noreturn            //!< cross-platform way to use `__attribute__((noreturn, ...))` and/or `_Noreturn`
#is align(4)            //!< cross-platform way to use `__attribute__((align, ...))` and/or `_Alignas`
#is alias(token)        //!< cross-platform way to use `__attribute__((alias, ...))`
#is format(func, 1, 2)  //!< cross-platform way to use `__attribute__((format, ...))`
#is malloc              //!< cross-platform way to use `__attribute__((malloc, ...))`
#is delete              //!< cross-platform way to use `__attribute__((delete, ...))`
#is pure                //!< cross-platform way to use `__attribute__((pure, ...))`
#is packed              //!< cross-platform way to use `__attribute__((packed, ...))`
```
Users can also define their own `#is` attributes - this is a powerful tool to give additional compile-time errors/warnings, so as to have safer/more rigourous code.
```c
#attribute create         = __attribute__((malloc))
#attribute delete(argpos) = __attribute__((delete(argpos)))
#attribute format(function, t_uint argpos_format, t_uint argpos_valist) =
	#if (!(typeof(function.arg_types[argpos_format]) is char*))
		#error f"Invalid 'format()' attribute: expected format string type argument at position #{argpos_format}"
	#elif (!(typeof(function.arg_types[argpos_valist]) is ...))
		#error f"Invalid 'format()' attribute: expected variadic ellipsis argumebt at position #{argpos_valist}"
	#else
		
	#endif

//decl_function
//decl_variable
//decl_compound
```



Below is a description of all the pre-defined `#is` attributes.


##### INLINE
Sets the function declared after it to be always inlined, using `__attribute__`:
```c
#is inline
void	MyFunction(void);
```
```c
// transpiles to:
__attribute__((always_inline)) inline
void*	MyFunction(void);
```


##### ALIAS
Creates an alias for a function/variable (must be globally scoped), using `__attribute__` (or, you can configure it to rather transpile like a `#define`, or a `#replace`).
```c
void			MyFunction(void);
#is alias	func	MyFunction
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
#is alias	func	// `func` is an alias for `MyFunction`

extern int my_global_var;
#is alias	my_gv	// `my_gv` is an alias for `my_global_var`
```


##### PACKED
Sets the struct declared after it to be packed a tight as possible, removing any and all byte-padding, by using `__attribute__`:
```c
#is packed
typedef struct example
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
typedef struct example
{
	...
```


##### PURE
Sets the function declared after it to be a "pure function", (ie: a function with no side-effects), using `__attribute__`:
```c
#is pure
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
#is malloc
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
#is format(printf, 1, 2)
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
```

PS: RegExp to get all code block contents here:
```regex
(?<=```c)\n(.*\n)+?(?=```)
```
