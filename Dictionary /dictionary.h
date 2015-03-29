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

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <string> 
#include <vector>

using namespace std;

//---------------------------------DICTIONARY---------------------------------
//Purpose: This is the dictionary class. In this class all the variables are 
//declared as well as all the routines used in the dictionary.cpp file.
//Date: 10/16/2012
//----------------------------------------------------------------------------
class Dictionary
{
	private:
			const	int maxWordsInDict;
			const 	int maxWordsPerFile;
					int totalWordsInDict;
					int numOfWordsInFile[26];
			static  bool failure;
			static  bool success;

	public:
			Dictionary();
			~Dictionary();
			Dictionary(int dictMaxWords, int fileMaxWords);
			bool AddAWord(string word);
			bool DeleteAWord(string word);
			bool SearchForWord(string word);
			bool PrintAFileInDict(string fileName);
			bool SpellChecking(string fileName);
			bool InsertWordsIntoDict(string fileName);
			bool SuccessfullyAddWord(string word,int index);
			void ProcessTransactionFile();
			void ProcessAddWord(string command, string word);
			void ProcessDeleteWord(string command, string word);	
			void ProcessSearchWord(string command, string word);
			void ProcessPrintAFile(string command, string word);
			void ProcessSpellCheck(string command, string word);
			void ProcessInsertWord(string command, string word);
};//end Dictionary
//-----------------------------------------------------------------------------
#endif
