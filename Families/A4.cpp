//-------------------------------ASSIGNMENT 4----------------------------------
// Purpose: The purpose of this program is to create a list of families each
// connected to their own individual husband or father. 
// Description: A file is opened and a set of commands is processed with 
// accompanying variables. These variables are then placed into their 
// appropriate families which can then be further manipulated or altogether 
// erased. 
// Inputs: The only input required is a file with the appropriate commands 
// written into the file. 
// Outputs: This program outputs the various families. If any modifications are
// made to the families, they can then be reprinted with the update information.
// Date: 12/6/12
// Author: Maxwell C. Partington
// Author ID: 001254900
// Email: mcpartington@gmail.com
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <iostream>
#include <string> 
#include <fstream>
using namespace std;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Inclusion of header files.
//-----------------------------------------------------------------------------
#include "family.h"
#include "husband.h"
#include "wife.h"
#include "child.h"
//-----------------------------------------------------------------------------

//-------------------------------ADD A HUSBAND---------------------------------
// Purpose: The function of this routine is to search to make sure a husband is
// not yet present in the node list, and if it is not, then a new husband node
// is created and attached to the top of the node list.
// Parameters: The parameters for this function are a valid id, first name, 
// and last name which are then used to create and add a new husband.
// Local Variables: The local varibles in this routine are husband pointers 
// which are used to check the validity of the husband information, and then to
// add it to the node list. 
// Date: 12/1/12
//-----------------------------------------------------------------------------
bool Family::AddAHusband(long id, string fName, string lName)
{
	husbandPtr status = SearchForHus(id);	
	
	if (status != NULL)
	{
		cout << "\n------------------------------------------------" << endl;
		cout << "ERROR: That husband already exists." << endl;
		cout << "------------------------------------------------" << endl;
		return false;
	}		

	husbandPtr H = new Husband(id, fName, lName);
	H -> nextFamily = top;
	top = H;
	return true;
}//end AddAHusband
//----------------------------------------------------------------------------- 

//-------------------------------REMOVE A HUSBAND------------------------------
// Purpose: This routine is used to remove a husband node from the node list.
// If the husband is married, or married with children, the routine removes
// the children, then it removes the wife, and then removes the husband itself
// from the node list.
// Parameters: The only parameter for this routine is a husband's ID number. It
// is used to remove the husband and family (if any) from the node list.
// Local Variables: The local variables for this routine are a series of 
// husband pointers which are used to remove the correct husband from the list.
// Date: 12/1/12
//-----------------------------------------------------------------------------
bool Family::RemoveAHusband(long id)
{
	husbandPtr H = SearchForHus(id);
	husbandPtr P = top;
	husbandPtr Q = NULL;

	if (H == NULL)
	{
		cout << "\n------------------------------------------------" << endl;
		cout << "ERROR: That husband does not exist." << endl;
		cout << "-------------------------------------------------" << endl;
		return false;
	}
	if (H -> myWife == NULL)
	{
		P ->nextFamily = H -> nextFamily;
		delete H;
		return true;
	}
	
	while (P != NULL)
	{
		if ((P -> myWife != NULL) && (P -> SSN == id))
		{
			RemoveAWife(id);
		
		if ((top == P) && (P -> SSN == id))
		{
			top = P -> nextFamily;
		}
		else
		{
			Q -> nextFamily = P -> nextFamily;	
		}
			delete P;
			return true;
		}
		Q = P;
		P = P -> nextFamily;			
	}//end while
}//end RemoveAHusband
//-----------------------------------------------------------------------------

//--------------------------------ADD A WIFE-----------------------------------
// Purpose: The function of this routine is to attached a new wife node to an
// already existing husband node. If the husband is already married, it does
// not add another.
// Parameters: The parameters for this routine are all those variables 
// necessary to check the validity of a new wife being added and the validity
// of an existing husband. They are then used to create a new wife node and 
// attach it to an existing husband node.
// Local Variables: The local variables of this routine are a husband pointer 
// to check and find the right husband, and a wife pointer which is used to 
// create a new wife which is then attached to the husband.
// Date 12/2/12
//-----------------------------------------------------------------------------
bool Family::AddAWife(long id, string fName, string lName, long husbandId)
{
	husbandPtr H = SearchForHus(husbandId);
	
	if (H == NULL)
	{
		cout << "\n------------------------------------------------" << endl;
                cout << "ERROR: That husband does not exist." << endl;
                cout << "------------------------------------------------" << endl;
                return false;
	}
	else if (H -> myWife != NULL)
	{
		cout << "\n------------------------------------------------" << endl;
                cout << "ERROR: That husband is already married." << endl;
                cout << "------------------------------------------------" << endl;
                return false;
	}
	else
	{
		wifePtr w = new Wife(id, fName, lName);
		H -> myWife = w;
	}
}//end addWife
//----------------------------------------------------------------------------- 

