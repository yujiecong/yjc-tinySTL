#pragma once

//迭代器实现
template<typename value_type>
class MyIterator {

public:
	typedef value_type* value_pointer;
	// constructor
	MyIterator(value_pointer thePosition = 0) { position = thePosition; }
	//重写加减
	// increment
	MyIterator& operator++()   // preincrement
	{
		++position;
		return *this;
	}
	MyIterator operator++(int) // postincrement
	{
		MyIterator old = *this;
		++position;
		return old;
	}

	// decrement
	MyIterator& operator--()   // predecrement
	{
		--position;
		return *this;
	}
	MyIterator operator--(int) // postdecrement
	{
		MyIterator old = *this;
		--position;
		return old;
	}
	int MyIterator operator-(const MyIterator &other)
	{
		return other;
	}

private:
	value_pointer position;


};