#ifndef CPPUNIT_EXTENSIONS_TESTPLUGINSUITE_H
#define CPPUNIT_EXTENSIONS_TESTPLUGINSUITE_H

#include <cppunit/TestComposite.h>
#if !defined(CPPUNIT_NO_TESTPLUGIN)

#include <cppunit/plugin/TestPlugIn.h>

namespace CppUnit
{

class DynamicLibraryManager;


/*! \brief A suite that wrap a test plug-in.
 * \ingroup WritingTestPlugIn
 */
class TestPlugInSuite : public TestComposite
{
public:
  /*! Constructs a TestPlugInSuite object.
   */
  TestPlugInSuite( const std::string &libraryFileName );

  /// Destructor.
  virtual ~TestPlugInSuite();

  int getChildTestCount() const;

protected:
  Test *doGetChildTestAt( int index ) const;

  /// Prevents the use of the copy constructor.
  TestPlugInSuite( const TestPlugInSuite &copy );

  /// Prevents the use of the copy operator.
  void operator =( const TestPlugInSuite &copy );

private:
  /// Manager for the dynamic library.
  DynamicLibraryManager *m_library;
  /// Interface returned by the plug-in.
  CppUnitTestPlugIn *m_interface;
  /// Suite returned by the plug-in.
  Test *m_librarySuite;
};


} //  namespace CppUnit


#endif // !defined(CPPUNIT_NO_TESTPLUGIN)

#endif  // CPPUNIT_EXTENSIONS_TESTPLUGINSUITE_H
