
#include "libccc/text/char_ascii.h"
#include "libccc/text/char_unicode.h"

#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
#include <wctype.h>
#endif

#include LIBCONFIG_ERROR_INCLUDE



#if LIBCONFIG_USE_STD_FUNCTIONS_ALWAYS
inline
t_bool	CharUTF32_IsPunctuation(t_utf32 c)
{ return (iswpunct(c)); }
#else
// TODO UTF handling
t_bool	CharUTF32_IsPunctuation(t_utf32 c)
{
	if ('!' <= c && c <= '/')		return (TRUE);
	if (':' <= c && c <= '@')		return (TRUE);
	if ('[' <= c && c <= '`')		return (TRUE);
	if ('{' <= c && c <= '~')		return (TRUE);
	if (c == 0xAA)					return (FALSE); // ª
	if (0xA0 < c && c < 0xB2)		return (TRUE);
	if (c == 0xB4)					return (TRUE); // ´
	if (c == 0xB6)					return (TRUE); // ¶
	if (c == 0xB7)					return (TRUE); // ·
	if (c == 0xB8)					return (TRUE); // ¸
	if (c == 0xBB)					return (TRUE); // »
	if (c == 0xBF)					return (TRUE); // ¿
	if (c == 0xD7)					return (TRUE); // ×
	if (c == 0xF7)					return (TRUE); // ÷
	if (c == 0x2B9)					return (TRUE); // '
	if (c == 0x2BA)					return (TRUE); // "
	if (c == 0x2C1)					return (FALSE); // 'ˁ'
	if (c == 0x2D0)					return (FALSE); // 'ː'
	if (c == 0x2D1)					return (FALSE); // 'ˑ'
	if (c == 0x2E0)					return (FALSE); // 'ˠ'
	if (c == 0x2E1)					return (FALSE); // 'ˡ'
	if (c == 0x2E2)					return (FALSE); // 'ˢ'
	if (c == 0x2E3)					return (FALSE); // 'ˣ'
	if (c == 0x2E4)					return (FALSE); // 'ˤ'
	if (c == 0x2EE)					return (FALSE); // 'ˮ'
	if (c == 0x2EF)					return (FALSE); // '˯'
	if (0x2C0 < c && c < 0x2F0)		return (TRUE);
	if (c == 0x374)					return (TRUE); // ʹ
	if (c == 0x375)					return (TRUE); // ͵
	if (c == 0x37E)					return (TRUE); // ;
	if (c == 0x384)					return (TRUE); // ΄
	if (c == 0x385)					return (TRUE); // ΅
	if (c == 0x387)					return (TRUE); // ·
	if (c == 0x3F6)					return (TRUE); // ϶
	if (c == 0x482)					return (TRUE); // ҂
	if (0x55A <= c && c < 0x560)	return (TRUE);
	if (c == 0x589)					return (TRUE); // ։
	if (c == 0x58A)					return (TRUE); // ֊
	if (c == 0x5BE)					return (TRUE); // ־
	if (c == 0x5C0)					return (TRUE); // ׀
	if (c == 0x5C3)					return (TRUE); // ׃
	if (c == 0x5F3)					return (TRUE); // ׳
	if (c == 0x5F4)					return (TRUE); // ״
	if (c == 0x60C)					return (TRUE); // ،
	if (c == 0x61B)					return (TRUE); // ؛
	if (c == 0x61F)					return (TRUE); // ؟
	if (c == 0x66A)					return (TRUE); // ٪
	if (c == 0x66B)					return (TRUE); // ٫
	if (c == 0x66C)					return (TRUE); // ٬
	if (c == 0x66D)					return (TRUE); // ٭
	if (c == 0x6D4)					return (TRUE); // ۔
	if (c == 0x6E9)					return (TRUE); // ۩
	if (c == 0x6FD)					return (TRUE); // ۽
	if (c == 0x6FE)					return (TRUE); // ۾
	if (0x700 <= c && c < 0x70E)	return (TRUE);

	if (c == 0x964)					return (TRUE); // ।
	if (c == 0x965)					return (TRUE); // ॥
	if (c == 0x970)					return (TRUE); // ॰
	if (c == 0x9F2)					return (TRUE); // ৲
	if (c == 0x9F3)					return (TRUE); // ৳
	if (c == 0x9FA)					return (TRUE); // ৺
	if (c == 0xB70)					return (TRUE); // ୰
	if (c == 0xDF4)					return (TRUE); // ෴
	if (c == 0xE3F)					return (TRUE); // ฿
	if (c == 0xE4F)					return (TRUE); // ๏
	if (c == 0xE5A)					return (TRUE); // ๚
	if (c == 0xE5B)					return (TRUE); // ๛

	if (c == 0xF18)					return (FALSE); // '༘'
	if (c == 0xF19)					return (FALSE); // '༙'
	if (0xF00 < c && c < 0xF20)		return (TRUE);
	if (c == 0xF34)					return (TRUE); // ༴
	if (c == 0xF36)					return (TRUE); // ༶
	if (c == 0xF38)					return (TRUE); // ༸
	if (c == 0xF3A)					return (TRUE); // ༺
	if (c == 0xF3B)					return (TRUE); // ༻
	if (c == 0xF3C)					return (TRUE); // ༼
	if (c == 0xF3D)					return (TRUE); // ༽
	if (c == 0xF85)					return (TRUE); // ྅
	if (c == 0xFBE)					return (TRUE); // ྾
	if (c == 0xFBF)					return (TRUE); // ྿
	if (c == 0xFC6)					return (FALSE); // '࿆
	if (c == 0xFCD)					return (FALSE); // ࿍
	if (c == 0xFCE)					return (FALSE); // ࿎
	if (0xFC0 <= c && c < 0xFD0)	return (TRUE);

	if (0x104A <= c && c < 0x1050)	return (TRUE);
	if (c == 0x10FB)				return (TRUE); // ჻

	if (0x1360 < c && c < 0x1369)	return (TRUE);

	if (c == 0x166D)				return (TRUE); // ᙭
	if (c == 0x166E)				return (TRUE); // ᙮
	if (c == 0x169B)				return (TRUE); // ᚛
	if (c == 0x169C)				return (TRUE); // ᚜
	if (c == 0x16EB)				return (TRUE); // ᛫
	if (c == 0x16EC)				return (TRUE); // ᛬
	if (c == 0x16ED)				return (TRUE); // ᛭
	if (c == 0x1735)				return (TRUE); // ᜵
	if (c == 0x1736)				return (TRUE); // ᜶
	if (c == 0x17D7)				return (FALSE); // ᜶
	if (0x17D3 < c && c < 0x17DC)	return (TRUE);
	if (0x1800 <= c && c < 0x180B)	return (TRUE);

	if (c == 0x1FBD)				return (TRUE); // 
	if (c == 0x1FBF)				return (TRUE); // 
	if (c == 0x1FC0)				return (TRUE); // ῀
	if (c == 0x1FC1)				return (TRUE); // ῁
	if (c == 0x1FCD)				return (TRUE); // ῍
	if (c == 0x1FCE)				return (TRUE); // ῎
	if (c == 0x1FCF)				return (TRUE); // ῏
	if (c == 0x1FDD)				return (TRUE); // ῝
	if (c == 0x1FDE)				return (TRUE); // ῞
	if (c == 0x1FDF)				return (TRUE); // ῟
	if (c == 0x1FED)				return (TRUE); // ῭
	if (c == 0x1FEE)				return (TRUE); // ΅
	if (c == 0x1FEF)				return (TRUE); // `
	if (c == 0x1FFD)				return (TRUE); // ´
	if (c == 0x1FFE)				return (TRUE); // ῾

	if (0x2010 <= c && c < 0x2028)	return (TRUE);
	if (0x2030 <= c && c < 0x2052)	return (TRUE);
	if (0x2052 <= c && c < 0x208A)	return (TRUE);
	if (0x208A <= c && c < 0x2B00)	return (TRUE);

	if (0x268A <= c && c <= 0x2700)	return (TRUE);
	if (0x2776 <= c && c <= 0x2798)	return (TRUE);
	if (0x27B0 <= c && c <= 0x27C0)	return (TRUE);

	if (0x2E80 <= c && c <= 0x2EF4)	return (TRUE);
	if (0x2F00 <= c && c <= 0x2FFB)	return (TRUE);
	if (0x3000 <= c && c <= 0x3020)	return (TRUE);
	if (c == 0x3030)				return (TRUE); // 〰
	if (c == 0x3036)				return (TRUE); // 〶
	if (c == 0x3037)				return (TRUE); // 〷
	if (c == 0x303D)				return (TRUE); // 〽
	if (c == 0x303E)				return (TRUE); // 〾
	if (c == 0x303F)				return (TRUE); // 〿
	if (c == 0x309B)				return (TRUE); // ゛
	if (c == 0x309C)				return (TRUE); // ゜
	if (c == 0x30A0)				return (TRUE); // ゠
	if (c == 0x30FB)				return (TRUE); // ・

	if (c == 0x3190)				return (TRUE); // 
	if (c == 0x3191)				return (TRUE); // 
	if (0x3196 <= c && c < 0x3200)	return (TRUE);
	if (0x3200 <= c && c < 0x3244)	return (TRUE);
	if (0x3260 <= c && c < 0x327C)	return (TRUE);
	if (c == 0x327F)				return (TRUE); //
	if (0x328A <= c && c <= 0x32B0)	return (TRUE);
	if (0x32C0 <= c && c < 0x3300)	return (TRUE);
	if (0x3300 <= c && c < 0x3400)	return (TRUE);

	if (0xA490 <= c && c <= 0xA4C6)	return (TRUE);

	if (c == 0xFB29)				return (TRUE); // ﬩
	if (c == 0xFD3E)				return (TRUE); // ﴾
	if (c == 0xFD3F)				return (TRUE); // ﴿
	if (c == 0xFDFC)				return (TRUE); // ﷼
	if (0xFE30 <= c && c < 0xFE6E)	return (TRUE);

	if (0xFF00 < c && c < 0xFF10)	return (TRUE);
	if (0xFF1A <= c && c <= 0xFF20)	return (TRUE);
	if (0xFF3B <= c && c <= 0xFF40)	return (TRUE);
	if (0xFF5B <= c && c <= 0xFF65)	return (TRUE);
	if (0xFFE0 <= c && c < 0xFFEF)	return (TRUE);
	if (c == 0xFFFC)				return (TRUE); // ￼
	if (c == 0xFFFD)				return (TRUE); // �

	if (0x1D000 <= c && c <= 0x1D1DD)	return (TRUE);

	if (0x1F100 <= c && c <= 0x1F19A)	return (TRUE);
	if (0x1F1E6 <= c && c < 0x1F200)	return (TRUE);
	if (0x1F300 <= c && c < 0x1F8AE)	return (TRUE);

	return (FALSE);
}
#endif
