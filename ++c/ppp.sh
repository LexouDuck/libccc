#!/bin/sh

rm $1.c
cp $1.++c $1.c
m4 --prefix-builtins -D    "#incbin"="INCBIN(packed)"							$1.c > $1.c
m4 --prefix-builtins -D    "#packed"="__attribute__((packed))"					$1.c > $1.c
m4 --prefix-builtins -D    "#format"="__attribute__((format($1, $2, $3)))"		$1.c > $1.c
m4 --prefix-builtins -D     "#alias"="__attribute__((alias(#$1)))"				$1.c > $1.c
m4 --prefix-builtins -D     "#align"="__attribute__((aligned($1)))"				$1.c > $1.c
m4 --prefix-builtins -D      "#pure"="__attribute__((pure))"					$1.c > $1.c
m4 --prefix-builtins -D    "#inline"="__attribute__((always_inline)) inline"	$1.c > $1.c
m4 --prefix-builtins -D    "#malloc"="__attribute__((malloc))"					$1.c > $1.c
m4 --prefix-builtins -D    "#delete"="__attribute__((delete))"					$1.c > $1.c
m4 --prefix-builtins -D    "#unused"="__attribute__((unused))"					$1.c > $1.c
m4 --prefix-builtins -D   "#replace"="define(|[$1]|,|[$2]|)"					$1.c > $1.c
m4 --prefix-builtins -D  "#operator"=""											$1.c > $1.c
m4 --prefix-builtins -D  "#accessor"=""											$1.c > $1.c
m4 --prefix-builtins -D  "#function"=""											$1.c > $1.c
m4 --prefix-builtins -D "#namespace"=""											$1.c > $1.c
