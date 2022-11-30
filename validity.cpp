#include <string>
#include "validity.h"

double enterDouble() {
	while (true)
	{
		double t;
		cin >> t;
		if (cin.fail())
		{
			cout << " Incorrect entry, please try again!\n";
			cin.clear();
			cin.ignore(879, '\n');
		}
		else
		{
			if (t < 0)
			{
				cout << "The quantity cannot be negative!\n>";
			}
			else
			{
				cin.ignore(879, '\n');
				return t;
			}
		}
	}
}
int enterInt() {
	while (true)
	{
		int t;
		cin >> t;
		if (cin.fail())
		{
			cout << " Incorrect entry, please try again!\n";
			cin.clear();
			cin.ignore(879, '\n');
		}
		else
		{
			if (t < 0)
			{
				cout << "The quantity cannot be negative!\n>";
			}
			else
			{
				cin.ignore(879, '\n');
				return t;
			}
		}
	}
}
int enterInt(int border1, int border2, string warn)
{
	int z;
	while (!(cin >> z) || z < border1 || z > border2 || cin.get() != '\n')
	{
		cout << warn << '\n';
		cin.clear();
		cin.ignore(879, '\n');
	}
	return z;
}
string inputString() {
	char ch;
	int num = 0;
	string str;
	int flag = 1;
	while (flag)
	{
		do
		{
			ch = _getch();
			if (ch == 13) break;
			if (ch == '\b' && !str.empty())
			{
				cout << '\b';
				cout << ' ';
				cout << '\b';
				str.pop_back();
				continue;
			}
			if (isalnum((unsigned char)ch))
			{
				num++;
				cout << ch;
				str.push_back(ch);
			}
		} while (num < MAX_STRING);
		if (num > 3)
		{
			cout << endl;
			return str;
		}
	}
}
string inputPassword() {
	char ch;
	int next = 0;
	string password;
	do
	{
		ch = _getch();

		if (ch == 13) break;
		if (ch == '\b' && !password.empty())
		{
			cout << '\b';
			cout << ' ';
			cout << '\b';

			password.pop_back();
			continue;
		}
		if (isalnum((unsigned char)ch))
		{
			next++;
			cout << '*';
			password.push_back(ch);
		}

	} while (next < PASSWORD_LENGHT - 1);
	cout << endl;
	return password;
}
string getLine() {
	string s;
	getline(cin, s);
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '#') {
			s[i] = ' ';
		}
	}
	return s;
}