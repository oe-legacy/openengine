// Math quaternion
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------

#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <string>
#include <sstream>
#include <ostream>
#include <boost/static_assert.hpp>

#include <Math/Vector.h>
#include <Math/Matrix.h>

namespace OpenEngine {
namespace Math {

/**
 * Quaternion.
 *
 * @class Quaternion Quaternion.h Math/Quaternion.h
 * @param T Type of elements
 */
template <class T>
class Quaternion {
private:
    // quaternion elements
    T real;
    Vector<3,T> image;

    // normalization invariant
    bool normalized;

public:
    /**
     * Create identity quaternion.
     *
     * @code
     * Quaternion<int> q;   // (1,[0, 0, 0])
     * @endcode
     */
    Quaternion() : normalized(true) {
        real = 1;
        image = Vector<3,T>(0,0,0);
    }
    /**
     * Create quaternion from scalar.
     * @code
     * Quaternion<int> q(7);   // (7,[0,0,0])
     * @endcode
     *
     * @param s Scalar value in real
     */
    explicit Quaternion(const T s) : normalized(false) {
        real = s;
        image = Vector<3,T>(0,0,0);
    }
    /**
     * Create quaternion from a vector.
     * @code
     * Vector<3,int> v(1,2,3);
     * Quaternion<int> q(v);   // (0,[1,2,3])
     * @endcode
     *
     * @param v Vector of imaginary parts
     */
    explicit Quaternion(const Vector<3,T> v) : normalized(false) {
        real = 0;
        image = v;
    }
    /**
     * Create quaternion from angle and axis.
     * @code
     * float pi = 3.14;
     * Vector<3,float> v(1,2,3);
     * Quaternion<float> q(pi, v);     // (~0,[~1,~2,~3])
     * Quaternion<float> q(2*pi, v);   // (~1,[~0,~0,~0])
     * @endcode
     *
     * @param angle Angle
     * @param axis Axis vector
     */
    Quaternion(const T angle, Vector<3,T> axis) : normalized(false) {
        real  = (T) cos(angle/2);
        image = ((T) sin(angle/2)) * axis;
    }

