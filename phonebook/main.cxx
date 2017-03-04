// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 1 :: main.cxx

#include <iostream>
#include <istream>
#include <iomanip>
#include <fstream>
#include <string>

#include "PhoneBook.h"
#include "PhoneBookEntry.h"
#include "PhoneBookNode.h"

char printMenu();

using namespace std;

PhoneBook book;

int main() 
{
    int count = 0;
    char choice;
    string file, search, areacode, phonenumber, copy;
    PhoneBookNode* found = 0;
    PhoneBookEntry info;

    cout << "\nAssignment 5: The PhoneBook by Paul Johnson\n" << endl;
    choice = printMenu();
    while (choice != 'q') 
    {
        if (choice == 'r') 
        {
            cout << "Enter the name of a phonebook file: ";
	    cin >> file;
	    ifstream ifs;
	
            if (book.root != NULL)
	    {
	        delete book.root;
	        book.root = NULL;
	    }
	    
            ifs.open(file.c_str());

	    while (ifs.peek()!=EOF)
	    {
	        PhoneBookEntry newEntry;
	        ifs >> newEntry;
	        ifs.get();
	        book.createNodes(newEntry,book.root);
                cout << "Node Created - " << count << endl;
		count++;
	    }
	    ifs.close();
        }

        if (choice == 'p') 
        {
            book.root->printTree();
        }

        if (choice == 'l') 
        {
            cout << "Enter the Area Code in the format xxx: ";
            cin >> areacode;
            cout << "Enter the Phone# in the format xxx-xxxx: ";
            cin >> phonenumber;

            copy = "(";
            copy = copy + areacode;
            copy = copy + ")";
            search = copy + phonenumber;

	    cout << "\nYou searched for the number " << search << "." << endl;	
            found = book.findNumber(search);
	
            if (found == NULL)
	    {
                cout << "Sorry, your number was not found." << endl;
	    }
	    else
            {
	        cout << *found << endl;
            }
        }

        if (choice == 'd') 
        {  
            book.deleteNode(found);
	    cout << search << " was deleted from the tree." << endl;
        }

        if (choice == 's') 
        { 
            book.root->sidewaysTree(4);
        }

        choice = printMenu();
    }
}

char printMenu() 
{
    char choice = ' ';

    cout << "	'r': read a phone book file and build the search tree" << endl;
    cout << "	'p': print the phone book in the order of phone numbers" << endl;
    cout << "	'l': look up a phone number" << endl;
    cout << "	'd': delete the most recently looked up number from the tree" << endl;
    cout << "	's': print the first four levels of the tree 'sideways'" << endl;
    cout << "	'q': quit" << endl; 
    cin >> choice;
 
    return (choice);
}
