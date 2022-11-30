#include "product.h"
#include "validity.h"
#include "header.h"

product::product() {
	setProduct("Name", 1, 0.1);
}
product::product(string str) {
	string _name;
	int _number;
	double _price;
	_name = str.substr(1, str.find_first_of("#") - 1);
	str = str.substr(str.find_first_of("#") + 1);
	_number = stoi(str.substr(0, str.find_first_of("#")));
	str = str.substr(str.find_first_of("#") + 1);
	_price = stod(str);
	setProduct(_name, _number, _price);
}
product::product(string n, int number, double p) {
	setProduct(n, number, p);
}
product::product(product& p) {
	setProduct(p._name, p._number, p._price);
}

void product::setName(string name) {
	this->_name = name;
}
void product::setNumber(int number) {
	this->_number = number;
}
void product::setPrice(double price) {
	this->_price = price;
}
void product::setProduct(string n, int number, double p) {
	setName(n);
	setNumber(number);
	setPrice(p);
}
void product::enterProduct() {
	string n;
	int num;
	double p;
	cout << "\n Name:";
	n = getLine();
	cout << " Amount:";
	num = enterInt();
	cout << " Price:";
	p = enterDouble();
	setProduct(n, num, p);
}
string product::getName() {
	return _name;
}
int product::getNumber() {
	return _number;
}
double product::getPrice(){
	return _price;
}
double product::getPrice(double price) {
	return _price;
}
std::ostream& operator<<(std::ostream& out, product& product) {
	out << "-" << product._name << "#" << product._number << "#" << product._price << "#" << endl;
	return out;
};