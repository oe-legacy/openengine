// Event profiling utility.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_EVENT_PROFILER_H_
#define _OE_EVENT_PROFILER_H_

#include <Core/IEvent.h>
#include <Core/IListener.h>
#include <Utils/Timer.h>

#include <string>
#include <list>

namespace OpenEngine {
namespace Utils {

class EventProfiler {
private:

    class Intercepter {
    public:
        Timer timer; 
        std::string name;
        unsigned int count;
        unsigned int time;
        Intercepter(std::string name) : name(name), count(0), time(0) {}
    };
    
    template <class E> class SpecIntercepter
        : public Intercepter, public Core::IListener<E> {
    public:
        Core::IListener<E>& peer;
        SpecIntercepter(std::string name, Core::IListener<E>& peer)
            : Intercepter(name), peer(peer) {}
        virtual void Handle(E arg) {
            count++;
            timer.Start();
            peer.Handle(arg);
            timer.Stop();
        }
    };

    std::list<Intercepter*> is;
    Timer timer;

public:
    EventProfiler();
    void DumpInfo();

    /**
     * Profile an event.
     * This call will register an interceptor 
     */
    template <class E>
    void Profile(std::string s, Core::IEvent<E>& e, Core::IListener<E>& l) {
        SpecIntercepter<E>* i = new SpecIntercepter<E>(s, l);
        e.Detach(l);
        e.Attach(*i);
        is.push_back(i);
    }
};

} // NS Utils
} // NS OpenEngine

#endif // _OE_EVENT_PROFILER_H_
