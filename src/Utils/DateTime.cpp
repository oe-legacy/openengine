#include <Utils/DateTime.h>

#include <ostream>
#include <iomanip>

namespace OpenEngine {
namespace Utils {

    int operator==(const DateTime& left,const DateTime& right) {
        if(left.GetSecond() == right.GetSecond() &&
           left.GetMinute() == right.GetMinute() &&
           left.GetHour() == right.GetHour() &&
           left.GetDay() == right.GetDay() &&
           left.GetMonth() == right.GetMonth() &&
           left.GetYear() == right.GetYear() )
            return true;
        return false;
    }

    int operator!=(const DateTime& left,const DateTime& right) {
        return !(left==right);
    }

    std::ostream& operator<<(std::ostream& os, const DateTime datetime) {
        os << std::setw(4) << std::setfill('0') << datetime.GetYear() << "/";
        os << std::setw(2) << std::setfill('0') << datetime.GetMonth() << "/";
        os << std::setw(2) << std::setfill('0') << datetime.GetDay() << " ";
        os << std::setw(2) << std::setfill('0') << datetime.GetHour() << ":";
        os << std::setw(2) << std::setfill('0') << datetime.GetMinute() << ":";
        os << std::setw(2) << std::setfill('0') << datetime.GetSecond();
        return os;
    }

} // NS Utils
} // NS OpenEngine
