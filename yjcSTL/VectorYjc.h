#pragma once
#include<iostream>
//#include"iterator.h"
#define MAX_LENGTH 100000//��������ռ�
#define GET_NAME(value) (#value)
#define DEFAULT_SIZE 0
#define NO_MALLOC NULL
using std::string;
using std::cout;
using std::endl;
static int defaultId; //vector��¼����
template<typename value_type>
class VectorYjc
{

public:
	typedef value_type* value_pointer;
	typedef value_type& value_reference;
	typedef value_type value_type;
	//����һ�������� ����Ϊ

	VectorYjc()
	{
		isPointer = typeIsPointer();
		_capacity=DEFAULT_SIZE;//Ĭ�Ϸ���Ԫ�� �ռ� 
		_array = nullptr;
		createDefaultName();
	
	}//Ĭ�Ϲ��� �յ�����
	~VectorYjc()
	{
		defaultId--;
		delete[]_array;
	}
	//����ָ����С
	VectorYjc(int capacity):VectorYjc(){
		if (capacity > MAX_LENGTH or capacity < 0) {
			throw "�����vector����! Wrong vector length!";
		}
		_capacity = capacity;
		_array = new value_type[_capacity];

		initVector();
		
	}
	VectorYjc(int capacity,std::string name):VectorYjc(capacity) {
		createDefaultName(name);
	}
	VectorYjc(const VectorYjc& rhs)
	{
		//֤���Ƿ�ͬһ������
		if (this!=&rhs)
		{
			_size = rhs._size;
			_capacity = rhs._capacity;
			isPointer = rhs.isPointer;
			_name = rhs._name;
			_array = new value_type[_capacity];
			for (std::size_t i = 0; i < _size; i++)
			{
				//�����ֵ��Ҳ����ν,�������ָ����?
				//��Ҫ���
				if (isPointer)
				{
					_array[i] = value_type(rhs._array[i]);
				}
				else {
					_array[i] = rhs._array[i];
				}
			
			}
		}


	
	}
	VectorYjc& operator=(const VectorYjc& rhs) {
		//֤���Ƿ�ͬһ������
		if (this!=&rhs)
		{
			_size = rhs._size;
			_capacity = rhs._capacity;
			isPointer = rhs.isPointer;
			_name = rhs._name;
			_array = new value_type[_capacity];
			for (std::size_t i = 0; i < _size; i++)
			{
				_array[i] = rhs._array[i];
			}
		}
		return *this;
	}
	value_type& operator[](int idx)
	{
		//������

		//֧�ָ������� 
		// -1��������һ��
		// -2 �������ڶ���
		// �Դ����� -idx��ʾ������capacity�� Ҳ���ǵ�һ��
		if (isVaildIndex(idx)) {
			if (idx < 0) {
				idx = _size + idx;
			}
			return _array[idx];
		}
		getErrorIndex(idx);
	};
	//
	VectorYjc& operator+(const VectorYjc &rhs){
		//ʵ������������
		//ȫ��append����

	
		for (std::size_t i=0;i<rhs._size;i++)
		{
			value_type tmp = rhs._array[i];
			append(tmp);
		}

		return *this;
	}


