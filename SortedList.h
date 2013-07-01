// SortedList.h: Header file for Sorted List ADT.
// Class is templated.

#ifndef SORTLIST_H
#define SORTLIST_H


#include <fstream>
#include <string>
using namespace std;

template <class ItemType>
struct NodeType;

// Assumption:  ItemType is a type for which the operators
// "<" and "==" are defined--either an appropriate
// built-in type or a class that overloads these operators.


template <class ItemType>
class SortedType
{
public:
    SortedType   ();			// Class constructor
    ~SortedType   (); 			// Class destructor

	SortedType(const SortedType& source);
	//copy constructor

	SortedType operator = (const SortedType& rhs);
	//assignment operator

	string getName() const;
	//Pre: none
	//Post: returns name of List

    bool IsFull() const;
    // Function: Determines whether list is full.
    // Post: Function value = (list is full)

    int  LengthIs() const;
    // Function: Determines the number of elements in list.
    // Post: Function value = number of elements in list.

    void MakeEmpty();
    // Function: Initializes list to empty state.
    // Post:  List is empty.

	void setName(string newName);
	//pre: none
	//post: sets name of list to newName

    bool RetrieveItem(ItemType& item);
    // Function: Retrieves list element whose key matches item's key (if present).
    // Pre:  Key member of item is initialized.
    // Post: If there is an element in the list whose key matches item's key,
    //       then item is a copy of that element and function returns true;
	//       else, item is unchanged and function returns false
    //       List is unchanged.

    bool InsertItem(ItemType item); 
    // Function: Adds item to list.
    // Pre:  List is not full
    // Post: item is in list.

    int DeleteItem(ItemType item);
    // Function: Deletes the element whose key matches item's key.
    // Pre:  Key member of item is initialized.
    // Post: deletes all occurences of item in the list and returns number of
	//		 items deleted

    void ResetList();
    // Function: Initializes current position for an iteration through the list.   
    // Post: Current position is prior to list.

    bool GetNextItem(ItemType&);
    // Function: Gets the next element in list.
    // Pre:  no changes to the list have been made since last call to ResetList
	//       or since last call to GetNextItem
    // Post: if list is empty or no more items exist, function returns false
	//       else, item is a copy of next item in the list and function returns true

	void RevPrint(ostream& fout);
	//Function:  Prints list in reverse order
	//pre:  none
	//post: items are printed to fout in reverse order

	void PrintToFile(ostream& fout);
	//Function:  Prints list to fout
	//pre:  itemType defines << operator
	//post: items are printed to fout

	bool operator == (const SortedType& source);
	//pre:
	//post:

	bool operator < (const SortedType& source);
	//pre:
	//post:

	bool operator != (const SortedType& source);
	//pre:
	//post:

	bool operator > (const SortedType& source);
	//pre:
	//post: 
	

private:
    NodeType<ItemType>* listData;
    int length;
	string name;
    NodeType<ItemType>* currentPos;

	//helper functions for recursive implementation:
	bool InsertItemHelp(ItemType item, NodeType<ItemType>* &listHead);
	int DeleteItemHelp(ItemType item, NodeType<ItemType>* &listHead);
	void RevPrintHelp(ostream& fout, NodeType<ItemType>* listHead);
	bool RetrieveItemHelp(ItemType& item, NodeType<ItemType>* listHead);
	void PrintToFileHelp(ostream& fout, NodeType<ItemType>* listHead);
};

#include "SortedList.cpp"

#endif