#include "accounts.h"

string account::getLogin() {
	return login;
}
string account::getPassword() {
	return password;
}
account::account() {
	this->login = "";
	this->password = "";
}
account::account(string s){
	int pos;
	pos = s.find_first_of(' ');
	login = s.substr(0, pos);
	s = s.substr(pos + 1, s.length()-1);
	pos = s.find_first_of(' ');
	password = s.substr(0, pos);
	s = s.substr(pos + 1, s.length() - 1);
	pos = s.find_first_of(' ');
	role = stoi(s.substr(0, pos));
	access = s.at(s.length() - 1);
}
bool account::getRole() {
	return role;
}
void account::setRole(int a) {
	this->role = a;
}
bool account::getAccess()
{
	return access;
}
void account::setAccess(int v) {
	this->access = v;
}
void account::setLogin(string login){
	this->login = login;
}
void account::setPassword(string p) {
	this->password = p;
}
void account::setUser(string n, string p, int r, int a){
	setLogin(n);
	setPassword(p);
	setRole(r);
	setAccess(a);
}
void account::enterUser() {
	string login, pass;
	int role, access;
	cout << " Enter login of account\n";
	login = inputString();
	cout << " Enter password of account\n";
	pass = inputPassword();
	cout << " Is the user an administrator?\n1: Yes\n2: No\n";
	int choice = enterInt(1, 2, " Choose one of the options provided.\n");
	switch (choice)	{
	case 1: role = 1; break;
	default: role = 0; 
	}
	cout << " Does the user have access?\n1: Yes\n2: No\n";
	choice = enterInt(1, 2, " Choose one of the options provided.\n");
	switch (choice) {
	case 1: access = 1; break;
	default: access = 0;
	}
	setUser(login, pass, role, access);
}

void account::menu(outletsList& link) {
	dataMenu(link);
}
void account::dataMenu(outletsList& link) {
	bool flag = 1;
	while (flag) {
		system("cls");
		cout << "\n-------MENU OF VIEW-------\n\n";
		cout << " 1: Show Outlets\n" << " 2: Search Outlet\n" << " 0: Exit\n";
		int switch_on = enterInt(0, 2, "\n Select one of the existing items of menu.\n");
		switch (switch_on) {
		case 0: flag = 0; break; //todo
		case 1: link.showOutlets(); break;
		case 2: 
			bool c = 0;
			while (!c) {
				outlet *o = link.searchOutlet();
				if (o == nullptr) break;
				else link.showDetails(o);
				cout << "\n Do you want to repeat the action(1: Yes / 2: No)?\n";
				c = enterInt(1, 2, "") - 1;
			}
			break; //todo
		}
	}
}

void admin::menu(outletsList& link) {
	bool flag = 1;
	while (flag) {
		system("cls");
		cout << "\n---MENU OF ADMINISTRATOR---\n\n";
		cout << " 1: Accounts menu\n" << " 2: Menu for viewing of data\n" << " 3: Menu for working with data\n" << " 0: Exit\n";
		int switch_on = enterInt(0, 3, "\n Select one of the existing items of menu.\n");
		switch (switch_on) {
		case 0: flag = 0; break;
		case 1: accountsMenu(); break;
		case 2: dataMenu(link); break;
		case 3: editDataMenu(link); break;
		}
	}
}
void admin::editDataMenu(outletsList& link) {
	bool flag = 1, undoFlag = -1;
	while (flag) {
		system("cls");
		if (undoFlag == 0) {
			cout << " Action canceled successfully.\n";
			undoFlag = -1;
		}
		cout << "\n----EDIT DATA MENU----\n\n";
		cout << " 1: Show Outlets\n" << " 2: Add outlet\n" << " 3: Delete outlet\n" << " 4: Edit outlet\n" <<" 5: Undo the last action\n" << " 0: Exit\n";
		int c;
		c = enterInt(0, 5, "\n Select one of the existing items of menu.\n");
		switch (c)
		{
		case 0: system("cls"); flag = 0; break;
		case 1: system("cls"); link.showOutlets(); break; 
		case 2: system("cls"); link.addOutlet(); break;
		case 3: system("cls"); link.deleteOutlet(); break;
		case 4: system("cls"); link.editOutlet(); break;
		case 5: system("cls"); undoFlag = link.undoAction(); break; //вывод сообщения что не
		}
	}

}
void admin::accountsMenu() {
	system("cls");
	bool flag = 1;
	while (flag) {
		cout << "\n----ACCOUNTS MENU----\n\n";
		cout << "1: Show accounts\n" << "2: Add account\n" << "3: Edit account\n" << "4: Delete account\n" << "5: Ban account\n" << "6: Unban account\n" << "0: Exit\n";
		int choice = enterInt(0, 6, "\n Select one of the existing items of menu.\n");
		switch (choice) {
		case 0: flag = 0; break;
		case 1: showAccounts(); break;
		case 2: addAccount();	break;
		case 3: editAccount();	break;
		case 4: deleteAccount(); break;
		case 5: banAccount();	break;
		case 6: unbanAccount(); break;
		}
	}
}

