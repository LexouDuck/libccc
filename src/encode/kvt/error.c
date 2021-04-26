
#include "libccc.h"
#include "libccc/encode/common.h"



e_error_kvt		global_error_kvt = OK; // TODO figure out a way to not use any global state ?



inline
e_error_kvt	KVT_GetError(void)
{
	return (global_error_kvt);
}

inline
e_error_kvt	KVT_SetError(e_error_kvt error)
{
	global_error_kvt = error;
	return (error);
}



t_char const*	KVT_GetErrorMessage(e_error_kvt error)
{
	switch (error)
	{
		case ERROR_KVT_OK:					return ("No error");
		case ERROR_KVT_INVALIDARGS:			return ("The arguments given to a KVT function were invalid");
		case ERROR_KVT_ALLOCATIONFAILURE:	return ("A KVT function was interrupted miday because it failed to allocate data");
		case ERROR_KVT_OBJECTKEYNOTFOUND:	return ("The given KVT item key could not be found within the given KVT object");
		case ERROR_KVT_INCORRECTTYPE:		return ("A KVT typed operation was attempted on a value with a mis-matching type");
		case ERROR_KVT_INDEXTOOLARGE:		return ("An index argument was given which is too large for the array in question");
		case ERROR_KVT_ENUMTOOLARGE:		return ("An enum value was given which is outside the bounds of the enum type it belongs to");
		case ERROR_KVT_ISREFERENCE:			return ("An operation was aborted since it attempted to free a 'reference' item");
		default:							return ("Unknown");
	}
}
