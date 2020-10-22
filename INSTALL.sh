#!/bin/sh
qmake
mv Makefile Makefile.am
aclocal
automake --add-missing --foreign
autoconf
mv Makefile.am Makefile
./configure
make
echo "Done"
