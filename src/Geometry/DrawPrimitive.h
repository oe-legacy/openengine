//  Drawing Primitive.
// -------------------------------------------------------------------
// Copyright (C) 2010 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _DRAW_PRIMITIVE_H_
#define _DRAW_PRIMITIVE_H_

#include <boost/shared_ptr.hpp>

namespace OpenEngine {
    namespace Geometry {
        class Material;
        typedef boost::shared_ptr<Material> MaterialPtr;
        class Mesh;
        typedef boost::shared_ptr<Mesh> MeshPtr;

        enum GeometryPrimitive {
            GL_POINTS,
            LINES,
            LINE_STRIP,
            TRIANGLES,
            TRIANGLE_STRIP,
            QUADS};

        class DrawPrimitive {
        protected:
            GeometryPrimitive prim;
            unsigned int indexOffset;
            unsigned int drawRange;
            MaterialPtr mat;
            MeshPtr mesh;
            
        public:
            DrawPrimitive(GeometryPrimitive prim,
                          MaterialPtr mat,
                          MeshPtr mesh);
            
            DrawPrimitive(GeometryPrimitive primitive,
                          unsigned int offset,
                          unsigned int range,
                          MaterialPtr mat,
                          MeshPtr mesh);

            inline GeometryPrimitive GetPrimitive() const { return prim; }
            inline unsigned int GetIndexOffset() const { return indexOffset; }
            inline unsigned int GetDrawingRange() { return drawRange; }
            inline MaterialPtr GetMaterial() const { return mat; }
            inline MeshPtr GetMesh() const { return mesh; }
            
        };

        typedef boost::shared_ptr<DrawPrimitive> DrawPrimitivePtr;

    }
}

#endif
