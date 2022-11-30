#include "header.h"

using namespace std;

class management {
	outletsList _outletsList;
	accounts _accountsList;
	account* currentUser;
public: 
	void login() {
		currentUser = _accountsList.LogIn();
		currentUser->menu(_outletsList);
	};
	void start() {
		bool flag = 1, trya = 0;
		_accountsList.readFile();
		_outletsList.readFile();
		while (flag) {
			system("cls");
			if (trya)cout << " *Wait until one of the administrators grants you access.\n\n";
			trya = 0;
			cout << "\n-------MANAGMENT-------\n\n 1: Log In\n 2: Register\n 0: Exit\n";
			int c = enterInt(0, 2, " Select one of the menu items\n");
			switch (c)
			{
			case 0: flag = 0; break;
			case 1: login(); break;
			case 2: system("cls");
				_accountsList.registration();
				trya = 1;
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	management m;
	m.start();
	return 0;
}