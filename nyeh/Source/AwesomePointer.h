#pragma once

template<class t = NULL>
class AwesomePointer
{
public:
	AwesomePointer(t* location);
	~AwesomePointer();
	t* operator->();
	t* operator++();
private:
	t* pointer;
};

template<class t>
AwesomePointer<t>::AwesomePointer(t* location)
{
}

template<class t>
AwesomePointer<t>::~AwesomePointer()
{
}

template<class t>
t* AwesomePointer<t>::operator->()
{
	return pointer;
}

template<class t>
t* AwesomePointer<t>::operator++()
{
	++pointer;
	return t;
}