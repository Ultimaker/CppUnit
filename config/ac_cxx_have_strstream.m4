dnl @synopsis AC_CXX_HAVE_STRSTREAM
dnl
dnl If the C++ library has a working strstream, define HAVE_STRSTREAM.
dnl
dnl Adapted from ac_cxx_have_sstream.m4 by Steve Robbins
dnl
AC_DEFUN([AC_CXX_HAVE_STRSTREAM],
[AC_CACHE_CHECK(whether the compiler has strstream,
ac_cv_cxx_have_strstream,
[AC_REQUIRE([AC_CXX_NAMESPACES])
 AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([#include <strstream.h>
#ifdef HAVE_NAMESPACES
using namespace std;
#endif],[ostrstream message; message << "Hello"; return 0;],
 ac_cv_cxx_have_strstream=yes, ac_cv_cxx_have_strstream=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_have_strstream" = yes; then
  AC_DEFINE(HAVE_STRSTREAM,1,[define if the compiler has strstream])
fi
])