void admin::banAccount() {
	system("cls");
	showAccounts();
	cout << "\n Enter the account number you want to ban:\n";
	int p, c = enterInt(1, list._accounts.getLength() + 1, "\n Select one of the existing accounts.\n") - 1;
	if (!isLastAdmin(c)) {
		if (list._accounts[c].item.getAccess() == 0) {
			system("cls");
			cout << "\n This account does not have access anyway.\n";
		}
		else {
			cout << " Are you sure you want to block this account?\n" << "1: Yes\n2: No\n";
			p = enterInt(1, 2, "\n Select one of the existing items of menu.\n");
			switch (p) {
			case 1: list._accounts[c].item.setAccess(0); break;
			default: cout << "You canceled this action. \n"; break;
			}
			system("cls");
			cout << "\nAccount has been blocked! \n" << endl;
		}
	}
	else {
		system("cls");
		cout << "This is the only administrator, so you cannot block this. \n" << endl;
		list.writeInFile();
	}
}
void admin::unbanAccount() {
	system("cls");
	int index, c;
	showAccounts();
	cout << " Enter the number of the account you are going to unblock: \n";
	index = enterInt(1, list._accounts.getLength() + 1, "\n Select one of the existing accounts.\n") - 1;
	if (list._accounts[index].item.getAccess() == 1) {
		system("cls");
		cout << "\n This account already has access.\n";
	}
	else {
		cout << " Are you sure you want to unblock this account?\n" << "1: Yes\n2: No\n";
		c = enterInt(1, 2, "\n Select one of the existing items of menu.\n");
		switch (c){
		case 1: list._accounts[index].item.setAccess(1); break;
		default: break;
		}
		system("cls");
		if (c == 2) cout << "\n Account has been unblocked\n";
		else cout << "\n You canceled this action\n";
		list.writeInFile();
	}
}
bool admin::isLastAdmin(int index) { ///???????
	int counter = 0;
	for (int i = 0; i < list._accounts.getLength(); i++) {
		if (list._accounts[i].item.getRole() == 1 && list._accounts[i].item.getAccess() == 1){
			counter++;
		}
	}
	if (counter > 1) return 0;
	else return 1;
}

