// Assignment #2
// Purpose of program: This program is designed to recieve a file from a user
// which then manipulates certain codes located inside of that file.
// Input required for program: A valid text file with 2 words per line.
// Output produced by program: Outputs produced will be statements declaring
// whether or not the transactions were successful.  
// Description of program: A file is asked for by the program, a user then
// then enters the correct text file. From there the program reads a line
// and takes the first word, depending on the word the command it is, it 
// then processes the second word by passing it into the corresponding
// routine based on the command.

// Date: 10/11/12
// Author: Maxwell Partington 
// Student ID: 001254900
// Email: parti006@csusm.edu

#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "dictionary.h"

bool Dictionary::failure = false;
bool Dictionary::success = true;

//--------------------------DEFAULT CONSTRUCTOR---------------------------------
//Purpose: Initializes the variables in the header file, including the 
//constants.
//Date: 10/16/2012
//------------------------------------------------------------------------------
Dictionary :: Dictionary():maxWordsInDict(10000), maxWordsPerFile(100)
{
	totalWordsInDict = 0;
	for (int i = 0; i < 26; i++)
	{
		numOfWordsInFile[i] = 0;
	}
}//end default constructor
//------------------------------------------------------------------------------

//------------------------------CONSTRUCTOR-------------------------------------
//Purpose: Initializes the variables in the header file, including the
//constants.
//Parameters: The parameters in the routine header are based on the constants.
//Date: 10/16/2012
//------------------------------------------------------------------------------
Dictionary :: Dictionary(int dictMaxWords, int fileMaxWords): maxWordsInDict(dictMaxWords),maxWordsPerFile(fileMaxWords)
{
        totalWordsInDict = 0;
	for (int i = 0; i < 26; i++)
	{ 
		numOfWordsInFile[i] = 0;
	}
}//end Constructor
//------------------------------------------------------------------------------

//------------------------------DESTRUCTOR--------------------------------------
//Purpose: Deallocates any resources used up by any objects created by 
//Dictionary.
//Date 10/16/2012
//------------------------------------------------------------------------------
Dictionary :: ~Dictionary()
{
	totalWordsInDict--;
}//end Destructor
//------------------------------------------------------------------------------

//--------------------------------ADDAWORD--------------------------------------
//Purpose: The routine determines if the word to be added is not overflowing
//the text file it is inteded to go to. Then it passes it to the 
//SuccessfullyAddWord routine.
//Parameter: A word is passed in, and then added into the dictionary.
//Date: 10/16/2012
//------------------------------------------------------------------------------
bool Dictionary :: AddAWord(string word)
{
	char ch = toupper(word[0]);
	int index = ch - 'A';

	if (totalWordsInDict >= maxWordsInDict)
		{
		return (Dictionary :: failure);
		}

	else if (numOfWordsInFile[index] >= maxWordsPerFile)	
		{
		return (Dictionary :: failure);
		}
	else if (SearchForWord(word) == success)	
		{
		return (Dictionary :: failure);
		}

	else 
		{
		(SuccessfullyAddWord(word, index));
		}
}//end AddAWord
//------------------------------------------------------------------------------

//----------------------SUCCESSFULLYADDWORD-------------------------------------
//Purpose: Adds each word passed in to the correct file in the dictionary.
//Parameters: A word is passed in which is then used to open the correct file.
//As well as the index which is used to determine the number of words in a file.
//Date: 10/16/2012
//------------------------------------------------------------------------------
bool Dictionary :: SuccessfullyAddWord(string word, int index)
{
	string fileName = "?.txt";
	char ch = toupper(word[0]);
	fileName[0] = ch;
	ofstream fout;
	fout.open(fileName.data(), ios::app);
	if (numOfWordsInFile[index] >= 1)
		{
		fout << endl <<  word;		
		}
	else
		{
		fout << word;
		}
	numOfWordsInFile[index]++;
	totalWordsInDict++;
	fout.close();
	return (Dictionary :: success);
}//end SuccessfullyAddWord
//------------------------------------------------------------------------------

//--------------------------------DELETEAWORD-----------------------------------
//Purpose: This routine takes the word passed in and searches for the word, then
//deletes it from the correct file in the dictionary. It first opens up the 
//the correct file, and then checks to make sure the word is in the file. If so,
//it does not added to the vector, which is then passed back out into the file, 
//this time without the word it is deleting. 
//Parameter: A word is passed in. It is the word to be deleted.
//Date: 10/16/2012
//------------------------------------------------------------------------------
bool Dictionary :: DeleteAWord(string word)
{
	string fileName = "?.txt";
	char ch = toupper(word[0]);
	fileName[0] = ch;
	int count  = 0;
	vector<string>temp;
	ifstream fin;
	ofstream fout;
	string wordToCmp;
	bool status = false;
	fin.open(fileName.data());
	
	//While it is not the end of the file, a word from the file is taken out
	//then it is checked to see if it is the same as the one passed in. If
	//if is, then is isn't added to the vector. Which is then passed back
	//out to be printed. 
	while (!fin.eof())
	{
		fin >> wordToCmp;
		if (wordToCmp != word)
		{
			temp.push_back(wordToCmp);
			count++;
		}
		else 
			status = true;	
	}//end while
	fin.close();
	
	//A file is opened and then using a for loop, it prints out the vector.
	fout.open(fileName.data());
	for (int i = 0; i < count; i++)
	{
		fout << temp[i] << endl;
	}
	fout.close();

	totalWordsInDict --;
	if (status == true)
		return (Dictionary :: success);
	else 
		return (Dictionary :: failure);
}//end DeleteAWord
//------------------------------------------------------------------------------

