#pragma once
#include <iostream>
#include "Node.h"
#include "ForwardNode.h"
#include "BackwardNode.h"

enum LINKLIST_MODE
{
	LINKLIST_FORWARD,
	LINKLIST_BACKWARD,
	TOTAL_LINKLIST_MODES,
};

template<class valueType>
class LinkList
{
public:
	LinkList(LINKLIST_MODE mode = LINKLIST_FORWARD);
	~LinkList();
	void InsertNode(const valueType& value);
	void DeleteNode(const unsigned index);
	valueType& operator[](const unsigned index) const;
	bool IsEmpty() const;
private:
	Node<valueType>* firstNode;
	LINKLIST_MODE mode;
};

template<class valueType>
LinkList<valueType>::LinkList(LINKLIST_MODE mode)
	:
firstNode(NULL),
mode(mode)
{
}

template<class valueType>
LinkList<valueType>::~LinkList()
{
	if(firstNode)
	{
		delete firstNode;
	}
}

template<class valueType>
void LinkList<valueType>::InsertNode(const valueType& value)
{
	if(firstNode)
	{
		firstNode = firstNode->InsertNode(value);
	}
	else
	{
		switch(mode)
		{
		case LINKLIST_FORWARD:
			firstNode = new ForwardNode<valueType>(value);
			break;
		case LINKLIST_BACKWARD:
			firstNode = new BackwardNode<valueType>(value);
		}
	}
}

template<class valueType>
void LinkList<valueType>::DeleteNode(const unsigned index)
{
	if(index == 0)
	{
		Node<valueType>* newFirstNode = firstNode->DeleteNode(0);
		delete firstNode;
		firstNode = newFirstNode;
	}
	else
	{
		firstNode = firstNode->DeleteNode(index);
	}
}

template<class valueType>
valueType& LinkList<valueType>::operator[](const unsigned index) const
{
	return firstNode->GetNode(index)->GetValue();
}

template<class valueType>
bool LinkList<valueType>::IsEmpty() const
{
	if(firstNode)
	{
		return false;
	}
	return true;
}