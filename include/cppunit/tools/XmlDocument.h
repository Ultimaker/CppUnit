#ifndef CPPUNIT_TOOLS_XMLDOCUMENT_H
#define CPPUNIT_TOOLS_XMLDOCUMENT_H

#include <cppunit/Portability.h>

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#endif

#include <string>


namespace CppUnit
{

class XmlElement;


/*! A XML Document.
 *
 * A XmlDocument represents a XML file. It holds a pointer on the root XmlElement
 * of the document. It also holds the encoding and style sheet used.
 */
class CPPUNIT_API XmlDocument
{
public:
  /*! Constructs a XmlDocument object.
   * \param encoding Encoding used in the XML file (default is Latin-1, ISO-8859-1 ). 
   */
  XmlDocument( const std::string &encoding = "",
               const std::string &styleSheet = "" );

  /// Destructor.
  virtual ~XmlDocument();

  std::string encoding() const;
  void setEncoding( const std::string &encoding = "" );
  
  std::string styleSheet() const;
  void setStyleSheet( const std::string &styleSheet = "" );

  void setRootElement( XmlElement *rootElement );
  XmlElement &rootElement() const;

  std::string toString() const;

private:
  /// Prevents the use of the copy constructor.
  XmlDocument( const XmlDocument &copy );

  /// Prevents the use of the copy operator.
  void operator =( const XmlDocument &copy );

protected:
  std::string m_encoding;
  std::string m_styleSheet;
  XmlElement *m_rootElement;
};


#if CPPUNIT_NEED_DLL_DECL
#pragma warning( pop )
#endif


} //  namespace CppUnit


#endif  // CPPUNIT_TOOLS_XMLDOCUMENT_H
