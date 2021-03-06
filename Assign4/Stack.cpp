/***********************************************************************************
** Program Filename: Stack.cpp
** Author: Daniel Beyer
** Date: 05/13/16
** Description: Implementation file for class functions in Stack.hpp.
***************************************************************************/
#include<iostream>
#include "Stack.hpp"
using std::cout;
using std::endl;

/**************************************************************
** Description: Default Stack constructor that sets top to NULL.
***********************************************************/
Stack::Stack()
{
	top = NULL;
}



/***************************************************************
** Function: add()
** Description: Adds a new Stacknode node struct to the top of the Stack containing the value given
** in the parameter. The cuccessor pointer is the node that is currently the top of the stack, and the newly
** created node is the new top of the stack.

** Parameter: char
** Pre-conditions: None
** Post-conditions: Node added.
******************************************************************/
void Stack::add(Creature* cr)
{
	if (top == NULL)
	{
		top = new Stacknode(cr);
	}
	else
	{
		top = new Stacknode(cr, top);
	}
}

/***************************************************************
** Function: remove()
** Description: Returns the char stored in the top of the Stack, removes that node, and adjusts the pointers.

** Parameter: None
** Pre-conditions: Node exists in the stack to be removed
** Post-conditions: Node is removed
******************************************************************/
Creature* Stack::remove()
{
	Stacknode *temp;
	Creature* crTemp = NULL;
	if (!top)
	{
		cout << "Stack is empty." << endl;
		return 0;
	}
	else
	{
		temp = top;
		crTemp = top->value;
		top = temp->next;
		delete temp;
		return crTemp;
	}
}
/****************************************************************
** Function: display()
** Description: Displays the values stored in the Stack nodes. (Primarily for testing purposes).

** Parameters: None
** Pre-conditions: None
** Post-conditions: Stack node contents displayed to screen.
***********************************************************************/
void Stack::display()
{
	Stacknode *temp = top;
	while (temp != NULL)
	{
		cout << temp->value->getCustomName() << " , " << temp->value->getWins() << endl;
		temp = temp->next;
	}
}

/*********************************************************************
** Function: ~Stack()
** Description: Destructor that deallocates memory used by the Stack.
***********************************************************************/
Stack::~Stack()
{
	//cout << "Stack destructor running..." << endl;
	Stacknode *temp = top;

	while (temp)
	{
		Stacknode *garbage = temp;
		temp = temp->next;
		delete garbage->value;
		delete garbage;
	}
}

/************************************************************
** Function: isEmpty()
** Description: Returns true if the stack is empty and false otherwise.
*********************************************************/
bool Stack::isEmpty() const
{
	if (!top)
		return true;
	else
		return false;
}