	void initVector(value_type init = NULL)
	{
		for (int i = 0; i < this->_capacity; ++i) {
			this->_array[i] = init;
		}
	}//��ʼ��Ϊ0
	void createDefaultName(string name="") {
		if (name ==""){
			char defaultStr[10];
			sprintf_s(defaultStr, "%d", defaultId);
			_name = std::string("defaultName") + std::string(defaultStr);
			defaultId++;
		}
		else {
			_name = name;
		}

	}
	//���Ԫ��
	void append(value_type value) {

		//�ж��Ƿ��Ѿ����� ����
		if (_size < _capacity) {
		}
		else {
			//��� ����֮��Ҫ���¿�ʼ����ռ���
			//Ϊԭ����+1 ����
			resize((_capacity+1)<<1);
		}
		_array[_size++] = value;
		
	}
	//����Ԫ��
	void insert(value_type value,int pos) {
		//���pos����_size Ĭ���ڶ�β����
		//����� -1 ��ô���������ĵط�����

		if(pos==-1 || pos>=_size || isEmpty()){
			append(value);
			return;
		}
		//���-pos���� _size+1 Ĭ���ڶ�ͷ����

		// Ϊʲô�������ͨ��??
		// -pos=-1
		// _size+1=4
		if (abs(pos) >= _size + 1) {

			pos = 0;
		}

		
		//������м��ͷ ����
		if (isVaildIndex(pos)) {

			if (pos < 0) {
				pos = pos + _size;
			}
			else if (_size == 1 || pos==_size-1) {
				//ֻ�ܶ�ͷ���� pos=0
				value_type lastone = _array[_size-1];
				_array[pos] = value;
				append(lastone);
			}//����ʼ�ƶ������Ԫ��
			else {

				value_type lastone = _array[_size - 1];
				//type_value 
				for (int i = _size-2; i >= pos; i--) {
					
					_array[i+1] = _array[i];
				
				}

				_array[pos] = value;
		
				append(lastone);
		
				
			}
		}
		else {
				getErrorIndex(pos);
		}
	}
	value_type pop(int idx=-1) {
		//ע�� �����ڴ�й©�ķ���
		// ���pop����û�������ͷ� ʹ�� ��ô��й¶

		//Ĭ�ϵ������һ��Ԫ��
		//����һ���ط�ɾ��Ԫ�� Ȼ��������ǰ�ƶ�
		if (isVaildIndex(idx)) {
			value_type bePoped;
			if (idx < 0) {
				idx = idx + _size;
			}
			bePoped = _array[idx];
			
			if (idx == _size - 1) {
				//���һ��Ԫ��
				_array[idx] = NULL;
			}
			else{
				//��Ҫɾ���� Ԫ�� ���� ����
				bePoped = _array[idx];
				for (int i = idx; i < _size - 1; i++) {
					_array[i] = _array[i + 1];
				}
			}
			//ĩβ����--
			_size--;
			return bePoped;
		}
		else {
			getErrorIndex(idx);
		}
	}

	void removeAll() {
		for (std::size_t i=0,t=_size;i<t;++i)
		{
			removeLast();
		}
	}
	//ɾ�����һ��Ԫ��
	void removeLast() {
		this->remove(-1);
	}
	void remove(int idx) {
		//size��ʱ��ҲҪ-- 
		// ���ʱ������������ -1
		if (isVaildIndex(idx)) {
			if (idx < 0) {
				idx = idx + _size;
			}

			freeOneByIdx(idx);

			if (idx == _size - 1) {
				
			}
			else {
				for (int i = idx; i < _size - 1; i++) {
					_array[i] = _array[i + 1];
				}
			}

			_capacity--;
			_size--;
		}
		else {
			getErrorIndex(idx);
		}


	}
	//����array����
	void resize(std::size_t capacity_){
		//cout << "����Ϊ" << capacity_<<endl;
		if (_capacity > capacity_) {

		}
		else {
			//����ǰ�� ���鸴�Ƶ� �·���Ŀռ���
			value_pointer _new = new value_type[capacity_];
			//����Ƕ���,��ô��ָ�� ɾ������� �����
			for (std::size_t i = 0; i < _capacity; ++i) {
				_new[i] = _array[i];
			}
			//ʣ�� size_-_size��δ��ʼ�����ڴ�,Ҫע��
		
			//�ͷ�ԭ���Ŀռ�
			delete[]_array;
			//���µ�ǰ�ռ�
			_capacity = capacity_;
			_array = _new;

		}
	}
	void print() {
		//cout << "���ڵ�capacityΪ" <<  _capacity <<endl;
		//cout << "���ڵ�sizeΪ" << _size << endl;
	
		for (std::size_t i = 0; i < _size; ++i) {
			//cout << i << _size << "û�ȵ���" << endl;
			if(isPointer)
				cout << *_array[i] << endl;
			else
				cout << _array[i] << " ";
		}
		cout << endl;
	}
	inline std::size_t count() {
		return capacity();
	}
	VectorYjc& copy() {
		
		return *new VectorYjc<value_type>(*this);
	}
	void sort(bool reverse=false) {
		//�����˳���Ǹ���ascii����,����
		//һ��ֻ���� �ַ� �ַ��� ���� �Ż�ȥ����
		//��ѡ ���� λ�� ���м���
		//����ҵ�һ���Ȼ�׼ֵ(Ĭ����leftλ��)�����
		//�ұ��ҵ�һ���Ȼ�׼ֵС����
		//Ȼ�󽻻�

		//if (typeid(value_type) == typeid(int) ||
		//	typeid(value_type) == typeid(char)) {
		//	
		//}
		//Ĭ��ʹ�ÿ�������
		quickSort(0, _size - 1,reverse);
		
	}
	
