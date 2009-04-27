#include <Resources/DirectoryManager.h>
#include <Logging/Logger.h>
#include <Resources/Exceptions.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

namespace OpenEngine {
namespace Resources {

namespace fs = boost::filesystem;

// initialization of static members
list<string> DirectoryManager::paths = list<string>();
map<string, string> DirectoryManager::pathcache = map<string, string>();

/** 
 * Append given path to the global path list
 * 
 * @param str File path to append
 */
void DirectoryManager::AppendPath(string str) {
    paths.push_back(str);
}

/** 
 * Prepend given path to the global path list
 * 
 * @param str File path to prepend
 */
void DirectoryManager::PrependPath(string str) {
    paths.push_front(str);
}

/** 
 * Test if the given path p is already in the search path
 * 
 * @param p Path to test
 * 
 * @return If the given path is already added
 */
bool DirectoryManager::IsInPath(string p) {
	list<string>::iterator itr;
	for (itr = paths.begin(); itr != paths.end() ; itr++) {
		if ((*itr) == p) {
			return true;
		}
	}
	return false;
}

/** 
 * Find a given file in the search paths
 * 
 * @param file Filename to find in path
 * 
 * @return The complete file path or the empty string if file is not found in path
 */
string DirectoryManager::FindFileInPath(string file) { 
	// looking in path cache for file -> fullpath
	map<string, string>::iterator thefile = pathcache.find(file);
	if (thefile != pathcache.end())
        return thefile->second;

	// file not found in cache, looking it up!
	list<string> possibles;
	
    // check for a global path as well
    possibles.push_back(file);

	for (list<string>::iterator itr = paths.begin(); itr != paths.end(); itr++) {
		string p = (*itr) + file;
		if (fs::exists(p)) {
			possibles.push_back(p);
		}
	}

	if (possibles.size() == 1) {
		pathcache[file] = *possibles.begin();
		return *possibles.begin();
	} else if (possibles.size() > 1) {
		string s = *possibles.begin();
		logger.warning << "Found more then one file matching the name given: " << file << logger.end;
		for (list<string>::iterator itr = possibles.begin(); itr != possibles.end(); itr++) {
			logger.warning << (*itr) << logger.end;
		}
		pathcache[file] = s;
		return s;
	} 
	throw ResourceException("Could not locate: " + file);
}

} // NS Resources
} // NS OpenEngine
