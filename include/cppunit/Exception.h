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

  class Exception : public std::exception
  {
    public:
      class Type
      {
      public:
        Type( std::string type ) : m_type ( type ) {}

        bool operator ==( const Type &other ) const
        {
          return m_type == other.m_type;
        }
      private:
        const std::string m_type;
      };


      Exception( std::string  message = "", 
                 long lineNumber = UNKNOWNLINENUMBER, 
                 std::string fileName = UNKNOWNFILENAME);
      Exception (const Exception& other);

      virtual ~Exception ();

      Exception& operator= (const Exception& other);

      const char *what() const throw ();

      long lineNumber ();
      std::string fileName ();

      static const std::string UNKNOWNFILENAME;
      static const long UNKNOWNLINENUMBER;

      virtual Exception *clone() const;

      virtual bool isInstanceOf( const Type &type ) const;

      static Type type();

    private:
      std::string m_message;
      long m_lineNumber;
      std::string m_fileName;
  };

} // namespace CppUnit

#endif // CPPUNIT_EXCEPTION_H

