#pragma once
#include <iostream>

template<class nodeType>
class Node
{
public:
	Node(const nodeType& value = nodeType());
	~Node();
	nodeType& GetValue();
	void SetValue(const nodeType value);
	Node* DeleteNode(const unsigned node);
	Node* GetNode(const unsigned index); //creates a node if index is out of range
	void SetNext(Node* node);
	virtual Node<nodeType>* InsertNode(const nodeType& insertValue) = 0;
protected:
	nodeType value;
	Node* next;
};

template<class nodeType>
Node<nodeType>::Node(const nodeType& value)
	:
next(NULL),
value(value)
{
}

template<class nodeType>
Node<nodeType>::~Node()
{
	delete next;
}

template<class nodeType>
nodeType& Node<nodeType>::GetValue()
{
	return value;
}

template<class nodeType>
void Node<nodeType>::SetValue(const nodeType value)
{
	this->value = value;
}

template<class nodeType>
Node<nodeType>* Node<nodeType>::DeleteNode(const unsigned index)
{
	//if we need to delete our next and it exists
	if(index == 1 && next)
	{
		next = next->next;
		next->next = NULL;
		delete next;
		return this;
	}
	//the only way this is possible is if we were to delete the first node in the list.
	//In that case, we simply let the list do the deletion.
	if(index == 0)
	{
		Node<nodeType>* newFirstNode = next;
		next = NULL;
		return newFirstNode;
	}
	return next = next->DeleteNode(index - 1);
}

template<class nodeType>
Node<nodeType>* Node<nodeType>::GetNode(const unsigned index)
{
	if(index == 0)
	{
		return this;
	}
	return next->GetNode(index - 1);
}

template<class nodeType>
void Node<nodeType>::SetNext(Node* node)
{
	if(next)
	{
		node->SetNext(next);
	}
	next = node;
}