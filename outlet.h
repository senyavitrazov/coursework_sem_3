#pragma once
#include <iostream>
#include "validity.h"

using namespace std;

const int PERMISSIONS_NUMBER = 5;

const string FILE_OF_DATA = "data.txt";
const string FILE_OF_DATA_2 = "data2.txt";
const string FILES_OF_DATA[2] = { "data.txt", "data2.txt" };

class outlet;

class outletsList {
	friend class user;
	friend class admin;
	doublyLinkedList<outlet> _outlets;
public:
	//void readFile();
	void writeInFile();
	void readFile(string filename = FILE_OF_DATA);
	int lengthDataFile(string filename = FILE_OF_DATA);

	void sort();
	void showOutlets();
	void showOneOutlet(int);
	void showDetails(int);
	void showDetails(outlet*);
	void showWithoutSorting();
	void addOutlet();
	void editOutlet();
	void deleteOutlet();
	bool undoAction();
	outlet* searchOutlet();
};

class outlet {
	string name;
	bool _permissions[PERMISSIONS_NUMBER];
	date _permissonsBegins[PERMISSIONS_NUMBER];
	date _permissonsEnds[PERMISSIONS_NUMBER];
	doublyLinkedList<product> assortment;
public: 
	outlet();
	outlet(string);

	string listOfPermissions(int);
	void setName(string);
	string getName();
	string getPermissions();
	int getPermissionsSum();
	void enterOutlet();
	void enterOutlet(string);

	bool abilityToTrade();
	void addPermissions();
	void showAll();
	void showPermissions();
	void editPermission(int i);

	void addAssortment();
	void showAssortment();
	void addProductToAssort(product& prod);
	void addProductToAssort();
	void editProduct(int);
	void deleteProductFromAssort(int);
	void editAssortment();

	bool operator==(const outlet& d);
	bool operator==(string s);
	friend ostream& operator<<(ostream& out, outlet& o);
};