// Directory handling utility class.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <list>
#include <string>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Static utility class for handling directories.
 *
 * @class Directory Directory.h Resources/Directory.h
 */
class Directory {
public:
    static bool Exists(std::string directory);
    static void Make(std::string directory);
    static std::string GetCWD();
    static std::list<std::string> ListFiles(std::string directory);
};

} //NS Resources
} //NS OpenEngine

#endif //  _DIRECTORY_H_
