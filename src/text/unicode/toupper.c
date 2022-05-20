
#include "libccc/text/unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_utf32	CharUTF32_ToUppercase(t_utf32 c)
{ return (towupper(c)); }
#else
t_utf32	CharUTF32_ToUppercase(t_utf32 c) // TODO make lookup table for weird 'if's with no discernible pattern
{
	if ('a' <= c && c <= 'z')						return (c - 0x20);			// LATIN_SMALL					-> LATIN_CAPITAL
	if (0xC0 <= c && c < 0xDF)						return (c);					// 								-> LATIN_CAPITAL
	if (0xE0 <= c && c < 0xFF)						return (c - 0x20);			// LATIN_SMALL					-> LATIN_CAPITAL
	if (c == 0x00FF)								return (0x0178);			// LATIN_SMALL_extA_Y_DIAERESIS	-> LATIN_CAPITAL_extA_Y_wDIAERESIS
	if (0x0100 <= c && c < 0x0130 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extA				-> LATIN_CAPITAL_extA
	if (c == 0x0130)								return (c);					// 								-> LATIN_CAPITAL_extA_I_wDOT
	if (c == 0x0131)								return ('I');				// LATIN_SMALL_extA_DOTLESS_I	-> LATIN_CAPITAL_I
	if (0x0132 <= c && c < 0x0138 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extA				-> LATIN_CAPITAL_extA
	if (0x0139 <= c && c < 0x0149 && (c % 2 == 0))	return (c - 1);				// LATIN_SMALL_extA				-> LATIN_CAPITAL_extA
	if (0x014A <= c && c < 0x0178 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extA				-> LATIN_CAPITAL_extA
	if (0x0179 <= c && c < 0x017F && (c % 2 == 0))	return (c - 1);				// LATIN_SMALL_extA				-> LATIN_CAPITAL_extA

	if (0x0182 <= c && c < 0x0186 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extB				-> LATIN_CAPITAL_extB
	if (c == 0x0188)								return (c - 1);				// LATIN_SMALL_extB_C_wHOOK		-> LATIN_CAPITAL_extB_C_wHOOK
	if (c == 0x018C)								return (c - 1);				// LATIN_SMALL_extB_D_wTOPBAR	-> LATIN_CAPITAL_extB_D_wTOPBAR
	if (c == 0x0192)								return (c - 1);				// LATIN_SMALL_extB_F_wHOOK		-> LATIN_CAPITAL_extB_F_wHOOK
	if (c == 0x0199)								return (c - 1);				// LATIN_SMALL_extB_K_wHOOK		-> LATIN_CAPITAL_extB_K_wHOOK
	if (0x01A0 <= c && c < 0x01A6 && (c % 2 == 0))	return (c - 1);				// LATIN_SMALL_extB				-> LATIN_CAPITAL_extB
	if (c == 0x01A8)								return (c - 1);				// LATIN_SMALL_extB_TONE TWO	-> LATIN_CAPITAL_extB_TONE TWO
	if (c == 0x01AD)								return (c - 1);				// LATIN_SMALL_extB_T_wHOOK		-> LATIN_CAPITAL_extB_T_wHOOK
	if (c == 0x01B0)								return (c - 1);				// LATIN_SMALL_extB_U_wHORN		-> LATIN_CAPITAL_extB_U_wHORN
	if (c == 0x01B4)								return (c - 1);				// LATIN_SMALL_extB_Y_wHOOK		-> LATIN_CAPITAL_extB_Y_wHOOK
	if (c == 0x01B6)								return (c - 1);				// LATIN_SMALL_extB_Z_wSTROKE	-> LATIN_CAPITAL_extB_Z_wSTROKE
	if (c == 0x01B9)								return (c - 1);				// LATIN_SMALL_extB_EZH_REVERSED-> LATIN_CAPITAL_extB_EZH_REVERSED
	if (c == 0x01BD)								return (c - 1);				// LATIN_SMALL_extB_TONE_FIVE	-> LATIN_CAPITAL_extB_TONE_FIVE
	if (c == 0x01C6)								return (c - 1);				// LATIN_SMALL_extB_DZ_wCARON	-> LATIN_CAPITAL_extB_DZ_wCARON
	if (c == 0x01C9)								return (c - 1);				// LATIN_SMALL_extB_LJ			-> LATIN_CAPITAL_extB_LJ
	if (c == 0x01CC)								return (c - 1);				// LATIN_SMALL_extB_NJ			-> LATIN_CAPITAL_extB_NJ
	if (0x01CD <= c && c < 0x01DD && (c % 2 == 0))	return (c - 1);				// LATIN_SMALL_extB				-> LATIN_CAPITAL_extB
	if (0x01DE <= c && c < 0x01F0 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extB				-> LATIN_CAPITAL_extB
	if (c == 0x01F3)								return (0x01F1);			// LATIN_SMALL_extB_DZ			-> LATIN_CAPITAL_extB_DZ
	if (c == 0x01F5)								return (c - 1);				// LATIN_SMALL_extB_G_wACUTE	-> LATIN_CAPITAL_extB_G_wACUTE
	if (0x01F8 <= c && c < 0x0220 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extB				-> LATIN_CAPITAL_extB

	if (c == 0x0253)								return (0x0181);			// LATIN_SMALL_extI_B_wHOOK		-> LATIN_CAPITAL_extI_B_wHOOK
	if (c == 0x0254)								return (0x0186);			// LATIN_SMALL_extI_OPEN O		-> LATIN_CAPITAL_extI_OPEN O
	if (c == 0x0257)								return (0x018A);			// LATIN_SMALL_extI_D_wHOOK		-> LATIN_CAPITAL_extI_D_wHOOK
	if (c == 0x0258)								return (0x018E);			// LATIN_SMALL_extI_REVERSED_E	-> LATIN_CAPITAL_extI_REVERSED_E
	if (c == 0x0259)								return (0x018F);			// LATIN_SMALL_extI_SCHWA		-> LATIN_CAPITAL_extI_SCHWA
	if (c == 0x025B)								return (0x0190);			// LATIN_SMALL_extI_OPEN_E		-> LATIN_CAPITAL_extI_OPEN_E
	if (c == 0x0260)								return (0x0193);			// LATIN_SMALL_extI_G_wHOOK		-> LATIN_CAPITAL_extI_G_wHOOK
	if (c == 0x0263)								return (0x0194);			// LATIN_SMALL_extI_GAMMA		-> LATIN_CAPITAL_extI_GAMMA
	if (c == 0x0268)								return (0x0197);			// LATIN_SMALL_extI_I_wSTROKE	-> LATIN_CAPITAL_extI_I_wSTROKE
	if (c == 0x0269)								return (0x0196);			// LATIN_SMALL_extI_IOTA		-> LATIN_CAPITAL_extI_IOTA
	if (c == 0x026F)								return (0x019C);			// LATIN_SMALL_extI_TURNED_M	-> LATIN_CAPITAL_extI_TURNED_M
	if (c == 0x0272)								return (0x019D);			// LATIN_SMALL_extI_N_wLEFT_HOOK-> LATIN_CAPITAL_extI_N_wLEFT_HOOK
	if (c == 0x0275)								return (0x019F);			// LATIN_SMALL_extI_BARRED_O	-> LATIN_CAPITAL_extI_O_wMIDDLE_TILDE
	if (c == 0x0283)								return (0x01A9);			// LATIN_SMALL_extI_ESH			-> LATIN_CAPITAL_extI_ESH
	if (c == 0x0288)								return (0x01AE);			// LATIN_SMALL_extI_T_wRETROFLEX-> LATIN_CAPITAL_extI_T_wRETROFLEX
	if (c == 0x028A)								return (0x01B1);			// LATIN_SMALL_extI_UPSILON		-> LATIN_CAPITAL_extI_UPSILON
	if (c == 0x028B)								return (0x01B2);			// LATIN_SMALL_extI_V_wHOOK		-> LATIN_CAPITAL_extI_V_wHOOK
	if (c == 0x0292)								return (0x01B7);			// LATIN_SMALL_extI_EZH			-> LATIN_CAPITAL_extI_EZH

	if (c == 0x03AC)								return (0x0386);			// GREEK_SMALL_ALPHA_wTONOS		-> GREEK_CAPITAL_ALPHA_wTONOS
	if (c == 0x03AD)								return (0x0388);			// GREEK_SMALL_EPSILON_wTONOS	-> GREEK_CAPITAL_EPSILON_wTONOS
	if (c == 0x03AE)								return (0x0389);			// GREEK_SMALL_ETA_wTONOS		-> GREEK_CAPITAL_ETA_wTONOS
	if (c == 0x03AF)								return (0x038A);			// GREEK_SMALL_IOTA_wTONOS		-> GREEK_CAPITAL_IOTA_wTONOS
	if (c == 0x03C2)								return (c);					// GREEK_SMALL_FINAL_SIGMA
	if (c == 0x03CC)								return (0x038C);			// GREEK_SMALL_OMICRON_wTONOS	-> GREEK_CAPITAL_OMICRON_wTONOS
	if (c == 0x03CD)								return (0x038E);			// GREEK_SMALL_UPSILON_wTONOS	-> GREEK_CAPITAL_UPSILON_wTONOS
	if (c == 0x03CE)								return (0x038F);			// GREEK_SMALL_OMEGA_wTONOS		-> GREEK_CAPITAL_OMEGA_wTONOS
	if (0x0391 <= c && c < 0x03AC)					return (c);					// 								-> GREEK_CAPITAL
	if (0x03B1 <= c && c < 0x03CC)					return (c - 0x20);			// GREEK_SMALL					-> GREEK_CAPITAL

	if (0x03E2 <= c && c < 0x03F0 && (c % 2 == 1))	return (c - 1);				// COPTIC_SMALL					-> COPTIC_CAPITAL

	if (0x0400 <= c && c < 0x0410)					return (c);					// 								-> CYRILLIC_CAPITAL
	if (0x0410 <= c && c < 0x0430)					return (c);					// 								-> CYRILLIC_CAPITAL
	if (0x0430 <= c && c < 0x0450)					return (c - 0x20);			// CYRILLIC_SMALL				-> CYRILLIC_CAPITAL
	if (0x0450 <= c && c < 0x0460)					return (c - 0x50);			// CYRILLIC_SMALL				-> CYRILLIC_CAPITAL
	if (0x0460 <= c && c < 0x0482 && (c % 2 == 1))	return (c - 1);				// CYRILLIC_SMALL				-> CYRILLIC_CAPITAL
	if (0x048A <= c && c < 0x04C0 && (c % 2 == 1))	return (c - 1);				// CYRILLIC_SMALL				-> CYRILLIC_CAPITAL
	if (0x04C1 <= c && c < 0x04CF && (c % 2 == 0))	return (c - 1);				// CYRILLIC_SMALL				-> CYRILLIC_CAPITAL
	if (c == 0x04CF)								return (0x04C0);			// CYRILLIC_SMALL_PALOCHKA		-> CYRILLIC_CAPITAL_PALOCHKA
	if (0x04D0 <= c && c < 0x0530 && (c % 2 == 1))	return (c - 1);				// CYRILLIC_SMALL				-> CYRILLIC_CAPITAL

	if (0x0531 <= c && c < 0x0557)					return (c);					// 								-> ARMENIAN_CAPITAL
	if (0x0561 <= c && c < 0x0587)					return (c - 0x30);			// ARMENIAN_SMALL				-> ARMENIAN_CAPITAL

	if (0x10A0 <= c && c < 0x10D0)					return (c);					// 								-> GEORGIAN_CAPITAL
	if (0x10D0 <= c && c < 0x1100)					return (c - 0x30);			// GEORGIAN_SMALL				-> GEORGIAN_CAPITAL

	if (0x1E00 <= c && c < 0x1E96 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL
	if (0x1EA0 <= c && c < 0x1F00 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL

	if (0x1F00 <= c && c < 0x2000 && (c & 8))		return (c + 8);				// GREEK_SMALL					-> GREEK_CAPITAL

	if (0x2170 <= c && c < 0x2180)					return (c);					// 								-> ROMAN_NUMERAL_CAPITAL
	if (0x2170 <= c && c < 0x2180)					return (c - 0x10);			// ROMAN_NUMERAL_SMALL			-> ROMAN_NUMERAL_CAPITAL

	if (0x24D0 <= c && c < 0x24EA)					return (c);					// 								-> LATIN_CIRCLED_CAPITAL
	if (0x24D0 <= c && c < 0x24EA)					return (c - 0x1A);			// LATIN_CIRCLED_SMALL			-> LATIN_CIRCLED_CAPITAL

	if (0x2C30 <= c && c < 0x2C60)					return (c);					// 								-> GLAGOLITIC_CAPITAL
	if (0x2C30 <= c && c < 0x2C60)					return (c - 0x30);			// GLAGOLITIC_SMALL				-> GLAGOLITIC_CAPITAL

	if (c == 0x2C61)								return (c - 1);				// LATIN_SMALL_L_wDOUBLEBAR		-> LATIN_CAPITAL_L_wDOUBLEBAR
	if (c == 0x2C68)								return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL
	if (c == 0x2C6A)								return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL
	if (c == 0x2C6C)								return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL
	if (c == 0x2C73)								return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL
	if (c == 0x2C76)								return (c - 1);				// LATIN_SMALL					-> LATIN_CAPITAL

	if (0x2C80 <= c && c < 0x2CE4)					return (c - 1);				// COPTIC_SMALL					-> COPTIC_CAPITAL
	if (c == 0x2CEC)								return (c - 1);				// COPTIC_SMALL					-> COPTIC_CAPITAL
	if (c == 0x2CEE)								return (c - 1);				// COPTIC_SMALL					-> COPTIC_CAPITAL
	if (c == 0x2CF3)								return (c - 1);				// COPTIC_SMALL					-> COPTIC_CAPITAL

	if (0xA640 <= c && c < 0xA66E && (c % 2 == 1))	return (c - 1);				// CYRILLIC_SMALL_extB			-> CYRILLIC_CAPITAL_extB
	if (0xA680 <= c && c < 0xA69C && (c % 2 == 1))	return (c - 1);				// CYRILLIC_SMALL_extB			-> CYRILLIC_CAPITAL_extB

	if (0xA722 <= c && c < 0xA730 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA732 <= c && c < 0xA770 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA779 <= c && c < 0xA77D && (c % 2 == 0))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA780 <= c && c < 0xA788 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA790 <= c && c < 0xA794 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA79A <= c && c < 0xA7AA && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA7B6 <= c && c < 0xA7C4 && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD
	if (0xA7C7 <= c && c < 0xA7CB && (c % 2 == 1))	return (c - 1);				// LATIN_SMALL_extD				-> LATIN_CAPITAL_extD

	// TODO inspect this region to see if there's anything not yet handled

	if (0xFF21 <= c && c < 0xFF3B)					return (c);					// 								-> LATIN_CAPITAL_FULLWIDTH
	if (0xFF41 <= c && c < 0xFF5B)					return (c - 0x20);			// LATIN_SMALL_FULLWIDTH		-> LATIN_CAPITAL_FULLWIDTH

	if (0x10400 <= c && c < 0x10428)				return (c);					// 								-> DESERET_CAPITAL
	if (0x10428 <= c && c < 0x10450)				return (c - 0x28);			// DESERET_SMALL				-> DESERET_CAPITAL

	if (0x104B0 <= c && c < 0x104D8)				return (c);					// 								-> OSAGE_CAPITAL
	if (0x104D8 <= c && c < 0x10500)				return (c - 0x28);			// OSAGE_SMALL					-> OSAGE_CAPITAL

	// TODO inspect this region to see if there's anything not yet handled

	// latin
	if (0x1D41A <= c && c < 0x1D434)				return (c - 0x1A);			// MATH_SMALL_LATIN_BOLD		-> MATH_CAPITAL_LATIN_BOLD
	if (0x1D44E <= c && c < 0x1D468)				return (c - 0x1A);			// MATH_SMALL_LATIN_ITALIC		-> MATH_CAPITAL_LATIN_ITALIC
	if (0x1D482 <= c && c < 0x1D49C)				return (c - 0x1A);			// MATH_SMALL_LATIN_BOLDITAL	-> MATH_CAPITAL_LATIN_BOLDITAL
	if (0x1D4B6 <= c && c < 0x1D4D0)				return (c - 0x1A);			// MATH_SMALL_SCRIPT			-> MATH_CAPITAL_SCRIPT
	if (0x1D4EA <= c && c < 0x1D504)				return (c - 0x1A);			// MATH_SMALL_SCRIPT_BOLD		-> MATH_CAPITAL_SCRIPT_BOLD
	if (0x1D51E <= c && c < 0x1D538)				return (c - 0x1A);			// MATH_SMALL_FRAKTUR			-> MATH_CAPITAL_FRAKTUR
	if (0x1D552 <= c && c < 0x1D56C)				return (c - 0x1A);			// MATH_SMALL_DOUBLESTRUCK		-> MATH_CAPITAL_DOUBLESTRUCK
	if (0x1D586 <= c && c < 0x1D5A0)				return (c - 0x1A);			// MATH_SMALL_FRAKTUR_BOLD		-> MATH_CAPITAL_FRAKTUR_BOLD
	if (0x1D5BA <= c && c < 0x1D5D4)				return (c - 0x1A);			// MATH_SMALL_LATINSANS			-> MATH_CAPITAL_LATINSANS
	if (0x1D5EE <= c && c < 0x1D608)				return (c - 0x1A);			// MATH_SMALL_LATINSANS_BOLD	-> MATH_CAPITAL_LATINSANS_BOLD
	if (0x1D622 <= c && c < 0x1D63C)				return (c - 0x1A);			// MATH_SMALL_LATINSANS_ITALIC	-> MATH_CAPITAL_LATINSANS_ITALIC
	if (0x1D656 <= c && c < 0x1D670)				return (c - 0x1A);			// MATH_SMALL_LATINSANS_BOLDITAL-> MATH_CAPITAL_LATINSANS_BOLDITAL
	if (0x1D68A <= c && c < 0x1D6A4)				return (c - 0x1A);			// MATH_SMALL_MONOSPACE			-> MATH_CAPITAL_MONOSPACE
	// greek
	if (0x1D6C2 <= c && c < 0x1D6DB)				return (c - 0x1A);			// MATH_SMALL_GREEK_BOLD		-> MATH_CAPITAL_GREEK_BOLD
	if (0x1D6FC <= c && c < 0x1D715)				return (c - 0x1A);			// MATH_SMALL_GREEK_ITALIC		-> MATH_CAPITAL_GREEK_ITALIC
	if (0x1D736 <= c && c < 0x1D74F)				return (c - 0x1A);			// MATH_SMALL_GREEK_BOLDITAL	-> MATH_CAPITAL_GREEK_BOLDITAL
	if (0x1D770 <= c && c < 0x1D789)				return (c - 0x1A);			// MATH_SMALL_GREEKSANS_BOLD	-> MATH_CAPITAL_GREEKSANS_BOLD
	if (0x1D7AA <= c && c < 0x1D7C3)				return (c - 0x1A);			// MATH_SMALL_GREEKSANS_BOLDITAL-> MATH_CAPITAL_GREEKSANS_BOLDITAL

	// TODO inspect this region to see if there's anything not yet handled

	return (c);
}
#endif