//-------------------------------REMOVE A WIFE--------------------------------
// Purpose: The purpose of this routine is to remove a wife from a husband and
// if they have any, their children. 
// Parameters: The only parameter used for this routine is a husband ID which 
// is used to find the right wife to remove, and then the right children to 
// remove.
// Local Variables: The local variables in this routine are those that are 
// required to point to the correct wife and children to remove from the 
// husband node. 
// Date: 12/3/12
//-----------------------------------------------------------------------------
bool Family::RemoveAWife(long husId)
{
	long childSSN;
	husbandPtr H = SearchForHus(husId);

	//---------------Error checking.-------------
	if (H == NULL)
	{
		cout << "\n------------------------------------------------" << endl;
                cout << "ERROR: That husband does not exist." << endl;
                cout << "------------------------------------------------" << endl;
		return false;
	}
	if (H -> myWife == NULL)
	{
		cout << "\n-----------------------------------------------" << endl;
		cout << "ERROR: That husband is not married." << endl;
		cout << "-----------------------------------------------" << endl;
		return false;
	}
	//--------------------------------------------

	wifePtr W = H -> myWife;
	childPtr C = W -> myChildren;

	if (C  == NULL)
	{
		H -> myWife = NULL;
		delete W;
		return false;
	}
	else
	{
		while (C != NULL)
		{
			childSSN = C -> SSN;
			RemoveAChild(husId, childSSN);
			C = C -> mySibling;
		}//end while 

		H -> myWife = NULL;
		delete	W;
		return true;
	}
}//end removeWife
//----------------------------------------------------------------------------- 

//--------------------------------ADD A CHILD----------------------------------
// Purpose: The purpose of this routine is to add a child to an existing wife
// or sibling node. If the wife has no children, the new child is added to that
// list, else it is added to the last sibling node. 
// Parameters: The parameters of this routine are all those required to create
// a new child node so that it may be added to the correct node. Also, the
// the father ID is used to validate where the child will be attached and that 
// it is a valid father.
// Local Variables: The local variables for this routine are a husband and 
// wife pointer which are used to add the child to the correct node in the list.
// Date: 12/3/12
//-----------------------------------------------------------------------------
bool Family::AddAChild(long id, string fName, string lName, long fatherId)
{
	husbandPtr H = SearchForHus(fatherId);
	
	if (H == NULL)
        {
                cout << "\n------------------------------------------------" << endl;
                cout << "ERROR: That father does not exist." << endl;
                cout << "------------------------------------------------" << endl;
                return false;
        }

	wifePtr W;
	W = H -> myWife;

	if (W -> myChildren == NULL)
	{
		childPtr C = new Child(id, fName, lName);
		W -> myChildren = C; 
	}
	else
	{	
		childPtr C = new Child(id, fName, lName);
		C -> mySibling = W -> myChildren;
		W -> myChildren = C; 	
	}
	return true;
}//end addAChild
//-----------------------------------------------------------------------------

