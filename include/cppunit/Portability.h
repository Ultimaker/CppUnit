#ifndef CPPUNIT_PORTABILITY_H
#define CPPUNIT_PORTABILITY_H

/* include platform specific config */
#if defined(__BORLANDC__)
#    include <cppunit/config/config-bcb5.h>
#elif defined (_MSC_VER)
#    include <cppunit/config/config-msvc6.h>
#else
#    include <cppunit/config-auto.h>
#endif

#include <cppunit/config/CppUnitApi.h>    // define CPPUNIT_API & CPPUNIT_NEED_DLL_DECL
#include <cppunit/config/SelectDllLoader.h>


/* Options that the library user may switch on or off.
 * If the user has not done so, we chose default values.
 */


/* Define to 1 if you wish to have the old-style macros
   assert(), assertEqual(), assertDoublesEqual(), and assertLongsEqual() */
#ifndef CPPUNIT_ENABLE_NAKED_ASSERT
#define CPPUNIT_ENABLE_NAKED_ASSERT          0
#endif

/* Define to 1 if you wish to have the old-style CU_TEST family
   of macros. */
#ifndef CPPUNIT_ENABLE_CU_TEST_MACROS
#define CPPUNIT_ENABLE_CU_TEST_MACROS        0
#endif

/* Define to 1 if the preprocessor expands (#foo) to "foo" (quotes incl.) 
   I don't think there is any C preprocess that does NOT support this! */
#ifndef CPPUNIT_HAVE_CPP_SOURCE_ANNOTATION
#define CPPUNIT_HAVE_CPP_SOURCE_ANNOTATION   1
#endif

// Compiler error location format for CompilerOutputter
// If not define, assumes that it's gcc
// See class CompilerOutputter for format.
#ifndef CPPUNIT_COMPILER_LOCATION_FORMAT
#define CPPUNIT_COMPILER_LOCATION_FORMAT "%f:%l:"
#endif


/*! Stringize a symbol.
 * 
 * Use this macro to convert a preprocessor symbol to a string.
 *
 * Example of usage:
 * \code
 * #define CPPUNIT_PLUGIN_EXPORTED_NAME cppunitTestPlugIn
 * const char *name = CPPUNIT_STRINGIZE( CPPUNIT_PLUGIN_EXPORTED_NAME );
 * \endcode
 */
#define CPPUNIT_STRINGIZE( symbol ) _CPPUNIT_DO_STRINGIZE( symbol )

/// \internal
#define _CPPUNIT_DO_STRINGIZE( symbol ) #symbol

/*! Joins to symbol after expanding them into string.
 *
 * Use this macro to join two symbols. Example of usage:
 *
 * \code
 * #define MAKE_UNIQUE_NAME(prefix) CPPUNIT_JOIN( prefix, __LINE__ )
 * \endcode
 *
 * The macro defined in the example concatenate a given prefix with the line number
 * to obtain a 'unique' identifier.
 *
 * \internal From boost documentation:
 * The following piece of macro magic joins the two 
 * arguments together, even when one of the arguments is
 * itself a macro (see 16.3.1 in C++ standard).  The key
 * is that macro expansion of macro arguments does not
 * occur in CPPUNIT_JOIN2 but does in CPPUNIT_JOIN.
 */
#define CPPUNIT_JOIN( symbol1, symbol2 ) _CPPUNIT_DO_JOIN( symbol1, symbol2 )

/// \internal
#define _CPPUNIT_DO_JOIN( symbol1, symbol2 ) _CPPUNIT_DO_JOIN2( symbol1, symbol2 )

/// \internal
#define _CPPUNIT_DO_JOIN2( symbol1, symbol2 ) symbol1##symbol2

/*! Adds the line number to the specified string to create a unique identifier.
 * \param prefix Prefix added to the line number to create a unique identifier.
 * \see CPPUNIT_TEST_SUITE_REGISTRATION for an example of usage.
 */
#define CPPUNIT_MAKE_UNIQUE_NAME( prefix ) CPPUNIT_JOIN( prefix, __LINE__ )


/* perform portability hacks */


/* Define CPPUNIT_SSTREAM as a stream with a "std::string str()"
 * method.
 */
#if CPPUNIT_HAVE_SSTREAM
#   include <sstream>
    namespace CppUnit {
      class OStringStream : public std::ostringstream 
      {
      };
    }
#else 
#if CPPUNIT_HAVE_CLASS_STRSTREAM
#   include <string>
#   if CPPUNIT_HAVE_STRSTREAM
#       include <strstream>
#   else
#       include <strstream.h>
#   endif

    namespace CppUnit {
      class OStringStream : public std::ostrstream 
      {
      public:
          std::string str()
          {
            (*this) << '\0';
            std::string msg(std::ostrstream::str());
            std::ostrstream::freeze(false);
            return msg;
          }
      };
    }
#else
#   error Cannot define CppUnit::OStringStream.
#endif
#endif


#endif // CPPUNIT_PORTABILITY_H
