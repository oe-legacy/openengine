#include <Math/RandomGenerator.h>

#include <Logging/Logger.h>
#include <Utils/Timer.h>

#include <math.h>

using OpenEngine::Utils::Time;
using OpenEngine::Utils::Timer;

namespace OpenEngine {
namespace Math {

RandomGenerator::RandomGenerator() {
    idum = -1;
    iy=0;
    Seed(1);
}

void RandomGenerator::Seed(const unsigned int start_point) {
    // initialize the stream of random deviates.
    for (unsigned int i=0; i< start_point; i++)
        ran1();
}

void RandomGenerator::SeedWithTime() {
    Time time = Timer::GetTime();
    this->Seed(time.usec);
    /*
    logger.warning << "Random generator seeded with time: (";
    logger.warning << time.usec;
    logger.warning << ") - therefore it is nondeterministic.";
    logger.warning << logger.end;
    */
}

/**
 *  Returns a uniform random deviate between 0.0 and 1.0
 *  (exclusive of the endpoint values).
 *
 *  Call with idum a negative integer to initialize: thereafter,
 *  do not alter idum between successive deviates in a sequence.
 */
float RandomGenerator::ran1() {
    const long   IA = 16807;
    const long   IM = 2147483647;
    const double AM = 1.0/IM; 
    const long   IQ = 127773;
    const long   IR = 2836;
    const double NDIV = 1+(IM-1)/NTAB;
    const double EPS = 1.2e-7;
    const double RNMX = 1.0-EPS;

    int j;
    long k;
    float temp;

    // Initialize 
    if ( idum <= 0 || !iy ) {
        if ( -(idum) < 1 ) idum = 1;  // Prevent idum = 0  
        else idum = -(idum);

        // Load shufflev table after 8 numbers 
        for ( j=NTAB+7; j>=0; j-- ) {
            k=(idum)/IQ;
            idum=IA*(idum-k*IQ)-IR*k;
            if ( idum<0 ) idum += IM;
            if ( j<NTAB ) iv[j] = idum;
        }
        iy=iv[0];
    }
    k=(idum)/IQ;
    idum=IA*(idum-k*IQ)-IR*k;
    if ( idum<0 ) idum += IM;
    j=(int)(iy/NDIV);
    iy=iv[j];
    iv[j]= idum;
    if ( (temp=AM*iy) > RNMX ) return RNMX;
    else return temp;
}

/**
 *  Returns a uniform random deviate floating point value
 *  in the open interval ]i,j[.
 */
float RandomGenerator::UniformFloat(float i, float j) {
    return (i+ran1()*(j-i));
}

/**
 *  Returns a uniform random deviate integer in the closed 
 *  interval [i,j].
 */
int RandomGenerator::UniformInt(int i, int j) {
    return (int)(i-1+ceil(ran1()*(j-i+1)));
}

/** 
 *  Returns a normal random deviate with mean: my and 
 *  variance: sigma*sigma.
 */      
float RandomGenerator::Normal(float my, float sigma) {
    float u1, u2, r, pi;
    pi = 4.0 * atan( 1.0 );
    u1 = ran1();
    u2 = ran1();
    r = my + sqrt( -2.0*sigma*sigma*log(u1) ) * cos( 2*pi*u2);
    return r;
}

} // NS Math
} // NS OpenEngine
