// Shader loader.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SHADER_LOADER_H_
#define _SHADER_LOADER_H_

#include <Scene/ISceneNodeVisitor.h>
#include <Renderers/OpenGL/TextureLoader.h>

namespace OpenEngine {
namespace Renderers {
namespace OpenGL {

using OpenEngine::Scene::GeometryNode;
using OpenEngine::Scene::ISceneNodeVisitor;

/**
 * OpenGL specific shader loader.
 *
 * @class ShaderLoader ShaderLoader.h Renderers/OpenGL/ShaderLoader.h
 */
class ShaderLoader : public ISceneNodeVisitor {
private:
    TextureLoader* textureLoader;
public:
    ShaderLoader();
    ~ShaderLoader();

    void VisitGeometryNode(GeometryNode* node);
};

} // NS OpenGL
} // NS Renderers
} // NS OpenEngine

#endif
