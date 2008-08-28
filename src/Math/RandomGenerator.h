/**
 *  RandomGenerator.h
 *
 *  Refactorization of random.h and random.cpp by pmn (31.5.06, pm-n.),
 *  which was done on the basis of:
 *  Ref. Press et al.: Numerical recipes in C ( 2. ed. ), p. 280.
 */

#ifndef _RANDOM_GENERATOR_H_
#define _RANDOM_GENERATOR_H_

namespace OpenEngine {
namespace Math {

class  RandomGenerator {
public:
    RandomGenerator();
    void Seed(unsigned int start_point);
    void SeedWithTime();
    float UniformFloat(float i, float j);
    int UniformInt(int i, int j);
    float Normal(float my, float sigma);
   
private:
    static const long NTAB = 32;
    long iv[NTAB];
    long iy;
    long idum;
   
    inline float ran1();
};

} // NS Math
} // NS OpenEngine

#endif // _RANDOM_GENERATOR_H_
