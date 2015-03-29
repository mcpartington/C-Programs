#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream> 
using namespace std;

class Person
{
	friend class University;
	protected:
		string name;
		string email;
		string address;
		string dateOfBirth;
		string gender;
	public:
		Person(){name = email = address = dateOfBirth = gender = " ";};
		Person(string pName, string pEmail, string pAddress, string pDOB, string pGender);
		~Person();		
};
#endif
