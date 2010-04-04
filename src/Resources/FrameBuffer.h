// Frame Buffer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_FRAME_BUFFER_H_
#define _OE_FRAME_BUFFER_H_

#include <Math/Vector.h>
#include <Resources/Texture2D.h>
#include <Display/Viewport.h>
#include <Utils/Convert.h>
#include <vector>

using OpenEngine::Display::Viewport;
using OpenEngine::Math::Vector;
using OpenEngine::Resources::Texture2D;
using OpenEngine::Resources::ITexture2DPtr;
using std::vector;

namespace OpenEngine {
    namespace Resources {
        
        /**
         * 
         */
        class FrameBuffer {
        protected:
            unsigned int id;
            ITexture2DPtr depth;
            vector<ITexture2DPtr> texs;
            Vector<4, int> dimension;
            
        public:
            FrameBuffer(Viewport& view, unsigned int colorBuffers = 1, bool useDepth = false)
                : id(0) {
                dimension = view.GetDimension();
                unsigned int width = dimension[2];
                unsigned int height = dimension[3];
                if (useDepth){
                    depth = ITexture2DPtr(new Texture2D<unsigned char>(width, height, 1));
                    depth->SetColorFormat(DEPTH);
                    depth->SetMipmapping(false);
                    depth->SetCompression(false);
                    depth->SetWrapping(CLAMP_TO_EDGE);
                }else
                    depth = ITexture2DPtr();

                texs = vector<ITexture2DPtr>(colorBuffers);
                for (unsigned int i = 0; i < texs.size(); ++i){
                    texs[i] = ITexture2DPtr(new Texture2D<unsigned char>(width, height, 4));
                    texs[i]->SetColorFormat(RGBA);
                    texs[i]->SetMipmapping(false);
                    texs[i]->SetCompression(false);
                    texs[i]->SetWrapping(CLAMP_TO_EDGE);
                }
            }
            
            /**
             * Get framebuffer id.
             *
             * @return Framebuffer id.
             */
            inline unsigned int GetID() const { return id; }

            /**
             * Set framebuffer id.
             *
             * @param Framebufer id.
             */
            inline void SetID(const unsigned int id) { this->id = id; }

            /**
             * Get framebuffer dimension. The values represent
             * [xoffset, yoffset, width, height].
             *
             * @return The vector containing the dimensions of the
             * framebuffer. 
             */
            inline Vector<4, int> GetDimension() const { return dimension; }

            /**
             * Set the dimension of the framebuffer.
             *
             * @param dim A vector containing the dimension.
             */
            inline void SetDimension(Vector<4, int> dim) { dimension = dim; }

            /**
             * Get the texture containing the depth buffer. Returns a
             * null smart pointer if depth buffering isn't enabled.
             *
             * @return The depth buffer.
             */
            inline ITexture2DPtr GetDepthTexture() const { return depth; }

            /**
             * 
             */
            inline unsigned int GetNumberOfAttachments() const { return texs.size(); }

            /**
             * Get the i'th texture attachment.
             */
            inline ITexture2DPtr GetTexAttachement(unsigned int i) const { 
#ifdef OE_SAFE
                if (texs.size() <= i)
                    throw Exception("No attachment at index " + Utils::Convert::ToString<unsigned int>(i));
#endif
                return texs[i]; 
            }

            /**
             * 
             */
            inline void SetColorAttachement(ITexture2DPtr tex, unsigned int i) {
                
            }

        };

    }
}

#endif
