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

        /**
         * A scene node that handles post processing effects on the
         * image.
         *
         * The node will handle most of the setup as long as a few
         * naming conventions are respected.
         *
         * The uniform sampler2DShadow depth contains the depth
         * texture for the subscene.
         *
         * The uniform sampler2D imageN contains the N'th texture
         * rendered to in the subscene.
         *
         * The uniform sampler2D finalImage0 contains the N'th image
         * from the previous application of the post process node with
         * the effect applied. Since this is undefined for the first
         * pass, it will contain the same as imageN.
         *
         * The uniform float time contains the time since the renderer
         * was created in miliseconds, if the node is attached to a ProcessEventArg.
         */        
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

            bool enabled;

        public:
            // Public variables
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

            virtual void Handle(Renderers::RenderingEventArg arg);

            /**
             * Initialize effect specific settings, such as more
             * framebuffers or other variables.
             */
            virtual void Initialize(Renderers::RenderingEventArg arg) {}

            /**
             * Handles any logic that needs to be done before the
             * effect, such as setting viewingvolume dependent
             * uniforms or updating time uniforms.
             */
            virtual void PreEffect(Renderers::RenderingEventArg* arg, Math::Matrix<4,4,float>* modelview) {}

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
             * Returns the shader that creates the effect
             *
             * @return The shader holding the effect.
             */
            inline Resources::IShaderResourcePtr GetEffect() { return effect; }

            /**
             * Returns a list of textures containing the last scene
             * rendered with the postprocess effect.
             */
            inline vector<ITexture2DPtr> GetFinalTexs() const { return finalTexs; }

            void SetEnabled(bool e) { enabled = e; }

            bool GetEnabled() { return enabled; }
        };

    }

}

#endif
