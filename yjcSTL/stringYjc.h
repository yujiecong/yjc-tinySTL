#pragma once
#include <memory>

class stringYjc
{
public:
	stringYjc()
	{
		_length = 0;
		_chars = nullptr;
	}
	stringYjc(char chars[]);
	stringYjc(long long i2s);
	~stringYjc();

	stringYjc& operator+(const stringYjc& rhs);
private:
	char *_chars;
	int _length;
};

 

