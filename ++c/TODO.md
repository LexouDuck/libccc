
# ++C

- A superset of C -> transpiles to C code (while keeping it as clean and readible as possible)
- You can enforce a certain code style to the resulting transpiled C code
- Automatic header include-guard insertion (and C++ `#ifdef __cplusplus extern "C" { ... }`)
- Includes m4 multi-pass pre-processor
- To differentiate ++C code from C or C++, by convention the following file formats are accepted:
	- `++c`, `ppc`, `xxc` (case insensitive), these transpile to `.c` files
	- `++h`, `pph`, `xxh` (case insensitive), these transpile to `.h` files
- Several language features added, all in the form of new pre-processor directives:
```c
#namespace NameSpace.SubSpace
#function type	FunctionName(int arg)	{ DoSomething(); return (var); }
#operator	$ (type a, type b) = int	{ return (DoOperation(a, b)); }
#accessor (type var)[int index] = int	{ return (GetFunction(var, index)); }
#incbin(myvar, "filepath")
#replace("old", "new")
#alias(token)
#align(4)
#format(func, 1, 2)
#malloc
#delete
#inline
#pure
#packed
#reflect // ?
```



# Warnings:

++C also acts as a linter - performing additional code checks and giving many useful warnings.
Here are the warnings which are added by default (any warning can be deactivated in the same way you would do with gcc: `-Wno-*`)
- `-Wimplicit-cast` explicit type casting everywhere (float to int, int to float, enum to int, etc)
- `-Wlingering-alloc` local variable 'a' was allocated, and function returned something which isn't 'a', 'a' should be freed
- `-Wunchecked-null` pointer potentially NULL
- `-Winvalid-enum` integer value was assigned to enum type, but this integer is not defined in the enum
- `-Wmisaligned-pointer` warn of potential pointer alignment issues, which can be platform-specific



# Features:

### Accepted alternate notation:

- dereference: * = $ (to avoid synonymy with the multiply operator)
```c
value = *pointer; // pure C
value = $pointer; // ++C
```
- get address: & = @ (to avoid synonymy with the bitwise AND operator)
```c
address = &value; // pure C
address = @value; // ++C
```
- pointer types: * = $ (mutable pointer) or @ (const pointer)
```c
void*		->	void$
void const*	->	void@
```



### Namespaces:

Namespaces can only be used in header files:
```c
// in .h header file
#namespace String
char*	Duplicate(char* str);
#namespace // using the namespace instruction with nothing after it ends the namespace section

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

// in .c source file
t_u8* decompressed_data_rle = Compression.RLE.Decompress(file);
t_u8* decompressed_data_lz77 = Compression.LZ77.Decompress(file);
```



### Functions declared in local scopes (prime citizens-ish):

Use the `#function` instruction to declare a function in a local scope
```c
void	WaitAndRunCallback(void (*callback)(void));

int	main()
{
	WaitAndRunCallback(
		#function void HelloWorld(void)
		{
			printf("Hello World!\n");
		}
	);
}
```
Perhaps we can implement a variable-capture mechanism which isn't too complex ?
Otherwise, for simplicity, only allow pure functions and functions with only global-scope side-effects, to be defined locally.
```c
// NB: when transpiled to C, the 'HelloWorld' local function will be in global scope, named:
void	WaitAndRunCallback(void (*callback)(void));

static void	main_HelloWorld(void)
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



### Operators:
```c
// integer power operator
#operator ** (int left, int right) = int
{
	return (Math<int>.Power(left, right));
}
// usage example:
printf("%d", 2 ** 15);
```
```c
// NULL check and return operator
#operator ?? (void const* left, void const* right) = void const*
{
	return (left == NULL ? right : left);
}
// usage example:
char* new_str = str ?? "str is NULL";
```
```c
// fixed-point math
#operator	+ (t_fixed a, t_fixed b) = t_fixed	{ return (Fixed.Add(a, b)); }
#operator	- (t_fixed a, t_fixed b) = t_fixed	{ return (Fixed.Sub(a, b)); }
#operator	* (t_fixed a, t_fixed b) = t_fixed	{ return (Fixed.Mul(a, b)); }
#operator	/ (t_fixed a, t_fixed b) = t_fixed	{ return (Fixed.Div(a, b)); }
```
```c
// string concatenation operators
#operator  +	(char const* left, char const* right) = char*	{ return (String.Join(left, right)); }
#operator  :+	(char*       left, char const* right) = char*	{ return (String.Append(left, right)); }
#operator  +:	(char const* left, char*       right) = char*	{ return (String.Prepend(left, right)); }
#operator  :+:	(char*       left, char*       right) = char*	{ return (String.Merge(left, right)); }

