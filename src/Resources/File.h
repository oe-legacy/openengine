// File handling utility class.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * Static utility class for handling files.
 *
 * @class File File.h Resources/File.h
 */
class File {
public:
    static ifstream* Open(string filename, ios_base::openmode mode = ios_base::in);
    static int GetSize(string filename);
    static string Extension(string filename);
    static string Parent(string filename);

    /**
     *  Reads a file from the supplied filename and returns the files data in a
     *  array. Returns pointer to data array if successful, and throw an exception
     * if an error occurred.
     */
    template<class T> static T* ReadShader(string filename) {
        // @todo: move this function from header to cpp
        string fullfilenamewithpath = filename;
        int size = File::GetSize(fullfilenamewithpath);
        
        // Allocate memory to hold the source of our shaders.
        T* shader = (T*)malloc(size);

        ifstream* file = File::Open(fullfilenamewithpath);
        file->read((char*)shader,size-1);
        // @todo check for error and throw exception if there is one
        shader[size-1] = '\0';
        file->close();
        delete file;
        return shader;
    }
};

} //NS Resources
} //NS OpenEngine

#endif
