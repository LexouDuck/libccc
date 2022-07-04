#! This file holds certain utility variables and settings for 'make'



# show warnings for undefined variables by default
#MAKEFLAGS += --warn-undefined-variables

# disable any builtin make rules (better to be explicit, fewer surprises)
MAKEFLAGS += --no-builtin-rules

# disable any builtin make rules (better to be explicit, fewer surprises)
.SUFFIXES:

# (uncomment to activate) set every `make` rule to execute in a single shell, instead of the default behavior of using one shell per recipe line
#.ONESHELL:

# (uncomment to activate) set the default shell that `make` will use as interpreter program
#SHELL := /bin/sh

# set rigorous shell flags to fail properly when a command errors
.SHELLFLAGS := -e -u -c

# have `make` automatically delete the target file when a recipe failed partway through
.DELETE_ON_ERROR:

# (uncomment to activate) enable secondary variable expansion for make target prerequisite lists
#.SECONDEXPANSION:



# TODO use .FEATURES variable to enable optional utils ?



# Here, we define variables for several important punctuation characters.
# This allows us to "escape" these characters in certain contexts, both in 'make' and 'sh' syntax.

#! Makefile text character variable: newline `\n`
define C_NL


endef

C_EMPTY:=

#! Makefile text character variable: tab `\t`
C_TAB:=$(C_EMPTY)	$(C_EMPTY)

#! Makefile text character variable: space ` `
C_SPACE:=$(C_EMPTY) $(C_EMPTY)

C_COMMA:=,#!< Makefile text character variable: comma `,`
C_COLON:=:#!< Makefile text character variable: colon (double-dot) `:`
C_PERIOD:=.#!< Makefile text character variable: period (dot) `.`
C_SEMICOLON:=;#!< Makefile text character variable: semi-colon (dot-comma) `;`

#! Makefile text character variable: underscore (low line) `_`
C_UNDERSCORE:=_
#! Makefile text character variable: pipe, or (vertical line) `|`
C_VERTICALBAR:=|
#! Makefile text character variable: ampersand (and) `&`
C_AMPERSAND:=&

#! Makefile text character variable: dash (minus) `-`
C_DASH:=-
#! Makefile text character variable: cross (plus) `+`
C_PLUS:=+
#! Makefile text character variable: tilde (wave) `~`
C_TILDE:=~
#! Makefile text character variable: dollar `$`
C_DOLLAR:=$$
#! Makefile text character variable: percent `%`
C_PERCENT:=%
#! Makefile text character variable: hashtag `#`
C_HASHTAG:=\#
#! Makefile text character variable: asterisk `*`
C_ASTERISK:=*

C_BACKQUOTE  :=`#!< Makefile text character variable: backtick '`'
C_SINGLEQUOTE:='#!< Makefile text character variable: single quote `'`
C_DOUBLEQUOTE:="#!< Makefile text character variable: double quote `"`

C_FWSLASH:=/#!< Makefile text character variable: forward slash (solidus) `/`
C_BKSLASH:=\\#!< Makefile text character variable: back slash (reverse solidus) `\`

C_PARENTHESE_OPENING:=(#!< Makefile text character variable: opening parenthese `(`
C_PARENTHESE_CLOSING:=)#!< Makefile text character variable: closing parenthese `)`

C_CURLYBRACE_OPENING:={#!< Makefile text character variable: opening curly brace `{`
C_CURLYBRACE_CLOSING:=}#!< Makefile text character variable: closing curly brace `}`

C_SQRBRACKET_OPENING:=[#!< Makefile text character variable: opening square bracket `[`
C_SQRBRACKET_CLOSING:=]#!< Makefile text character variable: closing square bracket `]`

C_ANGBRACKET_OPENING:=<#!< Makefile text character variable: opening angle bracket (less than) `<`
C_ANGBRACKET_CLOSING:=>#!< Makefile text character variable: closing angle bracket (more than) `>`