// usage example:
char* new_str = "Concatenated: " + str;
```

```c
// unary complex number conjugate operator
typedef struct	s_complex_
{
	float re;
	float im;
}				s_complex;
#operator ! (s_complex right) = s_complex
{
	return (Complex.Conjugate(right));
}
// usage example:
s_complex z = { 1.5, 2.2 };
s_complex conjug = !z;
```
```c
// bool exclusive OR (XOR) operator
#operator ^^ (bool left, bool right) = bool
{
	return ((left ? TRUE : FALSE) ^ (right ? TRUE : FALSE));
}
// usage example:
if (i < 3 ^^ x >= 4) { /* do stuff */}
```
```c
// 3D vector subtraction operator
#operator - (s_vector3d left, s_vector3d right) = s_vector3d
{
//	return (Vector3D.Add(left, right));
	return ((s_vector3d)
	{
		.x = left.x - right.x,
		.y = left.y - right.y,
		.z = left.z - right.z,
	});
}
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
#accessor (s_palette palette)[int index] = t_argb32
{
	return (palette.colors[index]);
}
// usage example:
t_argb32 color = palette[3];
```
```c
// example 32-bit color bitmap array
typedef struct	s_bitmap_
{
	t_argb32*	pixels;
	int width;
	int height;
}				s_bitmap;
// declare an accessor to get pixels from their coordinates
#accessor (s_bitmap bitmap)[int x, int y] = t_argb32
{
	return (bitmap.pixels[y * bitmap.width + x]);
}
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
	keyval*		items;
}				s_dict;

#namespace Dict
s_dict	New(int items, s_keyval ...);
{
	return ((s_dict)
	{
		.count = items,
		Array<s_keyval>.New(items, va_list),
	});
}
// declare an accessor to get dictionary values from their key names
#accessor (s_dict dict)[char const* key] = void*
{
	return (Dict.Get(dict, key));
}

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
#accessor 	(t_utf8* str)[size_t index] = t_utf8	
{
	return (String_Get_UTF8(str, index));
}
// usage example:
char* str = "char ñ";
t_utf8 utf8_char = (t_utf8*)str[5];
```



### Generic types:
```c
#namespace List<TYPE=void*> // by default, 'void*' type will be used

typedef struct	s_list_<TYPE>
{
	s_list*		next;
	size_t		item_size;
	<TYPE>		item;
}				s_list<TYPE>;
// usage example:
s_list<char*> const*	string_list;
```
##### Namespace:
```c
// a generic type can be applied to a namespace as well
#namespace Math<TYPE=float>
<TYPE>	Cos(<TYPE> x);

// usage example:
float cosine_float = Math<float>.Cos(value);	// specific implementation for 32-bit floating-point type cos()
double cosine_f64 = Math<double>.Cos(value);	// specific implementation for 64-bit floating-point type cos()
fixed cosine_fixed = Math<fixed>.Cos(value);	// specific implementation for fixed-point type cos()
```
Here's a set of examples of generic type usage with lists:
```c
// in .h header file
#namespace List<TYPE=void*> // by default, 'void*' type will be used

