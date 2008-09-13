#include <Core/IListener.h>
#include <Core/QueuedEvent.h>
#include <Renderers/IRenderer.h>
#include <Resources/ITextureResource.h>

using namespace OpenEngine::Core;
using namespace OpenEngine::Renderers;
using namespace OpenEngine::Resources;

#ifndef _TEXTURE_RELOADER_
#define _TEXTURE_RELOADER_

class TextureReloader : public IListener<RenderingEventArg>
, public IListener<TextureChangedEventArg> {
 private:
    QueuedEvent<TextureChangedEventArg> queue;
    IRenderer* renderer;

 public:
    TextureReloader() : renderer(NULL) {
        queue.Attach(*this);
    }

    // should be run on render preprocess
    void Handle(RenderingEventArg arg) {
        renderer = &arg.renderer;
        queue.Release(); // this->Handle
        renderer = NULL;
    }

    // rebind all textures in gl
    void Handle(TextureChangedEventArg arg) {
        renderer->RebindTexture(arg.resource);
    }

    // observe a texture for incomming events and queue them
    void ListenOn(IEvent<TextureChangedEventArg>& event) {
        event.Attach(queue);
    }

    QueuedEvent<TextureChangedEventArg>& Queue() {
        return queue;
    }
};

#endif // _TEXTURE_RELOADER_