//-------------------------------SEARCHFORWORD----------------------------------
//Purpose: This routine is used by various other routines in the program. It is
//used to make sure that the word being searched for isn't already in the 
//dictionary. If it already is, this routine returns true, if not, it returns
//false. 
//Parameters: A word is passed in and used to search in a file.
//Date: 10/16/2012
//------------------------------------------------------------------------------
bool Dictionary :: SearchForWord(string word)
{
	char ch = toupper(word[0]);
	string fileName = "?.txt";
	fileName[0] = ch;
	ifstream fin;
	fin.open(fileName.data());
	string wordToCmp;

	while ( fin >> wordToCmp)
	{
		if (wordToCmp == word)
	    	return (Dictionary :: success);
	}//end while
	return (Dictionary :: failure);
	fin.close();
}//end SearchForWord
//------------------------------------------------------------------------------

//----------------------------PRINTAFILEINDICT----------------------------------
//Purpose: This routine is intended to print out a specific file located in the 
//dictionary. It prints out all the words included in that file.
//Parameters: A file is passed in which is then opened and put into the 
//dictionary.
//Date: 10/16/2012
//------------------------------------------------------------------------------
bool Dictionary :: PrintAFileInDict(string fileName)
{
	ifstream fin;
    fin.open(fileName.data());
	string word;
	char ch = fileName[0];	
	int count = 0;
	if (fin)
	{	
		cout << "Result:\t     The dictionary file of the letter \"" << ch << "\" includes the following words:\n\n";
    		   //While it is not the end of a file, this loop takes the word out
			   //of the file and then prints it onto the screen, 5 at a time. 
	           while(!fin.eof())
                {		
						fin >> word;
						cout << word << " ";
						count++;
						if (count == 5)
						{
							cout << "\n";	
							count = 0;
						}// end if
                }//end while
				cout << "\n------------------------------------------------------------------------------------\n";
				return (Dictionary :: success);
     }
     else
     {     
     	      cout << "File not found. Please input a valid filename." << endl;
			  return (Dictionary :: failure);
     }
	fin.close();
}//end PrintAFileInDict
//------------------------------------------------------------------------------

//-------------------------------SPELLCHECKING----------------------------------
//Purpose: This routine recieves a file, then with that file, it takes out each
//word and uses the SearchForWord function. With that function, it checks it 
//the word against the dictionary and if it cannot locate it, then the word 
//is misspelled.
//Parameter: A file is passed and then opened. 
//Date: 10/16/2012
//------------------------------------------------------------------------------
bool Dictionary :: SpellChecking(string fileName)
{
	ifstream fin;
	fin.open(fileName.data());
	string word;
	while (fin >> word)
	{
		
		bool status = SearchForWord(word);
		if (status == (Dictionary :: failure))
			cout << "\nThe word: \"" <<  word << "\" is misspelled.";
	}//end while
	fin.close();
}//end SpellChecking
//-----------------------------------------------------------------------------

//-----------------------INSERTWORDSINTODICT-----------------------------------
//Purpose: This routine recieves a filename and then in turn takes the words 
//that are in the file and adds them one by one into the correct file using
//the AddAWord routine.
//Parameter: A file is passed in and words are taken out to be added into the
//dictionary.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
bool Dictionary :: InsertWordsIntoDict(string fileName)
{
	ifstream fin;
	fin.open(fileName.data());
	string word;

	if (fin)
		{
		while(!fin.eof())
		{
			fin >> word;
			AddAWord(word); 			
		}
		return (Dictionary :: success);
		}
	else
		{
        cout << "File not found. Please enter a valid filename." << endl;
		return (Dictionary :: failure);
		}
	fin.close();
}//end InsertWordsIntoDict
//---------------------------------------------------------------------


//-----------------------------PROCESSADDWORD----------------------------------
//Purpose: This routine calls the AddAWord routine using the word passed in and
//then uses that routine to add the word to the dictionary.
//Parameter: A command and a word is passed in and then the dictionary is 
//manipulated based on the command.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessAddWord(string command, string word)
{
	bool status;
	cout << "Transaction: AddW\t" << word << endl;
	status = AddAWord(word);
	if (status == (false))
		cout << "Result:\t     The word \"" << word << "\" was not added to the dictionary.\n";
	else
		cout << "Result:\t     The word \"" << word << "\" was successfully added to the dictionary.\n";
}//end ProcessAddWord
//-----------------------------------------------------------------------------

