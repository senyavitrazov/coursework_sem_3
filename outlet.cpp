#include "header.h"

int fileCounter = -1;

date currentDate()
{
	string str = "";
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);
	date currentDate((localtime.tm_mday), (localtime.tm_mon + 1), (localtime.tm_year + 1900));
	return currentDate;
}

outlet::outlet() {
	name = "name";
	date a;
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		_permissions[i] = 0;
		_permissonsBegins[i] = a;
		_permissonsEnds[i] = a;
	}
}
outlet::outlet(string s) {
	string name, permissions, permissionsBebins, permissionEnds;
	string arr[5];
	int mem[2];
	mem[0] = s.find_first_of("\"") + 1 ;
	mem[1] = s.find_last_of("\"");
	name = s.substr(mem[0], mem[1] - mem[0]);
	this->name = name;
	s = s.substr(mem[1]+1);
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		int temp = s.find_first_of("#")+1;
		_permissions[i] = stoi(s.substr(0,1));
		s = s.substr(temp);
	}
	int temp;
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		temp = s.find_first_of("#");
		date a(s.substr(0, temp));
		_permissonsBegins[i] = a;
		s = s.substr(temp + 1);
	}
	do {
		int i = 0;
		int temp = s.find_first_of("#");
		date a(s.substr(0, temp));
		_permissonsEnds[i] = a;
		s = s.substr(temp + 1);
		i++;
	} while (s != "");
}

string outlet::listOfPermissions(int choice) {
	switch (choice)	{
	case 1: return "Certificates of state registration"; break;
	case 2: return "Assortment list approval"; break;
	case 3: return "Confirmation of the purchase and delivery of goods"; break;
	case 4: return "Sanitaryand epidemiological permission"; break;
	default: return "Inclusion of information in the Commercial Register";
	}
}

void outlet::setName(string s) {

	this->name = s;
}
string outlet::getName() {
	return name;
}
string outlet::getPermissions() {
	string str = "";
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		str = str + to_string(int(_permissions[i])) + " ";
	};
	return str;
}
int outlet::getPermissionsSum(){
	int a = 0;
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		a += _permissions[i];
	}
	return a;
}
void outlet::enterOutlet(){
	string name;
	cout << "\n Enter name of the outlet:\n";
	name = getLine();
	setName(name);
	addPermissions();
	cout << "\n Enter assortmet of the outlet:\n";
	addAssortment();
}
void outlet::enterOutlet(string name) {
	setName(name);
	addPermissions();
	cout << "\n--ASSORTMENT--\n";
	addAssortment();
}
bool outlet::abilityToTrade() {
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		if (_permissions[i] == 0 || (currentDate() > _permissonsEnds[i] && _permissonsEnds[i].getYear() != 9999) ) return 0;
	}
	return 1;
}
void outlet::addPermissions() {
	int choice;
	bool flag = 0;
	cout << " Has the point of sale got all the permissions?\n1: Yes\n2: No\n3: Not a single\n";
	choice = enterInt(1, 3, " Choose one of the options provided.\n");
	switch (choice)	{
	case 1:
		for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
			_permissions[i] = 1;
		}
		break;
	case 2:
		for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
			editPermission(i);
		}
		break;
	default:
		for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
			_permissions[i] = 0;
		}
		cout << "The point of sale does not have permissions.\n";
		flag = 1;
	}
	for (int counter = 0, i = 0; i < PERMISSIONS_NUMBER; i++){
		if (_permissions[i] == 1) flag = 0;
	}
	if (!flag) {
		system("cls");
		cout << "\n----Permission dates----\n";
		cout << " \nAll permits were obtained in one day?\n1: Yes\n2: No\n";
		int c = enterInt(1, 2, " Choose one of the options provided.\n");
		date _date;
		switch (c) {
		case 1:
			_date.enterDate();
			for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
				if(_permissions[i] == 1) _permissonsBegins[i] = _date;
			}
			break;
		default:
			for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
				if (_permissions[i] == 1) {
					cout << "\n The date on which the \"" << listOfPermissions(i) << "\" was obtained\n";
					_date.enterDate();
					_permissonsBegins[i] = _date;
				}
			}
		}
		system("cls");
		cout << "\n----Expiration dates----\n";
		for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
			if (_permissions[i] == 1) {
				cout << "\n The expiration date of the " << listOfPermissions(i) << "is";
				_date.enterDate();
				_permissonsEnds[i] = _date;
			}
		}
	}
}
void outlet::showAll() {
	cout << "  " << setw(30) << left << getName() << " " << getPermissions() << setfill(' ');
	if (abilityToTrade() == 0) {
		cout << setw(12) << setfill(' ') << "     No way to trade";
	}
	else cout << setw(12) << right << "           Can trade";
	cout << endl;
}
void outlet::showPermissions(){
	date nan;
	cout << setw(56) << "Name of permission:" << setfill(' ') << setw(14) << right << " " << "   Obtaining  Expiration \n\n";
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		cout << setw(55) << listOfPermissions(i) << ':' << setfill(' ') << setw(15);
		_permissions[i] == 1 ? cout << "there is " : cout << "there isn't ";
		cout << "    ";
		_permissonsBegins[i] == nan ? cout << "NO DATE" : cout << _permissonsBegins[i];
		cout << "  ";
		_permissonsEnds[i] == nan ? cout << "NO DATE" : cout << _permissonsEnds[i];
		cout << "    " << endl;
	}
}
void outlet::editPermission(int i) {
	cout << endl << " Do you have the "<< listOfPermissions(i)<< "? \n1 : Yes\n2 : No\n";
	_permissions[i] = !(enterInt(1, 2, " Choose one of the options provided.\n")-1);
}

