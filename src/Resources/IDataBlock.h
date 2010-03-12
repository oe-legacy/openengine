// Data Block interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_DATA_BLOCK_H_
#define _I_DATA_BLOCK_H_

#include <Resources/Types/ResourceTypes.h>
#include <Resources/IResource.h>
#include <list>

using std::list;

using namespace OpenEngine::Resources::Types;

namespace OpenEngine {
    namespace Resources {

        class IDataBlockChangedEventArg;

        enum AccessType {READ, WRITE, COPY};
        enum BufferType {ARRAY, INDEX_ARRAY, PIXEL_PACK, PIXEL_UNPACK};
        enum UpdateMode {STATIC, DYNAMIC};

        /**
         * Basic buffer object interface. The buffer object consists
         * of an array where each element is an N'th dimensional vector.
         *
         * @class IDataBlock IDataBlock.h Resources/IDataBlock.h
         */
        class IDataBlock : public IResource<IDataBlockChangedEventArg>{
        protected:
            unsigned int id;
            Type type;
            void* data;
            unsigned int size, dimension;
            AccessType access;
            BufferType bufferType;
            UpdateMode updateMode;

            inline void SetAccessType(BufferType type){
                switch(type){
                case PIXEL_PACK:
                    access = COPY;
                    return;
                default:
                    access = WRITE;
                    return;
                }
            }

        public:
            IDataBlock() {
                id = size = dimension = 0;
                type = NOTYPE;
                data = NULL;
                access = WRITE;
                bufferType = ARRAY;
                updateMode = STATIC;
            }

            /**
             * Get buffer object id.
             *
             * @return Buffer Object id.
             */
            inline unsigned int GetID() const { return id; }
            
            /**
             * Set buffer object id.
             *
             * @param id Buffer object id.
             */
            virtual void SetID(int id) { this->id = id; }

            /**
             * Get pointer to loaded buffer object.
             *
             * @return Char pointer to loaded data.
             */
            inline void* GetVoidDataPtr() const { return data; }

            /**
             * Get the type of the buffer object.
             *
             * @return Type the type of the buffer object.
             */
            inline Type GetType() const { return type; }

            /**
             * Set the type of the buffer object.
             */
            virtual void SetType(Type t) { type = t; }

            /**
             * Get the number of elements in the buffer object.
             */
            inline unsigned int GetSize() const { return size; }

            /**
             * Get the elements number of dimensions.
             */
            inline unsigned int GetDimension() const { return dimension; }

            inline AccessType GetAccessType() const { return access; }

            inline BufferType GetBufferType() const { return bufferType; }

            virtual void SetBufferType(BufferType type) {
                bufferType = type;
                SetAccessType(type);
            }

            inline UpdateMode GetUpdateMode() const { return updateMode; }

            virtual void SetUpdateMode(UpdateMode mode) { updateMode = mode; }
            
        };
        
        /**
         * Buffer Object interface smart pointer.
         */
        typedef boost::shared_ptr<IDataBlock> IDataBlockPtr;
        typedef list<IDataBlockPtr > IDataBlockList;

        /**
         * IDataBlockChangedEventArg
         */
        class IDataBlockChangedEventArg {
            IDataBlockPtr resource;
            unsigned int start, end;
            IDataBlockChangedEventArg(IDataBlockPtr r) 
                : resource(r) {
                start = 0;
                end = r->GetSize();
            }
            IDataBlockChangedEventArg(IDataBlockPtr r, unsigned int s, unsigned int e)
                : resource(r), start(s), end(e) {}
        };
    }
}

#endif