	int index(value_type value) {
		//���ҵ�һ�����ֵ�Ԫ��
		//û�ж�����׳��쳣
		for (std::size_t i=0;i<_size;i++)
		{
			if (value==_array[i])
			{
				return i;
			}
		}
		char i2s[10];
		
		sprintf_s(i2s, "%d", value);
		string error = _name + std::string("�ﲻ����") + string(i2s);
		cout << error <<endl;
		throw error;

	}
	void clear() {
		//�������
		// ����� ָ������, ��ȫ���ͷ�
		int t = _size;
		for (std::size_t i=0;i<t;i++)
		{
			if (isPointer) {
				value_type vt= pop();
				delete vt;
			}
			else {
				pop();
			}
		}

	}
	void extend(const VectorYjc& rhs) {
		//Ч���� + ����ͬ ��������
		for (std::size_t i = 0; i < rhs._size; i++)
		{
			value_type tmp = rhs._array[i];
			append(tmp);
		}
	}
	void reverse() {
		for (std::size_t i=0;i<_size/2;i++)
		{
			value_type temp = _array[i];
			_array[i] = _array[_size - i-1];
			_array[_size - i-1] = temp;
		}
	}
	value_type max() {
		value_type _max = _array[0];
		for (std::size_t i=1;i<_size;i++)
		{
			if (_array[i] > _max) {
				_max = _array[i];
			}
		}
		return _max;
	}
	value_type min() {
		value_type _min = _array[0];
		for (std::size_t i = 1; i < _size; i++)
		{
			if (_array[i] < _min) {
				_min = _array[i];
			}
		}
		return _min;
	}

	inline std::size_t size() const {  return _size; };
	inline std::size_t capacity() const { return _capacity; };

	//MyIterator<value_type>p2s() { return pts;};
	//MyIterator<value_type> p2e() { return pte; };
	//MyIterator<value_type> p2t() { return ptt; };

private:
	//����һ�� �Զ������͵����� �ö�̬����
	//�ռ�Ĭ��Ϊ1
	value_type* _array;
	std::size_t _capacity; //Ĭ��������1
	std::size_t _size=0;
	std::string _name;
	bool isPointer=false;
	//MyIterator<value_type> *pts; //pointer to start
	//MyIterator<value_type> *pte; //pointer to end
	//MyIterator<value_type> *ptt; //pointer to tail

	void getErrorIndex(int idx) {
		cout << "�����vector��������! Wrong vector index as follow!" << endl;
		cout << _name << "[" << idx << "]" << endl;

		exit(-1);
	}
	bool isVaildIndex(int idx) {
		if (idx < 0) {
			if (-idx > _size) {
				return false;
			}
			else {
				//���ص�����i��
				return true;
			}
		}
		else {
			return idx > _size ? false : true;
		}
	}
	inline bool typeIsPointer() {
		return true ?std::is_pointer<value_type>::value:false;
	}
	inline bool isEmpty() {
		return true ? _size == 0 : false;
	}
	void freeOneByIdx(int idx) {
		if (isPointer) {//�����ָ�� ��ô�ͷ�
			delete _array[idx];
		}
		//�����ֵ����ֱ�Ӹ���ΪNULL
		else {
			_array[idx] = NO_MALLOC; //����Ϊû�з���ı�־
		}
	}
	void quickSort(int left,int right,bool reverse) {

		//�������Ѿ�����
		//�������
		if (left >= right)
			return;
		// i �ڱ� �� j �ڱ� 
		// base ��׼ֵ temp ��ʱ
		int i, j, base, temp;
		i = left, j = right;
		base = _array[left];  //ȡ����ߵ���Ϊ��׼��
		//���û������
		while (i < j)
		{
			if(!reverse){
				//�ҵ�һ������left����
				while (_array[j] >= base && i < j)
					j--;
				//�ҵ�һ���� right �����
				while (_array[i] <= base && i < j)
					i++;
			}
			else {
				while (_array[j] <= base && i < j)
					j--;
				while (_array[i] >= base && i < j)
					i++;
			}


			//������������� ��ô����
			if (i < j)
			{
				temp = _array[i];
				_array[i] = _array[j];
				_array[j] = temp;
			}
		}
		//��׼����λ
		_array[left] = _array[i];
		//
		_array[i] = base;
		quickSort(left, i - 1, reverse);//�ݹ����
		quickSort(i + 1, right , reverse);//�ݹ��ұ�
	}
};





