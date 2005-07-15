#! /bin/sh
set -e

(cd $1 && rm -rf `find . -name CVS`)
tar cf $1.tar $1
gzip -9 $1.tar
