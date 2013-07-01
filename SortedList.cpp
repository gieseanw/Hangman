// Implementation file for Sorted List ADT.
// Class specification is in file SortedList.h.
// Class is templated.


template <class ItemType>		
SortedType<ItemType>::SortedType()	
{
    length = 0;
	name = "Default";
    listData = NULL;
}

template <class ItemType>
SortedType<ItemType>::SortedType(const SortedType& source)
{
	//initialize variables 
	length = source.length;
	name = source.name;
	listData = NULL;

	NodeType<ItemType>* sourcePtr;
	NodeType<ItemType>* targetPtr;
	NodeType<ItemType>* targetEndPtr;

	//copy nodes from source
	sourcePtr = source.listData;
	while (sourcePtr != NULL)
	{
		targetPtr = new NodeType<ItemType>;
		targetPtr->info = sourcePtr->info;
		if (listData == NULL)
		{
			listData = targetPtr;
			targetEndPtr = targetPtr;
		}
		else
		{
			targetEndPtr->next = targetPtr;
			targetEndPtr = targetPtr;
		}
		targetPtr->next = NULL;
		sourcePtr = sourcePtr->next;	
	}
}


template <class ItemType>
SortedType<ItemType>::~SortedType()
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
SortedType<ItemType> SortedType<ItemType>::operator =(const SortedType& source)
{
	//check x=x case
	if (this == &source)
		return(*this);

    NodeType<ItemType>* sourcePtr;
	NodeType<ItemType>* targetPtr;
	NodeType<ItemType>* targetEndPtr;

	//delete existing list before assigning it the values in rtList
    while (listData != NULL)
    {
        targetPtr = listData;
        listData = listData->next;
        delete targetPtr;
    }
	length = source.length;
	name = source.name;

	//copy nodes from rhs
	sourcePtr = source.listData;
	while (sourcePtr != NULL)
	{
		targetPtr = new NodeType<ItemType>;
		targetPtr->info = sourcePtr->info;
		if (listData == NULL)
		{
			listData = targetPtr;
			targetEndPtr = targetPtr;
		}
		else
		{
			targetEndPtr->next = targetPtr;
			targetEndPtr = targetPtr;
		}
		targetPtr->next = NULL;
		sourcePtr = sourcePtr->next;	
	}
	
	return (*this);
}
   	

template <class ItemType>
bool SortedType<ItemType>::IsFull() const
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
string SortedType<ItemType>::getName() const
{
	return name;
}

template <class ItemType>
int SortedType<ItemType>::LengthIs() const
{
    return length;
}

template <class ItemType>
void SortedType<ItemType>::MakeEmpty()
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
void SortedType<ItemType>::setName(string newName)
{
	name = newName;
}

template <class ItemType>
bool SortedType<ItemType>::RetrieveItem(ItemType& item)
{
    
	
	return RetrieveItemHelp(item,listData);
}


template <class ItemType>
bool SortedType<ItemType>::InsertItem(ItemType item)
{
    return InsertItemHelp(item, listData);
}



template <class ItemType>
void SortedType<ItemType>::ResetList()
{
    currentPos = listData;
}
 
template <class ItemType>
bool SortedType<ItemType>::GetNextItem(ItemType& item)
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
int SortedType<ItemType>::DeleteItem(ItemType item)
{
    return DeleteItemHelp(item, listData);
} 

template <class ItemType>
void SortedType<ItemType>::RevPrint(ostream& fout)
{
	RevPrintHelp(fout, listData);
}

template <class ItemType>
void SortedType<ItemType>::PrintToFile(ostream& fout)
{
	PrintToFileHelp(fout, listData);
}



template <class ItemType>
bool SortedType<ItemType>::InsertItemHelp(ItemType item, NodeType<ItemType>* &listHead)
{
	if ((listHead == NULL) || (listHead->info > item))
	{
		NodeType<ItemType>* tempPtr = new NodeType<ItemType>;
		if (tempPtr == NULL)
			return false;
		tempPtr->info = item;
		tempPtr->next = listHead;
		listHead = tempPtr;
		length++;
		return true;
	}
	else if (listHead->info == item)
		return false;
	else
		return InsertItemHelp(item, listHead->next);
}

template <class ItemType>
int SortedType<ItemType>::DeleteItemHelp(ItemType item, NodeType<ItemType>* &listHead)
{
	if (listHead == NULL)
		return 0;

	NodeType<ItemType>* tempPtr = listHead;
	if (listHead->info == item)
	{
		tempPtr = listHead;
		listHead = listHead->next;
		delete tempPtr;
		length--;
		return 1 + DeleteItemHelp(item, listHead);
	}
	else
		return DeleteItemHelp(item, listHead->next);

}



template <class ItemType>
void SortedType<ItemType>::RevPrintHelp(ostream& fout, NodeType<ItemType>* listHead)
{
	if (listHead == NULL)
		return;
	RevPrintHelp(fout, listHead->next);
	fout << listHead->info << " ";
}

template <class ItemType>
void SortedType<ItemType>::PrintToFileHelp(ostream& fout, NodeType<ItemType>* listHead)
{
	if (listHead == NULL)
		return;
	fout << listHead->info << endl;
	PrintToFileHelp(fout, listHead->next);
}

template <class ItemType>
bool SortedType<ItemType>::RetrieveItemHelp(ItemType &item, NodeType<ItemType> *listHead)
{
	
	if (listHead == NULL || listHead->info > item)
		return false;
	else
	{
		if (listHead->info == item)
		{
			item = listHead->info;
			return true;
		}
		return RetrieveItemHelp(item, listHead->next);
	}

}//end of RetriveItemHelp function


template <class ItemType>
bool SortedType<ItemType>::operator == (const SortedType& source)
{
	if (name == source.name)
		return true;
	return false;
}

template <class ItemType>
bool SortedType<ItemType>::operator < (const SortedType& source)
{
	if (name < source.name)
		return true;
	return false;

}

template <class ItemType>
bool SortedType<ItemType>::operator != (const SortedType& source)
{
	if (name != source.name)
		return true;
	return false;
}

template <class ItemType>
bool SortedType<ItemType>::operator > (const SortedType& source)
{
	if (name > source.name)
		return true;
	return false;
}