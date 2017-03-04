// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 6 :: PhoneBookNode.cxx

#include "PhoneBookNode.h"
#include <iomanip>

using namespace std;

PhoneBookNode::PhoneBookNode(const PhoneBookEntry &e)
{
    entry = e;
    left = NULL;
    right = NULL;
}

PhoneBookNode::~PhoneBookNode()
{
    delete left;
    delete right;
}

void PhoneBookNode::printTree()
{
    if (left != NULL)
    {
        left->printTree();
    }

    cout << entry.theRest << entry.phonenumber << endl;

    if (right != NULL)
    {
	right->printTree();
    }
}

void PhoneBookNode::sidewaysTree(int depth)
{
    if (depth <= 0)
    {
	return;
    }

    if (right != NULL)
    {
        right->sidewaysTree(depth-1);
    }

    cout << setw(4*(4 - depth)) << ' ' << entry.phonenumber << endl;

    if (left != NULL)
    {
	left->sidewaysTree(depth-1);
    }
}

ostream& operator <<(ostream& out, PhoneBookNode &a1)
{
    out << a1.entry;
    return out;
}

bool operator ==(PhoneBookEntry &e1, PhoneBookEntry &e2)
{
    return (e1 == e2);
}
