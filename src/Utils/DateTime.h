#ifndef _DATE_TIME_
#define _DATE_TIME_

#include <Meta/Time.h>

#include <ostream>

namespace OpenEngine {

namespace Resources {
    class File;
}

namespace Utils {

class DateTime {
    friend class OpenEngine::Resources::File;
 protected:
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned int second;

    void fill(tm t) {
        year = t.tm_year;
        if (year<1900) year += 1900;

        month = t.tm_mon + 1;
        day = t.tm_mday;

        hour = t.tm_hour;
        minute = t.tm_min;
        second = t.tm_sec;
    }

    DateTime(tm t) {
        this->fill(t);
    }

    DateTime(time_t t) {
        struct tm* tminfo = localtime ( &t );
        this->fill(*tminfo);
    }
 public:
    DateTime() {
        year = month = day = 0;
        hour = minute = second = 0;
    }

    static DateTime GetCurrent() {
        time_t t;
        time(&t);
        return DateTime(t);
    }

    unsigned int GetYear() const {
        return year;
    }

    unsigned int GetMonth() const {
        return month;
    }

    unsigned int GetDay() const {
        return day;
    }

    unsigned int GetHour() const {
        return hour;
    }

    unsigned int GetMinute() const {
        return minute;
    }

    unsigned int GetSecond() const {
        return second;
    }
};

int operator==(const DateTime& left,const DateTime& right);
int operator!=(const DateTime& left,const DateTime& right);

std::ostream& operator<<(std::ostream& os, const DateTime datetime);

} // NS Utils
} // NS OpenEngine

#endif // _DATE_TIME_
