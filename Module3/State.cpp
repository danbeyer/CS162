/**********************************************
** File: State.cpp
** Author: Daniel Beyer
** Date: 05/05/16
** Description: Class implementation file for State.hpp
**************************************************************/
#include<iostream>
#include<cmath>
#include<ctime>
#include<queue>
#include<cstdlib>
#include "State.hpp"


using namespace std;

State::~State() // Destructor
{
	State *q;
	State *t;
	q = head;
	t = head;
	if (head == NULL)
		return;
	while (q->nextState != t)
	{
		head = q;
		q = q->nextState;
		delete head;
	}
	head = q;
	delete head;


}

/**************************************************
** Function: add()
** Description: Adds a node to the node chain.  Creates a circular chain by setting the final node pointer 
** to the head node.

** Parameters: char, char, char, char
** Pre-Conditions: Valid State object created
** Post-Condition: New node added to end of node chain
******************************************************************/
void State::add(char EW1, char NS1, char directionA, char directionB)
{
	if (head == NULL)
	{
		State *cur = new State(EW1, NS1, directionA, directionB);
		cur->nextState = cur;
		head = cur;

	}
	else
	{
		State *cur = head;
		while (cur->nextState != head)
		{
			cur = cur->nextState;
		}
		State *t;
		t = new State(EW1, NS1, directionA, directionB);
		t->nextState = head;
		cur->nextState = t;

	}
}

/**************************************************
** Function: display()
** Description: Loops through the nodes to display their contents.

** Parameters: None
** Pre-Conditions: None
** Post-Condition: Outputs node contents
******************************************************************/
void State::display()
{
	if (head == NULL)
	{
		cout << "No Traffic Lights" << endl;
	}
	State *q;
	q = head;
	for (int i = 1; i <= this->count(); i++)
	{
		cout << q->EW << " " << q->NS << " " << q->direction1 << " " << q->direction2 << endl;
		q = q->nextState;
	}
}

/**************************************************
** Function: count()
** Description: Count function to generate the number of nodes in the circular loop to be used by display().

** Parameters: None
** Pre-Conditions: None
** Post-Condition: Returns int c
******************************************************************/
int State::count()
{
	State *q;
	q = head;
	int c = 0;
	if (head == NULL)
		return 0;
	else
		c++;
	while (q->nextState != head)
	{
		c++;
		q = q->nextState;
	}
	return c;
}

/**************************************************
** Function: nrOfVehiclesDepart()
** Description: For each direcion, generates random numbers for vehicles departing using rand().  Outputs to the screen
** the number of cars that departed.  Then this value is subtracted from the total cars at each direction light.
** I also opted to place the output message for the total number of cars waiting at the light as this function is 
** called last in my main() function so this total will be the final total for this iteration.  The STL queue pop() function
** is used to pull the specified number of cars off the front of their respective direction Queues.  The wait time is also incremented here,
** with wait time = current time iteration - car's timestamp

** Parameters: Pointers to Queue objects and an int
** Pre-Conditions: None
** Post-Condition: Outputs messages to screen.
******************************************************************/
void State::nrOfVehiclesDepart(queue<int> &E, queue<int> &W, queue<int> &N, queue<int> &S, int x)
{
	if (EW == 'G')
	{
		int NrOfVehiclesDepartE = rand() % 6;
		int NrOfVehiclesDepartW = rand() % 6;
		if (NrOfVehiclesDepartE > NrOfVehiclesAtELight)
		{
			NrOfVehiclesDepartE = NrOfVehiclesAtELight;
		}
		if (NrOfVehiclesDepartW > NrOfVehiclesAtWLight)
		{
			NrOfVehiclesDepartW = NrOfVehiclesAtWLight;
		}
		cout << NrOfVehiclesDepartE << " vehicles departed from the East green light." << endl;
		for (int i = 0; i < NrOfVehiclesDepartE; i++)
		{
			int wait = E.front(); // adding wait time to wait variable in state
			totalwaitE = totalwaitE + (x - wait);
			cout << "Car " << E.front() << " departed" << endl;
			E.pop();
		}
		cout << NrOfVehiclesDepartW << " vehicles departed from the West green light." << endl;

		for (int i = 0; i < NrOfVehiclesDepartW; i++)
		{
			int wait = W.front(); // adding wait time to wait variable in state
			totalwaitW = totalwaitW + (x - wait);
			cout << "Car " << W.front() << " departed" << endl;
			W.pop();
		}

		NrOfVehiclesAtELight -= NrOfVehiclesDepartE;
		NrOfVehiclesAtWLight -= NrOfVehiclesDepartW;
		if (NrOfVehiclesAtELight <= 0)
		{
			NrOfVehiclesAtELight = 0;
		}
		if (NrOfVehiclesAtWLight <= 0)
		{
			NrOfVehiclesAtWLight = 0;
		}
		cout << "Number of vehicles at East light: " << NrOfVehiclesAtELight << endl;
		cout << "Number of vehicles at West light: " << NrOfVehiclesAtWLight << endl;

		totalDepartE += NrOfVehiclesDepartE;
		totalDepartW += NrOfVehiclesDepartW;
	}
	if (NS == 'G')
	{
		int NrOfVehiclesDepartN = rand() % 6;
		int NrOfVehiclesDepartS = rand() % 6;
		if (NrOfVehiclesDepartN > NrOfVehiclesAtNLight)
		{
			NrOfVehiclesDepartN = NrOfVehiclesAtNLight;
		}
		if (NrOfVehiclesDepartS > NrOfVehiclesAtSLight)
		{
			NrOfVehiclesDepartS = NrOfVehiclesAtSLight;
		}
		cout << NrOfVehiclesDepartN << " vehicles departed from the North green light." << endl;
		for (int i = 0; i < NrOfVehiclesDepartN; i++)
		{
			int wait = N.front(); // adding wait time to wait variable in state
			totalwaitN = totalwaitN + (x - wait);
			cout << "Car " << N.front() << " departed" << endl;
			N.pop();
		}
		cout << NrOfVehiclesDepartS << " vehicles departed from the South green light." << endl;

		for (int i = 0; i < NrOfVehiclesDepartS; i++)
		{
			int wait = S.front(); // adding wait time to wait variable in state
			totalwaitS = totalwaitS + (x - wait);
			cout << "Car " << S.front() << " departed" << endl;
			S.pop();
		}
		NrOfVehiclesAtNLight -= NrOfVehiclesDepartN;
		NrOfVehiclesAtSLight -= NrOfVehiclesDepartS;
		if (NrOfVehiclesAtNLight <= 0)
		{
			NrOfVehiclesAtNLight = 0;
		}
		if (NrOfVehiclesAtSLight <= 0)
		{
			NrOfVehiclesAtSLight = 0;
		}
		cout << "Number of vehicles at North light: " << NrOfVehiclesAtNLight << endl;
		cout << "Number of vehicles at South light: " << NrOfVehiclesAtSLight << endl;

		totalDepartN += NrOfVehiclesDepartN;
		totalDepartS += NrOfVehiclesDepartS;
	}

	cout << "Press enter to continue.." << endl;
	cin.ignore();
}