void outlet::addAssortment() {
	bool flag = 1, counter = 0;
	while (flag) {
		int choice; 
		if (counter) {
			cout << "\n Do you want to add another product?\n1: Yes\n2: No\n";
			choice = enterInt(1, 2, " Choose one of the options provided.\n");
		}
		else {
			choice = !counter;
		}
		switch (choice) {
		case 1:
			addProductToAssort();
			counter = 1;
		break;
		default: flag = 0; break;
		}
	}
}
void outlet::showAssortment() {
	cout << setw(70) << setfill(' ') << right << "Name of product:" << setw(12) << "Amount:" << setw(9) << "Price:" << endl;
	for (int i = 0; i < assortment.getLength(); i++) {
		cout  << setw(45) << setfill(' ')  << right << i + 1 <<  setw(25) << setfill(' ') << right << assortment[i].item.getName() <<
			setw(12) << assortment[i].item.getNumber() <<
			setw(9) << assortment[i].item.getPrice() << endl;
	}
}
void outlet::addProductToAssort(product& prod) {
	assortment.add(prod);
}
void outlet::addProductToAssort() {
	product p;
	p.enterProduct();
	assortment.add(p);
}
void outlet::deleteProductFromAssort(int index) {
	assortment.remove(index);
}
void outlet::editProduct(int i) {
	assortment[i].item.enterProduct();
}
void outlet::editAssortment() {
	bool flag = 1;
	int index = 0;
	while (flag) {
		system("cls");
		cout << "# " << setw(30) << left << "Name of Outlet" << setw(15) << setfill(' ') << "Permissions" << setw(15) << setfill(' ') << "Abitity to Trade\n\n";
		showAll();
		cout << endl;
		showAssortment();
		cout << "\n\n-----EDITING OF ASSORTMENT-----\n\n1: Add product\n2: Edit product\n3: Delete product\n0: Exit\n";
		int choose = enterInt(0, 3, " Select one of the menu items\n");
		switch (choose) {
		case 1: addProductToAssort(); break;
		case 2: 
			cout << " Choose the product you want to edit:\n";
			index = enterInt(1, assortment.getLength(), " Choose one of existing products\n") - 1;
			editProduct(index);
			break;
		case 3:
			cout << " Choose the product you want to delete:\n";
			index = enterInt(1, assortment.getLength(), " Choose one of existing products\n") - 1;
			deleteProductFromAssort(index);
			break;
		default: flag = 0; break;
		}
	}
}

bool outlet::operator==(const outlet& d) {
	if (name == d.name) {
		return true;
	}
	return false;
}
bool outlet::operator==(string _name) {
	if (name == _name) {
		return true;
	}
	return false;
}


ostream& operator<<(ostream& out, outlet& o) {
	out << "#\"" << o.name << "\"";
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		out << o._permissions[i] << "#";
	}
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		out << o._permissonsBegins[i] << "#";
	}
	for (int i = 0; i < PERMISSIONS_NUMBER; i++) {
		out << o._permissonsEnds[i] << "#";
	}
	out << "\n";
	//assortment
	for (int i = 0; i < o.assortment.getLength(); i++) {
		out << o.assortment[i].item;
	}
	return out;
}

