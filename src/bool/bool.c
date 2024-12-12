
#include "libccc/bool.h"

#include LIBCONFIG_ERROR_INCLUDE



extern inline t_bool	Bool_True        (t_bool a, t_bool b)	{ (void)a;	(void)b;	return (TRUE); }	 // ⊤
extern inline t_bool	Bool_False       (t_bool a, t_bool b)	{ (void)a;	(void)b;	return (FALSE); }	 // ⊥
extern inline t_bool	Bool_Left        (t_bool a, t_bool b)	{ (void)b;	return  (a); }	 // ⊣
extern inline t_bool	Bool_NotLeft     (t_bool a, t_bool b)	{ (void)b;	return !(a); }	 // ⊢
extern inline t_bool	Bool_Right       (t_bool a, t_bool b)	{ (void)a;	return  (b); }	 // ⫣
extern inline t_bool	Bool_NotRight    (t_bool a, t_bool b)	{ (void)a;	return !(b); }	 // ⊩
extern inline t_bool	Bool_And         (t_bool a, t_bool b)	{ return  (a && b); }	// ⋀
extern inline t_bool	Bool_NotAnd      (t_bool a, t_bool b)	{ return !(a && b); }	// ⊼
extern inline t_bool	Bool_Or          (t_bool a, t_bool b)	{ return  (a || b); }	// ⋁
extern inline t_bool	Bool_NotOr       (t_bool a, t_bool b)	{ return !(a || b); }	// ⊽
extern inline t_bool	Bool_ExOr        (t_bool a, t_bool b)	{ return  (a != b); }	// ⊻
extern inline t_bool	Bool_Equiv       (t_bool a, t_bool b)	{ return  (a == b); }	// ⇔
extern inline t_bool	Bool_Imply       (t_bool a, t_bool b)	{ return  (a == b || b); }	// ⇒
extern inline t_bool	Bool_NotImply    (t_bool a, t_bool b)	{ return !(a == b || b); }	// ⇏
extern inline t_bool	Bool_Needs       (t_bool a, t_bool b)	{ return  (a == b || a); }	// ⇐
extern inline t_bool	Bool_NotNeeds    (t_bool a, t_bool b)	{ return !(a == b || a); }	// ⇍