    /**
     * Create quaternion from Euler angles.
     * Algorithm taken from CTA page 494.
     *
     * @param x x angle
     * @param y y angle
     * @param z z angle
     */
    Quaternion(const T x, const T y, const T z) : normalized(false) {
        T cr, cp, cy, sr, sp, sy, cpcy, spsy;
        cr = cos(x/2);
        cp = cos(y/2);
        cy = cos(z/2);
        sr = sin(x/2);
        sp = sin(y/2);
        sy = sin(z/2);
        cpcy = cp * cy;
        spsy = sp * sy;
        real = cr * cpcy + sr * spsy;
        image = Vector<3,T>(sr * cpcy - cr * spsy,
                            cr * sp * cy + sr * cp * sy,
                            cr * cp * sy - sr * sp * cy);
    }
    /**
     * Create quaternion from scalar, and 3 scalar imaginary parts.
     * @code
     * Quaternion<int> q(1,2,3,4);   // (1,[2,3,4])
     * @endcode
     *
     * @param s Scalar value in real
     * @param i Scalar value in imaginary vector index [0]
     * @param j Scalar value in imaginary vector index [1]
     * @param k Scalar value in imaginary vector index [2]
     */
    Quaternion(const T s,const T i,const T j,const T k) : normalized(false) {
        real = s;
        image = Vector<3,T>(i,j,k);
    }
    /**
     * Create quaternion from matrix.
     * Algorithm taken from CTA page 493.
     *
     * @param m Rotation matrix
     */
    explicit Quaternion(Matrix<3,3,T> m) : normalized(false) {
        //compute the trace of the matrix
        float tr = m(0,0) + m(1,1) + m(2,2);
        // check if the trace is positive or negative
        if (tr > 0.0) {
            float s;
            s = sqrt(tr + 1.0);
            real = s / 2.0;
            s = 0.5 / s;
            image = Vector<3,T>( (m(1,2) - m(2,1)) * s,
                                 (m(2,0) - m(0,2)) * s,
                                 (m(0,1) - m(1,0)) * s);
        } else {
            int i, j, k;
            int nxt[3] = {1, 2, 0};
            i = 0;
            if (m(1,1) > m(0,0)) i = 1;
            if (m(2,2) > m(i,i)) i = 2;
            j = nxt[i];
            k = nxt[j];

            float s = sqrt((m(i,i) - (m(j,j) + m(k,k))) + 1.0);
            image = Vector<3,T>();
            image[i] = s * 0.5;

            if (s != 0.0) s = 0.5 / s;
            real     = (m(j,k) - m(k,j)) * s;
            image[j] = (m(i,j) + m(j,i)) * s;
            image[k] = (m(i,k) + m(k,i)) * s;
        }
    }
    /**
     * Create a quaternion with SLERP.
     *
     * Based on the algorithm in CTA page 498.
     *
     * @param from Initial end point.
     * @param to Final end point.
     * @param t Interpolation factor, 0 <= t <= 1
     */
    Quaternion(const Quaternion<float> from, const Quaternion<float> to, float t) {
        double omega, cosom, sinom, scale0, scale1;
        float toReal;
        Vector<3, float> toImage;

        cosom = from.real * to.real + (from.image * to.image);
        // flip sign if necessary in order to interpolate the "short way"
        if (cosom < 0.0) {
            cosom = -cosom;
            toReal = -to.real;
            toImage = to.image * -1;
        } else {
            toReal = to.real;
            toImage = to.image;
        }
        float DELTA = 0.1;
        if ((1.0 - cosom) > DELTA) {
            // perform slerp
            omega = acos(cosom);
            sinom = sin(omega);
            scale0 = sin((1.0 - t) * omega) / sinom;
            scale1 = sin(t * omega) / sinom;
        } else {
            // perform linear interpolation
            scale0 = 1.0 - t;
            scale1 = t;
        }
        //calculate final value
        real  = from.real  * scale0 + toReal  * scale1;
        image = from.image * scale0 + toImage * scale1;
    }
    /**
     * Copy constructor.
     *
     * @param q Quaternion to copy
     */
    Quaternion(const Quaternion<T>& q) : normalized(q.normalized) {
        real = q.real;
        image = q.image;
    }
    /**
     * Quaternion equality.
     * True if all elements are identical.
     */
    bool operator==(const Quaternion<T>& q) const {
        return ( real==q.real && image==q.image );
    }
    /**
     * Quaternion inequality.
     * True if one or more elements differ.
     */
    bool operator!=(const Quaternion<T>& q) const {
        return !(*this == q);
    }
    /**
     * Quaternion multiplication.
     * @code
     * Quaternion<int> a(1,2,3,4);     // (1, [2, 3, 4])
     * a * a;
     * @endcode
     */
    const Quaternion<T> operator*(const Quaternion<T> qr) const {
        const Quaternion<T> ql = (*this);
        Quaternion<T> r;
        r.real = (ql.real*qr.real) - (ql.image*qr.image);
        r.image = (ql.image % qr.image) + qr.real*ql.image + ql.real*qr.image;
        r.normalized = ql.normalized && qr.normalized;
        return r;
    }
    /**
     * Quaternion multiplication with scalar.
     * @code
     * Quaternion<int> a(1,2,3,4);     // (1, [2, 3, 4])
     * a * 2;
     * @endcode
     */
    const Quaternion<T> operator*(const T s) const {
        return (*this)*Quaternion(s);
    }
    /**
     * Destructive multiplication.
     */
    void operator*=(const Quaternion<T> q) {
        *this = *this * q;
    }
    /**
     * Get quaternion element by index.
     * @code
     * Quaternion<int> q(1,2,3,4);    // (1, [2, 3, 4])
     * q[1]                           // 2
     * @endcode
     *
     * @param i Index of element
     * @return value of element at index \a i
     */
    T& operator[](const int i) {
        if(i==0)
            return real;
        return image[i-1];
    }
    /**
     * Get the real element of the quaternion.
     *
     * @return real element
     */
    T GetReal() const {
        return real;
    }
    /**
     * Get the imaginary part of the quaternion.
     *
     * @return Vector of imaginary parts
     */
    Vector<3,T> GetImaginary() const {
        return image;
    }
    /**
     * Get the norm of the quaternion.
     *
     * @return Norm
     */
    T GetNorm() const {
        return (real * real) + (image * image);
    }
    /**
     * Get the conjugated quaternion.
     *
     * @return Conjugated quaternion
     */
    Quaternion<T> GetConjugate() const {
        return Quaternion<T>(real, -image.Get(0), -image.Get(1), -image.Get(2));
    }
    /**
     * Get the inverse quaternion.
     * If the quaternion is a unit the conjugate is returned.
     *
     * @return Inverse quaternion
     */
    Quaternion<T> GetInverse() const {
        if (normalized) return GetConjugate();
        return GetConjugate() * (1/GetNorm());
    }
    /**
     * Normalize the quaternion.
     * This is a destructive operation.
     * @see GetNormalize()
     */
    void Normalize() { 
        float srn = sqrt((*this).GetNorm());
        if (srn > 0) {
            if (real != 0)
                real /= srn;
            for(int i=0; i<3; i++)
                if (image[i] != 0)
                    image[i] /= srn;
        } else {
            throw ArithmeticException("Can not normalize a quaternion of length zero.");
        }
        normalized = true;
    }
    /**
     * Get a normalized copy of the quaternion.
     *
     * @see Normalize()
     * @return Normalized quaternion
     */
    Quaternion<T> GetNormalize() const {
        Quaternion<T> q(*this);
        q.Normalize();
        return q;
    }
    /**
     * Is the quaternion normalized (a unit).
     * This operation assumes that clients have not modified
     * the elements with the index operator.
     * It is meant as a quick check mostly for use in test cases.
     *
     * @return True if the quaternion is a unit
     */
    bool IsNormalized() const {
        return normalized;
    }
    /**
     * Get the matrix representation of the quaternion.
     *
     * @return Matrix representation
     */
    Matrix<3,3,T> GetMatrix() const {
        T w, x, y, z;
        w = real;
        x = image.Get(0);
        y = image.Get(1);
        z = image.Get(2);
        if (normalized)
            return Matrix<3,3,T> 
                (1-2*y*y-2*z*z, 2*x*y-2*w*z,   2*x*z+2*w*y,
                 2*x*y+2*w*z,   1-2*x*x-2*z*z, 2*y*z-2*w*x,
                 2*x*z-2*w*y,   2*y*z+2*w*x,   1-2*x*x-2*y*y);
        else
            return Matrix<3,3,T>
                (w*w+x*x-y*y-z*z, 2*x*y-2*w*z,     2*x*z+2*w*y,
                 2*x*y+2*w*z,     w*w-x*x+y*y-z*z, 2*y*z-2*w*x,
                 2*x*z-2*w*y,     2*y*z+2*w*x,     w*w-x*x-y*y+z*z);
    }
    /**
     * Rotate a vector according to the quaternion.
     *
     * @param v Vector to rotate
     * @return Rotated vector
     */
    Vector<3,T> RotateVector(const Vector<3,T>& v) const {
        Quaternion<T> q(v);
        q = (*this) * q * GetInverse();
        return q.GetImaginary();
    }
    /**
     * String representation.
     * Ex. (1, [2, 3, 4])
     *
     * @return Quaternion as string
     */
    std::string ToString() const {
        std::ostringstream out;
        out << "(" << real << ", " << image.ToString() << ")";
        return out.str();
    }

}; // Quaternion

/**
 * Stream operator to ease the use of ToString method.
 */
template <class T>
std::ostream& operator<<(std::ostream& os, const Quaternion<T> e) {
    os<<e.ToString();
    return os;
}

}  // NS OpenEngine
}  // NS Math

#endif // _QUATERNION_H_
