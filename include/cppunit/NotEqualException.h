#ifndef NOTEQUALEXCEPTION_H
#define NOTEQUALEXCEPTION_H

#include <cppunit/Exception.h>


namespace CppUnit {


class CPPUNIT_API NotEqualException : public Exception
{
public:
  NotEqualException( std::string expected,
                     std::string actual, 
                     SourceLine sourceLine = SourceLine(),
                     std::string additionalMessage = "" );

#ifdef CPPUNIT_ENABLE_SOURCELINE_DEPRECATED
  NotEqualException( std::string expected,
                     std::string actual, 
                     long lineNumber, 
                     std::string fileName );
#endif

  NotEqualException( const NotEqualException &other );


  virtual ~NotEqualException() throw();

  std::string expectedValue() const;

  std::string actualValue() const;

  std::string additionalMessage() const;

  /*! Copy operator.
   * @param other Object to copy.
   * @return Reference on this object.
   */
  NotEqualException &operator =( const NotEqualException &other );

  Exception *clone() const;

  bool isInstanceOf( const Type &type ) const;

  static Type type();

private:
  std::string m_expected;
  std::string m_actual;
  std::string m_additionalMessage;
};

}  // namespace CppUnit

#endif  // NOTEQUALEXCEPTION_H
