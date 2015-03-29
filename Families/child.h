//-----------------------------------CHILD-------------------------------------
// Purpose: The purpose of this header file is that is is used to create a new
// object of type Child when called upon. It uses the Person class for it's 
// basic attributes. 
// Description: When a new child is created, this header is used and then 
// attached to the appropriate Wifer (mother) class. 
// Author: Maxwell C. Partington
// Author ID: 001254900
// Email: mcpartington@gmail.com
// Date: 12/1/12
//-----------------------------------------------------------------------------

#ifndef CHILD_H
#define CHILD_H

#include <string>
using namespace std;

#include "person.h"

class Child;
typedef Child* childPtr;

//-----------------------------------------------------------------------------
class Child: public Person
{
	friend class Wife;
	friend class Family;
	protected:
		childPtr mySibling;
	public:
		Child(){SSN = 0; firstName = lastName = " "; mySibling = NULL;};
		Child(long id, string fName, string lName){SSN = id; firstName = fName; lastName = lName; mySibling = NULL;};
		~Child(){};
};//end Child
//-----------------------------------------------------------------------------
#endif
