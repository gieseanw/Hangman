//Leaderboard.cpp
//Implementation of Leaderboard API
//Mostly a linked list with a max value of 7

#include <iostream>
#include <string>
using namespace std;
#include "Leaderboard.h"


Leaderboard::Leaderboard(): m_numNames(0), m_info(NULL){}//end of default constructor

Leaderboard::Leaderboard(const Leaderboard& _leader){	
	//initialize with specified leaderboard object

	m_numNames = _leader.m_numNames;

	//move through info
	Name* tempPtr = _leader.m_info;
	if (tempPtr == NULL){
		m_info = NULL;
	}
	else{
		//create a Temp Name
		Name *temp;
		temp = new Name;

		//check for inability to allocate memory
		if (temp == NULL)
		{
			cout << "Allocation of memory failed Leaderboard.cpp" << endl;
			system("pause");
			exit(1);
		}
		
		//initialize Temp Name
		temp->m_theName = tempPtr->m_theName;
		temp->m_points = tempPtr->m_points;
		temp->m_numWords = tempPtr->m_numWords;
		temp->m_next = tempPtr->m_next;
		tempPtr = tempPtr->m_next;
		m_info = temp;

		//step through leaderboard, and link it to new leaderboard
		while (tempPtr != NULL){
			temp = temp->m_next;
			temp->m_theName = tempPtr->m_theName;
        	temp->m_points = tempPtr->m_points;
			temp->m_numWords = tempPtr->m_numWords;
			temp->m_next = tempPtr->m_next;
			tempPtr = tempPtr->m_next;
		}
	}

}//end of copy constructor

Leaderboard::~Leaderboard(){
	//deallocate memory for each object in leaderboard
	Name* tempPtr;
	tempPtr = m_info;
	while (tempPtr != NULL){
		Name* delPtr = tempPtr;
		tempPtr = tempPtr->m_next;
		delete delPtr;
	}
}//end of destructor


bool Leaderboard::Insert (const Name& _newName){
	 if(InsertHelp(_newName,m_info)){

		//check for overpopulation
		while(m_numNames > MAX_NAMES){
			Name* killPtr = m_info;
			while (killPtr->m_next != NULL)
				killPtr = killPtr->m_next;
			delete killPtr;
			m_numNames--;	
		}
		return true;
	 }
	 else
		 return false;
}//end of Insert function

bool Leaderboard::InsertHelp(const Name& _newName, Name*& _t){
	if ((_t == NULL) || (_t->m_points < _newName.m_points)){
		Name* temp = new Name;
		if (temp == NULL){
			cout << "Allocation of memory failed Leaderboard.cpp" << endl;
			system("pause");
			exit(1);
		}
		
		//add item in at appropriate position
		temp->m_theName = _newName.m_theName;
		temp->m_points = _newName.m_points;
		temp->m_numWords = _newName.m_numWords;
		temp->m_next = _t;
		_t = temp;
		m_numNames++;
		return true;
	}
	else
		return InsertHelp(_newName,_t->m_next);
}

bool Leaderboard::Delete(Name aName){

	//check for empty list
	if (m_info == NULL)
		return false;

	//check for first item
	if (m_info->m_theName == aName.m_theName && m_info->m_points == aName.m_points
		&& m_info->m_numWords == aName.m_numWords){
		Name* killPtr = m_info;
		m_info = m_info->m_next;
		delete killPtr;
		m_numNames--;
		return true;
	}

	//scan rest of list
	Name* tempPtr = m_info;
	while  (tempPtr->m_next != NULL && tempPtr->m_next->m_theName != aName.m_theName && tempPtr->m_next->m_points != aName.m_points
		&& tempPtr->m_next->m_numWords != aName.m_numWords)
		tempPtr = tempPtr->m_next;

	if (tempPtr->m_next == NULL)
		return false;

	//else, we're sitting at the node before the one we wish to delete
	Name* killPtr = tempPtr->m_next;
	tempPtr->m_next = killPtr->m_next;
	delete killPtr;
	m_numNames--;
	return true;

}//end of Delete function

bool Leaderboard::MakeEmpty(){
	//check for empty list
	if (m_info == NULL)
		return true;
	//list is not empty, deallocate memory from all nodes
	Name* killPtr = m_info;
	while (killPtr != NULL){
		m_info = m_info->m_next;
		delete killPtr;
		m_numNames--;
		killPtr = m_info;
	}
	return true;
}//end of MakeEmpty()

bool Leaderboard::IsHighScore(size_t _newPoints) const{
	//check for unfilled list
	if (m_numNames < MAX_NAMES){
		return true;
	}

	//check each node's points
	Name *namePtr = m_info;
	while (namePtr != NULL)
	{
		if (_newPoints >= namePtr->m_points)
			return true;
		namePtr = namePtr->m_next;
	}
	return false;

}//end of isHighScore() function

istream& operator >> (istream& _fin, Leaderboard& _leader){
	//clear leader
	Name* killPtr;
	while(_leader.m_info !=NULL){
		killPtr = _leader.m_info;
		_leader.m_info = _leader.m_info->m_next;
		delete killPtr;
	}
	cout << "Former names cleared" << endl;
	//declare variables
	string name;
	int points, wordAmt;
	Name* tempName = new Name;
	if (tempName == NULL){
		cout << "Allocation of memory failed Leaderboard.cpp" << endl;
		system("pause");
		exit(1);
	}
	Name* currentPtr;

	//get input
	while (isspace(_fin.peek()))
		_fin.ignore();
	_fin >> name;
	_fin >> points;
	_fin >> wordAmt;
	if (_fin.fail()){
		cout << "Error loading leaderboard files" << endl;
		exit(1);
	}
	tempName->m_theName = name;
	tempName->m_points = points;
	tempName->m_numWords = wordAmt;
	tempName->m_next = NULL;

	//set first one to info
	_leader.m_info = tempName;
	currentPtr = _leader.m_info;
	_leader.m_numNames++;

	_fin >> name;
	
	while (!_fin.fail()){
		_fin >> points;
		_fin >> wordAmt;

		tempName = new Name;
		if (tempName == NULL){
			cout << "Allocation of memory failed at Leaderboard.cpp" << endl;
			system("pause");
			exit(1);
		}
		while (isspace(_fin.peek()))
			_fin.ignore();

		tempName->m_theName = name;
		tempName->m_points = points;
		tempName->m_numWords = wordAmt;
		tempName->m_next = NULL;
		currentPtr->m_next = tempName;
		currentPtr = currentPtr->m_next;
		_leader.m_numNames++;

		_fin >> name;

	}
	return _fin;
}//end of overloaded operator

ostream& operator << (ostream& _fout, const Leaderboard& _leader){
	_fout << "Name		|     Score    |    Words" << endl;
	_fout << "---------------------------------------------" << endl;
	Name* tempName = _leader.m_info;
	size_t count = 0;
	while (count < _leader.m_numNames ){
		
		_fout << tempName->m_theName << "\t\t\t" << tempName->m_points << "\t\t" << tempName->m_numWords 
			<< endl;
		count++;
		tempName = tempName->m_next;
		
	}//end of while loop

	return _fout;
}// end of overloaded ostream operator
