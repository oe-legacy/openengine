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

namespace OpenEngine {
    namespace Resources {
        namespace Types {

            /**
             * Type enumeration.
             */
            enum Type {NOTYPE = 0x0000,
                       UBYTE  = 0x1401, 
                       BYTE   = 0x1400,
                       UINT   = 0x1405, 
                       INT    = 0x1404,
                       FLOAT  = 0x1406};
            
            /**
             * Yields an OpenEngine Type based on the template
             * parameter.
             */
            template <class T> Type GetResourceType(){
                if (typeid(T) == typeid(unsigned char))
                    return UBYTE;
                else if (typeid(T) == typeid(char))
                    return BYTE;
                else if (typeid(T) == typeid(unsigned int))
                    return UINT;
                else if (typeid(T) == typeid(int))
                    return INT;
                else if (typeid(T) == typeid(float))
                    return FLOAT;
                else 
                    return NOTYPE;
            }


        }
    }
}
        
#endif
