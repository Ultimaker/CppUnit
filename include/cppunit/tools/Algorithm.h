#ifndef CPPUNIT_TOOLS_ALGORITHM_H_INCLUDED
#define CPPUNIT_TOOLS_ALGORITHM_H_INCLUDED

#include <cppunit/Portability.h>

CPPUNIT_NS_BEGIN

template<class SequenceType, class ValueType>
void
removeFromSequence( SequenceType &sequence, 
                    const ValueType &valueToRemove )
{
   SequenceType::iterator it = sequence.begin();
   SequenceType::iterator itEnd = sequence.end();
   while ( it != itEnd )
   {
      if ( *it == valueToRemove )
         it = sequence.erase( it );
      else
         ++it;
   }
}

CPPUNIT_NS_END


#endif // CPPUNIT_TOOLS_ALGORITHM_H_INCLUDED