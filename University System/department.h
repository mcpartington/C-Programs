#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Department
{
	friend class University;
	protected:
		long id;
		string name;
		string location;
		long chairID;
		static long nextDepartID;
	public:
		Department(){name = location = " "; chairID = 0; id = nextDepartID++;};
		Department(string dName, string dLocation, long dChair);
		~Department();
		void print() const;
};
#endif
