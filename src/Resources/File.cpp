#include <Resources/File.h>
#include <Resources/Exceptions.h>

#include <sys/stat.h>

namespace OpenEngine {
namespace Resources {

/**
 * Open a file.
 *
 * @param filename File name.
 * @param mode Open mode (see standard io streams)
 * @return Input file stream pointer.
 * @throws ResourceException
 */
ifstream* File::Open(string filename, ios_base::openmode mode) {
    ifstream* file;
    file = new ifstream(filename.c_str(), mode);

    if(!file->is_open()) {
        file->close();
        delete file;
        throw ResourceException("File not found: " + filename);
    }
    if(file->fail()) {
        file->clear(ios::failbit);
        file->close();
        delete file;
        throw ResourceException("Failed while opening file: " + filename);
    }
    if (!file->good()) {
        file->close();
        delete file;
        throw ResourceException("Error opening file: " + filename);
    }
    return file;
}

/**
 *  Returns the size in bytes of the file "filename".
 *  If an error occurred, it throw an exception.
 *  Done by: open the file and seek to the end to find its length
 *
 * @param filename File name.
 * @return File size in bytes.
 * @throws ResourceException
 */
int File::GetSize(string filename) {
    ifstream* file = File::Open(filename);
    int size = 0;
	while (!file->eof()) {
		file->get();
		size++;
	}
	file->close();
    delete file;
    if(size==0)
        throw ResourceException("Error calculating size of: " + filename);
    return size;
}

Utils::DateTime File::GetLastModified(string filename) {
    struct stat sb;
    stat (filename.c_str(), &sb);
    time_t time(sb.st_mtime);
    return Utils::DateTime(time);
}

/**
 * Get the extension of a file.
 * It the filename contains no extension (part following the last
 * period) the empty string is returned.
 *
 * @code
 * File::Extension("/some/dir/file.ext");    // -> "ext"
 * File::Extension("/some/dir/my.file.ext"); // -> "ext"
 * File::Extension("/some/dir/file.");       // -> ""
 * File::Extension("/some/dir/file");        // -> ""
 * // watch out for this one!
 * File::Extension("/some/dir.d/file");      // -> "d/file"
 * @endcode
 *
 * @param filename File name.
 * @return File extension.
 */
string File::Extension(string filename) {
    size_t i = filename.rfind('.');
    if (i == string::npos || i+1 == filename.size()) return "";
    return filename.substr(i+1);
}

/**
 * Get the parent of a file string.
 * If the file has no parent the empty string is returned. If the
 * string ends with a slash the parent of the file without the slash
 * is returned.
 * @code
 * File::Parent("/some/dir/file"); // -> "/some/dir/"
 * File::Parent("/some/dir/");     // -> "/some/"
 * File::Parent("/some/");         // -> "/"
 * File::Parent("/");              // -> ""
 * @endcode
 *
 * @param filename File path.
 * @return File path parent.
 */
string File::Parent(string filename) {
    size_t i = filename.rfind('/');
    if (i == string::npos) return "";
    if (i == filename.size()-1)
        return Parent(filename.substr(0, filename.size()-1));
    return filename.substr(0, i+1);
}

} //NS Resources
} //NS OpenEngine
