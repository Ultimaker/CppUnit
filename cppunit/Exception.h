#ifndef CPPUNIT_EXCEPTION_H
#define CPPUNIT_EXCEPTION_H

#include <exception>
#include <string>

namespace CppUnit {

  /** 
   * Exception is an exception that serves
   * descriptive strings through its what() method
   *
   */

  class Exception : public exception
  {
    public:
      Exception (std::string  message    = "", 
        long         lineNumber = UNKNOWNLINENUMBER, 
        std::string  fileName   = UNKNOWNFILENAME);
      Exception (const Exception& other);

      virtual             ~Exception ();

      Exception&   operator= (const Exception& other);

      const char          *what() const throw ();

      long                lineNumber ();
      std::string         fileName ();

      static const std::string UNKNOWNFILENAME;
      static const int  UNKNOWNLINENUMBER;

    private:
      std::string         m_message;
      long                m_lineNumber;
      std::string         m_fileName;

  };

} // namespace CppUnit

#endif // CPPUNIT_EXCEPTION_H

