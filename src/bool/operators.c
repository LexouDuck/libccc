
#include "libccc/bool.h"

#include LIBCONFIG_ERROR_INCLUDE



inline t_bool	Bool_And   (t_bool a, t_bool b)	{ return  (a && b);	} // ⋀
inline t_bool	Bool_NAnd  (t_bool a, t_bool b)	{ return !(a && b);	} // ⊼
inline t_bool	Bool_Or    (t_bool a, t_bool b)	{ return  (a || b);	} // ⋁
inline t_bool	Bool_NOr   (t_bool a, t_bool b)	{ return !(a || b);	} // ⊽
inline t_bool	Bool_XOr   (t_bool a, t_bool b)	{ return  (a ^ b);	} // ⊻
inline t_bool	Bool_Eq    (t_bool a, t_bool b)	{ return (a == b);	} // ⇔
inline t_bool	Bool_Impl  (t_bool a, t_bool b)	{ return (a == b || b);	} // ⇒
inline t_bool	Bool_Need  (t_bool a, t_bool b)	{ return (a == b || a);	} // ⇐
//inline t_bool	Bool_NImpl (t_bool a, t_bool b)	{ return !(a == b || b);} // ⇏
//inline t_bool	Bool_NNeed (t_bool a, t_bool b)	{ return !(a == b || a);} // ⇍
//inline t_bool	Bool_True  (t_bool a, t_bool b)	{ return (TRUE);	} // ⊤
//inline t_bool	Bool_False (t_bool a, t_bool b)	{ return (FALSE);	} // ⊥
//inline t_bool	Bool_Left  (t_bool a, t_bool b)	{ return  (a);	} // ⊣
//inline t_bool	Bool_Right (t_bool a, t_bool b)	{ return !(a);	} // ⫣
//inline t_bool	Bool_NLeft (t_bool a, t_bool b)	{ return  (b);	} // ⊢
//inline t_bool	Bool_NRight(t_bool a, t_bool b)	{ return !(b);	} // ⊩
