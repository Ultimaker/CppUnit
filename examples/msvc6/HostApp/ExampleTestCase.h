
#ifndef CPP_UNIT_EXAMPLETESTCASE_H
#define CPP_UNIT_EXAMPLETESTCASE_H

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

/* 
 * A test case that is designed to produce
 * example errors and failures
 *
 */

class ExampleTestCase : public CppUnit::TestCase
{
  CU_TEST_SUITE( ExampleTestCase );
  CU_TEST( example );
  CU_TEST( anotherExample );
  CU_TEST( testAdd );
  CU_TEST( testDivideByZero );
  CU_TEST( testEquals );
  CU_TEST_SUITE_END();
protected:

	double			m_value1;
	double			m_value2;

public:

	void			setUp ();

protected:
	void			example ();
	void			anotherExample ();
	void			testAdd ();
	void			testDivideByZero ();
	void			testEquals ();

};


#endif