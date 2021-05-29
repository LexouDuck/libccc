
#include "libccc/sys/unicode.h"

#include LIBCONFIG_HANDLE_INCLUDE



t_utf32	UTF32_ToLowercase(t_utf32 c)
{
	if ('A' <= c && c <= 'Z')						return (c + 0x20);			// LATIN_CAPITAL					-> LATIN_SMALL
	if (0xC0 <= c && c < 0xDF)						return (c + 0x20);			// LATIN_CAPITAL					-> LATIN_SMALL
	if (0xE0 <= c && c < 0xFF)						return (c);					// 									-> LATIN_SMALL
	if (c == 0x0178)								return (0x00FF);			// LATIN_CAPITAL_extA_Y_DIAERESIS	-> LATIN_SMALL_extA_Y_wDIAERESIS
	if (0x0100 <= c && c < 0x0130 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (c == 0x0130)								return ('i');				// LATIN_CAPITAL_extA_I_wDOT		-> LATIN_SMALL_I
	if (c == 0x0131)								return (c);					// 									-> LATIN_SMALL_extA_DOTLESS_I
	if (0x0132 <= c && c < 0x0138 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (0x0139 <= c && c < 0x0149 && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (0x014A <= c && c < 0x0178 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA
	if (0x0179 <= c && c < 0x017F && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extA				-> LATIN_SMALL_extA

	if (0x0182 <= c && c < 0x0186 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (c == 0x0187)								return (c + 1);				// LATIN_CAPITAL_extB_C_wHOOK		-> LATIN_SMALL_extB_C_wHOOK
	if (c == 0x018B)								return (c + 1);				// LATIN_CAPITAL_extB_D_wTOPBAR		-> LATIN_SMALL_extB_D_wTOPBAR
	if (c == 0x0191)								return (c + 1);				// LATIN_CAPITAL_extB_F_wHOOK		-> LATIN_SMALL_extB_F_wHOOK
	if (c == 0x0198)								return (c + 1);				// LATIN_CAPITAL_extB_K_wHOOK		-> LATIN_SMALL_extB_K_wHOOK
	if (0x01A0 <= c && c < 0x01A6 && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (c == 0x01A7)								return (c + 1);				// LATIN_CAPITAL_extB_TONE TWO		-> LATIN_SMALL_extB_TONE TWO
	if (c == 0x01AC)								return (c + 1);				// LATIN_CAPITAL_extB_T_wHOOK		-> LATIN_SMALL_extB_T_wHOOK
	if (c == 0x01AF)								return (c + 1);				// LATIN_CAPITAL_extB_U_wHORN		-> LATIN_SMALL_extB_U_wHORN
	if (c == 0x01B3)								return (c + 1);				// LATIN_CAPITAL_extB_Y_wHOOK		-> LATIN_SMALL_extB_Y_wHOOK
	if (c == 0x01B5)								return (c + 1);				// LATIN_CAPITAL_extB_Z_wSTROKE		-> LATIN_SMALL_extB_Z_wSTROKE
	if (c == 0x01B8)								return (c + 1);				// LATIN_CAPITAL_extB_EZH_REVERSED	-> LATIN_SMALL_extB_EZH_REVERSED
	if (c == 0x01BC)								return (c + 1);				// LATIN_CAPITAL_extB_TONE_FIVE		-> LATIN_SMALL_extB_TONE_FIVE
	if (c == 0x01C5)								return (c + 1);				// LATIN_CAPITAL_extB_DZ_wCARON		-> LATIN_SMALL_extB_DZ_wCARON
	if (c == 0x01C8)								return (c + 1);				// LATIN_CAPITAL_extB_LJ			-> LATIN_SMALL_extB_LJ
	if (c == 0x01CB)								return (c + 1);				// LATIN_CAPITAL_extB_NJ			-> LATIN_SMALL_extB_NJ
	if (0x01CD <= c && c < 0x01DD && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (0x01DE <= c && c < 0x01F0 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB
	if (c == 0x01F1)								return (0x01F3);			// LATIN_CAPITAL_extB_DZ			-> LATIN_SMALL_extB_DZ
	if (c == 0x01F4)								return (c + 1);				// LATIN_CAPITAL_extB_G_wACUTE		-> LATIN_SMALL_extB_G_wACUTE
	if (0x01F8 <= c && c < 0x0220 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extB				-> LATIN_SMALL_extB

	if (c == 0x0181)								return (0x0253);			// LATIN_CAPITAL_extI_B_wHOOK		-> LATIN_SMALL_extI_B_wHOOK
	if (c == 0x0186)								return (0x0254);			// LATIN_CAPITAL_extI_OPEN_O		-> LATIN_SMALL_extI_OPEN_O
	if (c == 0x018A)								return (0x0257);			// LATIN_CAPITAL_extI_D_wHOOK		-> LATIN_SMALL_extI_D_wHOOK
	if (c == 0x018E)								return (0x0258);			// LATIN_CAPITAL_extI_REVERSED_E	-> LATIN_SMALL_extI_REVERSED_E
	if (c == 0x018F)								return (0x0259);			// LATIN_CAPITAL_extI_SCHWA			-> LATIN_SMALL_extI_SCHWA
	if (c == 0x0190)								return (0x025B);			// LATIN_CAPITAL_extI_OPEN_E		-> LATIN_SMALL_extI_OPEN_E
	if (c == 0x0193)								return (0x0260);			// LATIN_CAPITAL_extI_G_wHOOK		-> LATIN_SMALL_extI_G_wHOOK
	if (c == 0x0194)								return (0x0263);			// LATIN_CAPITAL_extI_GAMMA			-> LATIN_SMALL_extI_GAMMA
	if (c == 0x0197)								return (0x0268);			// LATIN_CAPITAL_extI_I_wSTROKE		-> LATIN_SMALL_extI_I_wSTROKE
	if (c == 0x0196)								return (0x0269);			// LATIN_CAPITAL_extI_IOTA			-> LATIN_SMALL_extI_IOTA
	if (c == 0x019C)								return (0x026F);			// LATIN_CAPITAL_extI_TURNED_M		-> LATIN_SMALL_extI_TURNED_M
	if (c == 0x019D)								return (0x0272);			// LATIN_CAPITAL_extI_N_wLEFT_HOOK	-> LATIN_SMALL_extI_N_wLEFT_HOOK
	if (c == 0x019F)								return (0x0275);			// LATIN_CAPITAL_extI_BARRED_O		-> LATIN_SMALL_extI_O_wMIDDLE_TILDE
	if (c == 0x01A9)								return (0x0283);			// LATIN_CAPITAL_extI_ESH			-> LATIN_SMALL_extI_ESH
	if (c == 0x01AE)								return (0x0288);			// LATIN_CAPITAL_extI_T_wRETROFLEX	-> LATIN_SMALL_extI_T_wRETROFLEX
	if (c == 0x01B1)								return (0x028A);			// LATIN_CAPITAL_extI_UPSILON		-> LATIN_SMALL_extI_UPSILON
	if (c == 0x01B2)								return (0x028B);			// LATIN_CAPITAL_extI_V_wHOOK		-> LATIN_SMALL_extI_V_wHOOK
	if (c == 0x01B7)								return (0x0292);			// LATIN_CAPITAL_extI_EZH			-> LATIN_SMALL_extI_EZH

	if (c == 0x0386)								return (0x03AC);			// GREEK_CAPITAL_ALPHA_wTONOS		-> GREEK_SMALL_ALPHA_wTONOS
	if (c == 0x0388)								return (0x03AD);			// GREEK_CAPITAL_EPSILON_wTONOS		-> GREEK_SMALL_EPSILON_wTONOS
	if (c == 0x0389)								return (0x03AE);			// GREEK_CAPITAL_ETA_wTONOS			-> GREEK_SMALL_ETA_wTONOS
	if (c == 0x038A)								return (0x03AF);			// GREEK_CAPITAL_IOTA_wTONOS		-> GREEK_SMALL_IOTA_wTONOS
	if (c == 0x03C2)								return (c);					// GREEK_CAPITAL_FINAL_SIGMA
	if (c == 0x038C)								return (0x03CC);			// GREEK_CAPITAL_OMICRON_wTONOS		-> GREEK_SMALL_OMICRON_wTONOS
	if (c == 0x038E)								return (0x03CD);			// GREEK_CAPITAL_UPSILON_wTONOS		-> GREEK_SMALL_UPSILON_wTONOS
	if (c == 0x038F)								return (0x03CE);			// GREEK_CAPITAL_OMEGA_wTONOS		-> GREEK_SMALL_OMEGA_wTONOS
	if (0x0391 <= c && c < 0x03AC)					return (c + 0x20);			// GREEK_CAPITAL					-> GREEK_SMALL
	if (0x03B1 <= c && c < 0x03CC)					return (c);					// 									-> GREEK_SMALL

	if (0x03E2 <= c && c < 0x03F0 && (c % 2 == 0))	return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL

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

	if (0x10A0 <= c && c < 0x10D0)					return (c + 0x30);			// GEORGIAN_CAPITAL					-> GEORGIAN_SMALL
	if (0x10D0 <= c && c < 0x1100)					return (c);					// 									-> GEORGIAN_SMALL

	if (0x1E00 <= c && c < 0x1E96 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (0x1EA0 <= c && c < 0x1F00 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL

	if (0x1F00 <= c && c < 0x2000 && !(c & 8))		return (c - 8);				// GREEK_CAPITAL					-> GREEK_SMALL

	if (0x2170 <= c && c < 0x2180)					return (c + 0x10);			// ROMAN_NUMERAL_CAPITAL			-> ROMAN_NUMERAL_SMALL
	if (0x2170 <= c && c < 0x2180)					return (c);					// 									-> ROMAN_NUMERAL_SMALL

	if (0x24D0 <= c && c < 0x24EA)					return (c + 0x1A);			// LATIN_CIRCLED_CAPITAL			-> LATIN_CIRCLED_SMALL
	if (0x24D0 <= c && c < 0x24EA)					return (c);					// 									-> LATIN_CIRCLED_SMALL

	if (0x2C30 <= c && c < 0x2C60)					return (c + 0x30);			// GLAGOLITIC_CAPITAL				-> GLAGOLITIC_SMALL
	if (0x2C30 <= c && c < 0x2C60)					return (c);					// 									-> GLAGOLITIC_SMALL

	if (c == 0x2C60)								return (c + 1);				// LATIN_CAPITAL_L_wDOUBLEBAR		-> LATIN_SMALL_L_wDOUBLEBAR
	if (c == 0x2C67)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C69)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C6B)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C72)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL
	if (c == 0x2C75)								return (c + 1);				// LATIN_CAPITAL					-> LATIN_SMALL

	if (0x2C80 <= c && c < 0x2CE4)					return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x2CEB)								return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x2CED)								return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL
	if (c == 0x2CF2)								return (c + 1);				// COPTIC_CAPITAL					-> COPTIC_SMALL

	if (0xA640 <= c && c < 0xA66E && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL_extB			-> CYRILLIC_SMALL_extB
	if (0xA680 <= c && c < 0xA69C && (c % 2 == 0))	return (c + 1);				// CYRILLIC_CAPITAL_extB			-> CYRILLIC_SMALL_extB

	if (0xA722 <= c && c < 0xA730 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA732 <= c && c < 0xA770 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA779 <= c && c < 0xA77D && (c % 2 == 1))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA780 <= c && c < 0xA788 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA790 <= c && c < 0xA794 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA79A <= c && c < 0xA7AA && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA7B6 <= c && c < 0xA7C4 && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD
	if (0xA7C7 <= c && c < 0xA7CB && (c % 2 == 0))	return (c + 1);				// LATIN_CAPITAL_extD				-> LATIN_SMALL_extD

	// TODO inspect this region to see if there's anything not yet handled

	if (0xFF21 <= c && c < 0xFF3B)					return (c + 0x20);			// LATIN_CAPITAL_FULLWIDTH			-> LATIN_SMALL_FULLWIDTH
	if (0xFF41 <= c && c < 0xFF5B)					return (c);					// 									-> LATIN_SMALL_FULLWIDTH

	if (0x10400 <= c && c < 0x10428)				return (c + 0x28);			// DESERET_CAPITAL					-> DESERET_SMALL
	if (0x10428 <= c && c < 0x10450)				return (c);					// 									-> DESERET_SMALL

	if (0x104B0 <= c && c < 0x104D8)				return (c + 0x28);			// OSAGE_CAPITAL					-> OSAGE_SMALL
	if (0x104D8 <= c && c < 0x10500)				return (c);					// 									-> OSAGE_SMALL

	// TODO inspect this region to see if there's anything not yet handled

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

	// TODO inspect this region to see if there's anything not yet handled

	return (c);
}
