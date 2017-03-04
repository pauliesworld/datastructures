// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 3 :: PhoneBook.h

#ifndef PHONEBOOK
#define PHONEBOOK

#include "PhoneBookNode.h"
#include "PhoneBookEntry.h"

class PhoneBook
{
    friend class PhoneBookEntry;
    friend class PhoneBookNode;

  public:
      // constructor
    PhoneBook();
      // creates nodes that build the tree based on the inputted file
    void createNodes(PhoneBookEntry &entry, PhoneBookNode* root);
      // deletes the node containing the current phone# looked up
    void deleteNode(PhoneBookNode* deleted);
      // searches the tree for the given phone#
    PhoneBookNode* findNumber(std::string number); 

    PhoneBookNode* root;

};

#endif
