// File UnsortedList.h: Header file for Unsorted List ADT.
// Class is templated.
// Items are in a linked list.

/**************************************************************
*	Author:			Andy Giese, Ryan Grothose, Laura Hawkins, Michael Mihlbachler
*	Assignment:		8
*	Class:			CPS 151
*	Instructor:		V. Starkey
*	Due Date:		Wednesday, March 28
*	The purpose of this assignment is to properly implement the
*   functions defined in the Unlist2.h header file
*
**************************************************************/

#ifndef UNSORT_H
#define UNSORT_H

template <class ItemType>
struct NodeType;

// Assumption:  ItemType is a type for which the operators "<" and "==" are // defined
// either an appropriate built-in type or a class that overloads these operators.

template <class ItemType>
class UnsortedType   
{
public:
    UnsortedType();				// Class constructor

    ~UnsortedType();   	        // Class destructor

	UnsortedType(const UnsortedType& source);
	//copy constructor

	UnsortedType operator =(const UnsortedType& source);
	//assignment operator


    bool IsFull() const;
    //pre:  none
    //post: returns true if list is full; false if not

    int  LengthIs() const;
	//pre:  none
    //post: Function value = number of elements in list.

    void MakeEmpty();
    //pre:  none
    //post: List is empty.

    bool RetrieveItem(ItemType& item);
    //pre:  Key member of item is initialized.
    //post: If there is an element someItem whose key matches item's key,
    //      then item is a copy of someItem and returns true; otherwise
    //      item is unchanged and returns false.  List is unchanged.

    bool InsertItem(ItemType item);
    //pre:  none
    //post: if list is not full or if item is already in list, returns false
	//		else item is added to list and returns true

    bool DeleteItem(ItemType item);
    //pre:  Key member of item is initialized.
    //post: Returns false if list is empty or item is not in list; else
	//		first occurrence of item is removed from list and returns true

    void ResetList();
	//pre:  none
    //post: List has been set for an iteration through the list

    bool GetNextItem(ItemType& item);
    //pre:  list has not been modified since last call to ResetList or GetNextItem
    //post: returns false if list is empty or already at last item
    //      else, item is a copy of next element and returns true

	bool removeMin(ItemType& item);
	//pre:  Comparison operators must be defined for ItemType
	//post: if list is empty, returns false and item is unchanged
	//	    else, item contains the minimum element of self, item has been removed from self,
	//	    and returns true

	int replaceItems(ItemType oldItem, ItemType newItem);
	//pre:  none
	//post: replaces all occurrences of oldItem with newItem
	//	     returns number of replacements made
	

	void merge(UnsortedType& listA, UnsortedType& listB);
	//pre:  none
	//post: self contains all items (and only those items) from listA and listB
	//	     listA and listB are empty
	

	void splitLists(UnsortedType& listA, UnsortedType& listB, ItemType item);
	//pre:  none
	//post: listA contains all items (and only those items) from self that are <= item ; 
	//	     listB contains all items (and only those items) from self that are > item.  
	//	     Self is unchanged. 

	void updateItem(ItemType item);
	//pre: none
	//post: sets currentPos-> info to item


private:
    NodeType<ItemType>* listData;
    int length;
    NodeType<ItemType>* currentPos;
};

#include "UnsortedList.cpp"

#endif