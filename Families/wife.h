//--------------------------------------WIFE-----------------------------------
// Purpose: The purpose of this header file is to create a new object of wife.
// That object is then attacthed to the Husband class, and this class has 
// objects of Child attached to it. 
// Description: This header is called when a new wife is created and a new 
// object is then created. 
// Author: Maxwell C. Partington
// Author ID: 001254900
// Email: mcpartington@gmail.com
// Date: 12/1/12
//-----------------------------------------------------------------------------

#ifndef WIFE_H
#define WIFE_H

#include <string>
using namespace std;

#include "person.h"

class Child;
typedef Child* childPtr;

//-----------------------------------------------------------------------------
class Wife: public Person
{
	friend class Child;
	friend class Family;
	protected:
		childPtr myChildren;
	public:
		Wife(){SSN = 0; firstName = lastName = " "; myChildren = NULL;}
		Wife(long id, string fName, string lName){SSN = id; firstName = fName; lastName = lName; myChildren = NULL;}
		~Wife(){};
};//end Wife
//-----------------------------------------------------------------------------
#endif
