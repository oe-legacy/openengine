#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>

namespace OpenEngine {
    namespace Core {

class Mutex {
    
private:

    pthread_mutex_t _mutex;

public:
    Mutex();
    ~Mutex();
    void Lock();
    void Unlock();
};

    }
}

#endif
