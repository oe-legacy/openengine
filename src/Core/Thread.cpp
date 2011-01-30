/*
 *  Thread.cpp
 *  OpenEngine
 *
 *  Created by Peter Kristensen on 13/07/09.
 *  Copyright 2009 Lucky Software. All rights reserved.
 *
 */

#include "Thread.h"
#include <unistd.h>

namespace OpenEngine {
namespace Core {


int Thread::Start() {
    
    return pthread_create(&thread, NULL, Thread::thread_func, (void*)this);

}

int Thread::Wait() {
    return pthread_join(thread, NULL);
    
}


void Thread::Sleep(long usec) {
    usleep(usec);
}

}
}
