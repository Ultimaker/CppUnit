#!/bin/sh

DIE=0

(autoconf --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "**Error**: You must have \`autoconf' installed ."
  DIE=1
}

(automake --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "**Error**: You must have \`automake' installed."
  DIE=1
  NO_AUTOMAKE=yes
}

(aclocal --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "**Error**: Missing \`aclocal'."
  DIE=1
}

(libtool --version) < /dev/null > /dev/null 2>&1 || {
  echo
  echo "**Error**: You must have \`libtool' installed."
  DIE=1
}


if [ -d /usr/local/share/aclocal ]; then
  ACLOCAL_FLAGS="-I /usr/local/share/aclocal $ACLOCAL_FLAGS"
fi
aclocal $ACLOCAL_FLAGS 
libtoolize --force 
autoheader
automake --add-missing
autoconf
