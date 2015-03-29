//----------------------------------HUSBAND------------------------------------
// Purpose: The purpose of this header file is to create a new object of type
// Husband when it is called.
// Description: When this header is called, an object Husband is created and 
// is then used to attach the wife, and children to it. It is then added to the 
// node list.
// Author: Maxwell C. Partington
// Author ID: 001254900
// Date: 12/1/12
//-----------------------------------------------------------------------------

#ifndef HUSBAND_H
#define HUSBAND_H

#include <string>
using namespace std;

#include "person.h"

class Husband; 
typedef Husband* husbandPtr;
class Wife; 
typedef Wife* wifePtr;
class Child;
typedef Child* childPtr;

//-----------------------------------------------------------------------------
class Husband: public Person
{
	friend class Family;
	protected:
		husbandPtr	nextFamily;
		wifePtr		myWife;

	public:
		Husband(){SSN = 0; firstName = lastName = " "; nextFamily = NULL; myWife = NULL;}
		Husband(long id, string fName, string lName){SSN = id; firstName = fName; lastName = lName; nextFamily = NULL;  myWife = NULL;}
		~Husband(){};
};//end Husband
//-----------------------------------------------------------------------------
#endif
