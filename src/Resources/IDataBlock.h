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
         * The block type tells the engine the primairy purpuse of
         * this data block.
         *
         * ARRAY means a standard data array.
         * INDEX_ARRAY means that the data blocks elements should
         * be interpreted as indices into other blocks.
         * PIXEL_PACK means that the data block will frequently have
         * it's data updated from a texture.
         * PIXEL_UNPACK means that the data block will often be used
         * to update a texture.
         */
        enum BlockType {ARRAY        = 0x8892,
                        INDEX_ARRAY  = 0x8893, 
                        PIXEL_PACK   = 0x88EB, 
                        PIXEL_UNPACK = 0x88EC};
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
         * UNLOAD_AUTOMATIC means that the data block will be unloaded
         * when the renderer binds it.
         * UNLOAD_EXPLICIT means that only an explicit call to
         * Unload can unload the data.
         */
        enum UnloadPolicy {UNLOAD_EXPLICIT, UNLOAD_AUTOMATIC};

        /**
         * Basic data block interface. The data block consists of an
         * array where each element is an N'th dimensional vector.
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
            BlockType blockType;
            UpdateMode updateMode;
            UnloadPolicy policy;

        public:
            /**
             * IDataBlock constructor.
             *
             * @param s is the number of elements in the data block.
             * @param d is an array containing the elements data.
             * @param b is the type of the data block.
             * @param u is the blocks update mode.
             */
            IDataBlock(unsigned int s = 0, void* d = NULL, 
                       BlockType b = ARRAY, UpdateMode u = STATIC) {
                id = dimension = 0;
                size = s;
                type = NOTYPE;
                data = d;
                blockType = b;
                updateMode = u;
                policy = UNLOAD_AUTOMATIC;
            }

            /**
             * Get data block id.
             *
             * @return data block id.
             */
            inline unsigned int GetID() const { return id; }
            
            /**
             * Set data block id.
             *
             * @param data block id.
             */
            virtual void SetID(int id) { this->id = id; }

            /**
             * Get a pointer to the data blocks raw data.
             *
             * @return pointer to loaded data.
             */
            inline void* GetVoidDataPtr() const { return data; }

            /**
             * Get a pointer to the i'th elements data.
             *
             * @param i The i'th element.
             */
            virtual void* GetVoidElement(unsigned int i) = 0;

            /**
             * Get the type of the data block.
             *
             * @return the type of the data block.
             */
            inline Type GetType() const { return type; }

            /**
             * Set the type of the data block.
             *
             * @param t The type.
             */
            virtual void SetType(Type t) { type = t; }

            /**
             * Get the number of elements in the data block.
             * 
             * @return the number of elements.
             */
            inline unsigned int GetSize() const { return size; }

            /**
             * Get the elements number of dimensions.
             *
             * @return the dimensionality of the elements.
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
             * UNLOAD_AUTOMATIC means that the dat block will be
             * unloaded when the renderer binds it.
             * UNLOAD_EXPLICIT means that only an explicit call to
             * Unload can unload the data.
             *
             * The default is UNLOAD_AUTOMATIC.
             *
             * @param policy The new unload policy.
             */
            virtual void SetUnloadPolicy(const UnloadPolicy policy) { this->policy = policy; }

            /**
             * Gets the active unload policy.
             *
             * @return the active unload policy.
             */
            inline UnloadPolicy GetUnloadPolicy() const { return policy; }

            /**
             * Gets the block type.
             *
             * @return the type of the data block.
             */
            inline BlockType GetBlockType() const { return blockType; }

            /** 
             * Gets the current update mode.
             *
             * @return the current update mode.
             */
            inline UpdateMode GetUpdateMode() const { return updateMode; }

            /**
             * The data blocks changed event.
             *
             * @return the IEvent
             */
            virtual IEvent<IDataBlockChangedEventArg>& ChangedEvent() { return changedEvent; }

        };
        
        /**
         * Data Block interface smart pointer.
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
