
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
		HANDLE_ERROR(ALLOCFAILURE, (result == NULL), goto failure;)
		concat = KVT_Duplicate(kvt1, TRUE);
		HANDLE_ERROR(ALLOCFAILURE, (concat == NULL), goto failure;)
		error = KVT_AddToArray_Item(result, concat);
		HANDLE_ERROR(UNSPECIFIED, (error), goto failure;)
		concat = KVT_Duplicate(kvt2, TRUE);
		HANDLE_ERROR(ALLOCFAILURE, (concat == NULL), goto failure;)
		error = KVT_AddToArray_Item(result, concat);
		HANDLE_ERROR(UNSPECIFIED, (error), goto failure;)
	}
	else if (kvt1_isarray && kvt2_isarray)
		KVT_Concat_Array(kvt1, kvt2);
	else if (kvt1_isobject && kvt2_isobject)
		KVT_Concat_Object(kvt1, kvt2);
	else // concatenate arrays (put objects inside array if needed)
	{
		result = KVT_Duplicate(kvt1, TRUE);
		HANDLE_ERROR(ALLOCFAILURE, (result == NULL), goto failure;)
		concat = KVT_Duplicate(kvt2, TRUE);
		HANDLE_ERROR(ALLOCFAILURE, (concat == NULL), goto failure;)

		if (kvt1_isarray)
			KVT_AddToArray_Item(result, concat);
		else if (kvt2_isarray)
			KVT_Insert_InArray(result, 0, concat);
	}
	HANDLE_ERROR(UNSPECIFIED, (result == NULL), goto failure;)
	return (result);

failure:
	KVT_Delete(result);
	KVT_Delete(concat);
	return (NULL);
}



s_kvt*	KVT_Concat_Array(s_kvt const* kvt1, s_kvt const* kvt2)
{
	s_kvt*	result = NULL;
	s_kvt*	concat = NULL;

	HANDLE_ERROR(WRONGTYPE, (!KVT_IsArray(kvt1)), return (NULL);)
	HANDLE_ERROR(WRONGTYPE, (!KVT_IsArray(kvt2)), return (NULL);)
	result = KVT_Duplicate(kvt1, TRUE);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), goto failure;)
	concat = KVT_Duplicate(kvt2, TRUE);
	HANDLE_ERROR(ALLOCFAILURE, (concat == NULL), goto failure;)

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

#include "libccc/encode/json.h"

s_kvt*	KVT_Concat_Object(s_kvt const* kvt1, s_kvt const* kvt2)
{
	s_kvt*	result = NULL;
	s_kvt*	concat = NULL;

	HANDLE_ERROR(WRONGTYPE, (!KVT_IsObject(kvt1)), return (NULL);)
	HANDLE_ERROR(WRONGTYPE, (!KVT_IsObject(kvt2)), return (NULL);)
	result = KVT_Duplicate(kvt1, TRUE);
	HANDLE_ERROR(ALLOCFAILURE, (result == NULL), goto failure;)
	concat = KVT_Duplicate(kvt2, TRUE);
	HANDLE_ERROR(ALLOCFAILURE, (concat == NULL), goto failure;)

IO_Output_Format("\nDEBUG CONCAT KVT1:\n%s\n", JSON_ToString_Pretty(result));
IO_Output_Format("\nDEBUG CONCAT KVT2:\n%s\n", JSON_ToString_Pretty(concat));

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
