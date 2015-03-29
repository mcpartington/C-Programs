// Assignment #3
// Purpose of program: The purpose of this program designed to recieve a text 
// file as input and which then manipulates certain codes located inside of
// that file.   
// Inputs required for program: A text file with the correct commands.
// Outputs produced by program: This program lists the courses, students and 
// faculty information when it is called.
// Description of program: The text file contains 17 commands that the
// program and with those commands it  processes the informations of various 
// courses, faculty members and students of a university. It organizes the 
// courses, faculties, and students into vectors and outputs the correct 
// information when called.

// Date: 11/12/2012
// Author: Maxwell Partington 
// Student ID: 001254900
// Email: mcpartington@gmail.com

//----------------------------------------------------------------------------
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Inclusion of header files
//----------------------------------------------------------------------------
#include "university.h"
#include "department.h"
#include "course.h"
#include "person.h"
#include "student.h"
#include "faculty.h"
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
bool University::failure = false;
bool University::success = true;
long Department::nextDepartID = 100;
long Course::nextCRN = 200;
long Student::nextStId = 500;
long Faculty::nextFacultyID = 600;
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
University::University(){}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
University::~University(){}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Department::~Department(){}
Course::~Course(){}
Student::~Student(){}
Faculty::~Faculty(){}
Person::~Person(){}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Department::Department(string dName, string dLocation, long dChair)
{
	id = nextDepartID++;
	name = dName;
	location = dLocation;
	chairID = dChair;	
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Course::Course(string courseName, long courseDepartID, long courseIsTaughtBy,
							 int courseMaxSeats)
{
	CRN = nextCRN++;
	maxAvailableSeats = courseMaxSeats;
	name = courseName;
	departID = courseDepartID;
	assignedSeats = 0;
	isTaughtBy = courseIsTaughtBy;
} 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Person::Person(string pName, string pEmail, string pAddress, string pDOB, string pGender)
{
	name = pName;
	email = pEmail;
	address = pAddress;
	dateOfBirth = pDOB;
	gender = pGender;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
Student::Student(string sName, string sEmail, string sAddress, string sDOB, 
		string sGender, int YOS, string sMajor, long sAdvisorID)
		:Person(sName,sEmail,sAddress,sDOB,sGender)
{
	id = nextStId++;
	yearOfStudy = YOS;
	major = sMajor;
	advisorID = sAdvisorID;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
Faculty::Faculty(string fName, string fEmail, string fAddress, string fDateOfBirth, string fGender, float fSalary, int fYearOfExp, long departmentID):Person(fName,fEmail,fAddress,fDateOfBirth,fGender)
{
	id  = nextFacultyID++;
	salary = fSalary;
	yearOfExp = fYearOfExp;
	departID = departmentID;
}
//----------------------------------------------------------------------------


//-----------------------------CREATENEWDEPARTMENT-----------------------------
// Purpose: This routine is designed to create a new department object. It then
// adds it to the department vector for the university.
// Date: 11/06/12
//----------------------------------------------------------------------------
bool University::CreateNewDepartment(string depName, string depLoc, long depChairId)
{
	bool valid; 
	valid = checkForValidity(depChairId);
	
	if (depChairId == 0)
	{
		Department newDept(depName, depLoc, depChairId);
		Departments.push_back(newDept);
		return (University::success);
	}
	else if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << depChairId << " is not a valid department chair ID number." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return University::failure;
	}
	
}//end CreateNewDepartment
//----------------------------------------------------------------------------

//----------------------------CHECKFORVALIDITY--------------------------------
// Purpose: This routine takes in a department chair ID as it's parameter and
// checks in the faculty vector to see if it is a valid department ID that is
// assigned to a faculty member.
// Date: 11/06/2012
//----------------------------------------------------------------------------
bool University::checkForValidity(long depChairId)
{
	for (int i = 0; i < Faculties.size(); i++)
		{
			if (Faculties[i].departID == depChairId)
			{
				return (University::success);
			}
		}
	return (University::failure);	
}//end checkForValidity
//----------------------------------------------------------------------------

//----------------------------REMOVEADEPARTMENT-------------------------------
// Purpose: This routine is designed to remove a department from the 
// department vector and the university itself. It takes in a department ID as
// it's parameter and uses it to make sure it is a valid deparment, to make
// sure no one is teaching or taking the course before it is removed. 
// Local variables: The local variables in this routine are used to check if 
// anyone is dependent on the department. If anyone is teaching the course, or
// is taking it, the course will not be removed, else it will. depName gets 
// the name of the department which is used in countStudent to see if anyone 
// is taking the course. 
// Date: 11/06/12 
//----------------------------------------------------------------------------
bool University::RemoveADepartment(long depId)
{
	string depName = getDeptName(depId);
	bool valid = checkValidDept(depId);
	int countS = countStudent(depName);
	int countF = countFacId(depId);
	int countC = countCourse(depId);
	if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << depId << " is an invalid department ID." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------	
	else if (countF > 0)
	{
		cout << "\n--------------------------------------------------------------";
		cout << "ERROR: The department has" << countF << "employees and cannot be deleted.";
		cout << "--------------------------------------------------------------";
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (countC > 0)
	{
		cout << "\n--------------------------------------------------------------";
		cout << "ERROR: The department" << depId << "still offers" << countC << "courses and cannot be removed."<< endl;
		cout << "--------------------------------------------------------------";
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (countS > 0)
	{
		cout << "\n--------------------------------------------------------------";
		cout << "ERROR: " << countS << " majors exist in " << depName << " and cannot be removed." << endl;
		cout << "--------------------------------------------------------------";
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else 
	{	
		 for(int i = 0; i < Departments.size(); i++)
                                {
				if (Departments[i].id == depId)
                                        {
                                        Departments.erase(Departments.begin() + i);
                                        return (University::success);
                                        }
                                }
	}
}//end RemoveADepartment
//----------------------------------------------------------------------------


//------------------------------COUNTFACID------------------------------------
// Purpose: This routine is designed to count the number of faculty members in 
// a department. 
// Date: 11/06/12
//----------------------------------------------------------------------------
int University::countFacId(long depId)
{
	int count = 0;
	for (int i = 0; i < Faculties.size(); i++)
	{
		if (Faculties[i].departID == depId)
			count++;
	}
	return (count);
}//end countFacId
//----------------------------------------------------------------------------

//------------------------------COUNTCOURSE-----------------------------------
// Purpose: This routine is designed to count the number of courses in a 
// department. 
// Date: 11/06/12 
//----------------------------------------------------------------------------
int University::countCourse(long depId)
{	
	int count = 0;
	for (int i = 0; i < Courses.size(); i++)
	{
		if (Courses[i].departID == depId)
			count++;
	}
	return (count);
}// end countCourse
//----------------------------------------------------------------------------

//-------------------------------GETDEPTNAME----------------------------------
// Purpose: This routine is designed to retrieve the department name of the
// corresponding department ID passed in as a parameter. 
// Date: 11/07/12
//----------------------------------------------------------------------------
string University::getDeptName(long depId)
{	
	string deptName = " ";
	for (int i = 0; i < Departments.size(); i++)
	{
		if (Departments[i].id == depId)
			deptName = Departments[i].name;
	}
	return (deptName);
}//end getDeptName
//----------------------------------------------------------------------------

//-------------------------------COUNTSTUDENT---------------------------------
// Purpose: This routine is designed to count the number of students whose 
// majors are corresponding with the department name passed in as a parameter.
// Date: 11/08/12
//----------------------------------------------------------------------------
int University::countStudent(string depName)
{	
	int count = 0;
	for (int i = 0; i < Students.size(); i++)
	{
		if (Students[i].major == depName)
			count++;
	}
	return (count);
}//end countStudent
//----------------------------------------------------------------------------


//------------------------------CREATENEWSTUDENT------------------------------
// Purpose: This routine is designed to create a new student object. That 
// object is then pushed into the students vector of the university.
// Parameters: The parameters passed into this routine are used to create 
// a new student object. The student major and advisor are first checked to 
// ensure that they are valid majors and an acutal advisors at the university. 
// Local variables: validMajor and validAdvisor call the appropriate functions
// which check to make sure is is a actual major and a acutal advisor.
// Date: 11/10/12
//----------------------------------------------------------------------------
bool University::CreateNewStudent(string sName, string sEmail, string sAddress,
			 string sDateOfBirth, string sGender, int sYearOfStudy, 
						string sMajor, long sAdvisorId)
{
	bool validMajor = checkValidMajor(sMajor);
	bool validAdvisor = checkValidAdvisor(sAdvisorId);
		//------------------------------------------------------------
		if (!validMajor)
			{
			cout << "\n-------------------------------------------------------------" << endl;
			cout << "ERROR: " << sMajor <<  " is not a valid major at this university." << endl;
			cout << "--------------------------------------------------------------" << endl;
			return (University::failure);
			}
		//------------------------------------------------------------
		else if	(!validAdvisor)
			{
			cout << "\n--------------------------------------------------------------" << endl;
			cout << "ERROR: " << sAdvisorId << " is not an advisor at this university." << endl;
			cout << "--------------------------------------------------------------" << endl;
			return (University::failure);
			}
		//------------------------------------------------------------
		else
			{
			Student newStudent(sName,sEmail,sAddress,sDateOfBirth,sGender,sYearOfStudy,sMajor,sAdvisorId);
			Students.push_back(newStudent);
			return (University::success);
			}
}//end createNewStudent
//----------------------------------------------------------------------------

//------------------------------CHECKVALIDMAJOR-------------------------------
// Purpose: The purpose of this routine is to check to make sure that the major
// declared by the student is acutally a major offerred at the university.
// Parameters: The parameter passed into this routine is the students major 
// and is used to search through the departments to make sure it is a valid 
// major.
// Date: 11/10/12
//----------------------------------------------------------------------------
bool University:: checkValidMajor(string major)
{
	for (int i = 0; i < Departments.size(); i++)
       	{
                if (Departments[i].name == major)
                {
                        return (University::success);
                }
        }
      	return (University::failure);
        
}//end checkValidMajor
//----------------------------------------------------------------------------

//------------------------------CHECKVALIDADVISOR-----------------------------
// Purpose: The purpose of this routine is to make sure that the advisor used
// to create the new student object is an actual faculty member at the 
// university. 
// Parameters: The parameter passed into the function is the advisor ID of the
// faculty member who is advising the student. 
// Date: 11/10/12
//----------------------------------------------------------------------------
bool University:: checkValidAdvisor(long advisorId)
{
	// check in assigned faculty for advisor 
	for (int i = 0; i < Faculties.size(); i++)
        {
                if (Faculties[i].id == advisorId)
                {
                        return (University::success);
                }
        }
        return(University::failure);
}//end checkValidAdvisor
//----------------------------------------------------------------------------

//-----------------------------REMOVEASTUDENT---------------------------------
// Purpose: The purpose of this routine is remove a student from the student
// vector and the university. It uses in the passed in ID to search for the
// student and remove them. 
// Parameters: The parameters passed into this routine is the student's ID 
// who is to be removed from the student vector. 
// Local Variables: The local variable valid is used to call the function
// checkValidSt which takes the student's ID and returns true or false,
// depending on if the student exsists or not. 
// Date: 11/10/12
//----------------------------------------------------------------------------
bool University::RemoveAStudent(long sStId)
{
	bool valid = checkValidSt(sStId);
	if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << sStId << " is not a valid student ID." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else 
	{
		for (int i = 0; i < Students.size(); i++)
		{
			if (Students[i].id == sStId)
			{	
				
				Students.erase(Students.begin() + i);			
				return (University::success);
			}
		}	
	}	
}//end RemoveAStudent
//----------------------------------------------------------------------------

//---------------------------------CHECKVALIDST-------------------------------
// Purpose: The purpose of this routine is to make sure the student is a valid
// student at the university. If the student is in the student vector, the 
// the routine returns true, else it returns false. 
// Parameters: The parameter is the students ID and is used to search through
// the student vector. 
// Date: 11/10/12
//----------------------------------------------------------------------------
bool University::checkValidSt(long stId)
{
	for (int i = 0; i < Students.size(); i++)
	{
		if (Students[i].id == stId)
		{
			return (University::success);
		}
	}
	return (University::failure);	
}//end CheckStValidity
//----------------------------------------------------------------------------

//---------------------------------CREATENEWCOURSE----------------------------
// Purpose: The function of this routine is to create a new course in the 
// university and add it to the courses vector. 
// Parameters: The parameters of this function are the information required to
// create a new course. 
// Local Variables: The local variables: validFaculty and validDept, are both
// used to make sure that the faculty teaching the course, and the department
// the course is being added to is a valid department at the university.
// Date: 11/12/12
//----------------------------------------------------------------------------
bool University::CreateNewCourse(string cName, long cDepId, long cTaughtBy, 
								int cMaxSeat)
{ 
	bool validFaculty = checkValidFaculty(cTaughtBy);
	bool validDept = checkValidDept(cDepId);
	//--------------------------------------------------------------------
	if (cTaughtBy == 0)
	{
		Course newCourse(cName, cDepId, cTaughtBy, cMaxSeat);
		Courses.push_back(newCourse);
		return (University::success);
	}
	//--------------------------------------------------------------------
	else if (!validFaculty)
	{
		cout << "\n--------------------------------------------------------------" << endl; 
		cout << "ERROR: " << cTaughtBy << " is not an existing faculty member at this university."  << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (!validDept)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << cDepId << " is not an existing department at this university." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------	
	else 
	{
		Course newCourse(cName, cDepId, cTaughtBy, cMaxSeat);
		Courses.push_back(newCourse);
		return (University::success);
	}
}// end CreateNewCourse
//----------------------------------------------------------------------------

//-------------------------------CHECKVALIDDEPT-------------------------------
// Purpose: The purpose of this routine to make sure that the department ID 
// passed into this function matches to an existing corresponding department. 
// Parameters: The parameter for this function is a department ID which is
// then used to search for the department vector. If it matches an ID in the 
// vector, the routine returns true, else it returns false.
// Date: 11/12/12
//----------------------------------------------------------------------------
bool University::checkValidDept(long deptId)
{
	for (int i = 0; i < Departments.size(); i++)
	{
		if (Departments[i].id == deptId)
		{
			return (University::success);
		}
	}
	return (University::failure);
}//end checkValidDept
//----------------------------------------------------------------------------

//----------------------------CHECKVALIDFACULTY-------------------------------
// Purpose: The purpose of this routine is to make sure that the faculty ID 
// passed into this function matches to an existing corresponding faculty
// member. 
// Parameters: The parameter for this function is a faculty ID which is then 
// used to search through the faculty vector. If it matches and ID in the
// vector, the routine returns true, else it returns false. 
// Date: 11/12/12
//----------------------------------------------------------------------------
bool University::checkValidFaculty(long facId)
{
	for (int i = 0; i < Faculties.size(); i++)
	{
		if (Faculties[i].id == facId)
			return (University::success);
	}//end for 
	return (University::failure);
}//end checkValidFaculty
//----------------------------------------------------------------------------

//--------------------------------REMOVEACOURSE-------------------------------
// Purpose: The purpose of this routine is to remove a course from the course
// vector and the university.  The CRN is then used to make sure it is a valid
// course, then it is used to search through the courses vector and is then
// removed if no student is teaching the course. 
// Parameters: The parameter passed into this routine is a course CRN.
// Local Variables: The local variable validCourse is used to call the 
// routine checkValidCourse which makes sure the course is valid.
// Date: 11/13/12
//----------------------------------------------------------------------------
bool University::RemoveACourse(long cCRN)
{
	bool validCourse = checkValidCourse(cCRN);
	if (!validCourse)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << cCRN << " is not an existing course at this university." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else
		for(int i = 0; i < Courses.size(); i++)
		{
			//----------------------------------------------------
			if (Courses[i].assignedSeats > 0)
			{	
				cout << "\n--------------------------------------------------------------" << endl;
				cout << "ERROR: " << cCRN << " has " << Courses[i].assignedSeats << " students taking the course and cannot be removed." << endl;
				cout << "--------------------------------------------------------------" << endl;
				return (University::failure);
			}
			//----------------------------------------------------
			else if (Courses[i].CRN == cCRN)
			{
				Courses.erase(Courses.begin() + i);			
				return (University::success);
			}
			//----------------------------------------------------
		}//end for	
}//end RemoveACourse
//----------------------------------------------------------------------------

//------------------------------CHECKVALIDCOURSE------------------------------
// Purpose: The purpose of this routine is to make sure the course is valid
// and exists at the university. The parameter is used to search through 
// the courses vector and make sure it is valid. If the CRN matches the CRN
// of one of the courses in the courses vector, it returns true. Else it 
// returns false. 
// Parameters: The parameter of this routine is a course CRN.
// Date: 11/12/12
//----------------------------------------------------------------------------
bool University::checkValidCourse(long CRN)
{
	for (int i = 0; i < Courses.size(); i++)
	{
		if (Courses[i].CRN == CRN)
			return (University::success);
	}//end for
	return (University::failure);
			
}//end checkValidCourse
//----------------------------------------------------------------------------

//------------------------------CREATENEWFACULTY------------------------------
// Purpose: The purpose of this routine is to create a new faculty member at
// the university and add it to the faculties vector. 
// Parameters: The parameters of this routine are all the pieces of 
// information required to create a new faculty member. 
// Local Variables: The local variable validFDeptId calls the function 
// checkValidDept which makes sure the department the faculty member is being
// added to exsists.
// Date: 11/12/12
//----------------------------------------------------------------------------
bool University::CreateNewFaculty(string fName, string fEmail, string fAddress, 
	string fDateOfBirth, string fGender, float fSalary, int fYearOfExp, 
								   long fDepId)
{
	bool validFDeptId =  checkValidDept(fDepId);
	if (!validFDeptId)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << fDepId << " is not a valid department." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}	
	else 
	{
		Faculty newFaculty(fName, fEmail, fAddress, fDateOfBirth, fGender, fSalary, fYearOfExp, fDepId);
		Faculties.push_back(newFaculty); 
		return (University::success);
	}
}//end CreateNewFaculty
//----------------------------------------------------------------------------

//--------------------------------REMOVEAFACULTY------------------------------
// Purpose: The purpose of this routine is to remove a faculty member from the 
// university and the faculties vector. It uses the parameter passed in to 
// make sure the faculty member is valid, not teaching a course, not advising
// a student, and not chairing a department. If all of the above are true, the
// faculty member is removed from the vector.  
// Parameters: The parameter passed in is a faculty ID.
// Local Variables: The local variables in this routine are used to call 
// checkValidFaculty which validates if it is an acutal faculty member. 
// Date: 11/13/12
//----------------------------------------------------------------------------
bool University::RemoveAFaculty(long fFactId)
{
	bool validFFactId = checkValidFaculty(fFactId);
	//--------------------------------------------------------------------
	if (!validFFactId)
		{
			cout << "\n--------------------------------------------------------------" << endl;
			cout << "ERROR: " << fFactId << " is not a valid faculty ID." << endl;
			cout << "--------------------------------------------------------------" << endl;
			return (University::failure);
		}
	//--------------------------------------------------------------------
	else 
	{
		 for(int i = 0; i < Courses.size(); i++)
                 {
			//----------------------------------------------------
                 	if (Courses[i].isTaughtBy == fFactId)
			{
				cout << "\n--------------------------------------------------------------" << endl;
				cout << "ERROR: " << fFactId << " is teaching a course and cannot be removed." << endl;
				cout << "--------------------------------------------------------------" << endl;
				return (University::failure);
			}
			//----------------------------------------------------
			else if (Students[i].advisorID == fFactId)
			{
				cout << "\n--------------------------------------------------------------" << endl;
				cout << "ERROR: " << fFactId << " advising a student and cannot be removed." << endl;
				cout << "--------------------------------------------------------------" << endl;
				return (University::failure);
			}
			//----------------------------------------------------
			else if (Departments[i].chairID == fFactId) 
			{
				cout << "\n--------------------------------------------------------------" << endl;
                                cout << "ERROR: " << fFactId << " is chairing a deparment and cannot be removed." << endl;
				cout << "--------------------------------------------------------------" << endl;
                                return (University::failure);
			}
			//----------------------------------------------------
                        else if (Faculties[i].id == fFactId)
			{
                                Faculties.erase(Faculties.begin() + i);
                                return (University::success);
			}
			//----------------------------------------------------
		}
	}
}//end RemoveAFaculty
//----------------------------------------------------------------------------

//------------------------LISTCOURSESTAUGHTYBYFACULTY-------------------------
// Purpose: The purpose of this routine is to list all of the courses taught
// by a specific faulty member. This routine searchs through all the courses
// and if the attribute "isTaughtBy" matches the faculty ID passed into the
// routine, is it then printed out.
// Parameters: The parameter for this rountine is a faculty ID.
// Local Variables: The local variable valid is used to call the routine 
// checkValidFaculty which then makes sure the faculty member exists.
// Date: 11/13/12
//----------------------------------------------------------------------------
bool University::ListCoursesTaughtByFaculty(long facultyId)
{
	bool valid = checkValidFaculty(facultyId);
	if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << facultyId << " is not a valid faculty id." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else
	{
		cout << "\n-------------Courses taught by faculty " << facultyId << "--------------------" << endl;
		for (int j = 0; j < Courses.size(); j++)
		{	
			if (Courses[j].isTaughtBy == facultyId)
				Courses[j].print();
		}//end for
		cout << "--------------------------------------------------------------" << endl;
		return (University::success);
	}		
}//end ListCoursesTaughtByFaculty
//----------------------------------------------------------------------------

//-------------------------LISTCOURSESTAKENBYSTUDENT--------------------------
// Purpose: This routine is designed to list all the courses taken by a 
// specific student. It uses the passed in student ID to compare the ID to the
// ID in the student vector. When it finds a matching ID, it then prints out
// all of the courses taken by that student. 
// Parameters: The parameter passed into this routine is a student ID.
// Local Variables: The local variable valid is used to call the checkValidSt
// routine which then checks to make sure the student exsists. 
// Date: 11/16/12
//----------------------------------------------------------------------------
bool University::ListCoursesTakenByStudent(long studentId)
{
	bool valid = checkValidSt(studentId);
	if (!valid)
	{
		cout << "--------------------------------------------------------------" << endl;
		cout << "ERROR: " << studentId << " is not a valid student id." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else
	{
		cout << "\n-----------------Courses taken by student " << studentId << "-----------------" << endl;
		for (int i = 0; i < Students.size(); i++)
		{
			if (Students[i].id == studentId)
			{
				for (int j = 0; j < Students[i].coursesTaken.size(); j++)
				{
					cout << "\nCourse CRN: " << Students[i].coursesTaken[j].CRN << endl;
					cout << "      Name: " << Students[i].coursesTaken[j].name << endl;
				}
			}
		}//end for
		cout << "--------------------------------------------------------------\n" << endl;
	return (University::success);
	}
}//end ListCoursesTakenByStudent
//----------------------------------------------------------------------------

//--------------------------LISTFACULTIESINDEPARTMENT-------------------------
// Purpose: The purpose of this routine is to list all of the faculty members
// in a specific department. It uses the passed in department ID to compare
// it to the department ID's attached to all of the faculty members. Any 
// faculty with a matching department ID is then printed on the screen.
// Parameters: The parameter of this routine is a department ID number.
// Local Variables: The local variable valid is used to call the routine 
// checkValidDept which validates the department using the department ID. If 
// a matching department ID is found in the departments vector, valid is equal
// true, else it is false.
// Date: 11/16/12
//----------------------------------------------------------------------------
bool University::ListFacultiesInDepartment(long departId)
{
	bool valid = checkValidDept(departId);
	if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << departId << " is not a valid department." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else 
	{
		cout << "\n--------------Faculty members in department " << departId << "---------------" << endl;
		for (int i = 0; i < Faculties.size(); i++)
		{
			if (Faculties[i].departID == departId)
				{	
					Faculties[i].print();
				}
		}//end for
		cout << "\n--------------------------------------------------------------" << endl;
		return (University::success);
	}
}//end ListFacultiesInDepartment
//----------------------------------------------------------------------------

//---------------------------LISTSTUDENTSOFACULTY-----------------------------
// Purpose: The purpose of this routine is to list all of the students being
// advised by a specific faulty member. It uses the faculty ID passed in 
// and compares it to the attribute advisorID in the student object. If it is
// a match, the students information is printed on the screen
// Parameters: The parameters of this function is a faculty ID. 
// Local Variables: The local variable valid is used to call the routine
// checkValidFaculty which checks to make sure the faculty ID is attached to a
// valid faculty member. 
// Date: 11/16/12
//----------------------------------------------------------------------------
bool University::ListStudentsOfAFaculty(long facultyId)
{
	bool valid = checkValidFaculty(facultyId);
	if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << facultyId << " is not a valid faculty ID." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else 
	{
		cout  << "\n------------Students being advised by faculty " << facultyId << "-------------" << endl;
		for (int i = 0; i < Students.size(); i++)
		{
			if (Students[i].advisorID == facultyId)
				Students[i].print();
		}//end for 	
		cout << "\n--------------------------------------------------------------" << endl;
		return (University::success);
	}
}//end ListStudentsOfAFaculty
//----------------------------------------------------------------------------

//------------------------LISTCOURSESOFADEPARTMENT----------------------------
// Purpose: The purpose of this routine is list all of the courses in a 
// specific department. It uses the department ID passed in to compare it to 
// the attribute department ID in the course object, if it matches, then it is
// printed on the screen.
// Parameters: The parameters of this routine is a department ID.
// Local Variables: The local variable valid of this routine is used to call 
// the routine checkValidDept which checks to make the department ID is a valid
// department ID. 
// Date: 11/16/12
//----------------------------------------------------------------------------
bool University::ListCoursesOfADepartment(long departId)
{
	bool valid = checkValidDept(departId);
	if (!valid)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " <<  departId << " is not a valid department." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else
	{
		cout << "\n------------------Courses in department " << departId << "-------------------" << endl;
		for (int i = 0; i < Courses.size(); i++)
		{
			if (Courses[i].departID == departId)
					Courses[i].print();
		}//end for
		cout << "\n--------------------------------------------------------------" << endl;
	 		return (University::success);
	}
}//end ListCoursesOfADepartment
//----------------------------------------------------------------------------

//-------------------------ADDACOURSEFORASTUDENT------------------------------
// Purpose: The purpose of this routine is to add a course for a student. It 
// takes the course ID and student ID and puts the course corresponding to the
// course ID into the course taken vector in the student object,
// Parameters: The parameters of this routine are a course ID and student ID.
// Local Variables: The local variables validC, validS, and validSeats are used
// to call functions checkValidCourse, checkValidSt, and checkValidSeats to
// make sure they are existing courses, existing students and to make sure 
// there is enough seats in the class.
// Date: 11/16/12
//----------------------------------------------------------------------------
bool University::AddACourseForAStudent(long courseId, long stId)
{
	bool validC = checkValidCourse(courseId);
	bool validS = checkValidSt(stId);
	bool validSeats = checkValidSeats(courseId);
	//--------------------------------------------------------------------
	if (!validC)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << courseId << " is not a valid course." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (!validS)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << stId << " is not a valid student." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (!validSeats)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: There are not enough seats to add the student: " << stId << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else 
	{
		for (int i = 0; i < Courses.size(); i++)
		{
			if (Courses[i].CRN == courseId)
			{
				for (int j = 0; j < Students.size(); j++)
				{
					if (Students[j].id == stId)
					{
						Students[j].coursesTaken.push_back(Courses[i]);
						Courses[i].assignedSeats++;
					}
				}
			}
		}
	 	return (University::success);
	 //--------------------------------------------------------------------
	 }
}//end AddACourseForAStudent
//----------------------------------------------------------------------------

//------------------------------CHECKVALIDSEATS-------------------------------
// Purpose: The purpose of this routine is to make sure there is enough valid 
// seats in the class so that a student may add. If there are enough, this
// routine returns true, else it is false.
// Parameters: The parameter of this function is a course ID. 
// Date: 11/16/12
//----------------------------------------------------------------------------
bool University::checkValidSeats(long courseId)
{
	for (int i = 0; i < Courses.size(); i++)
	{
		if(Courses[i].CRN == courseId)
			if (Courses[i].assignedSeats < Courses[i].maxAvailableSeats)
				return (University::success);
	}
	return (University::failure);
}//end checkValidSeats
//----------------------------------------------------------------------------

//---------------------------DROPACOURSEFORSTUDENT----------------------------
// Purpose: The purpose of this routine is drop a student from a specific 
// course. It takes the course ID and student ID and checks to see which 
// student is taking the course which corresponds to the course ID passed in. 
// It then removes the student from the course.
// Parameters: The parameters for this routine are a course ID and a student ID.
// Local Variables: The local variables validC and validS call the routines
// checkValidCourse and checkValidSt which then checks to make sure that the
// course the student is to be removed from, and the student to drop the course
// for are valid and exist. 
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::DropACourseForAStudent(long courseId, long stId)
{
	bool validC = checkValidCourse(courseId);
	bool validS = checkValidSt(stId);
	if (!validC)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << courseId << " is not a valid course." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else if (!validS)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << stId << " is not a valid student." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	else
	{
		for (int j = 0; j < Students.size(); j++)
		{
			if (Students[j].id == stId)
			{
				for (int k = 0; k < Students[j].coursesTaken.size(); k++)
				{
					if (Students[j].coursesTaken[k].CRN == courseId)
					{
						Students[j].coursesTaken[k].assignedSeats--;
						Students[j].coursesTaken.erase(Students[j].coursesTaken.begin() + k);
					}
				}		
    			}
    		}
		return (University::success);
	}	
}//end DropACourseForAStudent	
//----------------------------------------------------------------------------

//-----------------------------ASSIGNDEPARTMENTCHAIR--------------------------
// Purpose: The purpose of this routine is to assign a faculty member to the 
// position of the department chair of a specific department. It takes the
// the parameters passed in, checks to see that they are valid and then 
// assigns the facultyId to the department chair ID.
// Parameters: The parameters passed in are a facultyId and a departId.
// Local Variables: The local variables call the routines checkValidFaculty 
// and checkValidDepartment which make sure the facultyId and departId exist
// at the university. 
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::AssignDepartmentChair(long facultyId, long departId)
{
	bool validF = checkValidFaculty(facultyId);
	bool validD = checkValidDept(departId);
	//-------------------------------------------------------------------
	if (!validF)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << facultyId << " is not a valid faculty ID." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (!validD)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << departId << " is not a valid department." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else 
	{
		for (int i = 0; i < Departments.size(); i++)
		{
			if(Departments[i].id == departId)
				Departments[i].chairID = facultyId;
		}
		 return (University::success);
	}
}//end AssignDepartmentChair
//----------------------------------------------------------------------------

//--------------------------ASSIGNINSTRUCTORTOCOURSE--------------------------
// Purpose: The purpose of this routine is to assign an instructor to a course.
// It takes the facultyId passed in and assigns it to the taughtBy attribute
// in the course. 
// Parameters: The parameters of this routine are a facultyId and a courseId. 
// Local Variables: validC and validF are variables that call functions to 
// make sure that the courseId and the facultyId are valid courses and faculty
// members at the university.
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::AssignInstructorToCourse (long facultyId, long courseId)
{	
	bool validC = checkValidCourse(courseId);
	bool validF = checkValidFaculty(facultyId);
	//--------------------------------------------------------------------
	if (!validC)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << courseId << " is not a valid course." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else if (!validF)
	{
		cout << "\n--------------------------------------------------------------" << endl;
		cout << "ERROR: " << facultyId << " is not a valid faculty ID." << endl;
		cout << "--------------------------------------------------------------" << endl;
		return (University::failure);
	}
	//--------------------------------------------------------------------
	else
	{
		for (int i = 0; i < Courses.size(); i++)
		{
			if (Courses[i].CRN == courseId)
				Courses[i].isTaughtBy = facultyId;
		}
		return (University::success);
	}
}//end AssignInstructorToCourse
//----------------------------------------------------------------------------

//----------------------------LISTDEPARTMENTS---------------------------------
// Purpose: The purpose of this routine is to print all the department ID's
// and the names of all the departments in the departments vector. 
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::ListDepartments()
{
	cout << "\n-------------------------Departments--------------------------" << endl;
	for (int i = 0; i < Departments.size(); i++)
		{
			cout << "\nDepartment ID: " << Departments[i].id << endl;
			cout << "         Name: " << Departments[i].name << endl; 
		}
	cout << "\n--------------------------------------------------------------" << endl;
}//end ListDepartments
//----------------------------------------------------------------------------

//------------------------------LISTSTUDENTS----------------------------------
// Purpose: The purpose of this routine is to print all of the ID's and the 
// names of the students in the students vector. 
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::ListStudents()
{
	cout << "\n-------------------------Students-----------------------------" << endl;
	for (int i = 0; i < Students.size(); i++)
		{
			cout <<"\nStudent ID: " << Students[i].id << endl;
			cout <<"      Name: " << Students[i].name << endl;
		}
	cout << "\n--------------------------------------------------------------" << endl;
}//end ListStudents
//----------------------------------------------------------------------------

//------------------------------- LISTCOURSES---------------------------------
// Purpose: The purpose of this routine is to print all of the CRN's and the 
// names of the courses in the courses vector.
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::ListCourses()
{
	cout << "\n-------------------------Courses------------------------------" << endl;
	for (int i = 0; i < Courses.size(); i++)
		{
			cout <<"\nCourse CRN: " << Courses[i].CRN << endl;
			cout <<"      Name: " << Courses[i].name << endl;
		}
	cout << "\n--------------------------------------------------------------" << endl;
}//end ListCourses
//----------------------------------------------------------------------------

//--------------------------------LISTFACULTIES-------------------------------
// Purpose: The purpose of this routine is to print all of the ID's and names 
// of the faculty members in the faculties vector.
// Date: 11/15/12 
//----------------------------------------------------------------------------
bool University::ListFaculties()
{
	cout << "\n-------------------------Faculty------------------------------" << endl;
	for (int i = 0; i < Faculties.size(); i++)
		{
			cout <<"\nFaculty ID: " << Faculties[i].id << endl;
			cout <<"      Name: " << Faculties[i].name << endl;
		}
	cout << "\n--------------------------------------------------------------" << endl;
}//end ListFaculties
//----------------------------------------------------------------------------

//-------------------------------COURSE::PRINT--------------------------------
// Purpose: The purpose of this routine is to print out all of the information 
// of a course.
// Date: 11/15/12
//----------------------------------------------------------------------------
void Course::print() const
{
	cout << "\nCRN: " << CRN << endl;
	cout << "Name: " << name << endl;
	cout << "Department ID: " << departID << endl;
	cout << "Taught by : " << isTaughtBy << endl;
	cout << "Max seats available: " << maxAvailableSeats << endl;
	cout << "Assigned seats: " << assignedSeats << endl;
}// end Course::print()
//----------------------------------------------------------------------------

//-------------------------------STUDENT::PRINT-------------------------------
// Purpose: The purpose of this routine is to print out all of the information
// of a student. 
// Date: 11/15/12
//----------------------------------------------------------------------------
void Student::print() const
{
	cout << "\nID: " << id << endl;
	cout << "Name: " << name << endl;
	cout << "Email: " << email << endl;
	cout << "Address: " << address << endl;
	cout << "Date of birth: " << dateOfBirth << endl;
	cout << "Gender: " << gender << endl;
	cout << "Year of study: " << yearOfStudy << endl;
	cout << "Major: " << major << endl;
}// end Student::print()
//----------------------------------------------------------------------------

//-------------------------------FACULTY::PRINT-------------------------------
// Purpose: The purpose of this routine is to print out all of the information
// of a faculty member.
// Date: 11/15/12
//----------------------------------------------------------------------------
void Faculty::print() const
{
	cout << "\nID: " << id << endl;
	cout << "Name: " << name << endl;
	cout << "Email: " << email << endl;
	cout << "Address: " << address << endl;
	cout << "Date of birth: " << dateOfBirth << endl;
	cout << "Gender: " << gender << endl;
	cout << "Salary: " << salary << endl;
	cout << "Years of experience: " << yearOfExp << endl;
	cout << "Department ID: " << departID << endl;
}// end Faculty::print()
//----------------------------------------------------------------------------

//-------------------------PROCESSTRANSACTIONFILE-----------------------------
// Purpose: The purpose of this routine is to process a file that is passed in
// which it then creates new objects based on the command on each line in the 
// file.
// Parameters: The parameter passed into this routine is a filename which is 
// then opened and processed. 
// Date: 11/15/12
//----------------------------------------------------------------------------
bool University::ProcessTransactionFile (string fileName)
{
	// Variable for the intial command on each line
	string command;

	// Variables for new department
	long deptId;
	string depName;
	string depLoc;
	long depChairId;

	// Variables for new person
	string name;
	string email;
	string address;
	string dateOfBirth;
	string gender;
	
	// Variables for new student
	long stId;
	string major;
	int yearOfStudy;
	long advisor;

	// Variables for new course
	long crn;
	long taughtBy;
	long maxSeat;
	
	// Variables for new faculty	
	long factId;
	long salary;
	int yearOfExp;
	
	
	ifstream fin;
	bool status = true;

	fin.open(fileName.data());
	if (!fin)
	{
		status = false;
		cout << "File not found. Please enter a valid filename." << endl;
	}
	else if (status)
	{
		while (!fin.eof())
		{
			fin >> command;

  		         if (command == "CreateNewDepartment")
				{
				fin >> depName;
				fin >> depLoc;
				fin >> depChairId;
				CreateNewDepartment(depName, depLoc, depChairId);
				}
			else if (command == "RemoveADepatment")
				{
				fin >> deptId;
				RemoveADepartment(deptId);
				}
			else if (command == "CreateNewStudent")
				{
				fin >> name;
				fin >> email;
				fin >> address;
				fin >> dateOfBirth;
				fin >> gender;
				fin >> yearOfStudy;
				fin >> major;
				fin >> advisor;
				CreateNewStudent(name, email, address, dateOfBirth, gender, yearOfStudy, major, advisor);
				}
			else if (command == "RemoveAStudent")
				{
				fin >> stId;
				RemoveAStudent(stId);
				}
			else if (command == "CreateNewCourse")
				{
				fin >> name;
				fin >> deptId;
				fin >> taughtBy;
				fin >> maxSeat;
				CreateNewCourse(name, deptId, taughtBy, maxSeat);
				}
			else if (command == "RemoveACourse")
				{
				fin >> crn;
				RemoveACourse(crn);
				}
			else if (command == "CreateNewFaculty")
				{
				fin >> name;
				fin >> email;
				fin >> address;
				fin >> dateOfBirth;
				fin >> gender;
				fin >> salary;
				fin >> yearOfExp;
				fin >> deptId;
				CreateNewFaculty(name, email, address, dateOfBirth, gender, salary, yearOfExp, deptId);
				}
			else if (command == "RemoveAFaculty")
				{
				fin >> factId;
				RemoveAFaculty(factId);
				}
			else if (command == "ListCoursesTaughtByFaculty")
				{
				fin >> factId;
				ListCoursesTaughtByFaculty(factId);
				}
			else if (command == "ListCoursesTakenByStudent")
				{
				fin >> stId;
				ListCoursesTakenByStudent(stId);
				}
			else if (command == "ListFacultiesInDepartment")
				{
				fin >> deptId;
				ListFacultiesInDepartment(deptId);
				}
			else if (command == "ListStudentsOfAFaculty")
				{
				fin >> factId;
				ListStudentsOfAFaculty(factId);
				}
			else if (command == "ListCoursesOfADepartment")
				{
				fin >> deptId;
				ListCoursesOfADepartment(deptId);
				}
			else if (command == "AddACourseForAStudent")
				{
				fin >> crn;
				fin >> stId;
				AddACourseForAStudent(crn, stId);
				}
			else if (command == "DropACourseForAStudent")
				{
				fin >> crn;
				fin >> stId;
				DropACourseForAStudent(crn, stId);
				}
			else if (command == "AssignDepartmentChair")
				{
				fin >> factId;
				fin >> deptId;
				AssignDepartmentChair(factId, deptId);
				}
			else  if (command == "AssignInstructorToCourse") 
				{
				fin >> factId;
				fin >> crn;
				AssignInstructorToCourse(factId, crn);
				}
			else if (command == "ListDepartments")
				ListDepartments();
			else if (command == "ListStudents")
				ListStudents();
			else if (command == "ListCourses")
				ListCourses();
			else if (command == "ListFaculties")
				ListFaculties();
		}//end while
	}	
	fin.close();
}
//----------------------------------------------------------------------------

//------------------------------------MAIN------------------------------------
// Purpose: The purpose of this routine is to create a new university and 
// call the ProcessTransactionFile which then runs the rest of the program.
// Date: 11/07/12
//----------------------------------------------------------------------------
int main() 
{
	University csusm;
	csusm.ProcessTransactionFile("TransactionFile.txt");
//	csusm.ProcessTransactionFile("t.txt");
	return(0);
}
//----------------------------------------------------------------------------
