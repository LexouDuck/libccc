/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string/ft_strprint.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duquesne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2006/06/06 06:06:06 by duquesne          #+#    #+#             */
/*   Updated: 2006/06/06 06:06:06 by duquesne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_char.h"
#include "libft_string.h"



char	*ft_strprint(char const *str)
{
	unsigned char HI_nibble;
	unsigned char LO_nibble;
	char*	result;
	t_size	index = 0;
	t_size	i = 0;

#if HANDLE_NULLPOINTERS
	if (str == NULL)
		return (NULL);
#endif
	if (!(result = (char *)malloc(ft_strlen(str) * 4)))
		return (NULL);
	while (str[index])
	{
		if (!ft_isprint(str[index]))
		{
			result[i++] = '\\';
			switch (str[index])
			{
				case 0x07: result[i++] =  'a'; break; // Alert (Beep, Bell) (added in C89)[1]
				case 0x08: result[i++] =  'b'; break; // Backspace
				case 0x0C: result[i++] =  'f'; break; // Formfeed
				case 0x0A: result[i++] =  'n'; break; // Newline (Line Feed); see notes below
				case 0x0D: result[i++] =  'r'; break; // Carriage Return
				case 0x09: result[i++] =  't'; break; // Horizontal Tab
				case 0x0B: result[i++] =  'v'; break; // Vertical Tab
				case 0x5C: result[i++] = '\\'; break; // Backslash
				case 0x27: result[i++] = '\''; break; // Single quotation mark
				case 0x22: result[i++] = '\"'; break; // Double quotation mark
				case 0x3F: result[i++] =  '?'; break; // Question mark (used to avoid trigraphs)
				default: result[i++] = 'x'; // Hexadecimal char notation: \xFF
					HI_nibble = (str[index] & 0xF0) >> 4;
					LO_nibble = (str[index] & 0x0F);
					result[i++] = (HI_nibble < 10) ? (HI_nibble + '0') : (HI_nibble - 10 + 'A');
					result[i++] = (LO_nibble < 10) ? (LO_nibble + '0') : (LO_nibble - 10 + 'A');
				break;
			}
		}
		else result[i++] = str[index];
		++index;
	}
	result[i] = '\0';
	return (result);
}
