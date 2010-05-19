// Post process node.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _POST_PROCESS_NODE_H_
#define _POST_PROCESS_NODE_H_

#include <Scene/ISceneNode.h>
#include <Core/IListener.h>
#include <Renderers/IRenderer.h>
#include <Resources/Texture2D.h>
#include <Resources/FrameBuffer.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <vector>

namespace OpenEngine {
    namespace Resources {
        class IShaderResource;
        typedef boost::shared_ptr<IShaderResource> IShaderResourcePtr;
    }
    
    namespace Scene {
        
        class PostProcessNode : public Scene::ISceneNode,
                                public Core::IListener<Renderers::RenderingEventArg> {
            OE_SCENE_NODE(PostProcessNode, ISceneNode)

        protected:
            // Shader for the effect
            Resources::IShaderResourcePtr effect;

            // FBO attributes
            Vector<2, int> dimensions;
            Resources::FrameBuffer* sceneFrameBuffer;
            Resources::FrameBuffer* effectFrameBuffer;
            vector<ITexture2DPtr> finalTexs;

            unsigned int time;

        public:
            // Public variables
            bool enabled;
            bool offscreenRendering;

        public:
            PostProcessNode();
            PostProcessNode(Resources::IShaderResourcePtr effect, 
                            Math::Vector<2, int> dims, 
                            unsigned int colorBuffers = 1,
                            bool useDepth = true);
            /**
             * Post process node constructor.
             */
            PostProcessNode(Resources::IShaderResourcePtr effect, 
                            Resources::FrameBuffer* sceneFrameBuffer,
                            Resources::FrameBuffer* effectFrameBuffer = NULL);
            

            ~PostProcessNode();

            void Handle(Renderers::RenderingEventArg arg);

            /**
             * Initialize effect specific settings, such as more
             * framebuffers or other variables.
             */
            virtual void Initialize(Renderers::RenderingEventArg arg);

            /**
             * Handles any logic that needs to be done before the
             * effect, such as setting viewingvolume dependent
             * uniforms or updating time uniforms.
             */
            virtual void PreEffect(Renderers::IRenderer& renderer, Math::Matrix<4,4,float> modelview);

            /**
             * Gets the scene frame buffer, which all subnodes will be rendered to.
             */
            inline Resources::FrameBuffer* GetSceneFrameBuffer() const { return sceneFrameBuffer; }

            /**
             * Returns the effect framebuffer. This framebuffer
             * contains the textures after the effect has been
             * applied.
             */
            inline Resources::FrameBuffer* GetEffectFrameBuffer() const { return effectFrameBuffer; }

            /**
             * Returns the width and height of the images produced by
             * the post process node.
             *
             * @return A vector containing [width, height].
             */
            inline Math::Vector<2, int> GetDimension() const { return dimensions; }

            /**
             * Returns the shader that creates teh effect
             *
             * @return The shader holding the effect.
             */
            inline Resources::IShaderResourcePtr GetEffect() { return effect; }

            /**
             * Returns a list of textures containing the last scene
             * rendered with the postprocess effect.
             */
            inline vector<ITexture2DPtr> GetFinalTexs() const { return finalTexs; }
        };

    }

}

#endif
