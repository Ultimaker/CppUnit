#ifndef CPPUNIT_TOOLS_XMLELEMENT_H
#define CPPUNIT_TOOLS_XMLELEMENT_H

#include <cppunit/Portability.h>

#if CPPUNIT_NEED_DLL_DECL
#pragma warning( push )
#pragma warning( disable: 4251 )  // X needs to have dll-interface to be used by clients of class Z
#endif

#include <deque>
#include <string>


namespace CppUnit
{

class XmlElement;

#if CPPUNIT_NEED_DLL_DECL
  template class CPPUNIT_API std::deque<XmlElement *>;
#endif


/*! A XML Element.
 */
class CPPUNIT_API XmlElement
{
public:
  XmlElement( std::string elementName,
              std::string content ="" );
  XmlElement( std::string elementName,
              int numericContent );
  virtual ~XmlElement();

  void addAttribute( std::string attributeName,
                     std::string value );
  void addAttribute( std::string attributeName,
                     int numericValue );
  void addNode( XmlElement *element );

  std::string toString( const std::string &indent = "" ) const;

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

  typedef std::deque<XmlElement *> Elements;
  Elements m_elements;
};



} //  namespace CppUnit


#if CPPUNIT_NEED_DLL_DECL
#pragma warning( pop )
#endif


#endif  // CPPUNIT_TOOLS_XMLELEMENT_H
