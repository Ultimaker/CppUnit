#ifndef CPPUNIT_OUTPUTTER_H
#define CPPUNIT_OUTPUTTER_H

#include <cppunit/Portability.h>


namespace CppUnit
{

/*! This class represents an abstract outputter.
 */
class Outputter
{
public:
  /// Destructor.
  virtual ~Outputter() {}

  virtual void write() =0;
};



// Inlines methods for Outputter:
// ------------------------------


} //  namespace CppUnit


#endif  // CPPUNIT_OUTPUTTER_H
