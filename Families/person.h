//---------------------------------PERSON--------------------------------------
// Purpose: The purpose of this header file is to create a superclass for the 
// the classes "Husband" "Wife" and "Child". Each of which share the same basic
// attributes of a person. 
// Descripton: The classes "Husband" "Wife" and "Child" each call this header
// and create a new object of themselves with the basic information provided
// in this class. 
// Author: Maxwell C. Partington
// Author ID: 001254900
// Email: mcpartington@gmail.com
// Date: 12/1/12
//-----------------------------------------------------------------------------

#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

//-----------------------------------------------------------------------------
class Person
{
	friend class Family;
	friend class Husband;
	friend class Wife;
	friend class Child;

	protected:
		long SSN;
		string firstName;
		string lastName;
	
	public:
		Person(){SSN = 0; firstName = lastName = " ";}
		Person(long pSSN, string fName, string lName);
};//end person
//-----------------------------------------------------------------------------
#endif