//void outletsList::readFile() {
//	int counter = lengthDataFile();
//	string str = " ";
//	ifstream fin(FILE_OF_DATA, ios::in);
//	if (!fin.is_open()) {
//		fin.close();
//	}
//	else {
//		while (str != ""){
//			getline(fin, str);
//			if (str[0] == '#') {
//				outlet a(str);
//				_outlets.add(a);
//			}
//			if (str[0] == '-') {
//				product a(str);
//				_outlets.end()->item.addProductToAssort(a);
//			}
//		}
//	}
//	fin.close();
//}
void outletsList::readFile(string filename) {
	int counter = lengthDataFile(filename);
	string str = " ";
	ifstream fin(filename, ios::in);
	if (!fin.is_open()) {
		fin.close();
	}
	else {
		while (str != "") {
			getline(fin, str);
			if (str[0] == '#') {
				outlet a(str);
				_outlets.add(a);
			}
			if (str[0] == '-') {
				product a(str);
				_outlets.end()->item.addProductToAssort(a);
			}
		}
	}
	fin.close();
}
void outletsList::writeInFile(){
	if (fileCounter == -1) fileCounter = 0;
	fileCounter++;
	if (fileCounter == 2) fileCounter = 0;
	_outlets.writeInFile(FILES_OF_DATA[fileCounter]);
}
bool outletsList::undoAction() {
	if (fileCounter == -1) return 1;
	else {
		_outlets.clear();
		readFile(FILES_OF_DATA[!fileCounter]);
		fileCounter = -1;
		return 0;
	}
}
int outletsList::lengthDataFile(string filename) {
	int number_of_strings = 0;
	string str;
	ifstream fin(filename, ios::in);
	if (!fin.is_open())
	{
		fin.open(filename, ios::in);
		//fin.close();
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

void outletsList::showOutlets(){
	bool flag = 1;
	while (flag) {
	system("cls");
		cout << "# " << setw(30) << left << "Name of Outlet" << setw(15) << setfill(' ') << "Permissions" << setw(15) << setfill(' ') << "Abitity to Trade\n\n";
		for (int i = 0; i < _outlets.getLength(); i++) {
			showOneOutlet(i);
		};
		cout << "\n\n 1: View outlet in detail\n 2: Sort outlets\n 0: Exit\n";
		int c = enterInt(0, 2, " Select one of the existing menu items.\n");
		int index = -1;
		switch (c) {
		case 0: flag = 0;  break;
		case 1:
			cout << " Enter the number of the outlet you want to see in detail:\n";
			index = enterInt(1, _outlets.getLength(), " Select one of the existing points.\n") - 1;
			showDetails(index);
			break;
		case 2:
			sort();
			cout << "# " << setw(30) << left << "Name of Outlet" << setw(15) << setfill(' ') << "Permissions" << setw(15) << setfill(' ') << "Abitity to Trade\n\n";
			for (int i = 0; i < _outlets.getLength(); i++) {
				showOneOutlet(i);
			};
			break;
		default:
			break;
		}
	}
	//sort + details
}
void outletsList::sort() {
	cout << " 1: Sort by name\n" << " 2: Sort by ability to trade\n" << " 3: Permissions\n";
	int choice, n = enterInt(1, 3, "");
	switch (n) {
	case 1: cout << " 1. Alphabetically from 'A' to 'Z'\n" << " 2. Alphabetically from 'Z' to 'A'\n";
		choice = enterInt(1, 2, "");
		if (choice == 1) _outlets.sort(sortByNameDown);
		if (choice == 2) _outlets.sort(sortByNameUp);
		break;
	case 2: cout << " 1. The first are the ones that can trade\n" << " 2. The first ones are those that cannot trade\n";
		choice = enterInt(1, 2, "");
		if (choice == 1) _outlets.sort(sortByAbilityUp);
		if (choice == 2) _outlets.sort(sortByAbilityDown);
		break;
	case 3: cout << " 1. The first ones are those with more permissions\n" << " 2. The first ones are those with fewer permissions\n";
		choice = enterInt(1, 2, "");
		if (choice == 1) _outlets.sort(sortByPermissionsUp);
		if (choice == 2) _outlets.sort(sortByPermissionsDown);
		break;
	}
	cout << "Successfully sorted!" << endl;
}
void outletsList::showDetails(int index) {
	system("cls");
	cout << "  " << setw(30) << left << "Name of Outlet" << setw(15) << setfill(' ') << "Permissions" << setw(15) << setfill(' ') << "Abitity to Trade\n\n";
	_outlets[index].item.showAll();
	cout << endl << setw(55) << right << "---Current date: " << currentDate() << "---" << "\n\n";
	_outlets[index].item.showPermissions();
	if (_outlets[index].item.abilityToTrade()) cout << "\nThis outlet is able to trade.\n";
	else cout << "\nThis outlet is not able to trade.\n\n\n";
	_outlets[index].item.showAssortment();
	cout << "Enter any key to close.\n";
	_getch();
}
void outletsList::showDetails(outlet* o) {
	system("cls");
	cout << "  " << setw(30) << left << "Name of Outlet" << setw(15) << setfill(' ') << "Permissions" << setw(15) << setfill(' ') << "Abitity to Trade\n\n";
	o->showAll();
	cout << endl << setw(55) << right << "---Current date: " << currentDate() << "---" << "\n\n";
	o->showPermissions();
	if (o->abilityToTrade()) cout << "\nThis outlet is able to trade.\n";
	else cout << "\nThis outlet is not able to trade.\n\n\n";
	o->showAssortment();
	cout << "Enter any key to close.\n";
	_getch();
}

void outletsList::showOneOutlet(int i) {
	cout << i+1;
	_outlets[i].item.showAll();
}
outlet* outletsList::searchOutlet(){
	bool c = 0;
	string name;
	while (!c) {
		system("cls");
		cout << "\n Enter the name of the outlet you are looking for.\n";
		name = getLine();
		cout << endl;
		for (int i = 0; i < _outlets.getLength(); i++) {
			if (_outlets[i].item.getName() == name) {
				return &_outlets[i].item;
			}
		}
		cout << "\n Try again?(1: Yes / 2: No)\n";
		c = enterInt(1, 2, "") - 1;
		if (c) return nullptr;
	}
}
void outletsList::addOutlet(){
	outlet o;
	string name;
	bool flag = 1;
	while (flag)
	{
		bool founder = 0;
		cout << " Enter name of outlet:\n";
		name = getLine();
		for (int i = 0; i < _outlets.getLength(); i++) {
			if (_outlets[i].item.getName() == name)
			{
				cout << "\n There is already a sales outlet with this name. Change something in the title\n";
				founder = 1;
			}
		}
		if (!founder) flag = 0;
	}
	o.setName(name);
	o.addPermissions();
	cout << "\n Add assortment:\n";
	_outlets.add(o);
	_outlets.end()->item.addAssortment();
	writeInFile();
}
void outletsList::showWithoutSorting() {
	cout << "# " << setw(30) << left << "Name of Outlet" << setw(15) << setfill(' ') << "Permissions" << setw(15) << setfill(' ') << "Abitity to Trade\n\n";
	for (int i = 0; i < _outlets.getLength(); i++) {
		showOneOutlet(i);
	};
}
void outletsList::deleteOutlet() {
	system("cls");
	showWithoutSorting();
	int i = -1, choice = 0;
	bool flag = 1;
	while (flag) {
		cout << "\n\n Select the outlet you want to delete(0 - Exit):\n";
		i = enterInt(0, _outlets.getLength(), " Select one of the existing outlets.\n") - 1;
		if (i == -1) {
			flag = 0;
			break;
		}
		cout << " Are you sure?\n1: Yes\n2: Undo\n";
		choice = enterInt(1, 2, " Select one of menu items.\n");
		switch (choice)
		{
		case 1: 
			system("cls");
			if (i == 0) _outlets.removeFirst();
			else _outlets.remove(i+1);
			showWithoutSorting();
		default: break;
		}
	}
	writeInFile();
}
void outletsList::editOutlet() {
	int i = 0, choice = 0, c = 0;
	bool flag = 1;
	while (flag) {
		bool f = 1;
		system("cls");
		showWithoutSorting();
		cout << "\n\n Enter the number of outlet you want to edit(0 - Exit):\n";
		i = enterInt(0, _outlets.getLength(), " Select one of the existing accounts.\n") - 1;
		if (i == -1) {
			flag = 0;
			break;
		}
		cout << " What exactly do you want to change?\n1: Name\n2: Permissions\n3: Assortment\n0: Exit\n";
		choice = enterInt(0, 3, " Select one of the existing menu items.\n");
		string a;
		switch (choice) {
		case 0: break;
		case 1:
			while (f)
			{
				bool founder = 0;
				cout << "\n\n Enter new name of outlet:\n";
				a = getLine();
				for (int c = 0; c < _outlets.getLength(); c++) {
					if (_outlets[c].item.getName() == a)
					{
						cout << "\n There is already a sales outlet with this name. Change something in the title\n";
						founder = 1;
					}
				}
				if(!founder) f = 0;
			}
			_outlets[i].item.setName(a); break;
		case 2:
			_outlets[i].item.addPermissions(); break;
		case 3:
			_outlets[i].item.editAssortment(); break;
		}
		system("cls");
		cout << "\n The changes were successfully made.\n";
		writeInFile();
	}
}