#!/bin/sh

PPP_AWK=`find . -name "ppp.awk" | head -1`

for i in $*
do
	file="${i%.*}"
	awk -f "$PPP_AWK" "$file.++c" > "$file.c"
done

#m4 --prefix-builtins -D    "#incbin"="INCBIN(packed)"			$1.c > $1.c
#m4 --prefix-builtins -D    "#packed"="_PACKED()"				$1.c > $1.c
#m4 --prefix-builtins -D    "#format"="_FORMAT($1, $2, $3)))"	$1.c > $1.c
#m4 --prefix-builtins -D     "#alias"="_ALIAS($1)))"			$1.c > $1.c
#m4 --prefix-builtins -D     "#align"="_ALIGNED($1)))"			$1.c > $1.c
#m4 --prefix-builtins -D      "#pure"="_PURE()"					$1.c > $1.c
#m4 --prefix-builtins -D    "#inline"="_ALWAYS_INLINE() inline"	$1.c > $1.c
#m4 --prefix-builtins -D    "#malloc"="_MALLOC()"				$1.c > $1.c
#m4 --prefix-builtins -D    "#delete"="_DELETE()"				$1.c > $1.c
#m4 --prefix-builtins -D    "#unused"="_UNUSED()"				$1.c > $1.c
#m4 --prefix-builtins -D   "#replace"="define($1,$2)"			$1.c > $1.c
#m4 --prefix-builtins -D  "#operator"=""						$1.c > $1.c
#m4 --prefix-builtins -D  "#accessor"=""						$1.c > $1.c
#m4 --prefix-builtins -D "#namespace"=""						$1.c > $1.c
