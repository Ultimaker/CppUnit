#ifndef CPPUNIT_XMLTESTRESULTOUTPUTTER_H
#define CPPUNIT_XMLTESTRESULTOUTPUTTER_H

#include <cppunit/Portability.h>
#include <cppunit/Outputter.h>
#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <utility>


namespace CppUnit
{

class Test;
class TestFailure;
class TestResultCollector;


/*! Outputs a TestResultCollector in XML format.
 */
class XmlOutputter : public Outputter
{
public:
  /*! Constructs a XmlOutputter object.
   */
  XmlOutputter( TestResultCollector *result,
                std::ostream &stream,
                std::string encoding = "ISO-8859-1" );

  /// Destructor.
  virtual ~XmlOutputter();

  /*! Write the specified result as an XML document in the specified stream.
   *
   * Refer to examples/cppunittest/XmlOutputterTest.cpp for example
   * of use and XML document structure.
   *
   * \param result TestResult to write.
   * \param stream Output stream the result are wrote into.
   */
  virtual void write();

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


  virtual void writeProlog();
  virtual void writeTestsResult();

  typedef std::map<Test *,TestFailure*> FailedTests;
  virtual Node *makeRootNode();
  virtual void addFailedTests( FailedTests &failedTests,
                               Node *rootNode );
  virtual void addSucessfulTests( FailedTests &failedTests,
                                  Node *rootNode );
  virtual void addStatistics( Node *rootNode );
  virtual void addFailedTest( Test *test,
                              TestFailure *failure,
                              int testNumber,
                              Node *testsNode );
  virtual void addFailureLocation( TestFailure *failure,
                                   Node *testNode );
  virtual void addSucessfulTest( Test *test, 
                                 int testNumber,
                                 Node *testsNode );
protected:
  virtual void fillFailedTestsMap( FailedTests &failedTests );

protected:
  TestResultCollector *m_result;
  std::ostream &m_stream;
  std::string m_encoding;

private:
  /// Prevents the use of the copy constructor.
  XmlOutputter( const XmlOutputter &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlOutputter &copy );

private:
};


}  // namespace CppUnit

#endif  // CPPUNIT_XMLTESTRESULTOUTPUTTER_H