/**************************************************
** Function: nrOfVehiclesArrive()
** Description: For each direcion, generates random numbers for vehicles arriving using rand().  Outputs to the screen
** the number of cars that departed.  Then this value is subtracted from the total cars at each direction light.
** For each direction, the number of cars arriving is adding to its respective Queue STL queue push() with the timeStamp of the int in 
** parameter as its identifier for when it arrived.

** Parameters: Pointers to Queue objects and an int
** Pre-Conditions: None
** Post-Condition: Outputs messages to screen indicating number of cars arriving in each lane.
******************************************************************/
void State::nrOfVehiclesArrive(queue<int> &E, queue<int> &W, queue<int> &N, queue<int> &S, int x)
{
	if (EW == 'G')
	{
		int NrOfVehiclesArriveE = rand() % 12;
		int NrOfVehiclesArriveW = rand() % 12;
		cout << NrOfVehiclesArriveE << " vehicles arrived at the East light." << endl;
		for (int i = 0; i < NrOfVehiclesArriveE; i++)
		{
			E.push(x);
		}


		cout << NrOfVehiclesArriveW << " vehicles arrived at the West light." << endl;
		for (int i = 0; i < NrOfVehiclesArriveW; i++)
		{
			W.push(x);
		}


		NrOfVehiclesAtELight += NrOfVehiclesArriveE; 
		NrOfVehiclesAtWLight += NrOfVehiclesArriveW; 

		totalArrivalE += NrOfVehiclesArriveE;
		totalArrivalW += NrOfVehiclesArriveW;
	}
	if (NS == 'G')
	{
		int NrOfVehiclesArriveN = rand() % 12;
		int NrOfVehiclesArriveS = rand() % 12;
		cout << NrOfVehiclesArriveN << " vehicles arrived at the North light." << endl;
		for (int i = 0; i < NrOfVehiclesArriveN; i++)
		{
			N.push(x);
		}


		cout << NrOfVehiclesArriveS << " vehicles arrived at the South light." << endl;
		for (int i = 0; i < NrOfVehiclesArriveS; i++)
		{
			S.push(x);
		}


		NrOfVehiclesAtNLight += NrOfVehiclesArriveN;
		NrOfVehiclesAtSLight += NrOfVehiclesArriveS;

		totalArrivalN += NrOfVehiclesArriveN;
		totalArrivalS += NrOfVehiclesArriveS;
	}
}

/******************************************
** Getter functions for State
********************************/
char State::getEW()
{
	return EW;
}

char State::getNS()
{
	return NS;
}

State* State::getnextState()
{
	return nextState;
}
