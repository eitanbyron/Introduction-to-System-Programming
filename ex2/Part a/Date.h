//
// Created by BBIRONN on 07/06/2021.
//

#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

#include <iostream>


class Date {
    int day;
    int month;
    double time;


public:

    /**
* Date constructor: creating new class from type Date.
*
* @param day - the day that the exam occurs on.
* @param month - the month that the exam occurs on.
* @param time - the time that the exam occurs on.
*/
    Date (int day,int month,double time);
    /**
* Date copy constructor: copying the date details to new class.
*
* @param old_date - date to copy.
*/
    Date (const Date& old_date) = default;

    /**
* Date destructor: deleting the date details.
*/
    ~Date() = default;

    /**
* operator=: assignment operator.
*
* @param Date - date to assign.
*/
    Date& operator=(const Date&) = default;

    /**
* operator-: returning the difference in days between the left date and the right date.
*
* @param right_date - date.
*
* @return
* difference in days between the left date and the right date.
*/
    int operator-(const Date& right_date);

    /**
* operator<<: insertion operator.
*
* @param os - output stream object.
* @param date_print - date to send.
*/

    friend std::ostream& operator<<(std::ostream& os, const Date& date_print);
};


#endif //UNTITLED_DATE_H
