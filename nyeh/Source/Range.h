#pragma once

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

template<class type>
Range<type>::Range(const type& start, const type& end)
	:
start(start),
end(end)
{	
}

template<class type>
Range<type>::~Range()
{
}

template<class type>
bool Range<type>::IsInRange(const type& test) const
{
	if(test >= start && test <= end)
	{
		return true;
	}
	return false;
}

template<class type>
const type& Range<type>::Start() const
{
	return start;
}

template<class type>
const type& Range<type>::End() const
{
	return end;
}

template<class type>
const type& Range<type>::Start(const type& newStart)
{
	return start = newStart;
}

template<class type>
const type& Range<type>::End(const type& newEnd)
{
	return end = newEnd;
}

template<class type>
type Range<type>::Length() const
{
	return abs(end - start) + 1;
}

template<class type>
type Range<type>::MidPoint() const
{
	return start + (Length() - 1)/2;
}

template<class type>
const Range<type>& Range<type>::Set(const type& start, const type& end)
{
	this->start = start;
	this->end = end;
	return *this;
}