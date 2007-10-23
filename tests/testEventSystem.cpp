// Test the engine event system
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// include boost unit test framework
#include <boost/test/unit_test.hpp>
#include "testEventSystem.h"
#include <string>

// include event system
#include <Core/IModule.h>

#include <EventSystem/Event.h>
#include <EventSystem/EventQueue.h>
#include <EventSystem/Listener.h>
#include <EventSystem/QueuedListener.h>

namespace OpenEngine {
namespace Tests {

using std::string;
using namespace OpenEngine::Core;
using namespace OpenEngine::EventSystem;

// Define event arg to send on notification.
struct SomeEventArg { string data; };
        
// Create stub handler class
class MyEventHandler {
public:
    // constructor/destructor
    MyEventHandler();
    ~MyEventHandler();
    // count notify events
    int notifications;
    // last received event
    string recv;
    // event handler method
    void HandleEvent(SomeEventArg arg);
    void HandleEventDummy(SomeEventArg arg) {}
};

MyEventHandler::MyEventHandler() : notifications(0) {}
MyEventHandler::~MyEventHandler() {}
void MyEventHandler::HandleEvent(SomeEventArg arg){
    notifications++;
    recv = arg.data;
}
    
void testQueuedEventListeners() {
    EventQueue eventQueue;

    Event<SomeEventArg> keyEvent;

    // Instance of handler
    MyEventHandler* handler = new MyEventHandler();
    
    // Create queued listener
    QueuedListener<MyEventHandler, SomeEventArg> qListenerA(*handler, &MyEventHandler::HandleEvent, eventQueue);

    // Subscribe the queued listener to the event
    keyEvent.Add(&qListenerA);

    // Create event argument
    SomeEventArg keyEventArg; keyEventArg.data = "keypressed";

    // Fire the event two times
    keyEvent.Notify(keyEventArg);
    keyEvent.Notify(keyEventArg);
    // Check that the handler has not been notified
    BOOST_CHECK(handler->notifications == 0);
    // Process all events in the EventQueue.
    eventQueue.Process();
    // Check that the handler has been notified two times
    BOOST_CHECK(handler->notifications == 2);

    // Check that we only get two more notifications
    keyEvent.Notify(keyEventArg);
    keyEvent.Notify(keyEventArg);
    eventQueue.Process();
    BOOST_CHECK(handler->notifications == 4);
    
    // Unsubscribe the listener
    keyEvent.Remove(&qListenerA);

    // Fire the event no one is listening on anymore
    keyEvent.Notify(keyEventArg);

    // Process all events in the EventQueue again
    eventQueue.Process();

    // Check that the handler hasn't been notified again
    BOOST_CHECK(handler->notifications == 4);

    delete handler;
}

// Test that listeners are handled correctly by events.
void testEventListeners() {
    // Create the SomeEvent
    Event<SomeEventArg> someEvent;

    // Instance of handler
    MyEventHandler* handler = new MyEventHandler();
    // Create listener to callback handler.
    Listener<MyEventHandler, SomeEventArg> listener1(*handler, &MyEventHandler::HandleEvent);
    Listener<MyEventHandler, SomeEventArg> listener2(*handler, &MyEventHandler::HandleEventDummy);

    // TEST add listener
    // Subscribe listener to event
    someEvent.Add(&listener1);
    someEvent.Add(&listener2);


    // Check number of listeners
    BOOST_CHECK(someEvent.NumListeners() == 2);


    // TEST event notifications
    // Create event to fire
    SomeEventArg eventArg;
    eventArg.data = 'x';
    // notify event four times
    someEvent.Notify(eventArg);
    someEvent.Notify(eventArg);
    someEvent.Notify(eventArg);
    someEvent.Notify(eventArg);
    // Check for four callbacks
    BOOST_CHECK(handler->notifications == 4);
    // Check if the eventarg was recv
    //    BOOST_CHECK(handler->recv == 'x');


    // TEST remove listener
    // Unsubscribe listener from event
    someEvent.Remove(&listener1);
    someEvent.Remove(&listener2);

    // Check number of listeners
    BOOST_CHECK(someEvent.NumListeners() == 0);

    delete handler;
}

} // NS Tests
} // NS OpenEngine