//-------------------------------REMOVE A CHILD-------------------------------- 
// Purpose: This routine's function is to remove a child from the correct 
// family node.
// Parameters: The parameter's for this function are a father ID and a child ID
// which are used to find the right family to remove from and the right child
// to remove. Respectively. 
// Local Variables: The local variables of this routine are a husband pointer,
// a wife pointer, and child pointer. Since the children are attached to the 
// wife node, the routine first searches down to the wife node, which is then
// searched down to the children node to find the correct one to remove.
// Date: 12/3/12
//-----------------------------------------------------------------------------
bool Family::RemoveAChild(long fatherId, long childId)
{
	husbandPtr H = SearchForHus(fatherId);

	if (H == NULL)
        {
                cout << "\n------------------------------------------------" << endl;
                cout << "ERROR: That father does not exist." << endl;
                cout << "------------------------------------------------" << endl;
                return false;
        }

	wifePtr W;
	W = H -> myWife;
	childPtr C = W -> myChildren;
	childPtr D = W -> myChildren;
	
	// If there are no children, return false.
	if(W -> myChildren == NULL)
           return false;

	// If there is at least one child, the first child is to be removed.
         if (C -> SSN == childId)
         {
                 W -> myChildren = C->mySibling;
                 delete C;
         }
	//Check the other cases.
         else
           {
                 //Move the child pointer "C" to the child before the one to be removed.
                 while (C->mySibling != NULL && (C -> mySibling -> SSN != childId))
                 {
                         C = C -> mySibling;
                 }

                 //D points to the one to be removed.
                 D = C -> mySibling;

                //C points to the last child.
		//If the child is not found, print an error message.
		if(D == NULL)
		{
			cout << "\n------------------------------------------------" << endl;
      	 	        cout << "ERROR: That child does not exist." << endl;
       		        cout << "------------------------------------------------" << endl;
			return false;
		}
		//Lastly, the next pointer is pointed to the next sibling and is then
		//removed. 
		else
                   {
                     C -> mySibling = D -> mySibling;
                     delete D;
                     return true;
                   }

         }
}//end removeAChild
//-----------------------------------------------------------------------------

//-------------------------------PRINT A FAMILY-------------------------------- 
// Purpose: The purpose of this function is to print one family in the list.
// Parameters: The only parameter of this routine is the husband ID which is
// used to find the correct family to print out.
// Local Variables: The local variables of this routine are a husband, wife, 
// and child pointer. They are used to find the correct family members to print
// out. 
// Date: 12/4/12
//-----------------------------------------------------------------------------
bool Family::PrintAFamily(long husId)
{
	husbandPtr H = SearchForHus(husId);
	
	if (H == NULL)
	{
		cout << "\n------------------------------------------------" << endl;
                cout << "ERROR: That family does not exist." << endl;
                cout << "------------------------------------------------" << endl;
                return false;
	}
	else
	{
		cout << "\n------------------------------------------------" << endl;
		cout << "\t   " << H -> lastName << " Family Information" << endl;
		cout << "------------------------------------------------" << endl;
		cout << "\nHusband/Father's Information: " << endl;
		cout << "=============================" << endl;
		cout << "SSN: " << H -> SSN << endl;
		cout << "First name: " << H -> firstName << endl;
		cout << "Last name: " << H -> lastName << endl;

	wifePtr W = H -> myWife;

	if (W == NULL)
	{
		cout << "\nWife/Mother's Information: " << endl;
		cout << "========================== " << endl;
		cout << H -> firstName << " does not have a wife." << endl;
		cout << "\n------------------------------------------------" << endl;
		return true;
	}
	else
	{
		cout << "\nWife/Mother's Information: " << endl;
		cout << "==========================" << endl;
		cout << "SSN: " << W -> SSN << endl;
		cout << "First name: " << W -> firstName << endl;
		cout << "Last name: " << W -> lastName << endl;
		childPtr C = W -> myChildren;
		if (C == NULL)
		{
			cout << "\nChildren's Information: " << endl;
			cout << "=======================";
			cout << "\n" << H -> firstName << " and " << W -> firstName << " do not have any children." << endl;
			cout << "\n------------------------------------------------" << endl;
			return true;
		}
		else
		{
			cout << "\nChildren's Information: " << endl;
			cout << "=======================";
			while (C != NULL)
				{
				cout << "\nSSN: " << C -> SSN<< endl;
				cout << "First name: " << C -> firstName<< endl;
				cout << "Last name: " << C -> lastName << endl;
				C = C -> mySibling;
			}//end while
			cout << "\n------------------------------------------------" << endl;
		}
	}
	}
}//end printAFamily
//-----------------------------------------------------------------------------

//------------------------------PRINT ALL FAMILIES----------------------------- 
// Purpose: This routine prints out of the families located in the family 
// node list.
// Parameters: N/A
// Local Variables: The onl local variable is a husband pointer which is used 
// to find the right information to print.
// Date 12/5/12
//-----------------------------------------------------------------------------
bool Family::PrintAllFamilies()
{
	husbandPtr H = top;
	if (top == NULL)
	{
		cout << "\n-------------------------------------------------" << endl;
		cout << "There are no families to print." << endl;
		cout << "-------------------------------------------------" << endl;
		return false;
	}
		cout << "\n================================================" << endl;
		cout << "==================== FAMILIES ==================" << endl;
		cout << "================================================" << endl;
	while (H  != NULL)
	{
		PrintAFamily(H -> SSN);
		H = H -> nextFamily;
	}//end while
		cout << "\n================================================" << endl;
		cout << "================================================" << endl;
}//end printAllFamilies
//-----------------------------------------------------------------------------

