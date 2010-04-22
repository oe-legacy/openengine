// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_INTERFACE_ENVIRONMENT_H_
#define _OE_INTERFACE_ENVIRONMENT_H_

#include <Core/IModule.h>

namespace OpenEngine {

// forward declarations
namespace Devices { class IMouse; class IKeyboard; class IJoystick; }

namespace Display {

class IFrame;

using std::string;

/**
 * Abstract environment for a widget/display toolkit, such as SDL or Qt.
 *
 * @class IEnvironment IEnvironment.h Display/IEnvironment.h
 */
class IEnvironment : public virtual Core::IModule {
private:

public:
    IEnvironment() {}
    virtual ~IEnvironment() {}
    virtual IFrame& CreateFrame() = 0;
    virtual Devices::IMouse* GetMouse() = 0;
    virtual Devices::IKeyboard* GetKeyboard() = 0;
    virtual Devices::IJoystick* GetJoystick() = 0;
};

} // NS Display
} // NS OpenEngine

#endif // _OE_INTERFACE_ENVIRONMENT_H_
