
#include "libccc.h"
#include "libccc/char.h"
#include "libccc/string.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



#define KVT_CREATE_ARRAY(_TYPE_) \
	t_uint i = 0; \
	s_kvt* n = NULL; \
	s_kvt* p = NULL; \
	s_kvt* array = NULL; \
	if CCCERROR((source == NULL), ERROR_NULLPOINTER, \
		"source array given is NULL") \
		return (NULL); \
	array = KVT_CreateArray(); \
	if CCCERROR((array == NULL), ERROR_ALLOCFAILURE, NULL) \
		return (NULL); \
	for (i = 0; i < count; i++) \
	{ \
		n = KVT_Create##_TYPE_(source[i]); \
		if CCCERROR((n == NULL), ERROR_ALLOCFAILURE, \
			"could not create KVT array item of type `"#_TYPE_"` at index " SF_UINT, i) \
		{ \
			KVT_Delete(array); \
			return (NULL); \
		} \
		if (i == 0) \
		{ \
			array->value.child = n; \
		} \
		else \
		{ \
			p->next = n; \
			n->prev = p; \
		} \
		p = n; \
	} \
	if (array->value.child) \
	{ \
		array->value.child->prev = n; \
	} \
	return (array); \



s_kvt*	KVT_CreateArray_Boolean	(t_bool const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Boolean)	}

s_kvt*	KVT_CreateArray_UInt	(t_uint const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U8		(t_u8 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U16		(t_u16 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U32		(t_u32 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_U64		(t_u64 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
#if LIBCONFIG_USE_INT128
s_kvt*	KVT_CreateArray_U128	(t_u128 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
#endif

s_kvt*	KVT_CreateArray_SInt	(t_sint const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S8		(t_s8 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S16		(t_s16 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S32		(t_s32 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
s_kvt*	KVT_CreateArray_S64		(t_s64 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
#if LIBCONFIG_USE_INT128
s_kvt*	KVT_CreateArray_S128	(t_s128 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Integer)	}
#endif

s_kvt*	KVT_CreateArray_Float	(t_float const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Float)	}
s_kvt*	KVT_CreateArray_F32		(t_f32 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Float)	}
s_kvt*	KVT_CreateArray_F64		(t_f64 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Float)	}
#if LIBCONFIG_USE_FLOAT80
s_kvt*	KVT_CreateArray_F80		(t_f80 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Float)	}
#endif
#if LIBCONFIG_USE_FLOAT128
s_kvt*	KVT_CreateArray_F128	(t_f128 const*	source, t_uint count)		{ KVT_CREATE_ARRAY(Float)	}
#endif

s_kvt*	KVT_CreateArray_String	(t_char const* const* source, t_uint count){ KVT_CREATE_ARRAY(String)	}
