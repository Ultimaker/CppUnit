#ifndef CPPUNIT_TEXTTESTRUNNER_H
#define CPPUNIT_TEXTTESTRUNNER_H

#include <cppunit/ui/text/TestRunner.h>

CPPUNIT_NS_BEGIN


/*!
 * \brief A text mode test runner.
 * \ingroup ExecutingTest
 * \deprecated Use CppUnit::TextUi::TestRunner instead.
 */
typedef CPPUNIT_NS(TextUi::TestRunner) TextTestRunner;

CPPUNIT_NS_END

#endif  // CPPUNIT_TEXTTESTRUNNER_H
