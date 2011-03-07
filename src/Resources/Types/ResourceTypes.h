// Meta header for OpenEngine.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OPENENGINE_RESOURCE_FORMATS_H_
#define _OPENENGINE_RESOURCE_FORMATS_H_

#include <typeinfo>
#include <string>

namespace OpenEngine {
    namespace Resources {
        namespace Types {

            /**
             * Type enumeration.
             */
            enum Type {NOTYPE = 0x0000,
                       UBYTE  = 0x1401, // GL_UNSIGNED_BYTE
                       SBYTE  = 0x1400, // GL_BYTE
                       USHORT = 0x1403, // GL_UNSIGNED_SHORT
                       SHORT  = 0x1402, // GL_SHORT
                       UINT   = 0x1405, // GL_UNSIGNED_INT
                       INT    = 0x1404, // GL_INT
                       FLOAT  = 0x1406, // GL_FLOAT
                       DOUBLE = 0x140A}; // GL_DOUBLE
            
            /**
             * Yields an OpenEngine Type based on the template
             * parameter.
             */
            template <class T> Type GetResourceType(){
                if (typeid(T) == typeid(unsigned char))
                    return UBYTE;
                else if (typeid(T) == typeid(char))
                    return SBYTE;
                else if (typeid(T) == typeid(unsigned short))
                    return USHORT;
                else if (typeid(T) == typeid(short))
                    return SHORT;
                else if (typeid(T) == typeid(unsigned int))
                    return UINT;
                else if (typeid(T) == typeid(int))
                    return INT;
                else if (typeid(T) == typeid(float))
                    return FLOAT;
                else if (typeid(T) == typeid(double))
                    return DOUBLE;
                else 
                    return NOTYPE;
            }

            /*
            std::string ToString(Type t) {
                switch(t){
                case NOTYPE:
                    return "notype";
                case UBYTE:
                    return "unsigned byte";
                case SBYTE:
                    return "byte";
                case UINT:
                    return "unsigned integer";
                case INT:
                    return "integer";
                case FLOAT:
                    return "float";
                default:
                    return "unknown type";
                }
            }
            */
        }
    }
}
        
#endif
