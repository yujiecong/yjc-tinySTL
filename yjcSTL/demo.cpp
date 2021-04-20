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