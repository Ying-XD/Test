#define DEBUG
#include "MyList.h"
#include <iostream>
using namespace std;
template<typename T>
void printList(MyList<T>& list) {
	MyList<int>::iterator iter = list.begin();
	for (; iter != list.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
}
int main() {
	//	_Debug_message(L"HELLO", __FILEW__, __LINE__);

	MyList<int> list, list2;
	MyList<int>::iterator iter;
	for (int i = 0; i < 10; i++) {
		list.push_back(i);
	}
	for (int i = 0; i < 10; i++) {
		list.push_front(i);
	}
	printList(list);
	iter = list.find(5);
	if (list.find(5) == list.end())
		cout << "Not Found" << endl;
	else
		cout << "Found" << endl;

	list.insert(iter, 1111);
	//list.remove(5);


	printList(list);

}