#ifndef CPPUNIT_EXTENSIONS_REPEATEDTEST_H
#define CPPUNIT_EXTENSIONS_REPEATEDTEST_H

#include <cppunit/extensions/TestDecorator.h>

namespace CppUnit {

class Test;
class TestResult;


/*
 * A decorator that runs a test repeatedly.
 * Does not assume ownership of the test it decorates
 *
 */

class RepeatedTest : public TestDecorator 
{
public:
                        RepeatedTest (Test *test, int timesRepeat)
                            : TestDecorator (test), m_timesRepeat (timesRepeat) {}

    int                 countTestCases ();
    std::string         toString ();
    void                run (TestResult *result);

private:
    RepeatedTest( const RepeatedTest & );
    void operator( const RepeatedTest & );

    const int           m_timesRepeat;
};


// Counts the number of test cases that will be run by this test.
inline RepeatedTest::countTestCases ()
{ return TestDecorator::countTestCases () * m_timesRepeat; }

// Returns the name of the test instance. 
inline std::string RepeatedTest::toString ()
{ return TestDecorator::toString () + " (repeated)"; }

// Runs a repeated test
inline void RepeatedTest::run (TestResult *result)
{
    for (int n = 0; n < m_timesRepeat; n++) {
        if (result->shouldStop ())
            break;

        TestDecorator::run (result);
    }
}



} // namespace CppUnit

#endif // CPPUNIT_EXTENSIONS_REPEATEDTEST_H
