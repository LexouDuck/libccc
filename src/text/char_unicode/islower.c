
#include "libccc/bool.h"
#include "libccc/char.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <ctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
_INLINE()
t_bool	CharUTF32_IsLowercase(t_utf32 c)
{ return (iswlower(c)); }
#else
_INLINE()
t_bool	CharUTF32_IsLowercase(t_utf32 c)
{
	if ('a' <= c && c <= 'z')						return (TRUE);
	if (c == 0xDF)									return (TRUE);
	if (c == 0xAA)									return (TRUE); // ª
	if (c == 0xB5)									return (TRUE); // µ
	if (c == 0xBA)									return (TRUE); // º
	if (c == 0xF7)									return (FALSE); // ÷
	if (0xE0 <= c && c < 0x100)						return (TRUE);
	if (0x100 <= c && c < 0x138 && (c % 2 == 1))	return (TRUE);
	if (0x138 <= c && c <= 0x148 && (c % 2 == 0))	return (TRUE);
	if (0x148 <= c && c < 0x178 && (c % 2 == 1))	return (TRUE);
	if (c == 0x17A)									return (TRUE);
	if (c == 0x17C)									return (TRUE);
	if (c == 0x17E)									return (TRUE);
	if (c == 0x17F)									return (TRUE);
	if (c == 0x0180)								return (TRUE); // ƀ
	if (c == 0x0183)								return (TRUE); // ƃ
	if (c == 0x0185)								return (TRUE); // ƅ
	if (c == 0x0188)								return (TRUE); // ƈ
	if (c == 0x018C)								return (TRUE); // ƌ
	if (c == 0x018D)								return (TRUE); // ƍ
	if (c == 0x0192)								return (TRUE); // ƒ
	if (c == 0x0195)								return (TRUE); // ƕ
	if (c == 0x0199)								return (TRUE); // ƙ
	if (c == 0x019A)								return (TRUE); // ƚ
	if (c == 0x019B)								return (TRUE); // ƛ
	if (c == 0x019E)								return (TRUE); // ƞ
	if (c == 0x01A1)								return (TRUE); // ơ
	if (c == 0x01A3)								return (TRUE); // ƣ
	if (c == 0x01A5)								return (TRUE); // ƥ
	if (c == 0x01A8)								return (TRUE); // ƨ
	if (c == 0x01AA)								return (TRUE); // ƪ
	if (c == 0x01AB)								return (TRUE); // ƫ
	if (c == 0x01AD)								return (TRUE); // ƭ
	if (c == 0x01B0)								return (TRUE); // ư
	if (c == 0x01B4)								return (TRUE); // ƴ
	if (c == 0x01B6)								return (TRUE); // ƶ
	if (c == 0x01B9)								return (TRUE); // ƹ
	if (c == 0x01BA)								return (TRUE); // ƺ
	if (c == 0x01BD)								return (TRUE); // ƽ
	if (c == 0x01BE)								return (TRUE); // ƾ
	if (c == 0x01BF)								return (TRUE); // ƿ
	if (c == 0x01C5)								return (TRUE); // ǅ
	if (c == 0x01C6)								return (TRUE); // ǆ
	if (c == 0x01C8)								return (TRUE); // ǈ
	if (c == 0x01C9)								return (TRUE); // ǉ
	if (c == 0x01CC)								return (TRUE); // ǌ
	if (c == 0x01CB)								return (TRUE); // ǋ
	if (c == 0x01CE)								return (TRUE); // ǎ
	if (0x1D0 <= c && c < 0x1DD && (c % 2 == 0))	return (TRUE);
	if (c == 0x01F0)								return (TRUE); // ǰ
	if (c == 0x01F1)								return (FALSE); // Ǳ
	if (c == 0x01F2)								return (TRUE); // ǲ
	if (c == 0x01F7)								return (FALSE); // Ƿ
	if (c == 0x0221)								return (TRUE); // ȡ
	if (0x1DD <= c && c < 0x234 && (c % 2 == 1))	return (TRUE);
	if (0x234 <= c && c < 0x23A)					return (TRUE);
	if (c == 0x023C)								return (TRUE); // ȼ
	if (c == 0x023F)								return (TRUE); // ȿ
	if (c == 0x0240)								return (TRUE); // ɀ
	if (c == 0x0242)								return (TRUE); // ɂ
	if (c == 0x0247)								return (TRUE); // ɇ
	if (c == 0x0249)								return (TRUE); // ɉ
	if (c == 0x024B)								return (TRUE); // ɋ
	if (c == 0x024D)								return (TRUE); // ɍ
	if (c == 0x024F)								return (TRUE); // ɏ
	if (c == 0x0294)								return (TRUE); // ʔ
	if (0x250 <= c && c <= 0x2B8)					return (TRUE);
	if (c == 0x02C0)								return (TRUE); // ˀ
	if (c == 0x02C1)								return (TRUE); // ˁ
	if (c == 0x02E0)								return (TRUE); // ˠ
	if (c == 0x02E1)								return (TRUE); // ˡ
	if (c == 0x02E2)								return (TRUE); // ˢ
	if (c == 0x02E3)								return (TRUE); // ˣ
	if (c == 0x02E4)								return (TRUE); // ˤ
	if (c == 0x0345)								return (TRUE); // 
	if (c == 0x0371)								return (TRUE); // ͱ
	if (c == 0x0373)								return (TRUE); // ͳ
	if (c == 0x0377)								return (TRUE); // ͷ
	if (c == 0x037A)								return (TRUE); // ͺ
	if (c == 0x037B)								return (TRUE); // ͻ
	if (c == 0x037C)								return (TRUE); // ͼ
	if (c == 0x037D)								return (TRUE); // ͽ
	if (c == 0x03F8)								return (TRUE); // ϸ
	if (c == 0x03FB)								return (TRUE); // ϻ
	if (c == 0x03FC)								return (TRUE); // ϼ
	if (c == 0x0390)								return (TRUE); // ΐ
	if (0x3AC <= c && c < 0x3CF)					return (TRUE);
	if (c == 0x03D0)								return (TRUE); // ϐ
	if (c == 0x03D3)								return (FALSE); // ϓ
	if (c == 0x03D6)								return (TRUE); // ϖ
	if (0x3D0 <= c && c < 0x3F0 && (c % 2 == 1))	return (TRUE);
	if (c == 0x03F0)								return (TRUE); // ϰ
	if (c == 0x03F1)								return (TRUE); // ϱ
	if (c == 0x03F2)								return (TRUE); // ϲ
	if (c == 0x03F3)								return (TRUE); // ϳ
	if (c == 0x03F5)								return (TRUE); // ϵ

	if (0x430 <= c && c < 0x460)					return (TRUE);
	if (c == 0x0483)								return (FALSE); // '҃
	if (c == 0x0485)								return (FALSE); // '҅
	if (c == 0x0487)								return (FALSE); // '҇
	if (c == 0x0489)								return (FALSE); // '҉
	if (0x460 <= c && c < 0x4C0 && (c % 2 == 1))	return (TRUE);
	if (c == 0x04CF)								return (TRUE); // ӏ
	if (0x4C1 <= c && c < 0x4D0 && (c % 2 == 0))	return (TRUE);
	if (c == 0x04FB)								return (TRUE); // ӻ
	if (c == 0x04FD)								return (TRUE); // ӽ
	if (c == 0x04FF)								return (TRUE); // ӿ
	if (0x4D0 <= c && c < 0x4FA && (c % 2 == 1))	return (TRUE);
	if (0x500 <= c && c < 0x510 && (c % 2 == 1))	return (TRUE);
	if (0x510 <= c && c < 0x530 && (c % 2 == 1))	return (TRUE);
	if (c == 0x0560)								return (TRUE);
	if (0x561 <= c && c <= 0x588)					return (TRUE);

	if (c == 0x10FB)								return (FALSE); // ჻
	if (c == 0x10FC)								return (FALSE); // ჼ
	if (0x10D0 <= c && c < 0x1100)					return (TRUE);

	if (0x13F8 <= c && c < 0x13FE)					return (TRUE);

	if (0x1C80 <= c && c < 0x1C89)					return (TRUE);

	if (0x1D00 <= c && c < 0x1DC0)					return (TRUE);

	if (c == 0x1E9E)								return (FALSE);
	if (0x1E96 <= c && c < 0x1EA0)					return (TRUE);
	if (c == 0x1EFB)								return (TRUE); // ỻ
	if (c == 0x1EFD)								return (TRUE); // ỽ
	if (c == 0x1EFF)								return (TRUE); // ỿ
	if (0x1E00 <= c && c < 0x1F00 && (c % 2 == 1))	return (TRUE);
	if (c == 0x1F16)								return (FALSE); // ἖
	if (c == 0x1F17)								return (FALSE); // ἗
	if (c == 0x1F46)								return (FALSE); // ὆
	if (c == 0x1F47)								return (FALSE); // ὇
	if (c == 0x1F78)								return (TRUE); // ὸ
	if (c == 0x1F79)								return (TRUE); // ό
	if (c == 0x1F7A)								return (TRUE); // ὺ
	if (c == 0x1F7B)								return (TRUE); // ύ
	if (c == 0x1F7C)								return (TRUE); // ὼ
	if (c == 0x1F7D)								return (TRUE); // ώ
	if (c == 0x1FB5)								return (FALSE); // ᾵
	if (c == 0x1FBE)								return (TRUE); // ι
	if (c == 0x1FC0)								return (FALSE); // ῀
	if (c == 0x1FC1)								return (FALSE); // ῁
	if (c == 0x1FC5)								return (FALSE); // ῅
	if (c == 0x1FD4)								return (FALSE); // ῔
	if (c == 0x1FD5)								return (FALSE); // ῕
	if (c == 0x1FF0)								return (FALSE); // ῰
	if (c == 0x1FF1)								return (FALSE); // ῱
	if (c == 0x1FF5)								return (FALSE); // ῵
	if (0x1F00 <= c && c < 0x2000 && (c % 16 < 8))	return (TRUE);

	if (c == 0x2071)								return (TRUE); // ⁱ
	if (c == 0x207F)								return (TRUE); // ⁿ
	if (0x2090 <= c && c < 0x209D)					return (TRUE);

	if (c == 0x210A)								return (TRUE); // ℊ
	if (c == 0x210E)								return (TRUE); // ℎ
	if (c == 0x210F)								return (TRUE); // ℏ
	if (c == 0x2113)								return (TRUE); // ℓ
	if (c == 0x212F)								return (TRUE); // ℯ
	if (c == 0x2134)								return (TRUE); // ℴ
	if (c == 0x2139)								return (TRUE); // ℹ
	if (c == 0x213C)								return (TRUE); // ℼ
	if (c == 0x213D)								return (TRUE); // ℽ
	if (c == 0x2146)								return (TRUE); // ⅆ
	if (c == 0x2147)								return (TRUE); // ⅇ
	if (c == 0x2148)								return (TRUE); // ⅈ
	if (c == 0x2149)								return (TRUE); // ⅉ
	if (c == 0x214E)								return (TRUE); // ⅎ
	if (0x2170 <= c && c < 0x2180)					return (TRUE);
	if (c == 0x2184)								return (TRUE); // ↄ
	if (0x24D0 <= c && c < 0x24EA)					return (TRUE);
	if (0x2C30 <= c && c < 0x2C60)					return (TRUE);

	if (0xFB00 <= c && c < 0xFB07)					return (TRUE);
	if (0xFB13 <= c && c < 0xFB18)					return (TRUE);

	if (0xFF41 <= c && c < 0xFF5B)					return (TRUE);

	if (0x10428 <= c && c < 0x1044E)				return (TRUE);

	// latin
	if (0x1D41A <= c && c < 0x1D434)				return (TRUE);
	if (c == 0x1D455)								return (FALSE); // 𝑕
	if (0x1D44E <= c && c < 0x1D468)				return (TRUE);
	if (0x1D482 <= c && c < 0x1D49C)				return (TRUE);
	if (c == 0x1D4BA)								return (FALSE); // 𝒺
	if (c == 0x1D4BC)								return (FALSE); // 𝒼
	if (c == 0x1D4C1)								return (FALSE); // 𝓁
	if (c == 0x1D4C4)								return (FALSE); // 𝓄
	if (0x1D4B6 <= c && c < 0x1D4D0)				return (TRUE);
	if (0x1D4EA <= c && c < 0x1D504)				return (TRUE);
	if (0x1D51E <= c && c < 0x1D538)				return (TRUE);
	if (0x1D552 <= c && c < 0x1D56C)				return (TRUE);
	if (0x1D586 <= c && c < 0x1D5A0)				return (TRUE);
	if (0x1D5BA <= c && c < 0x1D5D4)				return (TRUE);
	if (0x1D5EE <= c && c < 0x1D608)				return (TRUE);
	if (0x1D622 <= c && c < 0x1D63C)				return (TRUE);
	if (0x1D656 <= c && c < 0x1D670)				return (TRUE);
	if (0x1D68A <= c && c < 0x1D6A4)				return (TRUE);
	// greek
	if (0x1D6C2 <= c && c < 0x1D6DB)				return (TRUE);
	if (0x1D6DC <= c && c < 0x1D6E2)				return (TRUE);
	if (0x1D6FC <= c && c < 0x1D715)				return (TRUE);
	if (0x1D716 <= c && c < 0x1D71C)				return (TRUE);
	if (0x1D736 <= c && c < 0x1D74F)				return (TRUE);
	if (0x1D750 <= c && c < 0x1D756)				return (TRUE);
	if (0x1D770 <= c && c < 0x1D789)				return (TRUE);
	if (0x1D78A <= c && c < 0x1D790)				return (TRUE);
	if (0x1D7AA <= c && c < 0x1D7C3)				return (TRUE);
	if (0x1D7C4 <= c && c < 0x1D7CA)				return (TRUE);

	return (FALSE);
}
#endif
