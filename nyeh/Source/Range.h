#pragma once
/****************************************************************************/
/*!
\file Range.h
\author Muhammad Shafik Bin Mazlinan
\par email: cyboryxmen@yahoo.com
\brief
A class used to see if a value is within a certain range
*/
/****************************************************************************/

/****************************************************************************/
/*!
Class Range:
\brief
Checks whether a value is within a certain range
*/
/****************************************************************************/
template<class type = int>
class Range
{
public:
	Range(const type& start = type(), const type& end = type());
	~Range();
	const type& Start() const;
	const type& End() const;
	const Range<type>& Set(const type& start, const type& end);
	const type& Start(const type& newStart);
	const type& End(const type& newEnd);
	type Length() const;
	type MidPoint() const;
	bool IsInRange(const type& test) const;
private:
	type start;
	type end;
};
/****************************************************************************/
/*!
\brief
default constructor that defines the start and end of a range
\param start
		defines the start of the range
\param end
		defines the end of the range
*/
/****************************************************************************/
template<class type>
Range<type>::Range(const type& start, const type& end)
	:
start(start),
end(end)
{	
}
/****************************************************************************/
/*!
\brief
empty default destructer
*/
/****************************************************************************/
template<class type>
Range<type>::~Range()
{
}
/****************************************************************************/
/*!
\brief
function to check if a value is in our range
\param test
		the value that will be checked against
*/
/****************************************************************************/
template<class type>
bool Range<type>::IsInRange(const type& test) const
{
	if(test >= start && test <= end)
	{
		return true;
	}
	return false;
}
/****************************************************************************/
/*!
\brief
function to return our start
*/
/****************************************************************************/
template<class type>
const type& Range<type>::Start() const
{
	return start;
}
/****************************************************************************/
/*!
\brief
function to return our end
*/
/****************************************************************************/
template<class type>
const type& Range<type>::End() const
{
	return end;
}
/****************************************************************************/
/*!
\brief
function to define and return a new start value
\param newStart
		the value that start will be set to
*/
/****************************************************************************/
template<class type>
const type& Range<type>::Start(const type& newStart)
{
	return start = newStart;
}
/****************************************************************************/
/*!
\brief
function to define and return a new end value
\param newEnd
		the value that end will be set to
*/
/****************************************************************************/
template<class type>
const type& Range<type>::End(const type& newEnd)
{
	return end = newEnd;
}
/****************************************************************************/
/*!
\brief
function to define and return a new start value
\param newStart
		the value that start will be set to
*/
/****************************************************************************/
template<class type>
type Range<type>::Length() const
{
	return abs(end - start) + 1;
}
/****************************************************************************/
/*!
\brief
function return our midpoint
*/
/****************************************************************************/
template<class type>
type Range<type>::MidPoint() const
{
	return start + (Length() - 1)/2;
}
/****************************************************************************/
/*!
\brief
A set function to set our values
\param start
		the value our start will be set to
\param end
		the value our end will be set to
*/
/****************************************************************************/
template<class type>
const Range<type>& Range<type>::Set(const type& start, const type& end)
{
	this->start = start;
	this->end = end;
	return *this;
}