void accounts::readFile() {
	int counter = lengthAccountsFile();
	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (!fin.is_open()) {
		account a;
		a.setAccess(1);
		a.setRole(1);
		a.setLogin("admin");
		a.setPassword("admin");
		_accounts.add(a);
	}
	else {
		_accounts.readFile(FILE_OF_ACCOUNTS, counter);
	}
	fin.close();
}
void accounts::writeInFile() {
	_accounts.writeInFile(FILE_OF_ACCOUNTS);
}
account* accounts::LogIn(){
	system("cls");
	int i;
	account  u;
	string login, password;
	do {
		cout << "\n------LOGIN MENU-----\n\n";
		cout << " Enter login:\n ";
		login = inputString();
		u.setLogin(login);
		i = _accounts.search(u);
		if (i == -1) {
			if (loginError() == 0) break;
			else continue;
		}
		else {
			cout << " Enter password:\n ";
			password = inputPassword();
			if (_accounts[i].item.getAccess() && _accounts[i].item.getPassword() == password) {
				if (_accounts[i].item.getRole() == 1 ){
					admin adm(*this);
					return &adm;
				}
				else {
					account acc;
					return &acc;
				}
			}
			else {
				if (!loginError()) break;
				else continue;
			}
		}
	} while (true);
}
void accounts::registration(){
	string login, password;
	cout << "\n------REGISTRATION------\n\n";
	cout << " Do you want to register?\n 1: Yes\n 2: No\n";
	bool c = enterInt(1, 2, " There is no such option\n") - 1;
	account reg;
	switch (c)
	{
	case 0:
		cout << " Enter login:\n ";
		login = inputString();
		cout << " Enter password:\n ";
		password = inputPassword();
		reg.setUser(login, password, 0, 0);
		_accounts.add(reg);
		break;
	default: break;
	}
	writeInFile();
}
bool accounts::loginError() {
	int choice;
	cout << "\n Something went wrong! Do you want to try again?\n1: Yes\n2: Exit\n";
	choice = enterInt(1, 2, " Select one of the existing accounts.\n\n");
	switch (choice) {
	case 1: system("cls"); return 1; break;
	case 2: return 0; break;
	}
}
int accounts::lengthAccountsFile() {
	int number_of_strings = 0;
	string str;
	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (!fin.is_open())
	{
		fin.close();
		return 0;
	}
	else {
		string buffer;
		while (getline(fin, buffer)) number_of_strings++;
		fin.close();
		number_of_strings -= 1;
		return number_of_strings;
	}
	return number_of_strings;
}

bool operator==(const account& o1, const account& o2) {
	if (o1.login == o2.login) {
		return true;
	}
	return false;
}
ostream& operator<<(ostream& out, const account& o) {
	out << o.login << ' ' << o.password << ' ' << o.role << ' ' << o.access << endl;
	return out;
}

void admin::showAccounts() {
	system("cls");
	cout << "#   Login    Password    role    access";
	list._accounts.print();
}
void admin::addAccount() {
	system("cls");
	account a;
	a.enterUser();
	list._accounts.add(a);
	list.writeInFile();
	system("cls");
}
void admin::editAccount() {
	system("cls");
	showAccounts();
	int i = 0, choice = 0, c = 0;
	cout << " Select the account you want to edit:\n";
	while (!i) {
		i = enterInt(1, list._accounts.getLength(), " Select one of the existing accounts.\n") - 1;
	}
	cout << " What exactly do you want to change?\n1: Login\n2: Password\n3: Role\n4: Access\n0: Exit\n";
	choice = enterInt(0, 4, " Select one of the existing menu items.\n");
	string a;
	switch (choice) {
	case 0: break;
	case 1:
		cout << "\n\n Enter new login:\n";
		a = inputString();
		list._accounts[i].item.setLogin(a); break;
	case 2:
		cout << "\n\n Enter new password:\n";
		a = inputString();
		list._accounts[i].item.setPassword(a); break;
	case 3:
		cout << " Select new role:\n1: User\n2: Administrator\n";
		c = (enterInt(1, 2, " Select one of the existing menu items.\n") - 1);
		list._accounts[i].item.setRole(c); break;
	case 4:
		cout << " Select the access right:\n1: Access is not possible\n2: Access is possible\n";
		c = (enterInt(1, 2, " Select one of the existing menu items.\n") - 1); 
		list._accounts[i].item.setAccess(c); break;
	}
	system("cls");
	cout << "\n The changes were successfully made.\n";
	list.writeInFile();
}
void admin::deleteAccount() {
	system("cls");
	showAccounts();
	int i = 0, choice = 0;
	cout << " Select the account you want to delete:\n";
	while (!i) {
		i = enterInt(1, list._accounts.getLength() + 1, " Select one of the existing accounts.\n");
	}
	cout << " Are you sure?\n1: Yes\n2: Undo\n";
	choice = enterInt(1, 2, " Select one of the existing accounts.\n");
	switch (choice)
	{
	case 1: list._accounts.remove(i);
	default: break;
	}
}


