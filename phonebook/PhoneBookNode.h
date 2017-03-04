// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 7 :: PhoneBookNode.h

#ifndef PHONEBOOKNODE
#define PHONEBOOKNODE

#include "PhoneBookEntry.h" 

class PhoneBookNode
{
    friend class PhoneBookEntry;
    friend class PhoneBook;

    friend std::ostream& operator<<(std::ostream& out, PhoneBookNode &a1);
    friend bool operator==(PhoneBookEntry &e1, PhoneBookEntry &e2);

  public:

    PhoneBookNode(const PhoneBookEntry &entry);
    PhoneBookNode():left(NULL),right(NULL){}
    ~PhoneBookNode();
      // prints the sorted tree of phone#'s to the terminal
    void printTree();
      // prints the first four levels of the phone#'s of the tree to the terminal
    void sidewaysTree(int depth);

  private:
    PhoneBookEntry entry;
    PhoneBookNode *left;
    PhoneBookNode *right;
};

#endif
