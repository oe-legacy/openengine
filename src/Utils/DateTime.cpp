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
        char fc = os.fill();
        os.fill('0');
        os << std::setw(4) << datetime.GetYear() << "/";
        os << std::setw(2) << datetime.GetMonth() << "/";
        os << std::setw(2) << datetime.GetDay() << " ";
        os << std::setw(2) << datetime.GetHour() << ":";
        os << std::setw(2) << datetime.GetMinute() << ":";
        os << std::setw(2) << datetime.GetSecond();
        os.flush();
        os.fill(fc);
        return os;
    }

} // NS Utils
} // NS OpenEngine
