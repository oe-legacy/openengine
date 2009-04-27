// Selection List.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SELECTION_LIST_H_
#define _OE_SELECTION_LIST_H_

#include <Core/IEvent.h>
#include <Core/Event.h>
#include <set>

namespace OpenEngine {
namespace Utils {

using Core::IEvent;
using Core::Event;
using std::set;


/**
 * Maintain a selection of objects. Fire events when selection is
 * updated.
 *
 * @class SelectionList SelectionList.h Utils/SelectionList.h
 */
template <class T> class SelectionList {
public:
    class ChangedEventArg {
    public:
        set<T*> selection;
    };
private:
    set<T*> selection;
    Event<ChangedEventArg> changed;
    inline void FireChangedEvent() {
        ChangedEventArg arg;
        arg.selection = selection;
        changed.Notify(arg);        
    }

public:
    IEvent<ChangedEventArg>& ChangedEvent() {
        return changed;
    }

    void Select(T* obj) {
        if (selection.insert(obj).second)
            FireChangedEvent();
    }

    void Select (set<T*> objs) {
        selection.insert(objs.begin(), objs.end());
        FireChangedEvent();
    }

    void DeSelect(T* obj) {
        if (selection.erase(obj) == 1) 
            FireChangedEvent();
    }

    void DeSelect (set<T*> objs) {
        selection.erase(objs.begin(), objs.end());
        FireChangedEvent();
    }

    void Clear() {
        selection.clear();
        FireChangedEvent();
   }

};

}
}
#endif
