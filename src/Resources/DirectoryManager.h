// Program name and description
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DIRECTORY_MANAGER_H_
#define _DIRECTORY_MANAGER_H_

#include <string>
#include <list>
#include <map>
#include <iostream>

using namespace std;

namespace OpenEngine {
namespace Resources {

class DirectoryManager {
 private:
    static list<string> paths;
    static map<string, string> pathcache;
	
 public:
    static void AppendPath(string);
    static void PrependPath(string);
    static bool IsInPath(string);
    static string FindFileInPath(string);
};

} // NS Resources
} // NS OpenEngine

#endif //_DIRECTORY_MANAGER_H_
