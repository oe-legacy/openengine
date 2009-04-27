// Selection Set.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SELECTION_SET_H_
#define _OE_SELECTION_SET_H_

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
 * @class SelectionSet SelectionSet.h Utils/SelectionSet.h
 */
template <class T> 
class SelectionSet {
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

    void AddToSelection(T* obj) {
        if (selection.insert(obj).second)
            FireChangedEvent();
    }

    void AddToSelection (set<T*> objs) {
        selection.insert(objs.begin(), objs.end());
        FireChangedEvent();
    }

    void Select(T* obj) {
        selection.clear();
        selection.insert(obj);
        FireChangedEvent();
    }

    void Select (set<T*> objs) {
        selection.clear();
        selection.insert(objs.begin(), objs.end());
        FireChangedEvent();
    }

    void RemoveFromSelection(T* obj) {
        if (selection.erase(obj) == 1) 
            FireChangedEvent();
    }

    void RemoveFromSelection (set<T*> objs) {
        selection.erase(objs.begin(), objs.end());
        FireChangedEvent();
    }

    bool Empty () {
        return selection.empty();
    }

    void Clear() {
        selection.clear();
        FireChangedEvent();
    }

    set<T*> GetSelection() {
        return selection;
    }
};

}
}
#endif
