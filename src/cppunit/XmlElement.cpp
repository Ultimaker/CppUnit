#include <cppunit/tools/XmlElement.h>


namespace CppUnit
{

  
XmlElement::XmlElement( std::string elementName,
                        std::string content ) 
  : m_name( elementName )
  , m_content( content )
{
}

    
XmlElement::XmlElement( std::string elementName,
                        int numericContent )
  : m_name( elementName )
{
  m_content = asString( numericContent );
}


XmlElement::~XmlElement()
{
  Elements::iterator itNode = m_elements.begin();
  while ( itNode != m_elements.end() )
    delete *itNode++;
}


void 
XmlElement::addAttribute( std::string attributeName,
                          std::string value  )
{
  m_attributes.push_back( Attribute( attributeName, value ) );
}


void 
XmlElement::addAttribute( std::string attributeName,
                          int numericValue )
{
  addAttribute( attributeName, asString( numericValue ) );
}


void 
XmlElement::addNode( XmlElement *node )
{
  m_elements.push_back( node );
}


std::string 
XmlElement::toString( const std::string &indent ) const
{
  std::string element( indent );
  element += "<";
  element += m_name;
  if ( !m_attributes.empty() )
  {
    element += " ";
    element += attributesAsString();
  }
  element += ">";

  if ( !m_elements.empty() )
  {
    element += "\n";

    std::string subNodeIndent( indent + "  " );
    Elements::const_iterator itNode = m_elements.begin();
    while ( itNode != m_elements.end() )
    {
      const XmlElement *node = *itNode++;
      element += node->toString( subNodeIndent );
    }

    element += indent;
  }

  if ( !m_content.empty() )
  {
    element += escape( m_content );
    if ( !m_elements.empty() )
    {
      element += "\n";
      element += indent;
    }
  }

  element += "</";
  element += m_name;
  element += ">\n";

  return element;
}


std::string 
XmlElement::attributesAsString() const
{
  std::string attributes;
  Attributes::const_iterator itAttribute = m_attributes.begin();
  while ( itAttribute != m_attributes.end() )
  {
    const Attribute &attribute = *itAttribute++;
    attributes += attribute.first;
    attributes += "=\"";
    attributes += escape( attribute.second );
    attributes += "\"";
  }
  return attributes;
}


std::string 
XmlElement::escape( std::string value ) const
{
  std::string escaped;
  for ( int index =0; index < value.length(); ++index )
  {
    char c = value[index ];
    switch ( c )    // escape all predefined XML entity (safe?)
    {
    case '<': 
      escaped += "&lt;";
      break;
    case '>': 
      escaped += "&gt;";
      break;
    case '&': 
      escaped += "&amp;";
      break;
    case '\'': 
      escaped += "&apos;";
      break;
    case '"': 
      escaped += "&quot;";
      break;
    default:
      escaped += c;
    }
  }
  
  return escaped;
}

// should be somewhere else... Future CppUnit::String ?    
std::string 
XmlElement::asString( int value )
{
  OStringStream stream;
  stream << value;
  return stream.str();
}


} //  namespace CppUnit

