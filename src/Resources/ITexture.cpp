// Texture resource interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/ITexture.h>
#include <Resources/ICubemap.h>

namespace OpenEngine {
namespace Resources {

    void ITexture::GenerateMipMap(ICubemapPtr map) {
        if (!(map->IsReadable()) || !(map->IsMipmapped())) return;

        
    }

}
}
