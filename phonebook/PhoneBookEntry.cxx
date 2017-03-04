// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 4 :: PhoneBookEntry.cxx

#include <istream>

#include "PhoneBookEntry.h"

using namespace std;

istream& operator>>(istream &in, PhoneBookEntry &e)
{
    e.phonenumber = '(';
    for(int i = 0; i<89; i++)
    {
	e.theRest += in.get();
    }

    in.get();

    for(int i = 0; i<4; i++)
    {
	e.phonenumber += in.get();
    }

    in.get();

    for(int i = 0; i<8; i++)
    {
	e.phonenumber += in.get();
    }

    return in;
}

ostream& operator<<(ostream &out, PhoneBookEntry &e)
{
   out << e.theRest << " " << e.phonenumber << " "<< endl;
   return out;
}

bool operator<(PhoneBookEntry &e1, PhoneBookEntry &e2)
{
    return e1.phonenumber < e2.phonenumber;
}
