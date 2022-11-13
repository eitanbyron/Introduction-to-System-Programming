//
// Created by BBIRONN on 07/06/2021.
//

#include "Date.h"
#include "ExamDetails.h"

using std::endl;
using std::ostream;


Date::Date(const int day_new,const int month_new,double time_new)
    {
    static const double LAST_HOUR = 23.5;
    static const double SIZE_DIFF = 0.000001;
    if (day_new<1 || day_new> 30 || month_new<1 || month_new> 12)
        throw mtm::ExamDetails::InvalidDateException();
    if (time_new <0 - SIZE_DIFF || time_new >LAST_HOUR + SIZE_DIFF)
        throw mtm::ExamDetails::InvalidTimeException();
    day = day_new;
    month =month_new;
    time = time_new;
}

int Date::operator-(const Date& right_date) 
{
        int month_diff =this->month - right_date.month;
        int days_diff = this->day - right_date.day;
        return month_diff*30 + days_diff;
}

ostream& operator<<(ostream& os, const Date& date_print)
{
       os << date_print.day << "." << date_print.month;
    int hours = (int)date_print.time ;
    double minutes = date_print.time - hours;
    if (minutes == 0)
        return os <<" at "<< hours << ":" << "00";
    else
        return os <<" at "<< hours << ":" << "30";
}