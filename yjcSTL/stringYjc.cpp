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
	//���ܻ����
//��intת��i2s����

}



stringYjc& stringYjc::operator+(const stringYjc& rhs)
{
	// TODO: �ڴ˴����� return ���
	//�����ַ������


	return *this;
}
