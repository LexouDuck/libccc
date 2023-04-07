
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsUppercase(t_utf32 c)
{ return (iswupper(c)); }
#else
inline
t_bool	CharUTF32_IsUppercase(t_utf32 c)
{
	if ('A' <= c && c <= 'Z')						return (TRUE);
	if (c == 0xD7)									return (FALSE);
	if (c == 0xDF)									return (FALSE);
	if (0xC0 <= c && c < 0xE0)						return (TRUE);
	if (0x100 <= c && c < 0x138 && (c % 2 == 0))	return (TRUE);
	if (0x138 <= c && c < 0x148 && (c % 2 == 1))	return (TRUE);
	if (0x14A <= c && c < 0x178 && (c % 2 == 0))	return (TRUE);
	if (c == 0x0178)								return (TRUE);	// Ÿ
	if (c == 0x0179)								return (TRUE);	// Ź
	if (c == 0x017B)								return (TRUE);	// Ż
	if (c == 0x017D)								return (TRUE);	// Ž
	if (c == 0x0181)								return (TRUE);	// Ɓ
	if (c == 0x0182)								return (TRUE);	// Ƃ
	if (c == 0x0184)								return (TRUE);	// Ƅ
	if (c == 0x0186)								return (TRUE);	// Ɔ
	if (c == 0x0187)								return (TRUE);	// Ƈ
	if (c == 0x0189)								return (TRUE);	// Ɖ
	if (c == 0x018A)								return (TRUE);	// Ɗ
	if (c == 0x018B)								return (TRUE);	// Ƌ
	if (c == 0x018E)								return (TRUE);	// Ǝ
	if (c == 0x018F)								return (TRUE);	// Ə
	if (c == 0x0190)								return (TRUE);	// Ɛ
	if (c == 0x0191)								return (TRUE);	// Ƒ
	if (c == 0x0193)								return (TRUE);	// Ɠ
	if (c == 0x0194)								return (TRUE);	// Ɣ
	if (c == 0x0196)								return (TRUE);	// Ɩ
	if (c == 0x0197)								return (TRUE);	// Ɨ
	if (c == 0x0198)								return (TRUE);	// Ƙ
	if (c == 0x019C)								return (TRUE);	// Ɯ
	if (c == 0x019D)								return (TRUE);	// Ɲ
	if (c == 0x019F)								return (TRUE);	// Ɵ
	if (c == 0x01A0)								return (TRUE);	// Ơ
	if (c == 0x01A2)								return (TRUE);	// Ƣ
	if (c == 0x01A4)								return (TRUE);	// Ƥ
	if (c == 0x01A6)								return (TRUE);	// Ʀ
	if (c == 0x01A7)								return (TRUE);	// Ƨ
	if (c == 0x01A9)								return (TRUE);	// Ʃ
	if (c == 0x01AC)								return (TRUE);	// Ƭ
	if (c == 0x01AE)								return (TRUE);	// Ʈ
	if (c == 0x01AF)								return (TRUE);	// Ư
	if (c == 0x01B1)								return (TRUE);	// Ʊ
	if (c == 0x01B2)								return (TRUE);	// Ʋ
	if (c == 0x01B3)								return (TRUE);	// Ƴ
	if (c == 0x01B5)								return (TRUE);	// Ƶ
	if (c == 0x01B7)								return (TRUE);	// Ʒ
	if (c == 0x01B8)								return (TRUE);	// Ƹ
	if (c == 0x01BC)								return (TRUE);	// Ƽ
	if (c == 0x01C4)								return (TRUE);	// Ǆ
	if (c == 0x01C7)								return (TRUE);	// Ǉ
	if (c == 0x01CA)								return (TRUE);	// Ǌ
	if (c == 0x01CD)								return (TRUE);	// Ǎ
	if (c == 0x01CF)								return (TRUE);	// Ǐ
	if (c == 0x01D1)								return (TRUE);	// Ǒ
	if (c == 0x01D3)								return (TRUE);	// Ǔ
	if (c == 0x01D5)								return (TRUE);	// Ǖ
	if (c == 0x01D7)								return (TRUE);	// Ǘ
	if (c == 0x01D9)								return (TRUE);	// Ǚ
	if (c == 0x01DB)								return (TRUE);	// Ǜ
	if (c == 0x01DE)								return (TRUE);	// Ǟ
	if (c == 0x01E0)								return (TRUE);	// Ǡ
	if (c == 0x01E2)								return (TRUE);	// Ǣ
	if (c == 0x01E4)								return (TRUE);	// Ǥ
	if (c == 0x01E6)								return (TRUE);	// Ǧ
	if (c == 0x01E8)								return (TRUE);	// Ǩ
	if (c == 0x01EA)								return (TRUE);	// Ǫ
	if (c == 0x01EC)								return (TRUE);	// Ǭ
	if (c == 0x01EE)								return (TRUE);	// Ǯ
	if (c == 0x01F1)								return (TRUE);	// Ǳ
	if (c == 0x01F4)								return (TRUE);	// Ǵ
	if (c == 0x01F6)								return (TRUE);	// Ƕ
	if (c == 0x01F7)								return (TRUE);	// Ƿ
	if (c == 0x01F8)								return (TRUE);	// Ǹ
	if (c == 0x01FA)								return (TRUE);	// Ǻ
	if (c == 0x01FC)								return (TRUE);	// Ǽ
	if (c == 0x01FE)								return (TRUE);	// Ǿ
	if (0x200 <= c && c < 0x233 && (c % 2 == 0))	return (TRUE);
	if (c == 0x0386)								return (TRUE);	// Ά
	if (c == 0x0388)								return (TRUE);	// Έ
	if (c == 0x0389)								return (TRUE);	// Ή
	if (c == 0x038A)								return (TRUE);	// Ί
	if (c == 0x038C)								return (TRUE);	// Ό
	if (c == 0x038E)								return (TRUE);	// Ύ
	if (c == 0x038F)								return (TRUE);	// Ώ
	if (c == 0x03A2)								return (FALSE);
	if (0x390 < c && c < 0x3AC)						return (TRUE);
	if (c == 0x03D3)								return (TRUE);
	if (c == 0x03D6)								return (FALSE);
	if (0x3D0 < c && c < 0x3F0 && (c % 2 == 0))		return (TRUE);
	if (c == 0x03F4)								return (TRUE);
	if (0x400 <= c && c < 0x430)					return (TRUE);
	if (0x460 <= c && c < 0x482 && (c % 2 == 0))	return (TRUE);
	if (0x48A <= c && c <= 0x4C0 && (c % 2 == 0))	return (TRUE);
	if (0x4C0 <= c && c <= 0x4CE && (c % 2 == 1))	return (TRUE);
	if (0x4D0 <= c && c < 0x4FA && (c % 2 == 0))	return (TRUE);
	if (0x500 <= c && c < 0x510 && (c % 2 == 0))	return (TRUE);
	if (0x531 <= c && c < 0x557)					return (TRUE);

	if (0x10A0 <= c && c < 0x10C6)					return (TRUE);

	if (0x1E00 <= c && c < 0x1E96 && (c % 2 == 0))	return (TRUE);
	if (0x1EA0 <= c && c < 0x1EFA && (c % 2 == 0))	return (TRUE);

	if (c == 0x1F1E)								return (FALSE); // ἞
	if (c == 0x1F1F)								return (FALSE); // ἟
	if (c == 0x1F4E)								return (FALSE); // ὎
	if (c == 0x1F4F)								return (FALSE); // ὏
	if (c == 0x1F58)								return (FALSE); // ὘
	if (c == 0x1F5A)								return (FALSE); // ὚
	if (c == 0x1F5C)								return (FALSE); // ὜
	if (c == 0x1F5E)								return (FALSE); // ὞
	if (0x1F00 <= c && c < 0x1F70 && (c % 16 >= 8))	return (TRUE);
	if (c == 0x1FEC)								return (TRUE); // Ῥ
	if (0x1FB0 <= c && c < 0x2000 && (c % 16 >= 8) && (c % 16 < 12))	return (TRUE);

	if (c == 0x2102)								return (TRUE); // ℂ
	if (c == 0x2107)								return (TRUE); // ℇ
	if (c == 0x210B)								return (TRUE); // ℋ
	if (c == 0x210C)								return (TRUE); // ℌ
	if (c == 0x210D)								return (TRUE); // ℍ
	if (c == 0x2110)								return (TRUE); // ℐ
	if (c == 0x2111)								return (TRUE); // ℑ
	if (c == 0x2112)								return (TRUE); // ℒ
	if (c == 0x2115)								return (TRUE); // ℕ
	if (c == 0x2119)								return (TRUE); // ℙ
	if (c == 0x211A)								return (TRUE); // ℚ
	if (c == 0x211B)								return (TRUE); // ℛ
	if (c == 0x211C)								return (TRUE); // ℜ
	if (c == 0x211D)								return (TRUE); // ℝ
	if (c == 0x2124)								return (TRUE); // ℤ
	if (c == 0x2126)								return (TRUE); // Ω
	if (c == 0x2128)								return (TRUE); // ℨ
	if (c == 0x212A)								return (TRUE); // K
	if (c == 0x212B)								return (TRUE); // Å
	if (c == 0x212C)								return (TRUE); // ℬ
	if (c == 0x212D)								return (TRUE); // ℭ
	if (c == 0x2130)								return (TRUE); // ℰ
	if (c == 0x2131)								return (TRUE); // ℱ
	if (c == 0x2133)								return (TRUE); // ℳ
	if (c == 0x213E)								return (TRUE); // ℾ
	if (c == 0x213F)								return (TRUE); // ℿ
	if (c == 0x2145)								return (TRUE); // ⅅ

	if (0xFF21 <= c && c < 0xFF3B)					return (TRUE);

	if (0x10400 <= c && c < 0x1041A)				return (TRUE);

	// latin
	if (0x1D400 <= c && c < 0x1D41A)				return (TRUE);
	if (0x1041A <= c && c < 0x10426)				return (TRUE);
	if (0x1D434 <= c && c < 0x1D44E)				return (TRUE);
	if (0x1D468 <= c && c < 0x1D482)				return (TRUE);
	if (c == 0x1D49D)								return (FALSE);
	if (c == 0x1D4A0)								return (FALSE);
	if (c == 0x1D4A1)								return (FALSE);
	if (c == 0x1D4A3)								return (FALSE);
	if (c == 0x1D4A4)								return (FALSE);
	if (c == 0x1D4A7)								return (FALSE);
	if (c == 0x1D4A8)								return (FALSE);
	if (c == 0x1D4AD)								return (FALSE);
	if (0x1D49C <= c && c < 0x1D4B6)				return (TRUE);
	if (0x1D4D0 <= c && c < 0x1D4EA)				return (TRUE);
	if (c == 0x1D506)								return (FALSE);
	if (c == 0x1D50B)								return (FALSE);
	if (c == 0x1D50C)								return (FALSE);
	if (c == 0x1D515)								return (FALSE);
	if (c == 0x1D51D)								return (FALSE);
	if (0x1D504 <= c && c < 0x1D51E)				return (TRUE);
	if (c == 0x1D53A)								return (FALSE);
	if (c == 0x1D53F)								return (FALSE);
	if (c == 0x1D545)								return (FALSE);
	if (c == 0x1D547)								return (FALSE);
	if (c == 0x1D548)								return (FALSE);
	if (c == 0x1D549)								return (FALSE);
	if (c == 0x1D551)								return (FALSE);
	if (0x1D538 <= c && c < 0x1D552)				return (TRUE);
	if (0x1D56C <= c && c < 0x1D586)				return (TRUE);
	if (0x1D5A0 <= c && c < 0x1D5BA)				return (TRUE);
	if (0x1D5D4 <= c && c < 0x1D5EE)				return (TRUE);
	if (0x1D608 <= c && c < 0x1D622)				return (TRUE);
	if (0x1D63C <= c && c < 0x1D656)				return (TRUE);
	if (0x1D670 <= c && c < 0x1D68A)				return (TRUE);
	// greek
	if (0x1D6A8 <= c && c < 0x1D6C1)				return (TRUE);
	if (0x1D6E2 <= c && c < 0x1D6FB)				return (TRUE);
	if (0x1D71C <= c && c < 0x1D735)				return (TRUE);
	if (0x1D756 <= c && c < 0x1D76F)				return (TRUE);
	if (0x1D790 <= c && c < 0x1D7A9)				return (TRUE);

	return (FALSE);
}
#endif
