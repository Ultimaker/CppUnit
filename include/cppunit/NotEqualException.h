#ifndef NOTEQUALEXCEPTION_H
#define NOTEQUALEXCEPTION_H

#include <cppunit/Exception.h>


namespace CppUnit {


  class NotEqualException : public Exception
  {
  public:
    NotEqualException( std::string expected,
                       std::string actual, 
                       long lineNumber = UNKNOWNLINENUMBER, 
                       std::string fileName = UNKNOWNFILENAME );

    NotEqualException( const NotEqualException &other );


    virtual ~NotEqualException() throw();

    std::string expectedValue() const;

    std::string actualValue() const;

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
  };

}  // namespace CppUnit

#endif  // NOTEQUALEXCEPTION_H
