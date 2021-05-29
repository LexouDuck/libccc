#!/bin/sh
echo "/* $(readlink $(which $CC)) */"
echo '#include <errno.h>' \
| $CC -dM -E - \
| grep -E '^[[:space:]]*#[[:space:]]*define[[:space:]]+E' \
| sort --numeric-sort -k3
