#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include "person.h"
#include "course.h"

class Student: public Person
{
	friend class University;
	protected:
		long id; 
		//string name;
		//string email;
		//string address;
		//string dateOfBirth;
		//string gender;
		int yearOfStudy;
		string major;
		long advisorID;
		vector <Course> coursesTaken;
		long static nextStId;
	public:
		Student(string sName, string sEmail, string sAddress, string sDOB, string sGender, int YOS, string sMajor, long sAdvisorID);
		Student():Person(){id  = nextStId++; major = " "; yearOfStudy = 0; advisorID = 0;};
		~Student();
		void print() const;
};
#endif
