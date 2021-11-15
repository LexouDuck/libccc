
#ifndef __PPP_H
#define __PPP_H

#include <stdlib.h>
#include <stdio.h>

#include <libccc.h>

#include "y.tab.h"



void	ppp_error(char const* message);

void	ppp_verbatim(char const* str);

void	ppp_comment_block(char const* str);
void	ppp_comment_line(char const* str);

int		ppp_symbol(char const* str);



#endif
