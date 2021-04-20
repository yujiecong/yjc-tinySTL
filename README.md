# yjc-tinySTL
自己写STL 合理吗? 这合理嘛 补一下基础

[![Build Status](README.assets/passing.svg)](https://travis-ci.org/Alinshans/MyTinySTL) [![Build Status](README.assets/MyTinySTL.svg)](https://ci.appveyor.com/project/Alinshans/mytinystl) [![Release](README.assets/MyTinySTL-1618849629966.svg)](https://github.com/Alinshans/MyTinySTL/releases) [![License](https://img.shields.io/badge/License-MIT%20License-blue.svg)](https://opensource.org/licenses/MIT) [![Chat](https://img.shields.io/badge/chat-on%20gitter-FF6EB4.svg)](https://gitter.im/alinshans/MyTinySTL)

## 简介

 基于 `C++11` 的 `tinySTL`，这是我的第一个stl项目，难免会有很多丑陋的地方,别人的stl我也看不懂 所还能自己来了

## 更新

- 2021年4月20日17:15:29 第二次提交
    - 现在基本可以用了 还行
- 2021年4月20日00:29:09 第一次提交
    - 正在重写vector 用的是python List 的思想

## 目标

* c++ vector 对标 python list
  
    * constructor (默认初始化数组元素为NULL)
        - [x] 默认构造 (默认 数组名)
        - [x] 指定大小构造 (默认数组名)
        - [x] 指定大小构造 (自定义数组名)
        - [ ] 指定大小构造+初始化值
        - [x] copy 构造
    
    - destructor
        - [x] 析构函数
    - 增删改查
        - append (自动判断数组空间  自动扩容)
            - 复杂度 O(1)
            - 扩容时 复杂度 O(n)
        - insert (从任意位置插入 支持负索引)
            - 复杂度 O(n)
            - 结尾插入时调用append
        - remove (从任意位置删除 支持负索引)
            - 复杂度 O(n)
            - 数组容量 同时-1(释放1个空间) 长度-1
        - pop(支持任意位置弹出 支持负索引)
            - 复杂度 O(n)
            - 数组长度-1
            - 返回元素
            - 可能有内存泄露的风险
        - resize (改变数组分配空间长度)
            - 复杂度 O(n)
        - copy() 
            - = 拷贝构造函数
        - count() 
            - = 拿到数组长度
        - sort() 排序 
            - 快排
        - 支持 operator + 即 列表 +列表
            - 返回一个 左手边列表引用
        - 支持 index 索引操作 
            - 查找不到会 throw出异常
        - 支持 clear() 释放所有空间
            - 容量不变
            - 长度 为0
        - 支持removeAll 逐个释放变成空数组 
            - 容量 会为0
            - 长度 为0
        - 支持 reverse()
            - 调转数组顺序
        - 支持 min() max()

## 运行

```
#include "VectorYjc.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;

class Person {
public:
	int id;
	Person(int id) {
		this->id = id;
	}
	~Person() {
		delete this;
	}
	friend std::ostream& operator<<(std::ostream& output, const Person& p) {
		output << "我的id是" << p.id << endl;
		return output;
	}

};
int main() {
	//std::vector<int> test;
	/*VectorYjc<int> v1=VectorYjc<int>();*/
	//v1.append(1);
	//v1.append(2);
	//v1.append(3);
	//VectorYjc<int> v2 ;

	//v2.append(4);
	//v2.append(5);
	//v2.append(6);
	//v2.print();
	//v1= v2 + v1;
	//v1.clear();;
	//
	//v1.print();
	
	//随机插入
	// 
	//int rint;
	//for (int i = 0; i < 10; i++) {
	//	//srand(i);
	//	rint = rand()%(v1.size()+1);
	//	v1.insert(0,rint);
	//	v1.print();
	//}
	VectorYjc<Person*> v1 = VectorYjc<Person*>();
	for (int i = 0; i < 3; i++) {
		Person *p =new Person(i) ;
		v1.append(p);
		//v1.print();
	}
	v1.reverse();
	
	v1.print();
	//v1.print();
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.print();

	//v1.insert(new Person(12), 0);
	//v1.insert(new Person(12), 0);
	//v1.append(new Person(12));
	//v1.append(new Person(12));
	//v1.append(new Person(12));
;
	return 0;
}
```

![1618849720865](README.assets/1618849720865.png)

![1618849725300](README.assets/1618849725300.png)

