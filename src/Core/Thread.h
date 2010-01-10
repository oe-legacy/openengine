/*
 *  Thread.h
 *  OpenEngine
 *
 *  Created by Peter Kristensen on 13/07/09.
 *  Copyright 2009 Lucky Software. All rights reserved.
 *
 */

#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace OpenEngine {
namespace Core {

class Thread {


private:
    pthread_t thread;
    static void* thread_func(void *d){((Thread *)d)->Run(); return 0;}

    
public:
    virtual ~Thread() {};
    
    virtual void Run() =0;
    
    int Start();
    int Wait();

    static void Sleep(long mills);
    
};

}
}

#endif
