// Data Block binder
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_DATA_BLOCK_BINDER_H_
#define _OE_DATA_BLOCK_BINDER_H_

#include <Scene/ISceneNodeVisitor.h>
#include <boost/shared_ptr.hpp>

namespace OpenEngine {
    //forward declarations
    namespace Geometry {
        class GeometrySet;
        typedef boost::shared_ptr<GeometrySet> GeometrySetPtr;
    }
    namespace Renderers {
        class IRenderer;
        class RenderingEventArg;
    }
    namespace Resources {
        class IDataBlock;
        typedef boost::shared_ptr<IDataBlock> IDataBlockPtr;
    }
    namespace Scene {
        class MeshNode;
        class ISceneNode;
    }

namespace Renderers {

using Geometry::GeometrySetPtr;
using Renderers::IRenderer;
using Resources::IDataBlockPtr;
using Scene::MeshNode;
using Scene::ISceneNode;
using Scene::ISceneNodeVisitor;

/**
 * Bind Data blocks
 *
 * @class BufferObjectBinder BufferObjectBinder.h Renderers/OpenGL/BufferObjectBinder.h
 */
class DataBlockBinder: public ISceneNodeVisitor {
 public:

    /**
     * Reload policies.
     *
     * RELOAD_NEVER means that data blocks will only be loaded if they
     * have not already been (their id is zero) and all future change
     * events will be ignored.
     * RELOAD_IMMEDIATE means that the data block will be reloaded as
     * soon as a changed event occurs.
     * RELOAD_QUEUED means that the data block will be reloaded on the
     * next Preprocess event.
     * RELOAD_DEFAULT is not a policy, but can be used to flag that
     * the loader should use whatever the default policy is.
     */
    enum ReloadPolicy {
        RELOAD_NEVER,
        RELOAD_QUEUED,
        RELOAD_IMMEDIATE,
        RELOAD_DEFAULT
    };

    DataBlockBinder(IRenderer& r, ReloadPolicy d = RELOAD_NEVER);
    virtual ~DataBlockBinder();

    /**
     * Load all data block resources from MeshNodes found in a scene.
     * If no reload policy flag is supplied the default policy will be
     * used.
     */        
    void Bind(Scene::ISceneNode& node, ReloadPolicy policy = RELOAD_DEFAULT);

    /**
     * Load a data block.
     * If no reload policy flag is supplied the default policy will be
     * used.
     */
    void Bind(IDataBlockPtr block, ReloadPolicy policy = RELOAD_DEFAULT);

    void SetDefaultPolicy(ReloadPolicy p);

    void VisitMeshNode(MeshNode* node);

 private:
    class Reloader;
    class InitBinder;
    IRenderer& r;
    Reloader* reloader;
    InitBinder* initbinder;
    ReloadPolicy defaultpolicy;

    void LoadGeometrySet(GeometrySetPtr geom);
};

} // NS OpenEngine
} // NS Renderers

#endif
