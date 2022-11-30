#pragma once
#include <iostream>

using namespace std;

class product {
	friend class outlet;
	string _name = "Name";
	int _number = 1; //amount sry
	double _price = 0.0;
public:
	product();
	product(string);
	product(string, int, double);
	product(product&);
	void setName(string);
	void setNumber(int);
	void setPrice(double);
	void setProduct(string, int, double);
	void enterProduct();
	string getName();
	int getNumber();
	double getPrice();
	double getPrice(double);
	friend ostream& operator<<(ostream& out, product& product);
};