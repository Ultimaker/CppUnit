#ifndef CPPUNIT_EXCEPTION_H
#define CPPUNIT_EXCEPTION_H

#include <cppunit/Portability.h>
#include <cppunit/Message.h>
#include <cppunit/SourceLine.h>
#include <exception>


namespace CppUnit {

/*! \brief Exceptions thrown by failed assertions.
 * \ingroup BrowsingCollectedTestResult
 *
 * Exception is an exception that serves
 * descriptive strings through its what() method
 */
class CPPUNIT_API Exception : public std::exception
{
public:

  class Type
  {
  public:
    Type( std::string type ) : m_type ( type ) 
    {
    }

    bool operator ==( const Type &other ) const
    {
	return m_type == other.m_type;
    }

  private:
    const std::string m_type;
  };


  /*! Constructs the exception with the specified message and source location.
   * \param message Message associated to the exception.
   * \param sourceLine Source location related to the exception.
   */
  Exception( const Message &message = Message(), 
	     const SourceLine &sourceLine = SourceLine() );

#ifdef CPPUNIT_ENABLE_SOURCELINE_DEPRECATED
  /*!
   * \deprecated Use other constructor instead.
   */
  Exception( std::string  message, 
	     long lineNumber, 
	     std::string fileName );
#endif

  /*! Constructs a copy of an exception.
   * \param other Exception to copy.
   */
  Exception( const Exception &other );

  /// Destructs the exception
  virtual ~Exception() throw();

  /// Performs an assignment
  Exception &operator =( const Exception &other );

  /// Returns descriptive message
  const char *what() const throw();

  /// Location where the error occured
  SourceLine sourceLine() const;

  /// Message related to the exception.
  Message message() const;

#ifdef CPPUNIT_ENABLE_SOURCELINE_DEPRECATED
  /// The line on which the error occurred
  long lineNumber() const;

  /// The file in which the error occurred
  std::string fileName() const;

  static const std::string UNKNOWNFILENAME;
  static const long UNKNOWNLINENUMBER;
#endif

  /// Clones the exception.
  virtual Exception *clone() const;
  
  /// Tests if the exception is an instance of the specified type.
  virtual bool isInstanceOf( const Type &type ) const;

  /// Type of this exception.
  static Type type();

protected:
  // VC++ does not recognize call to parent class when prefixed
  // with a namespace. This is a workaround.
  typedef std::exception SuperClass;

  Message m_message;
  SourceLine m_sourceLine;
  std::string m_whatMessage;
};


} // namespace CppUnit

#endif // CPPUNIT_EXCEPTION_H

