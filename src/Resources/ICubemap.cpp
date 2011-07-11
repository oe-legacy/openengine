// Cubemap texture interface.
// -------------------------------------------------------------------
// Copyright (C) 2011 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/ICubemap.h>

using namespace OpenEngine::Math;

namespace OpenEngine {
namespace Resources {

    void ICubemap::GenerateMipmaps(ICubemapPtr map) {
        if (!(map->IsReadable()) || !(map->IsMipmapped())) return;

        const Face faces[] = {POSITIVE_X, NEGATIVE_X, 
                              POSITIVE_Y, NEGATIVE_Y,
                              POSITIVE_Z, NEGATIVE_Z};
        // For each mip level except the first
        for (int m = 1; m < map->MipmapCount(); ++m) {
            // for each side
            for (int f = 0; f < 6; ++f) {
                // for each pixel
                GenerateMipmap(map, faces[f], m);
            }
        }
    }

    void ICubemap::GenerateMipmap(ICubemapPtr map, const Face face, const int miplevel) {
        // static const Face rightFace[] = {POSITIVE_X, NEGATIVE_X, 
        //                                  POSITIVE_Y, NEGATIVE_Y,
        //                                  POSITIVE_Z, NEGATIVE_Z};
        // static const Face bottomFace[] = {POSITIVE_X, NEGATIVE_X, 
        //                                   POSITIVE_Y, NEGATIVE_Y,
        //                                   POSITIVE_Z, NEGATIVE_Z};
        
        // @TODO use the neightbouring face for when outside own bounds.

        int pWidth = map->Width(miplevel-1);
        int pHeight = map->Height(miplevel-1);
        for (int x = 0; x < map->Width(miplevel); ++x) {
            for (int y = 0; y < map->Height(miplevel); ++y) {
                RGBAColor tl = map->GetPixel(face, x*2, y*2, miplevel-1);
                RGBAColor tr = map->GetPixel(face, x*2, std::min(y*2+1, pHeight-1), miplevel-1);
                RGBAColor bl = map->GetPixel(face, std::min(x*2+1, pWidth-1), y*2, miplevel-1);
                RGBAColor br = map->GetPixel(face, std::min(x*2+1, pWidth-1), std::min(y*2+1, pHeight-1), miplevel-1);
                Vector<4, float> hat = (tl + tr + bl + br) * 0.25;
                RGBAColor c = RGBAColor(hat[0], hat[1], hat[2], hat[3]);
                map->SetPixel(c, face, x, y, miplevel);
            }
        }
    }

}
}
