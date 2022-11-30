#pragma once
#include <iostream>
#include <string>

using namespace std;

class date {
    int day;
    int month;
    int year;
public:
    date();
    date(int, int, int);
    date(const date&);
    date(string);
    ~date(){};
    int dayInMonth(int);
    void setDay(int) ;
    void setMonth(int) ;
    void setYear(int) ;
    void setDate(int, int, int) ;
    int getDay() const ;
    int getMonth() const ;
    int getYear() const;
    bool isValidDate(int, int, int);
    void enterDate();

    bool operator>(const date& d) const;
    bool operator==(const date& d) const;
    friend ostream& operator<<(ostream& out, const date& d);
};