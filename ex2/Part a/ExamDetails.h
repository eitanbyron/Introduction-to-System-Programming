//
// Created by BBIRONN on 06/06/2021.
//

#ifndef UNTITLED_EXAMDEATAILS_H
#define UNTITLED_EXAMDEATAILS_H
#include <iostream>
#include "Date.h"

namespace mtm {

    class ExamDetails {
        int course_num;
        Date *date;
        int length;
        std::string link;
        ExamDetails();
    public:

        /**
* ExamDetails constructor: creating new class from type ExamDetails.
*
* @param course_num_new - course's name.
* @param month_new - the month that the exam occurs on.
* @param day_new - the day that the exam occurs on.
* @param time_new - the time that the exam occurs on.
* @param length_new - the exam length (in hours).
* @param link_new - link to zoom meeting.
*/
        ExamDetails(int course_num_new, int month_new, int day_new, double time_new, int length_new,
                    std::string link_new = "");

        /**
* ExamDetails copy constructor: copying the exam details to new class.
*
* @param old_details - exam to copy.
*/
        ExamDetails(const ExamDetails &old_details);

        /**
* ExamDetails destructor: deleting the exam details.
*/
        ~ExamDetails();

        /**
* operator=: assignment operator.
*
* @param details - exam to assign.
*/
        ExamDetails &operator=(const ExamDetails &details);

        /**
* getLink: returning the exam link.
*
* @return
* zoom link (string).
*/
        std::string getLink() const;

        /**
* setLink: updating the exam link.
*
* @param new_link - new link.
*/

        void setLink(const std::string &new_link);

        /**
* operator-: returning the difference in days between the left exam and the right exam.
*
* @param right_details - exam.
*
* @return
* difference in days between the left exam and the right exam.
*/
        int operator-(const ExamDetails &right_details) const;

        /**
* operator<: checking if the left exam occurs before the right exam.
*
* @param right_details - exam.
*
* @return
* true - if the left exam occurs before the right exam.
* false -  if the right exam occurs before the left exam.
*/

        bool operator<(const ExamDetails &right_details) const;

        /**
    * operator<<: insertion operator.
    *
    * @param os - output stream object.
    * @param details - exam to send.
    */
        friend std::ostream &operator<<(std::ostream &os, const ExamDetails &details);

        /**
* makeMatamExam: creating exam class with preset values.
*/
        static ExamDetails makeMatamExam();

        /**
* exeptions.
*/
        class InvalidDateException {};

        class InvalidTimeException {};

        class InvalidArgsException {};
    };
}

#endif //UNTITLED_EXAMDEATAILS_H
