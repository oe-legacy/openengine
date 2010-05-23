// Post process node.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/PostProcessNode.h>

#include <Resources/IShaderResource.h>
#include <Display/Viewport.h>
#include <Logging/Logger.h>
#include <Utils/Convert.h>

using namespace std;
using namespace OpenEngine::Resources;
using namespace OpenEngine::Renderers;

namespace OpenEngine {
    namespace Scene {

        PostProcessNode::PostProcessNode(){
            effect = IShaderResourcePtr();
            sceneFrameBuffer = NULL;
            dimensions = Vector<2, int>(0);
            time = 0;
            enabled = false;
            effectFrameBuffer = NULL;
            finalTexs.clear();
        }

        PostProcessNode::PostProcessNode(IShaderResourcePtr effect, 
                                         Vector<2, int> dims, 
                                         unsigned int colorBuffers,
                                         bool useDepth)
            : effect(effect), 
              dimensions(dims), 
              time(0),
              enabled(true) {
            sceneFrameBuffer = new FrameBuffer(dims, colorBuffers, useDepth);
            
            effectFrameBuffer = new FrameBuffer(dims, colorBuffers, useDepth);

            finalTexs.clear();
        }

        PostProcessNode::PostProcessNode(Resources::IShaderResourcePtr effect, 
                                         Resources::FrameBuffer* sceneFrameBuffer,
                                         Resources::FrameBuffer* effectFrameBuffer)
            : effect(effect),
              dimensions(sceneFrameBuffer->GetDimension()),
              time(0),
              enabled(true){
            this->sceneFrameBuffer = sceneFrameBuffer;

            if (effectFrameBuffer)
                this->effectFrameBuffer = effectFrameBuffer;
            else
                this->effectFrameBuffer = sceneFrameBuffer->Clone();

            finalTexs.clear();
        }


        PostProcessNode::~PostProcessNode(){
            delete sceneFrameBuffer;
            delete effectFrameBuffer;
        }

        void PostProcessNode::Handle(Renderers::RenderingEventArg arg){
            switch(arg.renderer.GetCurrentStage()){
            case Renderers::IRenderer::RENDERER_INITIALIZE:
                {
                    arg.renderer.BindFrameBuffer(effectFrameBuffer);
                    arg.renderer.BindFrameBuffer(sceneFrameBuffer);
                    
                    effect->Load();

                    // Setup shader texture uniforms
                    ITexture2DPtr depthTex = sceneFrameBuffer->GetDepthTexture();
                    if (effect->GetUniformID("depth") >= 0 && depthTex != NULL)
                        effect->SetTexture("depth", depthTex);
                    
                    for (unsigned int j = 0; j < sceneFrameBuffer->GetNumberOfAttachments(); ++j){
                        string colorid = "color" + Utils::Convert::ToString<unsigned int>(j);
                        if (effect->GetUniformID(colorid) >= 0)
                            effect->SetTexture(colorid, sceneFrameBuffer->GetTexAttachment(j));
                    }

                    // Setup final texture dependencies
                    // The final texture is undefined in the first
                    // pass, so link to original non effect texture
                    unsigned int finalColors = 0;
                    for (unsigned int j = 0; j < effectFrameBuffer->GetNumberOfAttachments(); ++j){
                        string colorid = "finalColor" + Utils::Convert::ToString<unsigned int>(j);
                        if (effect->GetUniformID(colorid) >= 0){
                            finalColors = j + 1;
                            effect->SetTexture(colorid, sceneFrameBuffer->GetTexAttachment(j));
                        }
                    }
                    //finalTexs.clear();
                    for (unsigned int i = 0; i < finalColors; ++i){
                        finalTexs.push_back(ITexture2DPtr(effectFrameBuffer->GetTexAttachment(i)->Clone()));
                    }
                
                    if (effect->GetUniformID("time") >= 0){
                        effect->SetUniform("time", (float)time);
                        arg.renderer.ProcessEvent().Attach(*this);
                    }
                    
                    // Initialize post process specific code
                    Initialize(arg);

                    break;
                }
            case Renderers::IRenderer::RENDERER_PROCESS:
                time += arg.approx / 1000.0f;
                effect->SetUniform("time", (float)time);
                break;
            default:
                ;
            }
        }

    }
}
