// Data Block interface.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/IDataBlock.h>
#include <Resources/DataBlock.h>

namespace OpenEngine {
    namespace Resources {

        IDataBlockPtr IDataBlock::Clone() {

            switch(this->type){
            case Types::UBYTE:
                switch(this->size){
                case 1: 
                    return IDataBlockPtr(new DataBlock<1, unsigned char>(this));
                case 2: 
                    return IDataBlockPtr(new DataBlock<2, unsigned char>(this));
                case 3: 
                    return IDataBlockPtr(new DataBlock<3, unsigned char>(this));
                case 4: 
                    return IDataBlockPtr(new DataBlock<4, unsigned char>(this));
                }
            case Types::SBYTE:
                switch(this->size){
                case 1: 
                    return IDataBlockPtr(new DataBlock<1, char>(this));
                case 2: 
                    return IDataBlockPtr(new DataBlock<2, char>(this));
                case 3: 
                    return IDataBlockPtr(new DataBlock<3, char>(this));
                case 4: 
                    return IDataBlockPtr(new DataBlock<4, char>(this));
                }
            case Types::UINT:
                switch(this->size){
                case 1: 
                    return IDataBlockPtr(new DataBlock<1, unsigned int>(this));
                case 2: 
                    return IDataBlockPtr(new DataBlock<2, unsigned int>(this));
                case 3: 
                    return IDataBlockPtr(new DataBlock<3, unsigned int>(this));
                case 4: 
                    return IDataBlockPtr(new DataBlock<4, unsigned int>(this));
                }
            case Types::INT:
                switch(this->size){
                case 1: 
                    return IDataBlockPtr(new DataBlock<1, int>(this));
                case 2: 
                    return IDataBlockPtr(new DataBlock<2, int>(this));
                case 3: 
                    return IDataBlockPtr(new DataBlock<3, int>(this));
                case 4: 
                    return IDataBlockPtr(new DataBlock<4, int>(this));
                }
            case Types::FLOAT:
                switch(this->size){
                case 1: 
                    return IDataBlockPtr(new DataBlock<1, float>(this));
                case 2: 
                    return IDataBlockPtr(new DataBlock<2, float>(this));
                case 3: 
                    return IDataBlockPtr(new DataBlock<3, float>(this));
                case 4: 
                    return IDataBlockPtr(new DataBlock<4, float>(this));
                }
            default:
                //throw Exception("Type " + Types::ToString(this->type) + " not supported by clone.");
                throw Exception("Unknown type not supported by clone.");
            }
        }

    }
}