s_list<TYPE>	New(size_t length, <TYPE> ...);
void			Append(s_list<TYPE> list, s_list<TYPE> element);
s_list<TYPE>	Filter(s_list<TYPE> list, bool (*filter)(s_list<TYPE> element));

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
		#function bool	filter(s_list<int> element)
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
#namespace List<TYPE=void*>
#operator + (s_list<TYPE>* left, s_list<TYPE>* right) = s_list<TYPE>
{
	return (List<TYPE>.Join(left, right));
}

// usage example:
s_list<char*> list = List<char*>.New(2, "foo", "bar");
s_list<char*> list = List<char*>.New(2, "bar", "baz");
s_list<char*> concat = list1 + list2; // type inferrence for the operator
```
##### Accessor:
```c
// list index get
#namespace List<TYPE=void*>
#accessor (s_list<TYPE>* list)[size_t index] = <TYPE>
{
	return (List<TYPE>.Get(list, index));
}

// usage example:
s_list<char*> list = List<char*>.New(3, "foo", "bar", "baz");
char* str = list[2]; // type inferrence for the accessor
```
dynamic anonymous 'object' type (JSON-like)
```c
#namespace KeyVal<TYPE>

typedef struct	keyval_<TYPE>
{
	char*	key;
	char*	type;
	<TYPE>	value;
}				keyval<TYPE>;

keyval<TYPE>	New(char* key, <TYPE> value);



#namespace Object<TYPE=void*>

typedef keyval<void*>*	object;

object*	New(size_t items, keyval ...);

#accessor (object* obj)[char const* key] = <TYPE>
{
	return (Object<TYPE>.Get(obj, key));
}



object* obj = Object.New(3,
	KeyVal<int>.New("index", 1), // = &(keyval<int>){ .key="index", .type="int", .value=1 }
	KeyVal<char*>.New("value", "foo"),
	KeyVal<object>.New("sub", Object.New(2,
		KeyVal<float>.New("float", 1.5),
		KeyVal<char*>.New("str", "hello")),
);
printf("%s\n", obj<object*>["sub"]<char*>["str"]); // type inferrence cannot be done here
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


##### ALIAS
Creates an alias for a function/variable, using `__attribute__` (or, you can configure it to rather transpile like a `#define`, or a `#replace`).
```c
void		MyFunction(void);
#alias	f	MyFunction
```
The above example transpiles by declaring `f` with the function aliasing attribute, like so:
```c
// transpiles to:
void	MyFunction(void);
void	f(void) __attribute__((weak, alias("MyFunction")));
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
void		MyFunction(void);
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




---

# M4

```sh
m4 --synclines
```

```m4
m4_changecom()m4_dnl
m4_changequote(`|[', `]|')m4_dnl
m4_define(#incbin	, |[INCBIN($1,$2)]|)m4_dnl
m4_define(#packed	, |[__attribute__((packed))]|)m4_dnl
m4_define(#format	, |[__attribute__((format($1,$2,$3)))]|)m4_dnl
m4_define(#alias	, |[__attribute__((alias(#$1)))]|)m4_dnl
m4_define(#align	, |[__attribute__((aligned($1)))]|)m4_dnl
m4_define(#pure		, |[__attribute__((pure))]|)m4_dnl
m4_define(#inline	, |[__attribute__((always_inline)) inline]|)m4_dnl
m4_define(#malloc	, |[__attribute__((malloc))]|)m4_dnl
m4_define(#delete	, |[__attribute__((delete))]|)m4_dnl
m4_define(#unused	, |[__attribute__((unused))]|)m4_dnl
m4_define(#replace	, |[define(|[$1]|,|[$2]|)]|)m4_dnl
m4_define(#operator	, |[]|)m4_dnl
m4_define(#accessor	, |[]|)m4_dnl
m4_define(#function	, |[]|)m4_dnl
m4_define(#namespace, |[]|)m4_dnl
```

PS: RegExp to get all code block contents here:
```regex
(?<=```c)\n(.*\n)+?(?=```)
```
