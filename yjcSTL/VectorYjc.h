#pragma once
#include<iostream>
//#include"iterator.h"
#define MAX_LENGTH 100000//��������ռ�
#define GET_NAME(value) (#value)
#define DEFAULT_SIZE 50
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
	//����һ�������� ����Ϊ0

	VectorYjc():_size(DEFAULT_SIZE)//Ĭ�Ϸ���Ԫ�� �ռ� 
	{
		isPointer = typeIsPointer();
		_array = new value_type[_size];
		createDefaultName();
	
	}//Ĭ�Ϲ��� �յ�����
	~VectorYjc()
	{
		defaultId--;
		delete[]_array;
	}
	//����ָ����С
	VectorYjc(int size) {
		if (size > MAX_LENGTH or size < 0) {
			throw "�����vector����! Wrong vector length!";
		}
		isPointer = typeIsPointer();
		_size = size;
		_array = new value_type[_size];
		initVector();
		
	}
	VectorYjc(int size,std::string name):VectorYjc(size) {
		createDefaultName(name);
	}
	VectorYjc(const VectorYjc& other)
	{
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
				idx = _capacity + idx;
			}
			return _array[idx];
		}
		getErrorIndex(idx);
	};

	void initVector(value_type init = NULL)
	{
		for (int i = 0; i < this->_size; ++i) {
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

		//�ж��Ƿ��Ѿ������ռ�
		if (_capacity < _size) {
		}
		else {
			//��� ����֮��Ҫ���¿�ʼ����ռ���
			//Ϊԭ��������
			resize(_size<<1);
		}
		_array[_capacity++] = value;
		
	}
	//����Ԫ��
	void insert(value_type value,int pos) {
		//�жϲ���λ���Ƿ�Ϸ�
		//�����-1
		//�жϲ����ռ������ �ȸ��� ��append�ķ�ʽ ���ö��ж���
		if (isVaildIndex(pos)) {
			if (pos < 0) {
				pos = pos + _capacity;
			}
			if (pos == _capacity - 1 || isEmpty()) { //����ǿյľ������ж�
				append(value);
			}
			else {
				//�����һ���ط��ƶ�����ǰλ��
				// 1,2,3,4
				// 1,2,5,3
				// 1,2,5,3,4
				//�������һ��Ȼ��append

				value_type lastone = _array[_capacity - 1];
				//type_value 
				for (int i = _capacity-1; i > pos; i--) {
					_array[i] = _array[i - 1];
				}
				_array[pos] = value;
				
				append(lastone);
				_capacity++;
			}
		}
		//ע��,�����ѡ������һ���ط�����Ļ�
		//��ʱcapacity==pos
		//��Ҫ
		else {
			if (_capacity == pos) {
				append(value);
			}
			else {
				getErrorIndex(pos);
			}
	
		}
	}
	value_type pop(int idx=-1) {
		//Ĭ�ϵ������һ��Ԫ��
		//����һ���ط�ɾ��Ԫ�� Ȼ��������ǰ�ƶ�
		if (isVaildIndex(idx)) {
			value_type bePoped;
			if (idx < 0) {
				idx = idx + _capacity;
			}
			bePoped = _array[idx];
			freeOneByIdx(idx);
			if (idx == _capacity - 1) {
				//���һ��Ԫ��
				
			}
			else{
				//��Ҫɾ���� Ԫ�� ���� ����
				bePoped = _array[idx];
				for (int i = idx; i < _capacity - 1; i++) {
					_array[i] = _array[i + 1];
				}
			}
			//ĩβ����--
			_capacity--;
			return bePoped;
		}
		else {
			getErrorIndex(idx);
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
				idx = idx + _capacity;
			}

			freeOneByIdx(idx);

			if (idx == _capacity - 1) {
				
			}
			else {
				for (int i = idx; i < _capacity - 1; i++) {
					_array[i] = _array[i + 1];
				}
			}

			_size--;
			_capacity--;
		}
		else {
			getErrorIndex(idx);
		}


	}
	//����array����
	void resize(int size_){
		cout << "����Ϊ" << size_<<endl;
		if (_size > size_) {

		}
		else {
			//����ǰ�� ���鸴�Ƶ� �·���Ŀռ���
			value_pointer _new = new value_type[size_];
			//����Ƕ���,��ô��ָ�� ɾ������� �����
			for (int i = 0; i < _size; ++i) {
				_new[i] = _array[i];
			}
			//ʣ�� size_-_size��δ��ʼ�����ڴ�,Ҫע��
		
			//�ͷ�ԭ���Ŀռ�
			delete[]_array;
			//���µ�ǰ�ռ�
			_size = size_;
			_array = _new;

		}
	}
	void print() {
		cout << "���ڵ�capacityΪ" << _capacity<<endl;
		cout << "���ڵ�sizeΪ" << _size << endl;
		for (int i = 0; i < _capacity; ++i) {
			cout << _array[i]<<endl;
			if (_array[i]!=NULL)
				cout << *_array[i]<<" ";
			else {
				break;
			}
		}
		cout << endl;
	}
	inline std::size_t size() const {  return _size; };

	//MyIterator<value_type>p2s() { return pts;};
	//MyIterator<value_type> p2e() { return pte; };
	//MyIterator<value_type> p2t() { return ptt; };

private:
	//����һ�� �Զ������͵����� �ö�̬����
	//�ռ�Ĭ��Ϊ1
	value_type* _array;
	std::size_t _size;
	std::size_t _capacity=0;
	std::string _name;
	bool isPointer;
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
			if (-idx > _capacity) {
				return false;
			}
			else {
				//���ص�����i��
				return true;
			}
		}
		else {
			return idx > _capacity ? false : true;
		}
	}
	inline bool typeIsPointer() {
		return true ?std::is_pointer<value_type>::value:false;
	}
	inline bool isEmpty() {
		return true ? _capacity == 0 : false;
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
};





