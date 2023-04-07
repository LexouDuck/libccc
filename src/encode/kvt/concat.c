
#include "libccc.h"
#include "libccc/memory.h"
#include "libccc/encode/common.h"

#include LIBCONFIG_ERROR_INCLUDE



s_kvt*	KVT_Concat(s_kvt const* kvt1, s_kvt const* kvt2)
{
	s_kvt*	result = NULL;
	s_kvt*	concat = NULL;
	e_cccerror	error;
	t_bool	kvt1_isarray;
	t_bool	kvt2_isarray;
	t_bool	kvt1_isobject;
	t_bool	kvt2_isobject;

	kvt1_isarray  = KVT_IsArray (kvt1);
	kvt2_isarray  = KVT_IsArray (kvt2);
	kvt1_isobject = KVT_IsObject(kvt1);
	kvt2_isobject = KVT_IsObject(kvt2);
	if (!kvt1_isarray && !kvt1_isobject &&
		!kvt2_isarray && !kvt2_isobject)
	{	// create a new array to store both values
		result = KVT_CreateArray();
		if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) goto failure;
		concat = KVT_Duplicate(kvt1, TRUE);
		if CCCERROR((concat == NULL), ERROR_ALLOCFAILURE, NULL) goto failure;
		error = KVT_AddToArray_Item(result, concat);
		if CCCERROR((error), ERROR_UNSPECIFIED, NULL) goto failure;
		concat = KVT_Duplicate(kvt2, TRUE);
		if CCCERROR((concat == NULL), ERROR_ALLOCFAILURE, NULL) goto failure;
		error = KVT_AddToArray_Item(result, concat);
		if CCCERROR((error), ERROR_UNSPECIFIED, NULL) goto failure;
	}
	else if (kvt1_isarray && kvt2_isarray)
		return (KVT_Concat_Array(kvt1, kvt2));
	else if (kvt1_isobject && kvt2_isobject)
		return (KVT_Concat_Object(kvt1, kvt2));
	else // concatenate arrays (put objects inside array if needed)
	{
		result = KVT_Duplicate(kvt1, TRUE);
		if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL) goto failure;
		concat = KVT_Duplicate(kvt2, TRUE);
		if CCCERROR((concat == NULL), ERROR_ALLOCFAILURE, NULL) goto failure;

		if (kvt1_isarray)
			KVT_AddToArray_Item(result, concat);
		else if (kvt2_isarray)
			KVT_Insert_InArray(result, 0, concat);
	}
	if CCCERROR((result == NULL), ERROR_UNSPECIFIED, NULL) goto failure;
	return (result);

failure:
	if (result)	KVT_Delete(result);
	if (concat)	KVT_Delete(concat);
	return (NULL);
}



s_kvt*	KVT_Concat_Array(s_kvt const* kvt1, s_kvt const* kvt2)
{
	s_kvt*	result = NULL;
	s_kvt*	concat = NULL;

	if CCCERROR((kvt1 == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if CCCERROR((kvt2 == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if CCCERROR(!KVT_IsArray(kvt1), ERROR_WRONGTYPE,
		"expected kvt of type ARRAY, but got type %u", kvt1->type)
		return (NULL);
	if CCCERROR(!KVT_IsArray(kvt2), ERROR_WRONGTYPE,
		"expected kvt of type ARRAY, but got type %u", kvt2->type)
		return (NULL);
	result = KVT_Duplicate(kvt1, TRUE);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;
	concat = KVT_Duplicate(kvt2, TRUE);
	if CCCERROR((concat == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;

	result->value.child->prev->next = concat->value.child; // use `prev` to access last element without looping
	concat->value.child->prev = result->value.child->prev;
	result->value.child->prev = concat->value.child->prev; // update the new first-elem `prev` to point to end of array
	Memory_Free(concat);
	return (result);

failure:
	KVT_Delete(result);
	KVT_Delete(concat);
	return (NULL);
}



s_kvt*	KVT_Concat_Object(s_kvt const* kvt1, s_kvt const* kvt2)
{
	s_kvt*	result = NULL;
	s_kvt*	concat = NULL;

	if CCCERROR((kvt1 == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if CCCERROR((kvt2 == NULL), ERROR_ALLOCFAILURE, NULL)
		return (NULL);
	if CCCERROR(!KVT_IsObject(kvt1), ERROR_WRONGTYPE,
		"expected kvt of type OBJECT, but got type %u", kvt1->type)
		return (NULL);
	if CCCERROR(!KVT_IsObject(kvt2), ERROR_WRONGTYPE,
		"expected kvt of type OBJECT, but got type %u", kvt2->type)
		return (NULL);
	result = KVT_Duplicate(kvt1, TRUE);
	if CCCERROR((result == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;
	concat = KVT_Duplicate(kvt2, TRUE);
	if CCCERROR((concat == NULL), ERROR_ALLOCFAILURE, NULL)
		goto failure;

	result->value.child->prev->next = concat->value.child; // use `prev` to access last element without looping
	concat->value.child->prev = result->value.child->prev;
	result->value.child->prev = concat->value.child->prev; // update the new first-elem `prev` to point to end of array
	Memory_Free(concat);
	return (result);

failure:
	KVT_Delete(result);
	KVT_Delete(concat);
	return (NULL);
}
