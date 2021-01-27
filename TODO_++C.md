
# ++C

- A superset of C -> transpiles to C code (while keeping it as clean and readible as possible)
- You can enforce a certain code style to the resulting transpiled C code
- includes m4 multi-pass pre-processor



# Features:

### Accepted alternate notation:

- dereference: * = $ (to avoid synonym with the multiply operator)
```c
value = *pointer; // pure C
value = $pointer; // ++C
```
- get address: & = @ (to avoid synonym with the bitwise AND operator)
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
```
```c
// in .c source file
char*	String.Duplicate(char* str)
{
	return (Memory.Duplicate(String.Length(str) + 1));
}
char* str = String.Duplicate("foo");
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
Otherwise, for simplicity, only allow pure functions and functions with only global-scope side-effects.



### Operators:
```c
bool		operator: ^^ (bool left, bool right)
{
	return ((left ? TRUE : FALSE) ^ (right ? TRUE : FALSE));
}
// usage example:
if (i < 3 ^^ x >= 4) { /* do stuff */}
```
```c
char*		operator: + (char* left, char* right)
{
	return (String.Join(left, right));
}
// usage example:
char* new_str = "Concatenated: " + str;
```
```c
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
```c
// example 32-bit color bitmap array
typedef struct	s_bitmap_
{
	t_argb32*	pixels;
	int width;
	int height;
}				s_bitmap;
// declare an accessor to get pixels from their coordinates
t_argb32	accessor: (s_bitmap* bitmap)[int x, int y]
{
	return (bitmap->pixels[y * bitmap->width + x]);
}
// usage example:
for (int x = 0; x < bitmap->width; ++x)
for (int y = 0; y < bitmap->height; ++y)
{
	t_argb32 color = bitmap[x, y];
}
```
```c
// parse utf8 char smartly in a string
t_utf8		accessor: (t_utf8* utf8)[size_t index]
{
	char* str = (char*)utf8;
	t_utf8 result = str[index];
	if (str[++index] && (result & 0x000080))	result |= (str[index] << 8);
	if (str[++index] && (result & 0x008000))	result |= (str[index] << 16);
	if (str[++index] && (result & 0x800000))	result |= (str[index] << 24);
	return (result);
}
// usage example:
int utf8_char = ((t_utf8*)str)[3];
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
// in .h header file
namespace List<TYPE=void*>
{
	s_list<TYPE>	New(<TYPE> item, size_t item_size);
	void			Append(s_list<TYPE> list, s_list<TYPE> element);
	s_list<TYPE>	Filter(s_list<TYPE> list, bool (*filter)(s_list<TYPE> element));
}
// usage example:
// in .c source file
s_list<char*> list = List<char*>.New("Cool", 4);
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
s_list<char*> list = List<char*>.New("foo", "bar");
s_list<char*> list = List<char*>.New("bar", "baz");
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
s_list<char*> list = List<char*>.New("foo", "bar", "baz");
char* str = list[2]; // type inferrence for the accessor
```
