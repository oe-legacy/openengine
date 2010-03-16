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

        /**
         * The buffer type tells the engine the primairy purpuse of
         * this buffer.
         *
         * ARRAY means a standard data array.
         * INDEX_ARRAY means that the data blocks elements should
         * be interpreted as indices into other blocks.
         * PIXEL_PACK means that the buffer will frequently have
         * it's data updated from a texture.
         * PIXEL_UNPACK means that the buffer will often be used
         * to update a texture.
         */
        enum BufferType {ARRAY, INDEX_ARRAY, PIXEL_PACK, PIXEL_UNPACK};
        /**
         * The UpdateMode is a hint to the engine as to how often the
         * content of the datablock will be changed.
         *
         * STATIC means that the datablock will almost never be
         * updated.
         * DYNAMIC means that the datablock will often be updated.
         */
        enum UpdateMode {STATIC, DYNAMIC};
        /**
         * The unload policy specifies how the data can be unloaded.
         *
         * UNLOAD_AUTOMATIC means that the buffer will be unloaded
         * when the renderer binds it.
         * UNLOAD_EXPLICIT means that only an explicit call to
         * Unload can unload the data.
         */
        enum UnloadPolicy {UNLOAD_EXPLICIT, UNLOAD_AUTOMATIC};

        /**
         * Basic buffer object interface. The buffer object consists
         * of an array where each element is an N'th dimensional vector.
         *
         * @class IDataBlock IDataBlock.h Resources/IDataBlock.h
         */
        class IDataBlock{
        protected:
            Event<IDataBlockChangedEventArg> changedEvent;
            
            unsigned int id;
            Type type;
            void* data;
            unsigned int size, dimension;
            BufferType bufferType;
            UpdateMode updateMode;
            UnloadPolicy policy;

        public:
            IDataBlock() {
                id = size = dimension = 0;
                type = NOTYPE;
                data = NULL;
                bufferType = ARRAY;
                updateMode = STATIC;
                policy = UNLOAD_AUTOMATIC;
            }

            IDataBlock(void* d, unsigned int s, 
                       BufferType b = ARRAY, UpdateMode u = STATIC) {
                id = dimension = 0;
                size = s;
                type = NOTYPE;
                data = d;
                bufferType = b;
                updateMode = u;
                policy = UNLOAD_AUTOMATIC;
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

            /**
             * Unloads the data of the data block, but keeps the
             * properties for future reference.
             */
            virtual void Unload() = 0;

            /**
             * Sets the default unload policy.
             *
             * UNLOAD_AUTOMATIC means that the buffer will be unloaded
             * when the renderer binds it.
             * UNLOAD_EXPLICIT means that only an explicit call to
             * Unload can unload the data.
             *
             * The default is UNLOAD_AUTOMATIC.
             */
            virtual void SetUnloadPolicy(const UnloadPolicy policy) { this->policy = policy; }

            /**
             * Gets the active unload policy.
             *
             * @return UnloadPolicy The active unload policy.
             */
            inline UnloadPolicy GetUnloadPolicy() const { return policy; }

            /**
             * Gets the buffer type.
             *
             * @return BufferType The type of the buffer.
             */
            inline BufferType GetBufferType() const { return bufferType; }

            /** 
             * Gets the current update mode.
             *
             * @return UpdateMode The current update mode.
             */
            inline UpdateMode GetUpdateMode() const { return updateMode; }

            /**
             * The data blocks changed event.
             */
            virtual IEvent<IDataBlockChangedEventArg>& ChangedEvent() { return changedEvent; }

            virtual void Rebind() {
                //changedEvent.Notify(IDataBlockChangedEventArg(this->weak_this));
            }

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
