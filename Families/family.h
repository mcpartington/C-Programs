//-------------------------------------FAMILY----------------------------------
// Purpose: The purpose of this header file is to create the Family class, 
// which holds the prototypes for the functions in the main .cpp file. Those
// routines perform all the necessary actions to create a node list of a family.
// Description: This header intializes the correct pointers which will be used 
// to create the new node list where all the other aspects of each individual
// node will be based off of. 
// Author: Maxwell C. Partington
// Author ID: 001254900
// Email: mcpartington@gmail.com
// Date: 12/1/12
//-----------------------------------------------------------------------------

#ifndef FAMILY_H
#define FAMILY_H

#include <string>
using namespace std;

#include "husband.h"
#include "wife.h"
#include "child.h"

class Family;
typedef Family* familyPtr;
class Husband;
typedef Husband* husbandPtr;
//-----------------------------------------------------------------------------
class Family
{
	protected:
		friend class Husband;
		Husband* top;

	public:
		bool AddAHusband(long id, string fName, string lName);
		bool RemoveAHusband(long id);
		
		bool AddAWife(long id, string fName, string lName, long husbandId);
		bool RemoveAWife(long husId);

		bool AddAChild(long id, string fName, string lName, long fatherId);
		bool RemoveAChild(long fatherId, long childId);

		bool PrintAFamily(long husId);
		bool PrintAllFamilies();

		Family(){top = NULL;}
		~Family(){Destroy();}

		void ReadTransactionFile();
		bool Destroy();
		husbandPtr SearchForHus(long id);
};//end Family
//-----------------------------------------------------------------------------
#endif
