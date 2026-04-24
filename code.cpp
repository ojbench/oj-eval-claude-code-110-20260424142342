#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
private:
    int _year;
    int _month;
    int _day;

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int getMonthDays(int year, int month) const {
        if (month == 2 && isLeapYear(year)) return 29;
        return month_days[month];
    }

    bool isValid(int yy, int mm, int dd) const {
        if (yy < 0 || mm < 1 || mm > 12 || dd < 1) return false;
        if (dd > getMonthDays(yy, mm)) return false;
        return true;
    }

    void normalize() {
        while (_day > getMonthDays(_year, _month)) {
            _day -= getMonthDays(_year, _month);
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        while (_day <= 0) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day += getMonthDays(_year, _month);
        }
    }

    // Days from 1900-1-1 to this date
    long long toDays() const {
        long long days = 0;
        for (int y = 1900; y < _year; ++y) {
            days += isLeapYear(y) ? 366 : 365;
        }
        for (int m = 1; m < _month; ++m) {
            days += getMonthDays(_year, m);
        }
        days += _day - 1;
        return days;
    }

    // Set date from days since 1900-1-1
    void fromDays(long long days) {
        _year = 1900;
        _month = 1;
        _day = 1;

        if (days >= 0) {
            while (true) {
                int yDays = isLeapYear(_year) ? 366 : 365;
                if (days >= yDays) {
                    days -= yDays;
                    _year++;
                } else {
                    break;
                }
            }
            while (true) {
                int mDays = getMonthDays(_year, _month);
                if (days >= mDays) {
                    days -= mDays;
                    _month++;
                } else {
                    break;
                }
            }
            _day += days;
        } else {
            // Handle negative days if needed, but constraints say 1900-1-1 is min
            // For completeness:
            while (days < 0) {
                _year--;
                days += isLeapYear(_year) ? 366 : 365;
            }
            // Now days is positive relative to the new _year-1-1
            while (true) {
                int mDays = getMonthDays(_year, _month);
                if (days >= mDays) {
                    days -= mDays;
                    _month++;
                } else {
                    break;
                }
            }
            _day += days;
        }
    }

public:
    Date() : _year(1900), _month(1), _day(1) {}

    Date(int yy, int mm, int dd) {
        if (isValid(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }

    // Pre-increment
    Date& operator++() {
        _day++;
        normalize();
        return *this;
    }

    // Post-increment
    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }

    // Pre-decrement
    Date& operator--() {
        _day--;
        normalize();
        return *this;
    }

    // Post-decrement
    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }

    Date operator+(int days) const {
        Date res = *this;
        res._day += days;
        res.normalize();
        return res;
    }

    Date operator-(int days) const {
        Date res = *this;
        res._day -= days;
        res.normalize();
        return res;
    }

    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    long long operator-(const Date& other) const {
        long long d1 = this->toDays();
        long long d2 = other.toDays();
        return abs(d1 - d2);
    }

    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }

    void out() const {
        cout << *this << endl;
    }
};

void Test()
{
    int op;
    if (!(cin >> op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl;
        for (int i=0;i<5;++i) cout << d0++ << endl;
        for (int i=0;i<5;++i) cout << d0-- << endl;
        for (int i=0;i<2;++i) cout << --d0 << endl;
        cout << d0 << endl;
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        cout << d0 - 1000 << endl;
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main()
{
    Test();
    return 0;
}
