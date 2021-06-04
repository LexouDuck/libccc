#!/bin/sh

# This script outputs all predefined macros for the current environment
if [ -z "$CC" ]; then
	echo "ERROR: CC environment variable has no value"
	exit 1
fi
echo "/*"
echo "** macro test: predefined"
echo "**	OS: $OS"
echo "**	SH: $(uname -s)"
echo "**	CC: $(which $CC)"
echo "*/"
echo "" \
| $CC -dM -E - \
| grep -E "^[[:space:]]*#[[:space:]]*define[[:space:]]+" \
| sort -k2
