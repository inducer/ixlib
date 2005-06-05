# !/bin/sh

set -e 

aclocal -I m4
autoheader
autoconf
automake -a
rm -f config.cache || true

# this is for debian
test -r config.sub || cp /usr/share/misc/config.sub .
test -r config.guess || cp /usr/share/misc/config.guess .

echo "ready to run 'configure'."
