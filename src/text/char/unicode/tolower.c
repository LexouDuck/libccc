
#include "libccc/text/char/unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_utf32	CharUTF32_ToLowercase(t_utf32 c)
{ return (towlower(c)); }
#else
t_utf32	CharUTF32_ToLowercase(t_utf32 c)
{
	if ('A' <= c && c <= 'Z')						return (c + 0x20);			// LATIN_CAPITAL					-> LATIN_SMALL

	if (c == 0xD7)									return (c);					// NOTE: exception: ×
	if (0xC0 <= c && c < 0xDF)						return (c + 0x20);			// LATIN_CAPITAL					-> LATIN_SMALL
	if (0xE0 <= c && c < 0xFF)						return (c);					// 									-> LATIN_SMALL

	if (0x0100 <= c && c < 0x0130 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (c == 0x0130)								return ('i');				// LATIN_CAPITAL_extA_I_wDOT		-> LATIN_SMALL_I
	if (c == 0x0131)								return (c);					// NOTE: exception: 		-> LATIN_SMALL_extA_DOTLESS_I
	if (0x0132 <= c && c < 0x0138 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (0x0139 <= c && c < 0x0149 && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (0x014A <= c && c < 0x0178 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (c == 0x0178)								return (0x00FF);			// LATIN_CAPITAL_extA_Y_DIAERESIS	-> LATIN_SMALL_extA_Y_wDIAERESIS
	if (0x0179 <= c && c < 0x017F && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA


	if (c == 0x0181)								return (0x0253);			// LATIN_CAPITAL_extI_B_wHOOK		-> LATIN_SMALL_extI_B_wHOOK
	if (0x0182 <= c && c < 0x0186 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (c == 0x0186)								return (0x0254);			// LATIN_CAPITAL_extI_OPEN_O		-> LATIN_SMALL_extI_OPEN_O
	if (c == 0x0187)								return (c + 1);				// LATIN_CAPITAL_extB_C_wHOOK		-> LATIN_SMALL_extB_C_wHOOK
	if (c == 0x0189)								return (0x0256);			// NOTE: exception: Ɖ -> ɖ
	if (c == 0x018A)								return (0x0257);			// LATIN_CAPITAL_extI_D_wHOOK		-> LATIN_SMALL_extI_D_wHOOK
	if (c == 0x018B)								return (c + 1);				// LATIN_CAPITAL_extB_D_wTOPBAR		-> LATIN_SMALL_extB_D_wTOPBAR
	if (c == 0x018E)								return (0x01DD);			// LATIN_CAPITAL_extI_REVERSED_E	-> LATIN_SMALL_extI_REVERSED_E // NOTE: exception: Ǝ -> ǝ
	if (c == 0x018F)								return (0x0259);			// LATIN_CAPITAL_extI_SCHWA			-> LATIN_SMALL_extI_SCHWA
	if (c == 0x0190)								return (0x025B);			// LATIN_CAPITAL_extI_OPEN_E		-> LATIN_SMALL_extI_OPEN_E
	if (c == 0x0191)								return (c + 1);				// LATIN_CAPITAL_extB_F_wHOOK		-> LATIN_SMALL_extB_F_wHOOK
	if (c == 0x0193)								return (0x0260);			// LATIN_CAPITAL_extI_G_wHOOK		-> LATIN_SMALL_extI_G_wHOOK
	if (c == 0x0194)								return (0x0263);			// LATIN_CAPITAL_extI_GAMMA			-> LATIN_SMALL_extI_GAMMA
	if (c == 0x0196)								return (0x0269);			// LATIN_CAPITAL_extI_IOTA			-> LATIN_SMALL_extI_IOTA
	if (c == 0x0197)								return (0x0268);			// LATIN_CAPITAL_extI_I_wSTROKE		-> LATIN_SMALL_extI_I_wSTROKE
	if (c == 0x0198)								return (c + 1);				// LATIN_CAPITAL_extB_K_wHOOK		-> LATIN_SMALL_extB_K_wHOOK
	if (c == 0x019C)								return (0x026F);			// LATIN_CAPITAL_extI_TURNED_M		-> LATIN_SMALL_extI_TURNED_M
	if (c == 0x019D)								return (0x0272);			// LATIN_CAPITAL_extI_N_wLEFT_HOOK	-> LATIN_SMALL_extI_N_wLEFT_HOOK
	if (c == 0x019F)								return (0x0275);			// LATIN_CAPITAL_extI_BARRED_O		-> LATIN_SMALL_extI_O_wMIDDLE_TILDE
	if (0x01A0 <= c && c < 0x01A6 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (c == 0x01A6)								return (0x0280);			// NOTE: exception: Ʀ -> ʀ
	if (c == 0x01A7)								return (c + 1);				// LATIN_CAPITAL_extB_TONE TWO		-> LATIN_SMALL_extB_TONE TWO
	if (c == 0x01A9)								return (0x0283);			// LATIN_CAPITAL_extI_ESH			-> LATIN_SMALL_extI_ESH
	if (c == 0x01AC)								return (c + 1);				// LATIN_CAPITAL_extB_T_wHOOK		-> LATIN_SMALL_extB_T_wHOOK
	if (c == 0x01AE)								return (0x0288);			// LATIN_CAPITAL_extI_T_wRETROFLEX	-> LATIN_SMALL_extI_T_wRETROFLEX
	if (c == 0x01AF)								return (c + 1);				// LATIN_CAPITAL_extB_U_wHORN		-> LATIN_SMALL_extB_U_wHORN
	if (c == 0x01B1)								return (0x028A);			// LATIN_CAPITAL_extI_UPSILON		-> LATIN_SMALL_extI_UPSILON
	if (c == 0x01B2)								return (0x028B);			// LATIN_CAPITAL_extI_V_wHOOK		-> LATIN_SMALL_extI_V_wHOOK
	if (c == 0x01B3)								return (c + 1);				// LATIN_CAPITAL_extB_Y_wHOOK		-> LATIN_SMALL_extB_Y_wHOOK
	if (c == 0x01B5)								return (c + 1);				// LATIN_CAPITAL_extB_Z_wSTROKE		-> LATIN_SMALL_extB_Z_wSTROKE
	if (c == 0x01B7)								return (0x0292);			// LATIN_CAPITAL_extI_EZH			-> LATIN_SMALL_extI_EZH
	if (c == 0x01B8)								return (c + 1);				// LATIN_CAPITAL_extB_EZH_REVERSED	-> LATIN_SMALL_extB_EZH_REVERSED
	if (c == 0x01BC)								return (c + 1);				// LATIN_CAPITAL_extB_TONE_FIVE		-> LATIN_SMALL_extB_TONE_FIVE
	if (c == 0x01C4)								return (c + 2);				// NOTE: exception: Ǆ -> ǆ
	if (c == 0x01C5)								return (c + 1);				// LATIN_CAPITAL_extB_DZ_wCARON		-> LATIN_SMALL_extB_DZ_wCARON
	if (c == 0x01C7)								return (c + 2);				// NOTE: exception: Ǉ -> ǉ
	if (c == 0x01C8)								return (c + 1);				// LATIN_CAPITAL_extB_LJ			-> LATIN_SMALL_extB_LJ
	if (c == 0x01CA)								return (c + 2);				// NOTE: exception: Ǌ -> ǌ
	if (c == 0x01CB)								return (c + 1);				// LATIN_CAPITAL_extB_NJ			-> LATIN_SMALL_extB_NJ
	if (0x01CD <= c && c < 0x01DD && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (0x01DE <= c && c < 0x01F0 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (c == 0x01F1)								return (0x01F3);			// LATIN_CAPITAL_extB_DZ			-> LATIN_SMALL_extB_DZ
	if (c == 0x01F2)								return (c + 1);				// 
	if (c == 0x01F4)								return (c + 1);				// 
	if (c == 0x01F6)								return (0x0195);			// LATIN_CAPITAL_extB_G_wACUTE		-> LATIN_SMALL_extB_G_wACUTE
	if (c == 0x01F7)								return (0x01BF);			// NOTE: exception: Ƿ -> ƿ
	if (0x01F8 <= c && c < 0x0220 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB

	if (c == 0x0220)								return (0x019E);			// NOTE: exception: Ƞ -> ƞ
	if (0x0222 <= c && c < 0x0234 && (c % 2 == 0))	return (c + 1);				// 
	if (c == 0x023A)								return (0x2C65);			// NOTE: exception: Ⱥ -> ⱥ
	if (c == 0x023B)								return (0x023C);			// NOTE: exception: Ȼ -> ȼ
	if (c == 0x023D)								return (0x019A);			// NOTE: exception: Ƚ -> ƚ
	if (c == 0x023E)								return (0x2C66);			// NOTE: exception: Ⱦ -> ⱦ
	if (c == 0x0241)								return (0x0242);			// NOTE: exception: Ɂ -> ɂ
	if (c == 0x0243)								return (0x0180);			// NOTE: exception: Ƀ -> ƀ
	if (c == 0x0244)								return (0x0289);			// NOTE: exception: Ʉ -> ʉ
	if (c == 0x0245)								return (0x028C);			// NOTE: exception: Ʌ -> ʌ
	if (0x0246 <= c && c < 0x0250 && (c % 2 == 0))	return (c + 1);				// 
	if (c == 0x0370)								return (0x0371);			// NOTE: exception: Ͱ -> ͱ
	if (c == 0x0372)								return (0x0373);			// NOTE: exception: Ͳ -> ͳ
	if (c == 0x0376)								return (0x0377);			// NOTE: exception: Ͷ -> ͷ
	if (c == 0x037F)								return (0x03F3);			// NOTE: exception: Ϳ -> ϳ

	if (c == 0x0386)								return (0x03AC);			// GREEK_CAPITAL_ALPHA_wTONOS		-> GREEK_SMALL_ALPHA_wTONOS
	if (c == 0x0388)								return (0x03AD);			// GREEK_CAPITAL_EPSILON_wTONOS		-> GREEK_SMALL_EPSILON_wTONOS
	if (c == 0x0389)								return (0x03AE);			// GREEK_CAPITAL_ETA_wTONOS			-> GREEK_SMALL_ETA_wTONOS
	if (c == 0x038A)								return (0x03AF);			// GREEK_CAPITAL_IOTA_wTONOS		-> GREEK_SMALL_IOTA_wTONOS
	if (c == 0x03C2)								return (c);					// GREEK_CAPITAL_FINAL_SIGMA
	if (c == 0x038C)								return (0x03CC);			// GREEK_CAPITAL_OMICRON_wTONOS		-> GREEK_SMALL_OMICRON_wTONOS
	if (c == 0x038E)								return (0x03CD);			// GREEK_CAPITAL_UPSILON_wTONOS		-> GREEK_SMALL_UPSILON_wTONOS
	if (c == 0x038F)								return (0x03CE);			// GREEK_CAPITAL_OMEGA_wTONOS		-> GREEK_SMALL_OMEGA_wTONOS
	if (c == 0x03A2)								return (c);					// NOTE: exception: ΢ -> ΢
	if (0x0391 <= c && c < 0x03AC)					return (c + 0x20);			// GREEK_CAPITAL					-> GREEK_SMALL
	if (0x03B1 <= c && c < 0x03CC)					return (c);					// 									-> GREEK_SMALL
	if (c == 0x03CF)								return (0x03D7);			// NOTE: exception: Ϗ -> ϗ
	if (c == 0x03D8)								return (0x03D9);			// NOTE: exception: Ϙ -> ϙ
	if (c == 0x03DA)								return (0x03DB);			// NOTE: exception: Ϛ -> ϛ
	if (c == 0x03DC)								return (0x03DD);			// NOTE: exception: Ϝ -> ϝ
	if (c == 0x03DE)								return (0x03DF);			// NOTE: exception: Ϟ -> ϟ
	if (c == 0x03E0)								return (0x03E1);			// NOTE: exception: Ϡ -> ϡ

	if (0x03E2 <= c && c < 0x03F0 && (c % 2 == 0))	return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x03F4)								return (0x03B8);			// NOTE: exception: ϴ -> θ
	if (c == 0x03F7)								return (0x03F8);			// NOTE: exception: Ϸ -> ϸ
	if (c == 0x03F9)								return (0x03F2);			// NOTE: exception: Ϲ -> ϲ
	if (c == 0x03FA)								return (0x03FB);			// NOTE: exception: Ϻ -> ϻ
	if (c == 0x03FD)								return (0x037B);			// NOTE: exception: Ͻ -> ͻ
	if (c == 0x03FE)								return (0x037C);			// NOTE: exception: Ͼ -> ͼ
	if (c == 0x03FF)								return (0x037D);			// NOTE: exception: Ͽ -> ͽ

	if (0x0400 <= c && c < 0x0410)					return (c + 0x50);			// CYRILLIC_CAPITAL					-> CYRILLIC_SMALL
	if (0x0410 <= c && c < 0x0430)					return (c + 0x20);			// CYRILLIC_CAPITAL					-> CYRILLIC_SMALL
	if (0x0430 <= c && c < 0x0450)					return (c);					// 									-> CYRILLIC_SMALL
	if (0x0450 <= c && c < 0x0460)					return (c);					// 									-> CYRILLIC_SMALL
	if (0x0460 <= c && c < 0x0482 && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL					-> CYRILLIC_SMALL
	if (0x048A <= c && c < 0x04C0 && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL					-> CYRILLIC_SMALL
	if (0x04C1 <= c && c < 0x04CF && (c % 2 == 1))	return (c + 1);				// CYRILLIC_CAPITAL					-> CYRILLIC_SMALL
	if (c == 0x04C0)								return (0x04CF);			// CYRILLIC_CAPITAL_PALOCHKA		-> CYRILLIC_SMALL_PALOCHKA
	if (0x04D0 <= c && c < 0x0530 && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL					-> CYRILLIC_SMALL

	if (0x0531 <= c && c < 0x0557)					return (c + 0x30);			// ARMENIAN_CAPITAL					-> ARMENIAN_SMALL
	if (0x0561 <= c && c < 0x0587)					return (c);					// 									-> ARMENIAN_SMALL

	if (c == 0x10C6)								return (c);					// NOTE: exception
	if (c == 0x10C8)								return (c);					// NOTE: exception
	if (c == 0x10C9)								return (c);					// NOTE: exception
	if (c == 0x10CA)								return (c);					// NOTE: exception
	if (c == 0x10CB)								return (c);					// NOTE: exception
	if (c == 0x10CC)								return (c);					// NOTE: exception
	if (c == 0x10CE)								return (c);					// NOTE: exception
	if (c == 0x10CF)								return (c);					// NOTE: exception
	if (0x10A0 <= c && c < 0x10D0)					return (c + 0x1C60);		// GEORGIAN_CAPITAL					-> GEORGIAN_SMALL
	if (0x10D0 <= c && c < 0x1100)					return (c);					// 									-> GEORGIAN_SMALL

	if (0x13A0 <= c && c < 0x13F0)					return (c + 0x97D0);		// 
	if (0x13F0 <= c && c < 0x13F6)					return (c + 8);				// 

	if (c == 0x1CBB)								return (c);					// NOTE: exception
	if (c == 0x1CBC)								return (c);					// NOTE: exception
	if (0x1C90 <= c && c < 0x1CC0)					return (c - 0xBC0);			// 

	if (0x1E00 <= c && c < 0x1E96 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x1E9E)								return (0xDF);				// NOTE: exception: ẞ -> ß
	if (0x1EA0 <= c && c < 0x1F00 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL

	if (c == 0x1F1E)								return (c);					// NOTE: exception: ἞
	if (c == 0x1F1F)								return (c);					// NOTE: exception: ἟
	if (c == 0x1F4E)								return (c);					// NOTE: exception: ὎
	if (c == 0x1F4F)								return (c);					// NOTE: exception: ὏
	if (c == 0x1F58)								return (c);					// NOTE: exception: ὘
	if (c == 0x1F5A)								return (c);					// NOTE: exception: ὚
	if (c == 0x1F5C)								return (c);					// NOTE: exception: ὜
	if (c == 0x1F5E)								return (c);					// NOTE: exception: ὞
	if (c == 0x1F78)								return (c);					// NOTE: exception: ὸ
	if (c == 0x1F79)								return (c);					// NOTE: exception: ό
	if (c == 0x1F7A)								return (c);					// NOTE: exception: ὺ
	if (c == 0x1F7B)								return (c);					// NOTE: exception: ύ
	if (c == 0x1F7C)								return (c);					// NOTE: exception: ὼ
	if (c == 0x1F7D)								return (c);					// NOTE: exception: ώ
	if (c == 0x1F7E)								return (c);					// NOTE: exception: ὾
	if (c == 0x1F7F)								return (c);					// NOTE: exception: ὿
	if (c == 0x1FBA)								return (0x1F70);			// NOTE: exception: Ὰ -> ὰ
	if (c == 0x1FBB)								return (0x1F71);			// NOTE: exception: Ά -> ά
	if (c == 0x1FBC)								return (0x1FB3);			// NOTE: exception: ᾼ -> ᾳ
	if (c == 0x1FBD)								return (c);					// NOTE: exception: ᾽
	if (c == 0x1FBE)								return (c);					// NOTE: exception: ι
	if (c == 0x1FBF)								return (c);					// NOTE: exception: ᾿
	if (c == 0x1FC8)								return (0x1F72);			// NOTE: exception: Ὲ -> ὲ
	if (c == 0x1FC9)								return (0x1F73);			// NOTE: exception: Έ -> έ
	if (c == 0x1FCA)								return (0x1F74);			// NOTE: exception: Ὴ -> ὴ
	if (c == 0x1FCB)								return (0x1F75);			// NOTE: exception: Ή -> ή
	if (c == 0x1FCC)								return (0x1FC3);			// NOTE: exception: ῌ -> ῃ
	if (c == 0x1FCD)								return (c);					// NOTE: exception: ῍
	if (c == 0x1FCE)								return (c);					// NOTE: exception: ῎
	if (c == 0x1FCF)								return (c);					// NOTE: exception: ῏
	if (c == 0x1FDA)								return (0x1F76);			// NOTE: exception: Ὶ -> ὶ
	if (c == 0x1FDB)								return (0x1F77);			// NOTE: exception: Ί -> ί
	if (c == 0x1FDC)								return (c);					// NOTE: exception: ῜
	if (c == 0x1FDD)								return (c);					// NOTE: exception: ῝
	if (c == 0x1FDE)								return (c);					// NOTE: exception: ῞
	if (c == 0x1FDF)								return (c);					// NOTE: exception: ῟
	if (c == 0x1FEA)								return (0x1F7A);			// NOTE: exception: Ὺ -> ὺ
	if (c == 0x1FEB)								return (0x1F7B);			// NOTE: exception: Ύ -> ύ
	if (c == 0x1FEC)								return (0x1FE5);			// NOTE: exception: Ῥ -> ῥ
	if (c == 0x1FED)								return (c);					// NOTE: exception: ῭
	if (c == 0x1FEE)								return (c);					// NOTE: exception: ΅
	if (c == 0x1FEF)								return (c);					// NOTE: exception: `
	if (c == 0x1FF8)								return (0x1F78);			// NOTE: exception: Ὸ -> ὸ
	if (c == 0x1FF9)								return (0x1F79);			// NOTE: exception: Ό -> ό
	if (c == 0x1FFA)								return (0x1F7C);			// NOTE: exception: Ὼ -> ὼ
	if (c == 0x1FFB)								return (0x1F7D);			// NOTE: exception: Ώ -> ώ
	if (c == 0x1FFC)								return (0x1FF3);			// NOTE: exception: ῼ -> ῳ
	if (c == 0x1FFD)								return (c);					// NOTE: exception: ´
	if (c == 0x1FFE)								return (c);					// NOTE: exception: ῾
	if (c == 0x1FFF)								return (c);					// NOTE: exception: ῿
	if (0x1F00 <= c && c < 0x2000 && (c % 16 >= 8))	return (c - 8);				// GREEK_CAPITAL					-> GREEK_SMALL

	if (c == 0x2126)								return (0x03C9);			// NOTE: exception: Ω -> ω
	if (c == 0x212A)								return (0x006B);			// NOTE: exception: K -> k
	if (c == 0x212B)								return (0x00E5);			// NOTE: exception: Å -> å
	if (c == 0x2132)								return (0x214E);			// NOTE: exception: Ⅎ -> ⅎ

	if (0x2160 <= c && c < 0x2170)					return (c + 0x10);			// ROMAN_NUMERAL_CAPITAL			-> ROMAN_NUMERAL_SMALL
	if (0x2170 <= c && c < 0x2180)					return (c);					// 									-> ROMAN_NUMERAL_SMALL
	if (c == 0x2183)								return (c + 1);				// NOTE: exception: Ↄ -> ↄ

	if (0x24B6 <= c && c < 0x24D0)					return (c + 0x1A);			// LATIN_CIRCLED_CAPITAL			-> LATIN_CIRCLED_SMALL
	if (0x24D0 <= c && c < 0x24EA)					return (c);					// 									-> LATIN_CIRCLED_SMALL

	if (0x2C00 <= c && c < 0x2C30)					return (c + 0x30);			// GLAGOLITIC_CAPITAL				-> GLAGOLITIC_SMALL
	if (0x2C30 <= c && c < 0x2C60)					return (c);					// 									-> GLAGOLITIC_SMALL

	if (c == 0x2C60)								return (c + 1);				// LATIN_CAPITAL_L_wDOUBLEBAR		-> LATIN_SMALL_L_wDOUBLEBAR
	if (c == 0x2C62)								return (0x026B);			// NOTE: exception: Ɫ -> ɫ
	if (c == 0x2C63)								return (0x1D7D);			// NOTE: exception: Ᵽ -> ᵽ
	if (c == 0x2C64)								return (0x027D);			// NOTE: exception: Ɽ -> ɽ
	if (c == 0x2C67)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C69)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C6B)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C6D)								return (0x0251);			// NOTE: exception: Ɑ -> ɑ
	if (c == 0x2C6E)								return (0x0271);			// NOTE: exception: Ɱ -> ɱ
	if (c == 0x2C6F)								return (0x0250);			// NOTE: exception: Ɐ -> ɐ
	if (c == 0x2C70)								return (0x0252);			// NOTE: exception: Ɒ -> ɒ
	if (c == 0x2C72)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C75)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C7E)								return (0x023F);			// NOTE: exception: Ȿ -> ȿ
	if (c == 0x2C7F)								return (0x0240);			// NOTE: exception: Ɀ -> ɀ

	if (0x2C80 <= c && c < 0x2CE4 && (c % 2 == 0))	return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x2CEB)								return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x2CED)								return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x2CF2)								return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL

	if (0xA640 <= c && c < 0xA66E && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL_extB			-> CYRILLIC_SMALL_extB
	if (0xA680 <= c && c < 0xA69C && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL_extB			-> CYRILLIC_SMALL_extB

	if (c == 0xA722)								return (c + 1);				// NOTE: exception: Ꜣ -> ꜣ
	if (c == 0xA724)								return (c + 1);				// NOTE: exception: Ꜥ -> ꜥ
	if (c == 0xA726)								return (c + 1);				// NOTE: exception: Ꜧ -> ꜧ
	if (c == 0xA728)								return (c + 1);				// NOTE: exception: Ꜩ -> ꜩ
	if (c == 0xA72A)								return (c + 1);				// NOTE: exception: Ꜫ -> ꜫ
	if (c == 0xA72C)								return (c + 1);				// NOTE: exception: Ꜭ -> ꜭ
	if (c == 0xA72E)								return (c + 1);				// NOTE: exception: Ꜯ -> ꜯ
	if (c == 0xA732)								return (c + 1);				// NOTE: exception: Ꜳ -> ꜳ
	if (c == 0xA734)								return (c + 1);				// NOTE: exception: Ꜵ -> ꜵ
	if (c == 0xA736)								return (c + 1);				// NOTE: exception: Ꜷ -> ꜷ
	if (c == 0xA738)								return (c + 1);				// NOTE: exception: Ꜹ -> ꜹ
	if (c == 0xA73A)								return (c + 1);				// NOTE: exception: Ꜻ -> ꜻ
	if (c == 0xA73C)								return (c + 1);				// NOTE: exception: Ꜽ -> ꜽ
	if (c == 0xA73E)								return (c + 1);				// NOTE: exception: Ꜿ -> ꜿ
	if (c == 0xA740)								return (c + 1);				// NOTE: exception: Ꝁ -> ꝁ
	if (c == 0xA742)								return (c + 1);				// NOTE: exception: Ꝃ -> ꝃ
	if (c == 0xA744)								return (c + 1);				// NOTE: exception: Ꝅ -> ꝅ
	if (c == 0xA746)								return (c + 1);				// NOTE: exception: Ꝇ -> ꝇ
	if (c == 0xA748)								return (c + 1);				// NOTE: exception: Ꝉ -> ꝉ
	if (c == 0xA74A)								return (c + 1);				// NOTE: exception: Ꝋ -> ꝋ
	if (c == 0xA74C)								return (c + 1);				// NOTE: exception: Ꝍ -> ꝍ
	if (c == 0xA74E)								return (c + 1);				// NOTE: exception: Ꝏ -> ꝏ
	if (c == 0xA750)								return (c + 1);				// NOTE: exception: Ꝑ -> ꝑ
	if (c == 0xA752)								return (c + 1);				// NOTE: exception: Ꝓ -> ꝓ
	if (c == 0xA754)								return (c + 1);				// NOTE: exception: Ꝕ -> ꝕ
	if (c == 0xA756)								return (c + 1);				// NOTE: exception: Ꝗ -> ꝗ
	if (c == 0xA758)								return (c + 1);				// NOTE: exception: Ꝙ -> ꝙ
	if (c == 0xA75A)								return (c + 1);				// NOTE: exception: Ꝛ -> ꝛ
	if (c == 0xA75C)								return (c + 1);				// NOTE: exception: Ꝝ -> ꝝ
	if (c == 0xA75E)								return (c + 1);				// NOTE: exception: Ꝟ -> ꝟ
	if (c == 0xA760)								return (c + 1);				// NOTE: exception: Ꝡ -> ꝡ
	if (c == 0xA762)								return (c + 1);				// NOTE: exception: Ꝣ -> ꝣ
	if (c == 0xA764)								return (c + 1);				// NOTE: exception: Ꝥ -> ꝥ
	if (c == 0xA766)								return (c + 1);				// NOTE: exception: Ꝧ -> ꝧ
	if (c == 0xA768)								return (c + 1);				// NOTE: exception: Ꝩ -> ꝩ
	if (c == 0xA76A)								return (c + 1);				// NOTE: exception: Ꝫ -> ꝫ
	if (c == 0xA76C)								return (c + 1);				// NOTE: exception: Ꝭ -> ꝭ
	if (c == 0xA76E)								return (c + 1);				// NOTE: exception: Ꝯ -> ꝯ
	if (c == 0xA779)								return (c + 1);				// NOTE: exception: Ꝺ -> ꝺ
	if (c == 0xA77B)								return (c + 1);				// NOTE: exception: Ꝼ -> ꝼ
	if (c == 0xA77D)								return (0x1D79);			// NOTE: exception: Ᵹ -> ᵹ
	if (c == 0xA77E)								return (c + 1);				// NOTE: exception: Ꝿ -> ꝿ
	if (c == 0xA780)								return (c + 1);				// NOTE: exception: Ꞁ -> ꞁ
	if (c == 0xA782)								return (c + 1);				// NOTE: exception: Ꞃ -> ꞃ
	if (c == 0xA784)								return (c + 1);				// NOTE: exception: Ꞅ -> ꞅ
	if (c == 0xA786)								return (c + 1);				// NOTE: exception: Ꞇ -> ꞇ
	if (c == 0xA78B)								return (c + 1);				// NOTE: exception: Ꞌ -> ꞌ
	if (c == 0xA78D)								return (0x0265);			// NOTE: exception: Ɥ -> ɥ
	if (c == 0xA790)								return (c + 1);				// NOTE: exception: Ꞑ -> ꞑ
	if (c == 0xA792)								return (c + 1);				// NOTE: exception: Ꞓ -> ꞓ
	if (c == 0xA796)								return (c + 1);				// NOTE: exception: Ꞗ -> ꞗ
	if (c == 0xA798)								return (c + 1);				// NOTE: exception: Ꞙ -> ꞙ
	if (c == 0xA79A)								return (c + 1);				// NOTE: exception: Ꞛ -> ꞛ
	if (c == 0xA79C)								return (c + 1);				// NOTE: exception: Ꞝ -> ꞝ
	if (c == 0xA79E)								return (c + 1);				// NOTE: exception: Ꞟ -> ꞟ
	if (c == 0xA7A0)								return (c + 1);				// NOTE: exception: Ꞡ -> ꞡ
	if (c == 0xA7A2)								return (c + 1);				// NOTE: exception: Ꞣ -> ꞣ
	if (c == 0xA7A4)								return (c + 1);				// NOTE: exception: Ꞥ -> ꞥ
	if (c == 0xA7A6)								return (c + 1);				// NOTE: exception: Ꞧ -> ꞧ
	if (c == 0xA7A8)								return (c + 1);				// NOTE: exception: Ꞩ -> ꞩ
	if (c == 0xA7AA)								return (0x0266);			// NOTE: exception: Ɦ -> ɦ
	if (c == 0xA7AB)								return (0x025C);			// NOTE: exception: Ɜ -> ɜ
	if (c == 0xA7AC)								return (0x0261);			// NOTE: exception: Ɡ -> ɡ
	if (c == 0xA7AD)								return (0x026C);			// NOTE: exception: Ɬ -> ɬ
	if (c == 0xA7AE)								return (0x026A);			// NOTE: exception: Ɪ -> ɪ
	if (c == 0xA7B0)								return (0x029E);			// NOTE: exception: Ʞ -> ʞ
	if (c == 0xA7B1)								return (0x0287);			// NOTE: exception: Ʇ -> ʇ
	if (c == 0xA7B2)								return (0x029D);			// NOTE: exception: Ʝ -> ʝ
	if (c == 0xA7B3)								return (0xAB53);			// NOTE: exception: Ꭓ -> ꭓ
	if (c == 0xA7B4)								return (c + 1);				// NOTE: exception: Ꞵ -> ꞵ
	if (c == 0xA7B6)								return (c + 1);				// NOTE: exception: Ꞷ -> ꞷ
	if (c == 0xA7B8)								return (c + 1);				// NOTE: exception: Ꞹ -> ꞹ
	if (c == 0xA7BA)								return (c + 1);				// NOTE: exception: Ꞻ -> ꞻ
	if (c == 0xA7BC)								return (c + 1);				// NOTE: exception: Ꞽ -> ꞽ
	if (c == 0xA7BE)								return (c + 1);				// NOTE: exception: Ꞿ -> ꞿ
	if (c == 0xA7C0)								return (c + 1);				// NOTE: exception: Ꟁ -> ꟁ
	if (c == 0xA7C2)								return (c + 1);				// NOTE: exception: Ꟃ -> ꟃ
	if (c == 0xA7C4)								return (0xA794);			// NOTE: exception: Ꞔ -> ꞔ
	if (c == 0xA7C5)								return (0x0282);			// NOTE: exception: Ʂ -> ʂ
	if (c == 0xA7C6)								return (0x1D8E);			// NOTE: exception: Ᶎ -> ᶎ
	if (c == 0xA7C7)								return (c + 1);				// NOTE: exception: Ꟈ -> ꟈ
	if (c == 0xA7C9)								return (c + 1);				// NOTE: exception: Ꟊ -> ꟊ
	if (c == 0xA7D0)								return (c + 1);				// NOTE: exception: Ꟑ -> ꟑ
	if (c == 0xA7D6)								return (c + 1);				// NOTE: exception: Ꟗ -> ꟗ
	if (c == 0xA7D8)								return (c + 1);				// NOTE: exception: Ꟙ -> ꟙ
	if (c == 0xA7F5)								return (c + 1);				// NOTE: exception: Ꟶ -> ꟶ

	// TODO inspect this region to see if there's anything not yet handled

	if (0xFF21 <= c && c < 0xFF3B)					return (c + 0x20);			// LATIN_CAPITAL_FULLWIDTH			-> LATIN_SMALL_FULLWIDTH
	if (0xFF41 <= c && c < 0xFF5B)					return (c);					// 									-> LATIN_SMALL_FULLWIDTH

	if (0x10400 <= c && c < 0x10428)				return (c + 0x28);			// DESERET_CAPITAL					-> DESERET_SMALL
	if (0x10428 <= c && c < 0x10450)				return (c);					// 									-> DESERET_SMALL

	if (0x104B0 <= c && c < 0x104D4)				return (c + 0x28);			// OSAGE_CAPITAL					-> OSAGE_SMALL
	if (0x104D8 <= c && c < 0x10500)				return (c);					// 									-> OSAGE_SMALL
	if (c == 0x1057B)								return (c);					// NOTE: exception: 𐕻
	if (c == 0x1058B)								return (c);					// NOTE: exception: 𐖋
	if (c == 0x10593)								return (c);					// NOTE: exception: 𐖓
	if (c == 0x10595)								return (0x105BC);			// NOTE: exception: 𐖼
	if (0x10570 <= c && c < 0x10595)				return (c + 0x27);			// 

	if (0x10C80 <= c && c < 0x10CB3)				return (c + 0x40);			// 

	if (0x118A0 <= c && c < 0x118C0)				return (c + 0x20);			// 

	if (0x16E40 <= c && c < 0x16E60)				return (c + 0x20);			// 

	// latin
	if (0x1D400 <= c && c < 0x1D41A)				return (c + 0x1A);			// MATH_CAPITAL_LATIN_BOLD			-> MATH_SMALL_LATIN_BOLD
	if (0x1D434 <= c && c < 0x1D44E)				return (c + 0x1A);			// MATH_CAPITAL_LATIN_ITALIC		-> MATH_SMALL_LATIN_ITALIC
	if (0x1D468 <= c && c < 0x1D482)				return (c + 0x1A);			// MATH_CAPITAL_LATIN_BOLDITAL		-> MATH_SMALL_LATIN_BOLDITAL
	if (0x1D49C <= c && c < 0x1D4B6)				return (c + 0x1A);			// MATH_CAPITAL_SCRIPT				-> MATH_SMALL_SCRIPT
	if (0x1D4D0 <= c && c < 0x1D4EA)				return (c + 0x1A);			// MATH_CAPITAL_SCRIPT_BOLD			-> MATH_SMALL_SCRIPT_BOLD
	if (0x1D504 <= c && c < 0x1D51E)				return (c + 0x1A);			// MATH_CAPITAL_FRAKTUR				-> MATH_SMALL_FRAKTUR
	if (0x1D538 <= c && c < 0x1D552)				return (c + 0x1A);			// MATH_CAPITAL_DOUBLESTRUCK		-> MATH_SMALL_DOUBLESTRUCK
	if (0x1D56C <= c && c < 0x1D586)				return (c + 0x1A);			// MATH_CAPITAL_FRAKTUR_BOLD		-> MATH_SMALL_FRAKTUR_BOLD
	if (0x1D5A0 <= c && c < 0x1D5BA)				return (c + 0x1A);			// MATH_CAPITAL_LATINSANS			-> MATH_SMALL_LATINSANS
	if (0x1D5D4 <= c && c < 0x1D5EE)				return (c + 0x1A);			// MATH_CAPITAL_LATINSANS_BOLD		-> MATH_SMALL_LATINSANS_BOLD
	if (0x1D608 <= c && c < 0x1D622)				return (c + 0x1A);			// MATH_CAPITAL_LATINSANS_ITALIC	-> MATH_SMALL_LATINSANS_ITALIC
	if (0x1D63C <= c && c < 0x1D656)				return (c + 0x1A);			// MATH_CAPITAL_LATINSANS_BOLDITAL	-> MATH_SMALL_LATINSANS_BOLDITAL
	if (0x1D670 <= c && c < 0x1D68A)				return (c + 0x1A);			// MATH_CAPITAL_MONOSPACE			-> MATH_SMALL_MONOSPACE
	// greek
	if (0x1D6A8 <= c && c < 0x1D6C1)				return (c + 0x1A);			// MATH_CAPITAL_GREEK_BOLD			-> MATH_SMALL_GREEK_BOLD
	if (0x1D6E2 <= c && c < 0x1D6FB)				return (c + 0x1A);			// MATH_CAPITAL_GREEK_ITALIC		-> MATH_SMALL_GREEK_ITALIC
	if (0x1D71C <= c && c < 0x1D735)				return (c + 0x1A);			// MATH_CAPITAL_GREEK_BOLDITAL		-> MATH_SMALL_GREEK_BOLDITAL
	if (0x1D756 <= c && c < 0x1D76F)				return (c + 0x1A);			// MATH_CAPITAL_GREEKSANS_BOLD		-> MATH_SMALL_GREEKSANS_BOLD
	if (0x1D790 <= c && c < 0x1D7A9)				return (c + 0x1A);			// MATH_CAPITAL_GREEKSANS_BOLDITAL	-> MATH_SMALL_GREEKSANS_BOLDITAL

	if (0x1E900 <= c && c < 0x1E922)				return (c + 0x22);			// 

	// TODO inspect this region to see if there's anything not yet handled

	return (c);
}
#endif
