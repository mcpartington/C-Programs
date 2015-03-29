#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "person.h"

class Faculty: public Person
{
	friend class University;
	protected:
		long id;
		//string name;
		//string email;
		//string address;
		//string dateOfBirth;
		//string gender;
		float salary;
		int yearOfExp;
		long departID;
		static long nextFacultyID;
	public:
		Faculty():Person(){/*name = email = address = dateOfBirth = gender = " ";*/ salary = 0; yearOfExp = 0; departID = 0; id = nextFacultyID++;}; 
		Faculty(string fName, string fEmail, string fAddress, string fDateOfBirth, string fGender, float fSalary, int fYearOfExp, long departID);
		~Faculty();
		void print() const;
};
#endif
