#ifndef CPPUNIT_XMLTESTRESULTOUTPUTTER_H
#define CPPUNIT_XMLTESTRESULTOUTPUTTER_H

#include <cppunit/Portability.h>
#include <deque>
#include <iostream>
#include <map>
#include <utility>


namespace CppUnit
{

class Test;
class TestFailure;
class TestResult;


/*! This class ouputs a TestResult in XML format.
 */
class XmlTestResultOutputter
{
public:
  /*! Constructs a XmlTestResultOutputter object.
   */
  XmlTestResultOutputter();

  /// Destructor.
  virtual ~XmlTestResultOutputter();

  /*! Write the specified result as an XML document in the specified stream.
   *
   * Refer to examples/cppunittest/XmlTestResultOutputterTest.cpp for example
   * of use and XML document structure.
   *
   * \param result TestResult to write.
   * \param stream Output stream the result are wrote into.
   */
  void write( TestResult *result,
              std::ostream &stream );

  /*! This class represents an XML Element.
   * \warning This class will probably be replaced with an abstract
   * builder in future version.
   */
  class Node
  {
  public:
    Node( std::string elementName,
          std::string content ="" );
    Node( std::string elementName,
          int numericContent );
    virtual ~Node();

    void addAttribute( std::string attributeName,
                       std::string value );
    void addAttribute( std::string attributeName,
                       int numericValue );
    void addNode( Node *node );

    std::string toString() const;

  private:
    typedef std::pair<std::string,std::string> Attribute;

    std::string attributesAsString() const;
    std::string escape( std::string value ) const;
    static std::string asString( int value );

  private:
    std::string m_name;
    std::string m_content;
    typedef std::deque<Attribute> Attributes;
    Attributes m_attributes;
    typedef std::deque<Node *> Nodes;
    Nodes m_nodes;
  };


  virtual void writeProlog( std::ostream &stream );
  virtual void writeTestsResult( TestResult *result, 
                                 std::ostream &stream );

  typedef std::map<Test *,TestFailure*> FailedTests;
  virtual Node *makeRootNode( TestResult *result );
  virtual Node *makeFailedTestsNode( FailedTests &failedTests, 
                                     TestResult *result );
  virtual Node *makeSucessfulTestsNode( FailedTests &failedTests, 
                                        TestResult *result );
  virtual Node *makeStatisticsNode( TestResult *result );
  virtual Node *makeFailedTestNode( Test *test,
                                    TestFailure *failure,
                                    int testNumber );
  virtual Node *makeSucessfulTestNode( Test *test, 
                                       int testNumber );
protected:
  void fillFailedTestsMap( TestResult *result, 
                           FailedTests &failedTests );

private:
  /// Prevents the use of the copy constructor.
  XmlTestResultOutputter( const XmlTestResultOutputter &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlTestResultOutputter &copy );

private:
};


}  // namespace CppUnit

#endif  // CPPUNIT_XMLTESTRESULTOUTPUTTER_H
