#ifndef CPPUNIT_PORTABILITY_H
#define CPPUNIT_PORTABILITY_H

/* include platform specific config */
#if defined(__BORLANDC__)
#    include <cppunit/config-bcb5.h>
#elif defined (_MSC_VER)
#    include <cppunit/config-msvc6.h>
#else
#    include <cppunit/config-auto.h>
#endif


/* Options that the library user may switch on or off.
 * If the user has not done so, we chose default values.
 */

/* FIXME: does not belong in Portability.h (?) */
/* Define to 1 if the compiler supports Run-Time Type Identification */
#ifndef CPPUNIT_USE_TYPEINFO
#define CPPUNIT_USE_TYPEINFO                CPPUNIT_HAVE_RTTI
#endif


/* Define to 1 if you wish to have the old-style macros
   assert(), assertEqual(), assertDoublesEqual(), and assertLongsEqual() */
#ifndef CPPUNIT_ENABLE_NAKED_ASSERT
#define CPPUNIT_ENABLE_NAKED_ASSERT         0
#endif


/* Define to 1 if the preprocessor expands (#foo) to "foo" (quotes incl.) */
#ifndef CPPUNIT_HAVE_CPP_SOURCEANNOTATION
#define CPPUNIT_HAVE_CPP_SOURCEANNOTATION   1
#endif



/* perform portability hacks */

#if _MSC_VER > 1000     // VC++
#pragma once
#pragma warning( disable : 4786 )   // disable warning debug symbol > 255...
#endif // _MSC_VER > 1000


#endif // CPPUNIT_PORTABILITY_H
