#include "stringYjc.h"

inline stringYjc::stringYjc(char chars[])
{
	int leng = strlen(_chars);
	_chars = new char[leng];
	for (int i = 0; i<leng; i++)
	{
		_chars[i] = chars[i];
	}
}

stringYjc::stringYjc(long long i2s)
{
	//可能会溢出
//将int转成i2s保存

}



stringYjc& stringYjc::operator+(const stringYjc& rhs)
{
	// TODO: 在此处插入 return 语句
	//两个字符串相加


	return *this;
}
