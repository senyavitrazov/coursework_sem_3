#pragma once
#include <iostream>
#include <fstream>

using namespace std;

template<typename T> class doublyLinkedList {
	template<typename T> class Node {
	public:
		T item;
		Node<T>* next = nullptr;
		Node<T>* prev = nullptr;
	};
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	int length = 0;
public:
	class iterator {
		Node<T>* i;
	public:
		iterator() {
			i = NULL;
		}
		iterator(doublyLinkedList<T>& list) {
			i = list.begin();
		}
		void operator++() {
			i = i->next;
		}
		void operator--() {
			i = i->prev;
		}
		T& operator*() {
			return i->item;
		}

	};
	void add(T element);
	void addFirst(T element);
	void insert(int pos, T element);
	void removeFirst();
	void removeLast();
	void clear();
	void remove(T);
	void remove(int);
	int search(T element);
	void print();
	void sort(bool (*comp)(T, T));
	void writeInFile(string);
	void readFile(string filename, int sizeOfFile);
	Node<T>* begin() { 
		return first; 
	};
	Node<T>* end() {
		return last; 
	};
	doublyLinkedList<T>& operator=(doublyLinkedList<T>& anotherlist) {
		Node<T>* curr = this->first;
		int i = 0;
		while (curr != NULL) {
			cout << "*" << endl;
			anotherlist.insert(i, curr->item);
			i++;
			curr = curr->next;
		}
		return *this;
	}
	Node<T>& operator[](const int index) {
		Node<T>* current = first;
		for (int i = 0; i < index; i++) current = current->next;
		return *current;
	}
	int getLength() {
		return length;
	}
};
template<typename T> void doublyLinkedList<T>::add(T element) {
	Node<T>* newnode = new Node<T>;
	newnode->item = element;
	if (length == 0) {
		first = last = newnode;
		newnode->prev = NULL;
		newnode->next = NULL;
	}
	else {
		last->next = newnode;
		newnode->prev = last;
		newnode->next = NULL;
		last = newnode;
	}
	length++;
}
template<typename T> void doublyLinkedList<T>::addFirst(T element) {
	Node<T>* newnode = new Node<T>;
	newnode->item = element;
	if (length == 0) {
		first = last = newnode;
		newnode->prev = NULL;
		newnode->next = NULL;
	}
	else {
		newnode->next = first;
		newnode->prev = NULL;
		first->prev = newnode;
		first = newnode;
	}
	length++;
}
template<typename T> void doublyLinkedList<T>::insert(int pos, T element) {
	Node<T>* newnode = new Node<T>;
	newnode->item = element;
	if (pos<0 || pos>length)
		cout << " Out of range" << endl;
	if (pos == 0)
		addFirst(element);
	else if (pos == length)
		add(element);
	else {
		Node<T>* current = first;
		for (int i = 1; i < pos; i++) current = current->next;
		newnode->next = current->next;
		newnode->prev = current;
		current->next = newnode;
		current->next->prev = newnode;
	}
	length++;
}
template<typename T> int doublyLinkedList<T>::search(T element) {
	Node<T>* current = first;
	int pos = 0;
	while (current != NULL) {
		if (current->item == element)
			return pos;
		current = current->next;
		pos++;
	}
	return -1;
}
template<typename T> void doublyLinkedList<T>::removeFirst() {
	if (length == 0)
		cout << " Empty list can't remove" << endl;
	else if (length == 1) {
		delete first;
		first = last = NULL;
	}
	else {

		Node<T>* curr;
		curr = first;
		first = first->next;
		first->prev = NULL;
		delete curr;

	}
	length--;
}
template<typename T> void doublyLinkedList<T>::removeLast() {
	if (length == 0)
		cout << " Empty string can't remove" << endl;
	else if (length == 1) {
		delete first;
		length--;
		first = last = NULL;
	}
	else {
		Node<T>* curr = last;
		last = last->prev;
		last->next = NULL;
		delete curr;
		length--;
	}

}
template<typename T> void doublyLinkedList<T>::remove(T element) {
	if (length == 0)
		cout << " Error code: -1" << endl;
	else if (first->item == element)
		removeFirst();
	else if (last->item == element)
		removeLast();
	else {
		Node<T>* curr = first;
		while (curr != NULL) {
			if (curr->item == element)
				break;
			curr = curr->next;
		}
		if (curr == NULL)
			cout << " Not found" << endl;
		else {
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete curr;
			length--;
		}
	}
}
template<typename T> void doublyLinkedList<T>::remove(int pos) {
	if (pos<0 || pos>length)
		cout << " Out of range" << endl;
	if (pos == 0) removeFirst();
	else if (pos == length) removeLast();
	else {
		Node<T>* current = first;
		for (int i = 1; i < pos; i++) current = current->next;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		length--;
	}
}
template<typename T> void doublyLinkedList<T>::clear(){
	Node<T>* temp = new Node<T>;
	while (first != NULL) {
		removeLast();
	}
}
template<typename T> void doublyLinkedList<T>::print() {
	Node<T>* current = first;
	cout << endl;
	int c = 1;
	while (current != NULL) {
		cout << c << " " << current->item;
		c++;
		current = current->next;
		cout << endl;
	}
	cout << endl;
}
template<typename T> void doublyLinkedList<T>::writeInFile(string filename) {
	ofstream out(filename, ios::out);
	Node<T>* current = first;
	if (out.is_open()) {
		while (current != NULL) {
			out << current->item;
			current = current->next;
		}
		out << endl;
	}
	out.close();
}
template<typename T> void doublyLinkedList<T>::readFile(string filename, int sizeOfFile) {
	string str;
	ifstream fin(filename, ios::in);
	if (!fin.is_open())
	{
		fin.close();
	}
	else {
		for (int i = 0; i < sizeOfFile; i++) {
			getline(fin, str);
			this->add(str);
		}
	}
}
template<typename T> void doublyLinkedList<T>::sort(bool (*comp)(T, T)) {
	Node<T>* left = first;
	Node<T>* right = first->next;
	Node<T>* temp = new Node<T>;
	while (left->next) {
		while (right) {
			if (comp(left->item, right->item)) {
				temp->item = left->item;
				left->item = right->item;
				right->item = temp->item;
			}
			right = right->next;
		}
		left = left->next;
		right = left->next;
	}
}