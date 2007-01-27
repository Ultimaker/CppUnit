#include <cppunit/TestAssert.h>

#include <math.h>

#if !defined(CPPUNIT_HAVE_ISFINITE)

    static inline bool isfinite( double x )
    {
#if defined(CPPUNIT_HAVE_FINITE)
	return finite( x );
#else
        return ( x * 0.0 ) == 0.0;
#endif
    }

#endif

CPPUNIT_NS_BEGIN


void 
assertDoubleEquals( double expected,
                    double actual,
                    double delta,
                    SourceLine sourceLine,
                    const std::string &message )
{
  AdditionalMessage msg( "Delta   : " + 
                         assertion_traits<double>::toString(delta) );
  msg.addDetail( AdditionalMessage(message) );

  bool equal;
  if ( isfinite(expected) && isfinite(actual) )
      equal = fabs( expected - actual ) <= delta;
  else
      equal = expected == actual;

  Asserter::failNotEqualIf( !equal,
                            assertion_traits<double>::toString(expected),
                            assertion_traits<double>::toString(actual),
                            sourceLine, 
                            msg, 
                            "double equality assertion failed" );
}


CPPUNIT_NS_END
