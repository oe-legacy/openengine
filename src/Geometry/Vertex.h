// Vertex.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_VERTEX_H
#define _OE_VERTEX_H

#include <Math/Vector.h>
#include <map>
#include <string>

using namespace std;

namespace OpenEngine {
    using namespace Math;
    namespace Geometry {

        template <class T> class Vertex {
        private:
            std::map<std::string, Vector<4, T> > attributes;
            
        public:
            Vertex() {}
            Vertex(std::map<std::string, Vector<4, T> > attributes)
                : attributes(attributes) {}
            
            virtual ~Vertex() {}
            
            inline Vector<4, T> GetAttribute(const std::string name) const {
                return attributes.find(name)->second;
            }

            inline typename std::map<std::string, Vector<4, T> >::iterator begin() {
                return attributes.begin();
            }
            inline typename std::map<std::string, Vector<4, T> >::iterator end() {
                return attributes.end();
            }
            
            inline void operator+=(const T& t) {
                typename map<string, Vector<4, T> >::iterator itr = attributes.begin();
                while (itr != attributes.end()){
                    itr->second += t;
                    ++itr;
                }
            }
            
            inline void operator+=(Vertex<T>& v) {
                typename map<string, Vector<4, T> >::const_iterator itr = v.begin();
                while (itr != v.end()) {
                    attributes.find(itr->first)->second += itr->second;
                    ++itr;
                }
            }

            inline void operator/=(const T& t) {
                typename map<string, Vector<4, T> >::iterator itr = attributes.begin();
                while (itr != attributes.end()){
                    itr->second /= t;
                    ++itr;
                }
            }

            inline std::string ToString() const {
                std::ostringstream out;
                out << "{";
                typename map<string, Vector<4, T> >::const_iterator itr = attributes.begin();
                while (itr != attributes.end()){
                    out << itr->first;
                    out << ":";
                    out << itr->second;
                    out << ", ";
                    ++itr;
                }
                out << "}";
                return out.str();
            }
            
        };

        /**
         * Stream operator to ease the use of ToString method.
         */
        template <class T>
        inline std::ostream& operator<<(std::ostream& os, const Vertex<T> v) {
            os<<v.ToString();
            return os;
        }

        
    }
}

#endif // _OE_VERTEX_H
