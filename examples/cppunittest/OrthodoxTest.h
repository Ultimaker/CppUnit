#ifndef ORTHODOXTEST_H
#define ORTHODOXTEST_H

#include <cppunit/extensions/HelperMacros.h>


class OrthodoxTest : public CppUnit::TestCase
{
  CPPUNIT_TEST_SUITE( OrthodoxTest );
  CPPUNIT_TEST( testValue );
  CPPUNIT_TEST( testValueBadConstructor );
  CPPUNIT_TEST( testValueBadInvert );
  CPPUNIT_TEST( testValueBadEqual );
  CPPUNIT_TEST( testValueBadNotEqual );
  CPPUNIT_TEST( testValueBadCall );
  CPPUNIT_TEST( testValueBadAssignment );
  CPPUNIT_TEST_SUITE_END();

public:
  OrthodoxTest();
  virtual ~OrthodoxTest();

  virtual void setUp();
  virtual void tearDown();

  void testValue();
  void testValueBadConstructor();
  void testValueBadInvert();
  void testValueBadEqual();
  void testValueBadNotEqual();
  void testValueBadCall();
  void testValueBadAssignment();

private:
  class Value
  {
  public:
    Value( int value =0 ) : m_value( value ) {}

    bool operator ==( const Value &other )
    {
      return m_value == other.m_value;
    }

    bool operator !=( const Value &other )
    {
      return !( *this == other );
    }

    Value operator !()
    {
      return -1 - m_value;
    }

  protected:
    int m_value;
  };


  class ValueBadConstructor : public Value
  {
  public:
    ValueBadConstructor()
    {
      static int serialNumber = 0;
      m_value = ++serialNumber;
    }

    ValueBadConstructor( int value ) : Value( value ) {}

    ValueBadConstructor operator !()
    {
      return -1 - m_value;
    }
  };

  
  class ValueBadInvert : public Value
  {
  public:
    ValueBadInvert( int value =0 ) : Value( value ) {}

    ValueBadInvert operator !()
    {
      return 1;
    }
  };

  
  class ValueBadEqual : public Value
  {
  public:
    ValueBadEqual( int value =0 ) : Value( value ) {}

    ValueBadEqual operator !()
    {
      return -1 - m_value;
    }

    bool operator ==( const ValueBadEqual &other )
    {
      return m_value != other.m_value;
    }
  };

  
  class ValueBadNotEqual : public Value
  {
  public:
    ValueBadNotEqual( int value =0 ) : Value( value ) {}

    ValueBadNotEqual operator !()
    {
      return -1 - m_value;
    }

    bool operator !=( const ValueBadNotEqual &other )
    {
      return m_value == other.m_value;
    }
  };


  class ValueBadCall : public Value
  {
  public:
    ValueBadCall( int value =0 ) : Value( value ) {}

    ValueBadCall( const ValueBadCall &other ) 
    {
      static int serialNumber = 0;
      m_value = ++serialNumber;
    }

    ValueBadCall operator !()
    {
      return -1 - m_value;
    }
  };


  class ValueBadAssignment: public Value
  {
  public:
    ValueBadAssignment( int value =0 ) : Value( value ) {}

    ValueBadAssignment operator !()
    {
      return -1 - m_value;
    }

    ValueBadAssignment &operator =( const ValueBadAssignment &other )
    {
      ++m_value;
      return *this;
    }
  };



  OrthodoxTest( const OrthodoxTest &copy );
  void operator =( const OrthodoxTest &copy );

  void checkSuccess();
  void checkFailure();

private:
  CppUnit::TestResult *m_result;
};



#endif  // ORTHODOXTEST_H
