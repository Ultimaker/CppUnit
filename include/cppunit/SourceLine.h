#ifndef CPPUNIT_SOURCELINE_H
#define CPPUNIT_SOURCELINE_H

#include <cppunit/Portability.h>
#include <string>

/*! Constructs a SourceLine object initialized with the location where the macro is expanded.
 * Used to write your own assertion macros.
 * \see Asserter for example of usage.
 */
#define CPPUNIT_SOURCELINE() ::CppUnit::SourceLine( __FILE__, __LINE__ )


namespace CppUnit
{

/*! \class SourceLine
 * \brief This class represents the location of a line of text in a specified file.
 * Use the CPPUNIT_SOURCELINE macro to construct that object.
 *
 * Used to capture the failure location in assertion.
 *
 * \see Asserter.
 */
class CPPUNIT_API SourceLine
{
public:
  SourceLine();

  SourceLine( const std::string &fileName,
              int lineNumber );

  /// Destructor.
  virtual ~SourceLine();

  bool isValid() const;

  int lineNumber() const;

  std::string fileName() const;

  bool operator ==( const SourceLine &other ) const;
  bool operator !=( const SourceLine &other ) const;

private:
  std::string m_fileName;
  int m_lineNumber;
};


} // namespace CppUnit



#endif  // CPPUNIT_SOURCELINE_H