//-----------------------------PROCESSDELETEWORD-------------------------------
//Purpose: This routine accepts a file and then takes out the word passed in 
//and calls the DeleteAWord function to remove the word from the corresponding
//file.
//Parameter: A command and a word is passed in and then the dictionary is 
//manipulated based on the command.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessDeleteWord(string command, string word)
{
	bool status;
	cout << "Transaction: DeleteAWord   " << command << endl;
	status = DeleteAWord(word);
	if (status == (true))
		cout << "Result:      The word \"" << word << "\" was deleted from the dictionary." << endl;
	else if (status == (false))
		cout << "Result:      The word \"" << word << "\" does not exsist in the dictionary." << endl;
}//end ProcessDeleteWord
//-----------------------------------------------------------------------------


//--------------------------PROCESSSEARCHWORD----------------------------------
//Purpose: This routine takes in a word from the file, and checks to see if
//that word is in fact in the corresponding dictionary file. 
//Parameter: A command and a word is passed in and then the dictionary is 
//manipulated based on the command.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessSearchWord(string command, string word)
{
	if (SearchForWord(word) == (Dictionary :: success))
	{
		cout << "Transaction: " << command << "\t" << word;
		cout << "\nResult:\t     The word \"" << word << "\" is in the dictionary." << endl;
	}
	else
	{
		cout << "Transaction: " << command << "\t" << word;
		cout << "\nResult:\t     The word \"" << word << "\" is not in the dictionary." << endl;
	}
}//
//-----------------------------------------------------------------------------


//---------------------------PROCESSPRINTAFILE---------------------------------
//Purpose: This routine recieves a file and then calls the PrintAFileInDict
//routine which then prints out the dictionary onto the screen.
//Parameter: A command and a word is passed in and then the dictionary is 
//manipulated based on the command.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessPrintAFile(string command, string word)
{
	cout << "Transaction: " << command << "\t" << word << endl;
	PrintAFileInDict(word);
}//
//-----------------------------------------------------------------------------


//----------------------------PROCESSSPELLCHECK--------------------------------
//Purpose: This routine uses the word passed in and calls the routine 
//SpellChecking. This routine makes sure the word is spelled correctly.
//Parameter: A command and a word is passed in and then the dictionary is 
//manipulated based on the command.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessSpellCheck(string command, string word)
{
	cout << "Transaction: " << command << "\t" << word << endl;
	SpellChecking(word);
}//end ProcessSpellCheck
//-----------------------------------------------------------------------------

//-----------------------------PROCESSINSERTWORD-------------------------------
//Purpose: This routine recieves the command "InsertW". With this command
//it then proceeds to take out each word individually from the file, and insert
//it into the correct dictionary file based on the first letter of the word.
//Parameter: A command and a word is passed in and then the dictionary is 
//manipulated based on the command.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessInsertWord(string command, string word)
{
	bool status;
	cout << "Transaction: " << command << "\t" << word << endl;
	status = InsertWordsIntoDict(word);
	if (status == false)
		cout << "Result:      The file \"" << word << "\" was not inserted into the dictionary.";
	else
		cout << "Result:      The file \"" << word << "\" was successfully inserted into the dictionary.";
}//end ProcessInsertWord
//-----------------------------------------------------------------------------

//--------------------------PROCESSTRANSACTIONFILE-----------------------------
//Purpose: This routine reads in an input file. Every line on the file should 
//then have a specific command call which in turn takes the corresponding
//word or file on the same line and processes that piece of information into or
//out of the correct dictionary file.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
void Dictionary :: ProcessTransactionFile()
{
	string fileName;
	string command;	
	string commanda;
	ifstream fin;
	bool status = true;

	cout << "Please enter a file to be processed: ";
	cin >> fileName;
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
			fin >> commanda;
			cout << "\n\n------------------------------------------------------------------------------------\n";
			if (command == "AddW")
				{
				ProcessAddWord(command, commanda);	
				}
			else if (command == "DeleteW")
				{
				ProcessDeleteWord(command, commanda);	
				}
			else if (command == "SearchW")
				{
				ProcessSearchWord(command, commanda);
				}
			else if (command == "PrintF")
				{
				ProcessPrintAFile(command, commanda);
				}
			else if (command == "SpellCheck")
				{
				ProcessSpellCheck(command, commanda);
				}
			else if (command == "InsertF")
				{
				ProcessInsertWord(command, commanda);
				}
		}//end while
	}
	fin.close();
}//end ProcessTransactionFile
//-----------------------------------------------------------------------------


//---------------------------------MAIN----------------------------------------
//Purpose: This is the main driver for the program. It creates an object of the
//dictionary class. Then it calls the ProcessTransactionFile routine, which
//then calls the appropriate routine based on the input recieved from a correct
//file.
//Date: 10/16/2012
//-----------------------------------------------------------------------------
int main()
{
	Dictionary DictForCS211;
	DictForCS211.ProcessTransactionFile();
	return (0);
}//end main
//------------------------------------------------------------------------------
#endif 
