// Type conversion functions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/Convert.h>

namespace OpenEngine {
namespace Utils {

/**
 * Lowercase a string.
 *
 * @param str String to lowercase.
 * @return String in lowercase.
 */
string Convert::ToLower(string str) {
    string lstr;
    for (unsigned int i=0; i<str.size(); i++) {
        char c = str[i];
        lstr.push_back(tolower(c));
    }
    return lstr;
}

} // NS Utils
} // NS OpenEngine
