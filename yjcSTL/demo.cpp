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
	friend std::ostream& operator<<(std::ostream& output, const Person& p) {
		output << "ÎÒµÄidÊÇ" << p.id << endl;
		return output;
	}

};
int main() {
	//std::vector<int> test;
	VectorYjc<Person*> v1=VectorYjc<Person*>(3);
	//for (int i = 0; i < 10; i++) {
	//	Person *p =new Person(i) ;
	//	v1.append(p);
	//}
	//v1.print();
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.remove(0);
	//v1.print();
	v1.insert(new Person(12),0);
	//v1.append(new Person(12));
	//v1.append(new Person(12));
	//v1.append(new Person(12));
	v1.print();
	return 0;
}