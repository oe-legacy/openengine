// Math extensions and utilities.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------
// Used to get namespace documentation and a cmake library.

namespace OpenEngine { 

/**
 * Math extensions and utilities.
 *
 * @namespace OpenEngine::Math
 */
namespace Math {

/**
 *  from: http://en.wikipedia.org/wiki/Binary_GCD_algorithm
 */
unsigned int GCD(const unsigned int left, const unsigned int right) {

    unsigned int u = left;
    unsigned int v = right;
    int shift;

    /* GCD(0,x) := x */
    if (u == 0 || v == 0)
      return u | v;

    /* Let shift := lg K, where K is the greatest power of 2
       dividing both u and v. */
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }

    while ((u & 1) == 0)
      u >>= 1;

    /* From here on, u is always odd. */
    do {
        while ((v & 1) == 0)  /* Loop X */
          v >>= 1;

        /* Now u and v are both odd, so diff(u, v) is even.
           Let u = min(u, v), v = diff(u, v)/2. */
        if (u < v) {
            v -= u;
        } else {
            unsigned int diff = u - v;
            u = v;
            v = diff;
        }
        v >>= 1;
    } while (v != 0);

    return u << shift;
}

}
}
