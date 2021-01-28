
# ++C

- A superset of C -> transpiles to C code (while keeping it as clean and readible as possible)
- You can enforce a certain code style to the resulting transpiled C code
- includes m4 multi-pass pre-processor



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



### Namespaces (only in header files):
```c
// in .h header file
namespace String
{
	char*	Duplicate(char* str);
}

// in .c source file
char*	String.Duplicate(char* str)
{
	return (Memory.Duplicate(String.Length(str) + 1));
}
char* str = String.Duplicate("foo");
```
```c
// namespaces can be nested
// in .h header file
namespace Compression
{
	namespace RLE
	{
		t_u8*	Compress(t_u8* data, size_t length);
		t_u8*	Decompress(t_u8* data);
	}
	namespace LZ77
	{
		t_u8*	Compress(t_u8* data, size_t length);
		t_u8*	Decompress(t_u8* data);
	}
}

// in .c source file
t_u8* decompressed_data = Compression.LZ77.Decompress(file);
```



### Functions declared in local scopes (prime citizens-ish):

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
// NB: when transpiled to C, the 'HelloWorld' local function will be in global scope, named:
static void	WaitAndRunCallback_HelloWorld(void)
{
	printf("Hello World!\n");
}
```
Perhaps we can implement a variable-capture mechanism which isn't too complex ?
Otherwise, for simplicity, only allow pure functions and functions with only global-scope side-effects, to be defined locally.



### Operators:
```c
// string concatenation operator
char*		operator: + (char const* left, char const* right)
{
	return (String.Join(left, right));
}
// usage example:
char* new_str = "Concatenated: " + str;
```
```c
// NULL check and return operator
void const*	operator: ?? (void const* left, void const* right)
{
	return (left == NULL ? right : left);
}
// usage example:
char* new_str = str ?? "str is NULL";
```
```c
// unary operator: complex number conjugate
typedef struct	s_complex_
{
	float re;
	float im;
}				s_complex;
s_complex	operator: ! (s_complex right)
{
	return (Complex.Conjugate(right));
}
// usage example:
s_complex z = { 1.5, 2.2 };
s_complex conjug = !z;
```
```c
// bool exclusive OR (XOR) operator
bool		operator: ^^ (bool left, bool right)
{
	return ((left ? TRUE : FALSE) ^ (right ? TRUE : FALSE));
}
// usage example:
if (i < 3 ^^ x >= 4) { /* do stuff */}
```
```c
// 3D vector subtraction operator
s_vector3d	operator: - (s_vector3d left, s_vector3d right)
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
The accessor function body must be a simple inline-able `return` statement.
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
t_argb32	accessor: (s_palette palette)[int index]
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
t_argb32	accessor: (s_bitmap bitmap)[int x, int y]
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
namespace Dict
{
	s_dict	New(int items, s_keyval ...);
	{
		return ((s_dict)
		{
			.count = items,
			Array<s_keyval>.New(items, va_list),
		});
	}
	// declare an accessor to get dictionary values from their key names
	void*	accessor: (s_dict dict)[char const* key]
	{
		return (Dict.Get(dict, key));
	}
}
// usage example:
s_dict dict = Dict.New(2,
	(s_keyval){ .key="foo", .value="FOO" },
	(s_keyval){ .key="bar", .value="BAR" },
);
char* bar = (char*)dict["bar"];
```
Perhaps allow replacing/overriding the standard pointer deref brackets, for things other than structs ?
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
t_utf8		accessor: (t_utf8* str)[size_t index]
{
	return (String_Get_UTF8(str, index));
}
// usage example:
char* str = "char ñ";
t_utf8 utf8_char = (t_utf8*)str[5];
```



### Generic types:
```c
typedef struct	s_list_<TYPE=void*>
{
	s_list*		next;
	size_t		item_size;
	<TYPE>		item;
}				s_list<TYPE=void*>; // by default, 'void*' type will be used
// usage example:
s_list<char*> const*	string_list;
```
Here's a set of examples of generic type usage with lists:
##### Namespace:
```c
// a generic type can be applied to a namespace
namespace Math<TYPE=float>
{
	<TYPE>	Cos(<TYPE> x);
}
// usage example:
float cosine_float = Math<float>.Cos(value);	// 32-bit floating-point type cos()
double cosine_f64 = Math<double>.Cos(value);	// 64-bit floating-point type cos()
fixed cosine_fixed = Math<fixed>.Cos(value);	// fixed-point type cos()
```
```c
// in .h header file
namespace List<TYPE=void*>
{
	s_list<TYPE>	New(size_t length, <TYPE> ...);
	void			Append(s_list<TYPE> list, s_list<TYPE> element);
	s_list<TYPE>	Filter(s_list<TYPE> list, bool (*filter)(s_list<TYPE> element));
}
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
namespace List<TYPE=void*>
{
	s_list<TYPE>*	operator: + (s_list<TYPE>* left, s_list<TYPE>* right)
	{
		return (List<TYPE>.Join(left, right));
	}
}
// usage example:
s_list<char*> list = List<char*>.New(2, "foo", "bar");
s_list<char*> list = List<char*>.New(2, "bar", "baz");
s_list<char*> concat = list1 + list2; // type inferrence for the operator
```
##### Accessor:
```c
// list index get
namespace List<TYPE=void*>
{
	<TYPE>		accessor: (s_list<TYPE>* list)[size_t index]
	{
		return (List<TYPE>.Get(list, index));
	}
}
// usage example:
s_list<char*> list = List<char*>.New(3, "foo", "bar", "baz");
char* str = list[2]; // type inferrence for the accessor
```
dynamic anonymous 'object' type (JSON-like)
```c
typedef struct	keyval_<TYPE=void*>
{
	char*	key;
	char*	type;
	<TYPE>	value;
}				keyval<TYPE>;
namespace KeyVal<TYPE=void*>
{
	keyval<TYPE>	New(char* key, <TYPE> value);
}
typedef keyval<void*>*	object;
namespace Object<TYPE=void*>
{
	object*	New(size_t items, keyval ...);

	<TYPE>		accessor: (object* obj)[char const* key]
	{
		return (Object<TYPE>.Get(obj, key));
	}
}

KeyVal<int>.New("index", 1) // = &(keyval<int>){ .key="index", .type="int", .value=1 }

object* obj = Object.New(3,
	KeyVal<int>.New("index", 1),
	KeyVal<char*>.New("value", "foo"),
	KeyVal<object>.New("sub", Object.New(2,
		KeyVal<float>.New("float", 1.5),
		KeyVal<char*>.New("str", "hello")),
);
printf("%s\n", obj<object*>["sub"]<char*>["str"]); // type inferrence cannot be done here
```
