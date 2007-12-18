// Type conversion functions.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

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
    static string int2string(int i);
    static string ToLower(string str);

	template<class T>
	static string ToString(const T& t);
};

} // NS Utils
} // NS OpenEngine
