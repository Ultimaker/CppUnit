
#ifndef CPP_UNIT_EXAMPLETESTCASE_H
#define CPP_UNIT_EXAMPLETESTCASE_H

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

/* 
 * A test case that is designed to produce
 * example errors and failures
 *
 */

class ExampleTestCase : public CppUnit::TestCase
{
protected:

	double			m_value1;
	double			m_value2;

public:

	void			setUp ();
	static CppUnit::Test		*suite ();

protected:
	void			example ();
	void			anotherExample ();
	void			testAdd ();
	void			testDivideByZero ();
	void			testEquals ();

};


#endif