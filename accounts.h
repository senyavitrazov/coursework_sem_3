#pragma once
#include <iostream>
#include "header.h"
#include "outlet.h"

using namespace std;

const string FILE_OF_ACCOUNTS = "añcount.txt";

class account;

class accounts {
	friend class admin;
	doublyLinkedList<account> _accounts;
public:
	void readFile();
	void writeInFile();
	int lengthAccountsFile();
	account* LogIn();
	void registration();
	bool loginError();
};


class account {
	string login;
	string password;
	bool role;
	bool access;
public:
	account();
	account(string);

	bool getRole();
	void setRole(int);
	bool getAccess();
	void setAccess(int);
	string getLogin();
	void setLogin(string);
	string getPassword();
	void setPassword(string);

	void setUser(string n, string p, int r, int a);
	void enterUser();

	virtual void menu(outletsList& link);
	void dataMenu(outletsList& link);

	friend bool operator==(const account& o1, const account& o2);
	friend ostream& operator<<(ostream& out, const account& d);
};

class admin : public account {
	accounts& list;
public:
	admin(accounts& link) : list(link) {};
	void menu(outletsList& link);
	void editDataMenu(outletsList& link);
	void accountsMenu();

	bool isLastAdmin(int);
	void banAccount();
	void unbanAccount();

	void addAccount();
	void editAccount();
	void deleteAccount();
	void showAccounts();
};