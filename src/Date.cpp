#include "Date.h"
#include <stdio.h>

#define MINUTES_PER_HOUR 60
#define SHIFT_PER_DAY (MINUTES_PER_HOUR * 16)



Date::Date()
{
    //ctor
    minutes = 0;
}

Date::~Date()
{
    //dtor
}

void Date::parse_date(char *c)
{
    sscanf(c, "%d-%d-%d", &date, &month, &year);
}

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
    os << dt.date << '-' << dt.month << '-' << dt.year;
    return os;
}

int Date::compare(const Date& d)
{

    if (year > d.year) return 1;
    else if (year < d.year) return -1;

    if (month > d.month) return 1;
    else if (month < d.month) return -1;

    if (date > d.date) return 1;
    else if (date < d.date) return -1;

    return 0;

}

int Date::getDayForMonth(int month, int year)
{
    int days_per_month[] = {
        31, //jan
        28, //feb
        31,
        30,
        31,
        30,
        31,
        31,
        30,
        31,
        30, //nov
        31, //dec
    };

    if (month != 2) return days_per_month[month - 1];

    // this is for leap year
    if (year % 4 ==0 ) return 29;
    else return 28;
}



void Date::addMinutes(int minutes)
{
    int minu = this->minutes;
    minu += minutes;
    while(minu > SHIFT_PER_DAY) {
        minu -= SHIFT_PER_DAY; // remove one shift
        date += 1; // increase date
        int days_in_month = getDayForMonth(month, year);
        if (date > days_in_month) { // increase month
            date = 1;
            month += 1;
        }
        if (month > 12) { // increase year
            month = 1;
            year += 1;
        }
    }
}

int Date::rdn(int y, int m, int d)   /* Rata Die day one is 0001-01-01 */
{
    if (m < 3)
        y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}

int Date::days_difference(const Date& d)
{
    int days = rdn(year, month, date) - rdn(d.year, d.month, d.date);
    return days;
}


Date& Date::operator=(const Date& d)
{
    year = d.year;
    month = d.month;
    date = d.date;
    minutes = d.minutes;
    return *this;
}
