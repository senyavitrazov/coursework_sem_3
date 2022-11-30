#include "date.h"
#include "validity.h"

date::date() {
    day = 9;
    month = 9;
    year = 9999;
}
date::date(int d = 0, int m = 0, int y = 0) {
        setDate(d, m, y);
    }
date::date(const date& d) {
        setDate(d.day, d.month, d.year);
    }
int date::dayInMonth(int month)
    {
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) days[1] = 29;
        return days[month - 1];
    }
void date::setDay(int day) {
        this->day = day;
    }
void date::setMonth(int month) {
        this->month = month;
    }
void date::setYear(int year) {
        this->year = year;
    }
void date::setDate(int day, int month, int year) {
        if (isValidDate(day, month, year)) {
            setDay(day);
            setMonth(month);
            setYear(year);
        };
    }
int date::getDay() const {
        return day;
    }
int date::getMonth() const {
        return month;
    }
int date::getYear() const {
        return year;
    }
bool date::isValidDate(int day, int month, int year)
{
    if ((day < 1 || day>31) || (month < 1 || month>12))
    {
        cout << "Not valid date" << endl;
        return false;
    }
    return true;
}
date::date(string str) {
    string date = str;
    int counter = 0;
    if (date.at(1) == '.') date = '0' + date;
    if (date.at(4) == '.') date.insert(3, "0");
    for (int i = 0; i < date.length(); i++) {
        if (date.at(i) == '.') date.erase(i, 1);
        if (isdigit(date.at(i))) counter++;
    }
    int d = stoi(date.substr(0, 2)), m = stoi(date.substr(2, 2)), y = stoi(date.substr(4, 4));
    if (date.length() == 8 && counter == 8 && isValidDate(d, m, y)) {
        day = d;
        month = m;
        year = y;
    }
}
void date::enterDate() {
    bool flag = 1;
    int counter = 0, zero = 0;
    while (flag) {
        cout << "\n Input date in format dd.mm.yy:\n";
        string str;
        cin >> str;
        if (str.size() > 10 || str.size() < 8) {
            cout << " Invalid date! Try again\n";
            continue;
        }
        for (int i = 0; i < str.size(); i++) {
            if (!isdigit(str.at(i)) && str.at(i) != '.') {
                if (str.at(i) != '.') counter++;
                if (str.at(i) == '0') zero++;
                cout << " Invalid date! Try again\n";
                break;
            }
            else {
                if ((i != 1 && i != 2 && i != 3 && i != 4 && i != 5) && str.at(i) == '.') {
                    cout << " Invalid date! Try again\n";
                    break;
                }
                if (zero == 2 && str.size() <= 8) {
                    cout << " Invalid date! Try again\n";
                    break;
                }
                else {
                    if (stoi(str.substr(str.size()-4)) > 9998 || counter > 2) {
                        cout << " Invalid date! Try again\n";
                        break;
                    }
                    else {
                        flag = 0;
                        date a(str);
                        *this = a;
                    }
                }
            }

        }
    }
}

bool date::operator>(const date& d) const
{
    if (year > d.year) {
        return true;
    }
    else if (year == d.year) {
        if (month > d.month) {
            return true;
        }
        else if (month == d.month) {
            if (day > d.day) {
                return true;
            }
        }
    }
    return false;
}
bool date::operator==(const date& d) const {
    if (year == d.year && day == d.day && month == d.month) return true;
    return false;
}
ostream& operator<<(ostream& out, const date& d) {
    out << d.getDay() << '.' << d.getMonth() << '.' << d.getYear();
    return out;
};