//------------------------------SEARCH FOR HUSBAND-----------------------------
// Purpose: This routine is used to search for the correct and valid husband in
// the node list. It returns "NULL" if it cannot find the husband, and it 
// returns a pointer to the husband if it does.
// Parameters: The only parameter of this routine is the husbands ID which is
// which is used to search through the node list.
// Local Variables: The only local variable is a husband pointer which is used
// to search through the node list with the ID for the correct husband.
// Date: 12/4/12 
//-----------------------------------------------------------------------------
husbandPtr Family::SearchForHus(long id)
{
	husbandPtr H = top;
	while (H != NULL)
	{
		if (H -> SSN == id)
		{	
			return H;
		}
		H = H -> nextFamily;
	}//end while
	return NULL;
}//end searchForHus
//-----------------------------------------------------------------------------

//---------------------------------DESTROY-------------------------------------
// Purpose: The purpose of this routine is remove all nodes from the node list.
// Parameters: N/A
// Local Variables: The local variables are two pointers which are used to move
// through the node list and remove (destroy) each node individually.
// Date: 12/4/12
//-----------------------------------------------------------------------------
bool Family::Destroy()
{
	husbandPtr p = top;
	husbandPtr q = top;

	while (p != NULL)
	{
		q = p;
		p = p -> nextFamily;
		delete q;
	}//end While
	top = NULL;
	return true;
}//end Destroy
//-----------------------------------------------------------------------------

//---------------------------READ TRANSACTION FILE-----------------------------
// Purpose: The purpose of this routine is to open and read in commands from a
// file.
// Parameters: N/A
// Local Variables: The local variables of this function are those required to
// create or remove various nodes from the node list. Command is used to get
// the command from the file, and fin is used to open the file. 
// Date: 12/5/12
//-----------------------------------------------------------------------------
void Family::ReadTransactionFile()
{
	long ssn;
	string fName;
	string lName;
	
	long husbandSSN;	
	long childSSN;

	string command;

	ifstream fin;
	fin.open("Trans.txt");
	
	if (!fin)
	{
		cout << "\n------------------------------------------------" << endl;
		cout << "ERROR: File not found. End program." << endl;
		cout << "\n------------------------------------------------" << endl;
	}	

	else
	{
		while (!fin.eof())
		{
			fin >> command;
		
			if (command == "AddHusband")
			{
				fin >> ssn;
				fin >> fName;
				fin >> lName;
				AddAHusband(ssn, fName, lName);
			}		
			else if (command =="RemoveAHusband")
			{
				fin >> ssn;
				RemoveAHusband(ssn);
			}
			else if (command == "AddWife")
			{
				fin >> ssn;
				fin >> fName;
				fin >> lName;
				fin >> husbandSSN;
				AddAWife(ssn, fName, lName, husbandSSN);
			}
			else if (command == "RemoveAWife")
			{
				fin >> husbandSSN;
				RemoveAWife(husbandSSN);
			}
			else if (command == "AddAchild")
			{
				fin >> ssn;
				fin >> fName;
				fin >> lName;
				fin >> husbandSSN;
				AddAChild(ssn, fName, lName, husbandSSN);
			}
			else if (command == "RemoveAchild")
			{
			
				fin >> husbandSSN;
				fin >> childSSN;
				RemoveAChild(husbandSSN, childSSN);
			}
			else if (command == "PrintAFamily")
			{
				fin >> ssn;
				PrintAFamily(ssn);
			}
			else if (command == "PrintAllFamilies")
			{
				PrintAllFamilies();
			}
			else if (command ==  "Destroy")
			{
				Destroy();
			}
		}//end while
	}
	fin.close();
}//end ReadTransactionFile
//-----------------------------------------------------------------------------

//------------------------------------MAIN-------------------------------------
// Purpose: The purpose of this routine is run the program. It creates a new 
// Family ojbect and uses that to call the ReadTransactionFile routine which
// creates the node list.
// Parameters: N/A
// Local Variables: The only local variable is the object created by the Family
// class.
// Date: 12/2/12
//-----------------------------------------------------------------------------
int main()
{
	Family		USAFamilies;
	USAFamilies.ReadTransactionFile();
	return 0;
}//end main 
//-----------------------------------------------------------------------------
