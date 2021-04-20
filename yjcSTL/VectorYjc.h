#pragma once
#include<iostream>
//#include"iterator.h"
#define MAX_LENGTH 100000//最大可申请空间
#define GET_NAME(value) (#value)
#define DEFAULT_SIZE 0
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
	typedef value_type value_type;
	//声明一个空容器 长度为

	VectorYjc()
	{
		isPointer = typeIsPointer();
		_capacity=DEFAULT_SIZE;//默认分配元素 空间 
		_array = nullptr;
		createDefaultName();
	
	}//默认构造 空的容器
	~VectorYjc()
	{
		defaultId--;
		delete[]_array;
	}
	//构造指定大小
	VectorYjc(int capacity):VectorYjc(){
		if (capacity > MAX_LENGTH or capacity < 0) {
			throw "错误的vector长度! Wrong vector length!";
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
		//证明是否同一个测试
		if (this!=&rhs)
		{
			_size = rhs._size;
			_capacity = rhs._capacity;
			isPointer = rhs.isPointer;
			_name = rhs._name;
			_array = new value_type[_capacity];
			for (std::size_t i = 0; i < _size; i++)
			{
				//如果是值倒也无所谓,那如果是指针呢?
				//需要深拷贝
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
		//证明是否同一个测试
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
		//输入检查

		//支持负数索引 
		// -1代表倒数第一个
		// -2 代表导数第二个
		// 以此类推 -idx表示倒数第capacity个 也就是第一个
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
		//实际上是连起来
		//全部append即可

	
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

		//判断是否已经超出 容量
		if (_size < _capacity) {
		}
		else {
			//如果 大于之后要重新开始分配空间了
			//为原来的+1 两倍
			resize((_capacity+1)<<1);
		}
		_array[_size++] = value;
		
	}
	//插入元素
	void insert(value_type value,int pos) {
		//如果pos大于_size 默认在队尾插入
		//如果是 -1 那么就是再最后的地方插入

		if(pos==-1 || pos>=_size || isEmpty()){
			append(value);
			return;
		}
		//如果-pos大于 _size+1 默认在队头插入

		// 为什么这里可以通过??
		// -pos=-1
		// _size+1=4
		if (abs(pos) >= _size + 1) {

			pos = 0;
		}

		
		//如果是中间或头 插入
		if (isVaildIndex(pos)) {

			if (pos < 0) {
				pos = pos + _size;
			}
			else if (_size == 1 || pos==_size-1) {
				//只能队头插入 pos=0
				value_type lastone = _array[_size-1];
				_array[pos] = value;
				append(lastone);
			}//否则开始移动后面的元素
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
		//注意 存在内存泄漏的风险
		// 如果pop出来没有主动释放 使用 那么会泄露

		//默认弹出最后一个元素
		//任意一个地方删除元素 然后后面的往前移动
		if (isVaildIndex(idx)) {
			value_type bePoped;
			if (idx < 0) {
				idx = idx + _size;
			}
			bePoped = _array[idx];
			
			if (idx == _size - 1) {
				//最后一个元素
				_array[idx] = NULL;
			}
			else{
				//把要删除的 元素 覆盖 即可
				bePoped = _array[idx];
				for (int i = idx; i < _size - 1; i++) {
					_array[i] = _array[i + 1];
				}
			}
			//末尾索引--
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
	//删除最后一个元素
	void removeLast() {
		this->remove(-1);
	}
	void remove(int idx) {
		//size这时候也要-- 
		// 这个时候是整个数组 -1
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
	//重置array长度
	void resize(std::size_t capacity_){
		//cout << "扩容为" << capacity_<<endl;
		if (_capacity > capacity_) {

		}
		else {
			//将当前的 数组复制到 新分配的空间中
			value_pointer _new = new value_type[capacity_];
			//如果是对象,那么是指针 删除后访问 会崩溃
			for (std::size_t i = 0; i < _capacity; ++i) {
				_new[i] = _array[i];
			}
			//剩下 size_-_size是未初始化的内存,要注意
		
			//释放原来的空间
			delete[]_array;
			//更新当前空间
			_capacity = capacity_;
			_array = _new;

		}
	}
	void print() {
		//cout << "现在的capacity为" <<  _capacity <<endl;
		//cout << "现在的size为" << _size << endl;
	
		for (std::size_t i = 0; i < _size; ++i) {
			//cout << i << _size << "没先到吧" << endl;
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
		//排序的顺序是根据ascii来排,所以
		//一般只有是 字符 字符串 数字 才会去排序
		//挑选 两个 位置 向中间走
		//左边找到一个比基准值(默认是left位置)大的数
		//右边找到一个比基准值小的数
		//然后交换

		//if (typeid(value_type) == typeid(int) ||
		//	typeid(value_type) == typeid(char)) {
		//	
		//}
		//默认使用快速排序
		quickSort(0, _size - 1,reverse);
		
	}
	
	int index(value_type value) {
		//查找第一个出现的元素
		//没有对象会抛出异常
		for (std::size_t i=0;i<_size;i++)
		{
			if (value==_array[i])
			{
				return i;
			}
		}
		char i2s[10];
		
		sprintf_s(i2s, "%d", value);
		string error = _name + std::string("里不存在") + string(i2s);
		cout << error <<endl;
		throw error;

	}
	void clear() {
		//清空数组
		// 如果是 指针类型, 则全部释放
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
		//效果与 + 号相同 但不返回
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
	//创建一个 自定义类型的容器 用动态分配
	//空间默认为1
	value_type* _array;
	std::size_t _capacity; //默认容量是1
	std::size_t _size=0;
	std::string _name;
	bool isPointer=false;
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
			if (-idx > _size) {
				return false;
			}
			else {
				//返回倒数第i个
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
		if (isPointer) {//如果是指针 那么释放
			delete _array[idx];
		}
		//如果是值类型直接覆盖为NULL
		else {
			_array[idx] = NO_MALLOC; //设置为没有分配的标志
		}
	}
	void quickSort(int left,int right,bool reverse) {

		//如两边已经相遇
		//交换完成
		if (left >= right)
			return;
		// i 哨兵 和 j 哨兵 
		// base 基准值 temp 临时
		int i, j, base, temp;
		i = left, j = right;
		base = _array[left];  //取最左边的数为基准数
		//如果没有相遇
		while (i < j)
		{
			if(!reverse){
				//找到一个比他left的数
				while (_array[j] >= base && i < j)
					j--;
				//找到一个比 right 大的数
				while (_array[i] <= base && i < j)
					i++;
			}
			else {
				while (_array[j] <= base && i < j)
					j--;
				while (_array[i] >= base && i < j)
					i++;
			}


			//如果不是相遇了 那么交换
			if (i < j)
			{
				temp = _array[i];
				_array[i] = _array[j];
				_array[j] = temp;
			}
		}
		//基准数归位
		_array[left] = _array[i];
		//
		_array[i] = base;
		quickSort(left, i - 1, reverse);//递归左边
		quickSort(i + 1, right , reverse);//递归右边
	}
};





