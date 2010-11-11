#include <Resources/Directory.h>

#include <Resources/Exceptions.h>

// see: http://www.gnu.org/software/libc/manual/html_node/File-System-Interface.html
#include <sys/stat.h> //includes mkdir
//#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Resources {

std::string Directory::GetCWD() {
    char buffer[255];
    getcwd(buffer,255);
    std::string back = buffer;
    return buffer;
}

/**
 * Check if a directory exists.
 *
 * @param directory the path to the directory
 * @return true if the directory exists, false otherwise
 */
bool Directory::Exists(std::string directory) {
    std::string back = GetCWD();
    if (chdir(directory.c_str()) != 0) {
        return false; 
    }else {
        chdir(back.c_str());
        return  true;
    }
}

std::list<std::string> Directory::Tokenize(std::string directory) {
    std::list<std::string> out;
    std::istringstream iss(directory);
    std::string token;
    while (getline(iss, token, '/')) {
        out.push_back(token);
    }
    return out;
}

std::string Directory::TokensToString(std::list<std::string> folders) {
    std::list<std::string>::iterator folder = folders.begin();
    std::string directory = "";
    while (folder != folders.end()) {
        directory += *folder + "/";
        folder++;
    }
    return directory;
}

void Directory::Make(std::string directory) {
    std::list<std::string> dirs = Tokenize(directory);
    if (dirs.size() > 1) {
        dirs.pop_back();
        Make(TokensToString(dirs));
    }

    if (Directory::Exists(directory)) {
        return;
        //throw Core::Exception("directory allready exists: " + directory);
    }
	#if defined(_WIN32)
    if (mkdir(directory.c_str()) != 0) {
    #else
    if (mkdir(directory.c_str(),0777) != 0) {
    #endif
        throw Core::Exception("could not create directory: " + directory);
    }
}

std::list<std::string> Directory::ListFiles(std::string directory) {
    std::list<std::string> files;

    DIR *dp;
    struct dirent *dirp;
    if ((dp  = opendir(directory.c_str())) == NULL) {
        throw Core::Exception("Error opening: " + directory);
    }

    while ((dirp = readdir(dp)) != NULL) {
        std::string file(dirp->d_name);
        if (file != "." && file != "..")
            files.push_back(file);
    }
    closedir(dp);
    return files;
}

} //NS Resources
} //NS OpenEngine
