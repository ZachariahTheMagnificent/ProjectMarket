#pragma once
#include "Node.h"

template<class nodeType>
class ForwardNode : public Node<nodeType>
{
public:
	ForwardNode();
	ForwardNode(const nodeType& value);
	~ForwardNode();
	Node<nodeType>* InsertNode(const nodeType& insertValue);
};

template<class nodeType>
ForwardNode<nodeType>::ForwardNode()
{
}

template<class nodeType>
ForwardNode<nodeType>::ForwardNode(const nodeType& value)
	:
Node(value)
{
}

template<class nodeType>
ForwardNode<nodeType>::~ForwardNode()
{
}

template<class nodeType>
Node<nodeType>* ForwardNode<nodeType>::InsertNode(const nodeType& insertValue)
{
	//if our value is smaller than us, insert it behind us
	if(insertValue <= value)
	{
		Node<nodeType>* insertNode = new ForwardNode<nodeType>(insertValue);
		insertNode->SetNext(this);
		return insertNode;
	}
	if(next)
	{
		next = next->InsertNode(insertValue);
		return this;
	}
	Node<nodeType>* insertNode = new ForwardNode<nodeType>(insertValue);
	next = insertNode;
	return this;
}