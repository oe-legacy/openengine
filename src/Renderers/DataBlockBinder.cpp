// Data Blockbinder
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/DataBlockBinder.h>

#include <Core/QueuedEvent.h>
#include <Scene/MeshNode.h>
#include <Geometry/Mesh.h>
#include <Geometry/GeometrySet.h>
#include <Resources/DataBlock.h>
#include <Renderers/IRenderer.h>
#include <Core/IListener.h>
#include <Logging/Logger.h>

namespace OpenEngine {
    using Core::QueuedEvent;
    using Geometry::MeshPtr;
    using Geometry::GeometrySetPtr;
    using Resources::IDataBlockPtr;
    using Resources::IDataBlockChangedEventArg;
    using Resources::IDataBlockList;
    using Scene::MeshNode;
    using Core::IListener;

namespace Renderers {

    /**
     * Utility class that listens for data block change events and
     * rebinds them in the renderer.
     */
    class DataBlockBinder::Reloader : public IListener<IDataBlockChangedEventArg> {
        IRenderer& renderer;
        QueuedEvent<IDataBlockChangedEventArg> queue;
    public:
        Reloader(IRenderer& renderer)
            : renderer(renderer) {
            queue.Attach(*this);
        }
        /**
         * Dispatch the changed events in the queue.
         */
        void ReloadQueue() {
            queue.Release();
        }
        /**
         * Update the data block that was changed.
         */
        void Handle(IDataBlockChangedEventArg arg) {
            /*
            renderer.RebindDataBlock(arg.resource,
                                     arg.start,
                                     arg.end);
            */
        }
        /**
         * Adds a data block to the reloader.
         */
        void Add(IDataBlockPtr block, ReloadPolicy policy) {
            // Remember to detach the listener first to make sure we
            // don't listen twice.
            if (policy == RELOAD_IMMEDIATE) {
                block->ChangedEvent().Detach(*this);
                block->ChangedEvent().Attach(*this);
            } else if (policy == RELOAD_QUEUED) {
                block->ChangedEvent().Detach(queue);
                block->ChangedEvent().Attach(queue);
            }
        }
    };

    
    class DataBlockBinder::InitBinder : public IListener<RenderingEventArg> {
    private:
        struct pair {
            IDataBlockPtr b;
            ReloadPolicy p;
            pair(IDataBlockPtr b, ReloadPolicy p) : b(b), p(p) {}
        };
        list<pair> queue;
        Reloader& reloader;
    public:
        InitBinder(Reloader& reloader) : reloader(reloader) {}

        void Add(IDataBlockPtr b, ReloadPolicy p){
            queue.push_back(pair(b,p));
        }

        void Handle(RenderingEventArg arg) {
            list<pair>::iterator itr;
            for (itr = queue.begin(); itr != queue.end(); ++itr){
                if (itr->b->GetID() == 0)
                    arg.renderer.BindDataBlock(itr->b.get());
                reloader.Add(itr->b, itr->p);
            }
            queue.clear();
        }
    };


    DataBlockBinder::DataBlockBinder(IRenderer& r,
                                     ReloadPolicy d)
        :r(r), reloader(new Reloader(r)), initbinder(new InitBinder(*reloader)), defaultpolicy(d) {
        r.InitializeEvent().Attach(*initbinder);
    }
    
    DataBlockBinder::~DataBlockBinder() {
        delete reloader;
        delete initbinder;
    }

    void DataBlockBinder::Bind(ISceneNode& node, ReloadPolicy policy){
        node.Accept(*this);
    }

    void DataBlockBinder::Bind(IDataBlockPtr block, ReloadPolicy policy){
        policy = (policy == RELOAD_DEFAULT) ? defaultpolicy : policy;
        if (IRenderer::RENDERER_UNINITIALIZE == r.GetCurrentStage()){
            initbinder->Add(block, policy);
        }else{
            // If the texture has not already been loaded
            if (block->GetID() == 0)
                r.BindDataBlock(block.get());
            // Listen for reload events (based on policy)
            reloader->Add(block, policy);
        }
    }
        
    void DataBlockBinder::SetDefaultPolicy(ReloadPolicy p){
        // The default policy must never be RELOAD_DEFAULT
        if (p == RELOAD_DEFAULT)
            throw Math::Exception("Invalid default reload policy.");
        defaultpolicy = p;
    }

    void DataBlockBinder::VisitMeshNode(MeshNode* node) {
        if (node->GetMesh()->GetIndices() && node->GetMesh()->GetIndices()->GetID() == 0)
            Bind(node->GetMesh()->GetIndices(), defaultpolicy);
        
        GeometrySetPtr geom = node->GetMesh()->GetGeometrySet();
        LoadGeometrySet(geom);
        
        node->VisitSubNodes(*this);
    }
    
    void DataBlockBinder::LoadGeometrySet(GeometrySetPtr geom){
        map<string, IDataBlockPtr> attrs = geom->GetAttributeLists();
        map<string, IDataBlockPtr>::iterator itr = attrs.begin();
        while (itr != attrs.end()){

            Bind(itr->second, defaultpolicy);
            
            ++itr;
        }
    }
    
    
} // NS OpenEngine
} // NS Renderers
