// Tests for the input/output system
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>
#include "testDevices.h"
#include <string>
#include <map>
#include <iostream>

#include <Core/GameEngine.h>
#include <Core/IModule.h>
#include "GameTestFactory.h"

// include devices system
#include <Devices/IKeyboard.h>
#include <Devices/IMouse.h>
#include <Display/IFrame.h>

namespace OpenEngine {
namespace Tests {

using namespace std;
using namespace OpenEngine::Core;
using namespace OpenEngine::Devices;
using namespace OpenEngine::Display;

class KeyHandler : public IModule {
public:
    bool done;
    map<string, Key> questions;
    map<string, Key>::iterator current;
    KeyHandler() : done(false) {}
    void ask() {
        cout << "Please press " << current->first << endl; 
    }
    void HandleEvent(KeyboardEventArg arg) {
        if (done) return;
        BOOST_CHECK(arg.sym == current->second);
        if (++current == questions.end()) done = true;
        else ask();
    }
    void Initialize() {
        // make the questions list
        questions.insert(make_pair("Enter",KEY_RETURN));
        questions.insert(make_pair("F1",   KEY_F1));
        questions.insert(make_pair("F2",   KEY_F2));
        questions.insert(make_pair("F3",   KEY_F3));
        current = questions.begin();
        // ask the first question
        ask(); 
    }
    void Process(const float dt, const float p) { if (done) GameEngine::Instance().Stop(); }
    void Deinitialize() {}
    bool IsTypeOf(const type_info& info) { return false; }
};

void testKeyboard() {
    // get the testing engine
    IGameEngine& engine = GameEngine::Instance();
    // create a keyboard handler
    KeyHandler handler;
    // register it as a listener
    Listener<KeyHandler, KeyboardEventArg> 
        listener(handler, &KeyHandler::HandleEvent);
    IKeyboard::keyDownEvent.Add(&listener);
    // add it as a module
    engine.AddModule(handler);
    // start the engine
    engine.Start(GetTestFactory());
    // remove the listener
    IKeyboard::keyDownEvent.Remove(&listener);
}


class MouseHandler : public IModule {
public:
    bool done1, doneNE, doneSW;
    int width, height;
    MouseMovedEventArg lastMove;
    map<string, MouseButton> questions;
    map<string, MouseButton>::iterator current;
    MouseHandler() : done1(false), doneNE(false), doneSW(false) {}
    void ask() {
        cout << current->first << endl; 
    }
    void HandleButtonEvent(MouseButtonEventArg arg) {
        if (done1) return;
        BOOST_CHECK(arg.button == current->second);
        if (++current == questions.end()) {
            done1 = true;
            cout << "Place the mouse in the top-right corner" << endl;
        }
        else ask();
    }
    void HandleMovedEvent(MouseMovedEventArg arg) {
        // check that events only send when moved.
        // if this check fails the IMouse implementation is sending
        // moved events even though the mouse has not moved.
        BOOST_CHECK(lastMove.x != arg.x || lastMove.y != arg.y);
        lastMove = arg;
        // placement tests
        if (done1 && !doneNE)
            if (arg.x > (unsigned)(width - 100) && arg.y < (unsigned)100) {
                doneNE = true;
                cout << "Place the mouse in the lower-left corner" << endl;
            }
        if (doneNE && !doneSW)
            if (arg.x < (unsigned)100 && arg.y > (unsigned)(height - 100))
                doneSW = true;
    }
    void Initialize() {
        // find the frame size
        IFrame* f = dynamic_cast<IFrame*>(GameEngine::Instance().Lookup(typeid(IFrame)));
        BOOST_CHECK(f != NULL);
        width  = f->GetWidth();
        height = f->GetHeight();
        // make the questions list
        questions.insert(make_pair("1. Press LEFT mouse button",   BUTTON_LEFT));
        questions.insert(make_pair("2. Press RIGHT mouse button",  BUTTON_RIGHT));
        questions.insert(make_pair("3. Press MIDDLE mouse button (or right and left at the same time if your mouse has no middle button)",
                                   BUTTON_MIDDLE));
        questions.insert(make_pair("4. SCROLL UP on wheel",        BUTTON_WHEEL_UP));
        questions.insert(make_pair("5. SCROLL DOWN on wheel",      BUTTON_WHEEL_DOWN));
        current = questions.begin();
        // ask the first question
        ask();
    }
    void Process(const float dt, const float p) { 
        if (doneSW) GameEngine::Instance().Stop(); 
    }
    void Deinitialize() {}
    bool IsTypeOf(const type_info& info) { return false; }
};

void testMouse() {
    // get the testing engine
    IGameEngine& engine = GameEngine::Instance();
    // create a keyboard handler
    MouseHandler handler;
    // register it as a button listener
    Listener<MouseHandler, MouseButtonEventArg> 
        b_listener(handler, &MouseHandler::HandleButtonEvent);
    IMouse::mouseUpEvent.Add(&b_listener);
    // register it as a movement listener
    Listener<MouseHandler, MouseMovedEventArg> 
        m_listener(handler, &MouseHandler::HandleMovedEvent);
    IMouse::mouseMovedEvent.Add(&m_listener);
    // add it as a module
    engine.AddModule(handler);
    // start the engine
    engine.Start(GetTestFactory());
    // remove the listeners
    IMouse::mouseUpEvent.Remove(&b_listener);
    IMouse::mouseMovedEvent.Remove(&m_listener);
}

} // NS Tests
} // NS OpenEngine
