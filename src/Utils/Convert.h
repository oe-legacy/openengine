// Type conversion functions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CONVERT_
#define _CONVERT_

#include <sstream>
#include <string>

namespace OpenEngine {
namespace Utils {

using std::string;

/**
 * Type conversion functions.
 *
 * @class Convert Convert.h Utils/Convert.h
 */
class Convert {
public:
    static string ToLower(string str);

    /** 
     * Generic method for converting something to string
     * 
     * @param t Input you want to convert to string
     * 
     * @return String representing the input
     */
    template<class T> static string ToString(const T& t) {
        std::stringstream ss;
	ss << t;
	return ss.str();
    }
};

} // NS Utils
} // NS OpenEngine

#endif
