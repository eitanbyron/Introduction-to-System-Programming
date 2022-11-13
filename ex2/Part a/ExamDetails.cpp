//
// Created by BBIRONN on 06/06/2021.
//

#include "ExamDetails.h"

using std::string;
using std::endl;
using std::ostream;
namespace mtm {

    ExamDetails::ExamDetails(const int course_num_new, int month_new, int day_new, double time_new,
                             const int length_new, string link_new) {
        try {
            date = new Date(day_new, month_new, time_new);
        }
        catch (std::bad_alloc &ba) {
            throw std::bad_alloc();
        }
        catch (ExamDetails::InvalidDateException d) {
            throw ExamDetails::InvalidDateException();
        }
        catch (ExamDetails::InvalidTimeException t) {
            throw ExamDetails::InvalidTimeException();
        }
        if (course_num_new < 0 || length_new < 0)
            throw ExamDetails::InvalidArgsException();
        course_num = course_num_new;
        length = length_new;
        link = link_new;
    }


    ExamDetails::ExamDetails(const ExamDetails &old_details) :
            course_num(old_details.course_num),
            length(old_details.length),
            link(old_details.link) {
        try {
            date = new Date(*old_details.date);
        }
        catch (std::bad_alloc &ba) {
            throw std::bad_alloc();
        }
    }

    ExamDetails::~ExamDetails() {
        delete date;
    }

    ExamDetails &ExamDetails::operator=(const ExamDetails &details) {
        if (this == &details)
            return *this;
        Date *temp = nullptr;
        try {
            temp = new Date(*details.date);
        }
        catch (std::bad_alloc &ba) {
            throw std::bad_alloc();
        }
        delete this->date;
        this->date = temp;
        this->course_num = details.course_num;
        this->length = details.length;
        this->link = details.link;
        return *this;
    }

    string ExamDetails::getLink() const {
        string new_str(this->link);
        return new_str;
    }

    void ExamDetails::setLink(const string &new_link) {
        this->link = new_link;
    }


    int ExamDetails::operator-(const ExamDetails &right_details) const {
        int diff = *this->date - *right_details.date;
        return diff;

    }


    bool ExamDetails::operator<(const ExamDetails &right_details) const {
        if (*this - right_details < 0)
            return true;
        else
            return false;
    }

    ostream &operator<<(ostream &os, const ExamDetails &details) {
        os << "Course Number: " << details.course_num << endl;
        os << "Time: " << *details.date << endl;
        os << "Duration: " << details.length << ":00" << endl;
        return os << "Zoom Link: " << details.link << endl;
    }

    ExamDetails ExamDetails::makeMatamExam() {
        string link_mtm = "https://tinyurl.com/59hzps6m";
        ExamDetails mtm_exam;
         try {
           mtm_exam=ExamDetails(234124, 7, 28, 13, 3, link_mtm);
        }
        catch (std::bad_alloc &ba) {
            throw std::bad_alloc();
        }
        return mtm_exam;
    }

    ExamDetails::ExamDetails() :
    course_num(0),
    date(nullptr),
    length(0),
    link("")
    {
    }


}