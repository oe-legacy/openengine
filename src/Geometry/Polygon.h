#ifndef _POLYGON_
#define _POLYGON_

#include <Math/Vector.h>
#include <Logging/Logger.h>
#include <set>

namespace OpenEngine {
namespace Geometry {

class Polygon {
 private:
    std::vector< Math::Vector<3,float> > points;
 public:
    Polygon() {}
    void AddPoint(Math::Vector<3,float> point) {
        points.push_back(point);
    }

    unsigned int NumberOfPoints() {
        return points.size();
    }

    Vector<3,float> GetPoint(unsigned int index) {
        return points[index];
    }

    Vector<3,float> GetCenterOfGravity() {
        Vector<3,float> cog(0.0f);
        unsigned int size = points.size();
        for (unsigned int i=0; i<size; i++) { 
            cog += points[i] * (1.0f/size);
        }
        return cog;
    }

    void SortPoints() {
        /** two way sort */

        //logger.info << "-------------------- starting new sort --------------" << logger.end;
        // move points into new vector
        std::vector< Math::Vector<3,float> > points;
        points.insert(points.end(), this->points.begin(), this->points.end());

        // transfer first point, and remove it from the set
        std::vector< Vector<3,float> > newPoints;
        {
        newPoints.push_back( points.front() );
        points.erase(points.begin());

        // find second point - with shortest distance, and remove it from the set
        std::vector< Vector<3,float> >::iterator itr = points.begin();
        std::vector< Vector<3,float> >::iterator itrOfPointWithSmallestDist = itr;
        itr++;
        for (;itr != points.end(); itr++) {
            Vector<3,float> fixedPoint = newPoints.front();

            Vector<3,float> pointWithSmallestDist
                = *itrOfPointWithSmallestDist;
            if ( (*itr-fixedPoint).GetLength() <
                 (pointWithSmallestDist-fixedPoint).GetLength()) {
                itrOfPointWithSmallestDist = itr;
            }
        }
        //logger.info << "inserting with length: " << (*itrOfPointWithSmallestDist).GetLength() << logger.end;
        newPoints.push_back( *itrOfPointWithSmallestDist );
        points.erase(itrOfPointWithSmallestDist);
    }
        while (points.size() > 0) {
            std::vector< Vector<3,float> >::iterator itr = points.begin();

            // choose two abitrary points in the set
            std::vector< Vector<3,float> >::iterator 
                leftItrOfPointWithSmallestDist = itr;
            std::vector< Vector<3,float> >::iterator
                rightItrOfPointWithSmallestDist = itr;

            // find points with smallest distance to the end points of newPoints
            itr++;
            for (; itr!=points.end(); itr++) {
                Vector<3,float> fixedPoint = *itr;

                Vector<3,float> leftPointWithSmallestDist 
                    = *leftItrOfPointWithSmallestDist;
                if ( (fixedPoint - newPoints.front()).GetLength() <
                     (leftPointWithSmallestDist - newPoints.front()).GetLength()) {
                    leftItrOfPointWithSmallestDist = itr;
                    /*
                    logger.info << "updating left length: " << 
                        (*leftItrOfPointWithSmallestDist - newPoints.front()).GetLength() << logger.end;
                    */
                }
                Vector<3,float> rightPointWithSmallestDist
                    = *rightItrOfPointWithSmallestDist;
                if ( (fixedPoint - newPoints.back()).GetLength() <
                     (rightPointWithSmallestDist - newPoints.back()).GetLength()) {
                    rightItrOfPointWithSmallestDist = itr;
                    /*
                    logger.info << "updating right length: " << 
                        (*rightItrOfPointWithSmallestDist - newPoints.back()).GetLength() << logger.end;
                    */
                }
            }
            float leftDist = 
                (*leftItrOfPointWithSmallestDist - newPoints.front()).GetLength();
            float rightDist = 
                (*rightItrOfPointWithSmallestDist - newPoints.back()).GetLength();
            if (isnan(leftDist))
                logger.error << "left is nan" << logger.end;
            if (isnan(rightDist))
                logger.error << "right is nan" << logger.end;
            if (leftDist==0) {
                logger.error << "left is zero" << logger.end;
                /*
                logger.info << "left:" << *leftItrOfPointWithSmallestDist << logger.end;
                logger.info << "new begin: " << newPoints.front() << logger.end;
                for (unsigned int i=0; i<this->points.size(); i++) {
                    logger.info << "points[" << i << "]: " << this->points[i] << logger.end;
                }
                    throw -1;
                */
            }
            if (rightDist==0) {
                logger.error << "right is zero" << logger.end;
                /*
                logger.info << "right:" << *rightItrOfPointWithSmallestDist << logger.end;
                logger.info << "new end: " << newPoints.back() << logger.end;
                for (unsigned int i=0; i<this->points.size(); i++) {
                    logger.info << "points[" << i << "]: " << this->points[i] << logger.end;
                }
                    throw -1;
                */
            }
            if (leftDist < rightDist) {
                // insert left point at begining, and remove it from the set
                /*
                logger.info << "inserting with length: " <<
                    (*leftItrOfPointWithSmallestDist - newPoints.front()).GetLength() << logger.end;
                */
                newPoints.insert(newPoints.begin(), *leftItrOfPointWithSmallestDist);
                points.erase(leftItrOfPointWithSmallestDist);
                //logger.info << "inserting at front" << logger.end;
            } else {
                // insert right point at end, and remove it from the set
                /*
                logger.info << "inserting with length: " <<
                    (*rightItrOfPointWithSmallestDist - newPoints.back()).GetLength() << logger.end;
                */
                newPoints.insert(newPoints.end(), *rightItrOfPointWithSmallestDist);
                points.erase(rightItrOfPointWithSmallestDist);
                //logger.info << "inserting at end" << logger.end;
            }
            //logger.info << "size: " << newPoints.size() << logger.end;
        }
        if (this->points.size() != newPoints.size())
            logger.error << "size not the same!" << logger.end;
        //logger.info << "number of points: " << newPoints.size() << logger.end;


        this->points = newPoints;
        //this->points.clear();
        //this->points.insert(this->points.end(), newPoints.begin(), newPoints.end());

        //this->points.insert(points.begin(),points.end());
        //logger.info << "sort done" << logger.end;

        //points.erase(indexOfPointWithSmallestDist);
        /*
        // sort based on shortest distance
        for (unsigned int counter = 0; counter<size; counter++) {
            Vector<3,float> fixedPoint = tmpPoints[counter];

            unsigned int indexOfPointWithSmallestDist = counter+1;
            for (unsigned int i = counter+1; i < size; i++) {
                Vector<3,float> newPoint = tmpPoints[i];
                Vector<3,float> pointWithSmallestDist
                    = tmpPoints[indexOfPointWithSmallestDist];

                if ( (newPoint-fixedPoint).GetLength() <
                     (pointWithSmallestDist-fixedPoint).GetLength()) {
                    indexOfPointWithSmallestDist = i;
                }
            }

            // swap points
            if (counter+1<size) {
                Vector<3,float> tmp = tmpPoints[indexOfPointWithSmallestDist];
                tmpPoints[indexOfPointWithSmallestDist] = tmpPoints[counter+1];
                tmpPoints[counter+1] = tmp;
            }
        }

        // write back values
        points.clear();
        for (unsigned int i = 0; i < size; i++)
            points.push_back( tmpPoints[i] );
        //delete[] tmpPoints;
        */
        /** oneway sort
        // copy points
        const unsigned int size = points.size();
        Vector<3,float>* tmpPoints = new Vector<3,float>[size];
        for (unsigned int i = 0; i < size; i++)
            tmpPoints[i] = points[i];

        // sort based on shortest distance
        for (unsigned int counter = 0; counter<size; counter++) {
            Vector<3,float> fixedPoint = tmpPoints[counter];

            unsigned int indexOfPointWithSmallestDist = counter+1;
            for (unsigned int i = counter+1; i < size; i++) {
                Vector<3,float> newPoint = tmpPoints[i];
                Vector<3,float> pointWithSmallestDist
                    = tmpPoints[indexOfPointWithSmallestDist];

                if ( (newPoint-fixedPoint).GetLength() <
                     (pointWithSmallestDist-fixedPoint).GetLength()) {
                    indexOfPointWithSmallestDist = i;
                }
            }

            // swap points
            if (counter+1<size) {
                Vector<3,float> tmp = tmpPoints[indexOfPointWithSmallestDist];
                tmpPoints[indexOfPointWithSmallestDist] = tmpPoints[counter+1];
                tmpPoints[counter+1] = tmp;
            }
        }

        // write back values
        points.clear();
        for (unsigned int i = 0; i < size; i++)
            points.push_back( tmpPoints[i] );
        delete[] tmpPoints;
        */
        /*
    // from: http://www.euclideanspace.com/maths/algebra/vectors/angleBetween/index.htm
        Vector<3,float> cog = GetCenterOfGravity();
        Vector<3,float> point0 = points[0] - cog;
        point0.Normalize();
            logger.info << "------------------------- " << logger.end;
            logger.info << "Center of gravity: " << cog << logger.end;

        // find vectors that are not parallel and
        // calculate rotation axis
        Vector<3,float> axis;
        for (unsigned int i=1; i<points.size(); i++) { 
            axis = point0 % (points[i]- cog).GetNormalize();
            // undefined if vectors are parallel
            if (!axis.IsZero()) {
                axis.Normalize();
                break;
            }
        }
        if (axis.IsZero())
            throw Core::Exception("unsound polygon");

        // sort points based on angle and axis sign
        //unsigned int counter = 0;
        //static unsigned int skip = 0;
        unsigned int i=0; 
        while (i<points.size()-1) { 
            //counter++;
            Vector<3,float> point1 = points[i] - cog;
            Vector<3,float> point2 = points[i+1] - cog;
            point1.Normalize();
            point2.Normalize();
            Vector<3,float> axis1 = point0 % point1;
            Vector<3,float> axis2 = point0 % point2;

            float sign1 = 1;
            if (!axis1.IsZero()) {
                axis1.Normalize();
                sign1 = axis * axis1;
            }

            float sign2 = 1;
            if (!axis2.IsZero()) {
                axis2.Normalize();
                sign2 = axis * axis2;
            }

            float dot1 = point0 * point1;
            float angle1 = acos( dot1 );
            if (sign1 < 0)
                angle1 *= -1;

            float dot2 = point0 * point2;
            float angle2 = acos( dot2 );
            if (sign2 < 0)
                angle2 *= -1;

            logger.info << "i: " << i << logger.end;

            logger.info << "p0: " << point0 << logger.end;
            logger.info << "p1: " << point1 << logger.end;
            logger.info << "p2: " << point2 << logger.end;
            logger.info << "sign1: " << sign1 << logger.end;
            logger.info << "sign2: " << sign2 << logger.end;
            logger.info << "angle1: " << angle1 << logger.end;
            logger.info << "angle2: " << angle2 << logger.end;
            logger.info << "dot1: " << dot1 << logger.end;
            logger.info << "dot2: " << dot2 << logger.end;

            if (angle1 > angle2) {
                logger.info << "swapping"<< logger.end;
                Vector<3,float> tmp = points[i];
                points[i] = points[i+1];
                points[i+1] = tmp;
                if (i > 0)
                    i--;
            } else
                i++;

//             if (counter > 100) {
//                 logger.info << "skipping: " << skip++ << logger.end;
//                 break;
//             }

        }
        */
    }

    std::string ToString() const {
        std::stringstream ss;
        ss << "(";
        for (unsigned int i=0; i<points.size(); i++) {
            ss << points[i];
            if (i<points.size()-1)
                ss << ",";
        }
        ss << ")";
        return ss.str();
    }
};

} // NS Geometry
} // NS OpenEngine

#endif // _POLYGON_
