#pragma once
#include "Node.h"

template<class nodeType>
class BackwardNode : public Node<nodeType>
{
public:
	BackwardNode();
	BackwardNode(const nodeType& value);
	~BackwardNode();
	Node<nodeType>* InsertNode(const nodeType& insertValue);
};

template<class nodeType>
BackwardNode<nodeType>::BackwardNode()
{
}

template<class nodeType>
BackwardNode<nodeType>::BackwardNode(const nodeType& value)
	:
Node(value)
{
}

template<class nodeType>
BackwardNode<nodeType>::~BackwardNode()
{
}

template<class nodeType>
Node<nodeType>* BackwardNode<nodeType>::InsertNode(const nodeType& insertValue)
{
	//if our value is smaller than us, insert it behind us
	if(insertValue > value)
	{
		Node<nodeType>* insertNode = new BackwardNode<nodeType>(insertValue);
		insertNode->SetNext(this);
		return insertNode;
	}
	if(next)
	{
		next = next->InsertNode(insertValue);
		return this;
	}
	Node<nodeType>* insertNode = new BackwardNode<nodeType>(insertValue);
	next = insertNode;
	return this;
}