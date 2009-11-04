/*
 *  Thread.cpp
 *  OpenEngine
 *
 *  Created by Peter Kristensen on 13/07/09.
 *  Copyright 2009 Lucky Software. All rights reserved.
 *
 */

#include "Thread.h"

int Thread::Start() {
    
    return pthread_create(&thread, NULL, Thread::thread_func, (void*)this);

}

int Thread::Wait() {
    return pthread_join(thread, NULL);
    
}

