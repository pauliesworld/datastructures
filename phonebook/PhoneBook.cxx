// CSCI 2270
// Assignment 5 :: The PhoneBook by Paul Johnson
// File - 2 :: PhoneBook.cxx

#include "PhoneBook.h"

using namespace std;

PhoneBook::PhoneBook()
{
    root = NULL;
}

void PhoneBook::createNodes(PhoneBookEntry &entry,PhoneBookNode* current)
{
    if (root == NULL)
    {
        root = new PhoneBookNode(entry);
    }

    else
    {
        if (entry < current->entry)
        {
            if (current->left == NULL)
	    {
                current->left = new PhoneBookNode(entry);
	    }
        
            else
            {
	        current = current->left;
	        createNodes(entry, current);
	    }
        }
        else 
        {
            if (current->right == NULL)
	    {
                current->right = new PhoneBookNode(entry);
	    }
            else
	    {
                current = current->right;
	        createNodes(entry, current);
            }
	}
    }
}

void PhoneBook::deleteNode(PhoneBookNode* deleted)
{
    PhoneBookNode* current, *previous;
    current = deleted;

    if (current->right != NULL)
    {
        current = current->right;
        previous = current;

        while (current->left != NULL)
        {
   	    previous = current;
	    current = current->left;
        }

        previous->left = current->right;
    }
    else 
    {
        if (current->left != NULL)
        {
            current = current->left;
            deleted->left = current->left;
            deleted->right = current->right;
        }

  	else
        {
            current = root;
            while (current->left != deleted && current->right != deleted)
	    {
	        if (current->entry < deleted->entry)
	        {
		    current = current->right;
	        }

		else
		{
	            current = current->left;
		}
	    }
 
            if (current->right == deleted)
	    {
	        current->right = NULL;
	    }

            if (current->left == deleted)
	    {
		current->left = NULL;
	    }
        }

        delete deleted;
        return;
    }
  
    deleted->entry = current->entry; 
    current->right = NULL;
    current->left = NULL;
    delete current;
}

PhoneBookNode* PhoneBook::findNumber(std::string phonenumber)
{
    PhoneBookNode* current;
    current = root;
  
    while (current != NULL)
    {
        if (current->entry.phonenumber == phonenumber)
	{
    	    return current;
	}

        if (current->entry.phonenumber > phonenumber)
	{
	    current = current->left;
	}
        else
	{
	    current = current->right;
        }
    }
    return NULL;
}

