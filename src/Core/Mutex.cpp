#include <Core/Mutex.h>

namespace OpenEngine {
namespace Core {

    Mutex::Mutex() {
        pthread_mutex_init(&_mutex,NULL);
    }
    
    Mutex::~Mutex() {
        pthread_mutex_destroy(&_mutex);
    }

    void Mutex::Lock() {
        pthread_mutex_lock(&_mutex);
    }

    void Mutex::Unlock() {
        pthread_mutex_unlock(&_mutex);
    }


}
}
