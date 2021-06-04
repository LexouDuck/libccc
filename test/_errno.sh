#!/bin/sh

# This script outputs all errno macros for the current environment
if [ -z "$CC" ]; then
	echo "ERROR: CC environment variable has no value"
	exit 1
fi
echo "/*"
echo "** macro test: errno"
echo "**	OS: $OS"
echo "**	SH: $(uname -s)"
echo "**	CC: $(which $CC)"
echo "*/"
echo "#include <errno.h>" \
| $CC -dM -E - \
| grep -E "^[[:space:]]*#[[:space:]]*define[[:space:]]+E" \
| sort -k3 --numeric-sort
