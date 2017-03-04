// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 5 :: PhoneBookEntry.h

#ifndef PHONEBOOKENTRY
#define PHONEBOOKENTRY

#include <iostream>

class PhoneBookEntry
{
    friend class PhoneBook;
    friend class PhoneBookNode;

    friend std::istream& operator>>(std::istream &in, PhoneBookEntry &entry);
    friend std::ostream& operator<<(std::ostream &out, PhoneBookEntry &e); 
    friend bool operator<(PhoneBookEntry &entry1, PhoneBookEntry &entry2);
    
  public:
    PhoneBookEntry(){}

  private:
    std::string theRest;
    std::string phonenumber;
};
#endif
