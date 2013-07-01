// Implementation file for Unsorted List ADT.
// Class specification in file UnsortedList.h
// Class is templated.

/*****************************************************************
//Author: Andy Giese
//Date Created: April 2007
//Last Modified: April 26 2007
//This is is the header file implenting an Unsorted Linked List ADT
******************************************************************/


template<class ItemType>
struct NodeType
{
    ItemType info;
    NodeType* next;
};

template <class ItemType>		
UnsortedType<ItemType>::UnsortedType()		// Class constructor
{
    length = 0;
    listData = NULL;
	currentPos = NULL;
}


template <class ItemType>
UnsortedType<ItemType>::~UnsortedType()
{
    NodeType<ItemType>* tempPtr;

    while (listData != NULL)
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
}

template <class ItemType>
UnsortedType<ItemType>::UnsortedType(const UnsortedType& source)
{
	
	NodeType<ItemType>* sourcePtr;
	NodeType<ItemType>* selfPtr;

	if (source.listData == NULL)
		listData = NULL;
	else
	{
		//copy first node from source 
		listData = new NodeType<ItemType>;
		if (listData == NULL)
		{
			cout << "Insufficient memory.\n";
			exit(1);
		}
		listData->info = source.listData->info;
		sourcePtr = source.listData->next;
		selfPtr = listData;
		
		//copy rest of items
		while (sourcePtr != NULL)
		{
			selfPtr->next = new NodeType<ItemType>;
			if (selfPtr->next == NULL)
			{
				cout << "Insufficient memory.\n";
				exit(1);
			}
			selfPtr = selfPtr->next;
			selfPtr->info = sourcePtr->info;
			sourcePtr = sourcePtr->next;
		}
		selfPtr->next = NULL;
	}
	length = source.length;
}

template <class ItemType>
UnsortedType<ItemType> UnsortedType<ItemType>::operator =(const UnsortedType& source)
{
	//check x=x case
	if (this == &source)
		return *this;

	NodeType<ItemType>* sourcePtr;
	NodeType<ItemType>* selfPtr;

	//delete existing list before assigning it the values in rtList  
    while (listData != NULL)
    {
        selfPtr = listData;
        listData = listData->next;
        delete selfPtr;
    }

	//copy source list
	if (source.listData == NULL)
		listData = NULL;
	else
	{
		//copy first node from source 
		listData = new NodeType<ItemType>;
		if (listData == NULL)
		{
			cout << "Insufficient memory.\n";
			exit(1);
		}
		listData->info = source.listData->info;
		sourcePtr = source.listData->next;
		selfPtr = listData;
		
		//copy rest of items
		while (sourcePtr != NULL)
		{
			selfPtr->next = new NodeType<ItemType>;
			if (selfPtr->next == NULL)
			{
				cout << "Insufficient memory.\n";
				exit(1);
			}
			selfPtr = selfPtr->next;
			selfPtr->info = sourcePtr->info;
			sourcePtr = sourcePtr->next;
		}
		selfPtr->next = NULL;
	}
	length = source.length;
	return *this;
}
    
template <class ItemType>
bool UnsortedType<ItemType>::IsFull() const
{
    NodeType<ItemType>* ptr;

    ptr = new NodeType<ItemType>;
    if (ptr == NULL)
        return true;
    else
    {
        delete ptr;
        return false;
    }
}

template <class ItemType>
int UnsortedType<ItemType>::LengthIs() const
{
    return length;
}

template <class ItemType>
void UnsortedType<ItemType>::MakeEmpty()
{
    NodeType<ItemType>* tempPtr;

    while (listData != NULL)
    {
        tempPtr = listData;
        listData = listData->next;
        delete tempPtr;
    }
    length = 0;
}

template <class ItemType>
bool UnsortedType<ItemType>::RetrieveItem(ItemType& item)
{
    NodeType<ItemType>* tempPtr;

    tempPtr = listData;
    while (tempPtr != NULL)
    {
        if (tempPtr->info == item)
        {
            item = tempPtr->info;
			return true;
        }
        else
        {
            tempPtr = tempPtr->next;
        }
    }
	return false;
}

template <class ItemType>
bool UnsortedType<ItemType>::InsertItem(ItemType item)
{
    NodeType<ItemType>* tempPtr;
	
    tempPtr = new NodeType<ItemType>;
	if (tempPtr == NULL)
		return false;


	
    tempPtr->info = item;
    tempPtr->next = listData;
    listData = tempPtr;
    length++;
	return true;
}


template <class ItemType>
void UnsortedType<ItemType>::ResetList()
{
  	currentPos = listData;
}
 
template <class ItemType>
bool UnsortedType<ItemType>::GetNextItem(ItemType& item)
{
	if (currentPos == NULL)
		return false;
	else
	{
		item = currentPos->info;
		currentPos = currentPos->next;
		return true;
	}

} 

template <class ItemType>
void UnsortedType<ItemType>::updateItem(ItemType item)
{
	NodeType<ItemType>* nextPos;
	nextPos = listData;
	//search for item to update
	while (nextPos!=NULL && nextPos->info != item)
	{
		nextPos = nextPos->next;
	}
	if (nextPos!=NULL)
	{
		//if item is found, update it
		if (nextPos->info == item)
		{
			nextPos->info = item;
			//cout << "Item updated" << endl;
			//cout << item << endl;
			currentPos = nextPos->next;
		}
	}

	//else list remains unchanged
}