
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"



#define KVT_CREATE_ARRAY(_TYPE_) \
	t_sint i = 0;							\
	s_kvt* n = NULL;						\
	s_kvt* p = NULL;						\
	s_kvt* array = NULL;					\
	if ((count < 0) || (source == NULL))	\
		return (NULL);						\
	array = KVT_CreateArray();				\
	for (i = 0; array && (i < count); i++)	\
	{										\
		n = KVT_Create##_TYPE_(source[i]);	\
		if (!n)								\
		{									\
			KVT_Delete(array);				\
			return (NULL);					\
		}									\
		if (!i)								\
		{									\
			array->value.child = n;			\
		}									\
		else								\
		{									\
			p->next = n;					\
			n->prev = p;					\
		}									\
		p = n;								\
	}										\
	if (array && array->value.child)		\
	{										\
		array->value.child->prev = n;		\
	}										\
	return (array);							\



s_kvt*	KVT_CreateArray_Boolean	(t_bool const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Boolean)	}

s_kvt*	KVT_CreateArray_UInt	(t_uint const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U8		(t_u8 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U16		(t_u16 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U32		(t_u32 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U64		(t_u64 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
#ifdef __int128
s_kvt*	KVT_CreateArray_U128	(t_u128 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
#endif

s_kvt*	KVT_CreateArray_SInt	(t_sint const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S8		(t_s8 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S16		(t_s16 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S32		(t_s32 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S64		(t_s64 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
#ifdef __int128
s_kvt*	KVT_CreateArray_S128	(t_s128 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Integer)	}
#endif

s_kvt*	KVT_CreateArray_Float	(t_float const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Float)	}
s_kvt*	KVT_CreateArray_F32		(t_f32 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Float)	}
s_kvt*	KVT_CreateArray_F64		(t_f64 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Float)	}
#ifdef __float80
s_kvt*	KVT_CreateArray_F80		(t_f80 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Float)	}
#endif
#ifdef __float128
s_kvt*	KVT_CreateArray_F128	(t_f128 const*	source, t_sint count)		{ KVT_CREATE_ARRAY(Float)	}
#endif

s_kvt*	KVT_CreateArray_String	(t_char const* const* source, t_sint count){ KVT_CREATE_ARRAY(String)	}
