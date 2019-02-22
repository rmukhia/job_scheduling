#ifndef DATE_H
#define DATE_H

#include <istream>
#include <ostream>


class Date
{
    public:
        Date();
        virtual ~Date();
        int date;
        int month;
        int year;
        int minutes;

        void parse_date(char *c);

        int compare(const Date &d);

        void addMinutes(int minutes);

        int days_difference(const Date &d);

        friend std::ostream& operator<<(std::ostream& os, const Date& dt);
        Date& operator= (const Date &date);
    protected:

    private:
        int getDayForMonth(int month, int year);
        int rdn(int y, int m, int d);
};

#endif // DATE_H
