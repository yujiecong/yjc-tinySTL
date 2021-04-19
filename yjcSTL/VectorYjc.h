#pragma once
#include<iostream>
//#include"iterator.h"
#define MAX_LENGTH 100000//最大可申请空间
#define GET_NAME(value) (#value)
#define DEFAULT_SIZE 50
#define NO_MALLOC NULL
using std::string;
using std::cout;
using std::endl;
static int defaultId; //vector记录名字
template<typename value_type>
class VectorYjc
{

public:
	typedef value_type* value_pointer;
	typedef value_type& value_reference;
	//声明一个空容器 长度为0

	VectorYjc():_size(DEFAULT_SIZE)//默认分配元素 空间 
	{
		isPointer = typeIsPointer();
		_array = new value_type[_size];
		createDefaultName();
	
	}//默认构造 空的容器
	~VectorYjc()
	{
		defaultId--;
		delete[]_array;
	}
	//构造指定大小
	VectorYjc(int size) {
		if (size > MAX_LENGTH or size < 0) {
			throw "错误的vector长度! Wrong vector length!";
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
		//输入检查

		//支持负数索引 
		// -1代表倒数第一个
		// -2 代表导数第二个
		// 以此类推 -idx表示倒数第capacity个 也就是第一个
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
	}//初始化为0
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
	//添加元素
	void append(value_type value) {

		//判断是否已经超出空间
		if (_capacity < _size) {
		}
		else {
			//如果 大于之后要重新开始分配空间了
			//为原来的两倍
			resize(_size<<1);
		}
		_array[_capacity++] = value;
		
	}
	//插入元素
	void insert(value_type value,int pos) {
		//判断插入位置是否合法
		//如果是-1
		//判断插入后空间可以用 先覆盖 再append的方式 不用多判断了
		if (isVaildIndex(pos)) {
			if (pos < 0) {
				pos = pos + _capacity;
			}
			if (pos == _capacity - 1 || isEmpty()) { //如果是空的就另作判断
				append(value);
			}
			else {
				//从最后一个地方移动到当前位置
				// 1,2,3,4
				// 1,2,5,3
				// 1,2,5,3,4
				//保存最后一个然后append

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
		//注意,如果是选择从最后一个地方插入的话
		//此时capacity==pos
		//需要
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
		//默认弹出最后一个元素
		//任意一个地方删除元素 然后后面的往前移动
		if (isVaildIndex(idx)) {
			value_type bePoped;
			if (idx < 0) {
				idx = idx + _capacity;
			}
			bePoped = _array[idx];
			freeOneByIdx(idx);
			if (idx == _capacity - 1) {
				//最后一个元素
				
			}
			else{
				//把要删除的 元素 覆盖 即可
				bePoped = _array[idx];
				for (int i = idx; i < _capacity - 1; i++) {
					_array[i] = _array[i + 1];
				}
			}
			//末尾索引--
			_capacity--;
			return bePoped;
		}
		else {
			getErrorIndex(idx);
		}
	}
	//删除最后一个元素
	void removeLast() {
		this->remove(-1);
	}
	void remove(int idx) {
		//size这时候也要-- 
		// 这个时候是整个数组 -1
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
	//重置array长度
	void resize(int size_){
		cout << "扩容为" << size_<<endl;
		if (_size > size_) {

		}
		else {
			//将当前的 数组复制到 新分配的空间中
			value_pointer _new = new value_type[size_];
			//如果是对象,那么是指针 删除后访问 会崩溃
			for (int i = 0; i < _size; ++i) {
				_new[i] = _array[i];
			}
			//剩下 size_-_size是未初始化的内存,要注意
		
			//释放原来的空间
			delete[]_array;
			//更新当前空间
			_size = size_;
			_array = _new;

		}
	}
	void print() {
		cout << "现在的capacity为" << _capacity<<endl;
		cout << "现在的size为" << _size << endl;
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
	//创建一个 自定义类型的容器 用动态分配
	//空间默认为1
	value_type* _array;
	std::size_t _size;
	std::size_t _capacity=0;
	std::string _name;
	bool isPointer;
	//MyIterator<value_type> *pts; //pointer to start
	//MyIterator<value_type> *pte; //pointer to end
	//MyIterator<value_type> *ptt; //pointer to tail

	void getErrorIndex(int idx) {
		cout << "错误的vector索引如下! Wrong vector index as follow!" << endl;
		cout << _name << "[" << idx << "]" << endl;

		exit(-1);
	}
	bool isVaildIndex(int idx) {
		if (idx < 0) {
			if (-idx > _capacity) {
				return false;
			}
			else {
				//返回倒数第i个
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
		if (isPointer) {//如果是指针 那么释放
			delete _array[idx];
		}
		//如果是值类型直接覆盖为NULL
		else {
			_array[idx] = NO_MALLOC; //设置为没有分配的标志
		}
	}
};





