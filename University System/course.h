#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Course
{
	friend class University;
	protected:
		long CRN;
		int maxAvailableSeats;
		string name;
		long departID;
		long assignedSeats;
		long isTaughtBy;
		static long nextCRN;
	public:
		Course(){CRN = nextCRN++; departID =  assignedSeats = isTaughtBy = 0;  maxAvailableSeats = 0;  name = " ";};
		Course(string courseName, long courseDepartID /*long courseAssignedSeats*/, long courseIsTaughtBy, int courseMaxSeats);
		~Course();
		void print() const;
};
#endif
