// Data Block interface.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _I_DATA_BLOCK_H_
#define _I_DATA_BLOCK_H_

#include <Core/Exceptions.h>
#include <Math/Vector.h>
#include <Resources/Types/ResourceTypes.h>
#include <Resources/IResource.h>

#include <list>
#include <string>

namespace OpenEngine {
    namespace Resources {
        /**
         * Forward declerations.
         */
        class IDataBlockChangedEventArg;
        class IDataBlock;
        /**
         * Data Block interface smart pointer.
         */
        typedef boost::shared_ptr<IDataBlock> IDataBlockPtr;
        typedef std::list<IDataBlockPtr > IDataBlockList;

        /**
         * The block type tells the engine the primary purpose of
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
         * array where each element is a N'th dimensional vector.
         *
         * @class IDataBlock IDataBlock.h Resources/IDataBlock.h
         */
        class IDataBlock{
        protected:
            Event<IDataBlockChangedEventArg> changedEvent;
            
            unsigned int id;
            Types::Type type;
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
                type = Types::NOTYPE;
                data = d;
                blockType = b;
                updateMode = u;
                //policy = UNLOAD_AUTOMATIC;
                policy = UNLOAD_EXPLICIT;
            }

	    virtual ~IDataBlock() {}

            /**
             * Clones the IDataBlock properties and it's data, except
             * for the id, which is set to 0.
             *
             * @return A new IDataBlock with with the same properties and copied data.
             */
            virtual IDataBlockPtr Clone() = 0;

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
            virtual void* GetVoidData() { return data; }
            /*DEPRECATED*/virtual void* GetVoidDataPtr() { return data; }

            /**
             * Copies the i'th element of the datablock into the
             * supplied vector.
             *
             * @param i The index into the block.
             * @param element The vector to place the data in.
             */
            virtual void GetElement(unsigned int i, Math::Vector<4, unsigned char> &element) { throw Core::NotImplemented(); }
            virtual void GetElement(unsigned int i, Math::Vector<2, float> &element) { throw Core::NotImplemented(); }
            virtual void GetElement(unsigned int i, Math::Vector<3, float> &element) { throw Core::NotImplemented(); }
            virtual void GetElement(unsigned int i, Math::Vector<4, float> &element) { throw Core::NotImplemented(); }
            virtual void GetElement(unsigned int i, Math::Vector<2, double> &element) { throw Core::NotImplemented(); }
            virtual void GetElement(unsigned int i, Math::Vector<3, double> &element) { throw Core::NotImplemented(); }
            virtual void GetElement(unsigned int i, Math::Vector<4, double> &element) { throw Core::NotImplemented(); }

            /**
             * Sets the i'th element in the data block to the vector.
             *
             * @param i The index into the block.
             * @param value The value to be set to.
             */
            virtual void SetElement(unsigned int i, const Math::Vector<4, unsigned char> value)  { throw Core::NotImplemented(); }
            virtual void SetElement(unsigned int i, const Math::Vector<2, float> value)  { throw Core::NotImplemented(); }
            virtual void SetElement(unsigned int i, const Math::Vector<3, float> value)  { throw Core::NotImplemented(); }
            virtual void SetElement(unsigned int i, const Math::Vector<4, float> value)  { throw Core::NotImplemented(); }
            virtual void SetElement(unsigned int i, const Math::Vector<2, double> value)  { throw Core::NotImplemented(); }
            virtual void SetElement(unsigned int i, const Math::Vector<3, double> value)  { throw Core::NotImplemented(); }
            virtual void SetElement(unsigned int i, const Math::Vector<4, double> value)  { throw Core::NotImplemented(); }

            /**
             * Get the type of the data block.
             *
             * @return the type of the data block.
             */
            inline Types::Type GetType() const { return type; }

            /**
             * Set the type of the data block.
             *
             * @param t The type.
             */
            virtual void SetType(Types::Type t) { type = t; }

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

            /**
             * String representation.
             *
             * @return IDataBlock as a string.
             */
            virtual std::string ToString() = 0;

            // *** Math ***

            /**
             * Destructive vector addition on all elements in the
             * datablock.
             */
            virtual void operator+=(const Math::Vector<4, unsigned char> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<1, unsigned int> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<2, float> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<3, float> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<4, float> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<2, double> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<3, double> value)  { throw Core::NotImplemented(); }
            virtual void operator+=(const Math::Vector<4, double> value)  { throw Core::NotImplemented(); }
            /**
             * Nondestructive vector addition on all elements in the
             * datablock.
             */
            virtual IDataBlockPtr operator+(const Math::Vector<4, unsigned char> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<1, unsigned int> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<2, float> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<3, float> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<4, float> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<2, double> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<3, double> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator+(const Math::Vector<4, double> value)  { throw Core::NotImplemented(); }

            /**
             * Destructive vector subtraction on all elements in the
             * datablock.
             */
            virtual void operator-=(const Math::Vector<4, unsigned char> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<1, unsigned int> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<2, float> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<3, float> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<4, float> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<2, double> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<3, double> value)  { throw Core::NotImplemented(); }
            virtual void operator-=(const Math::Vector<4, double> value)  { throw Core::NotImplemented(); }
            /**
             * Nondestructive vector subtraction on all elements in the
             * datablock.
             */
            virtual IDataBlockPtr operator-(const Math::Vector<4, unsigned char> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<1, unsigned int> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<2, float> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<3, float> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<4, float> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<2, double> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<3, double> value)  { throw Core::NotImplemented(); }
            virtual IDataBlockPtr operator-(const Math::Vector<4, double> value)  { throw Core::NotImplemented(); }

            /**
             * Destructive scalar multiplication on all elements in
             * the datablock.
             */
            virtual void operator*=(const float s)  { throw Core::NotImplemented(); }
            /**
             * Nondestructive scalar multiplication on all elements in
             * the datablock.
             */
            virtual IDataBlockPtr operator*(const float s)  { throw Core::NotImplemented(); }
            
            /**
             * Destructive scalar division on all elements in the
             * datablock.
             */
            virtual void operator/=(const float s)  { throw Core::NotImplemented(); }
            /**
             * Nondestructive scalar division on all elements in the
             * datablock.
             */
            virtual IDataBlockPtr operator/(const float s)  { throw Core::NotImplemented(); }

            /**
             * Destructively normalize all elements of the datablock.
             */
            virtual void Normalize()  { throw Core::NotImplemented(); }

        };
        
        /**
         * IDataBlockChangedEventArg
         */
        class IDataBlockChangedEventArg {
        public:
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
