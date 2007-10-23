// Engine module interface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _INTERFACE_MODULE_H_
#define _INTERFACE_MODULE_H_

#include <typeinfo>

namespace OpenEngine {
namespace Core {

/**
 * Engine module interface.
 *
 * @class IModule IModule.h Core/IModule.h
 */
class IModule {
public:
    IModule();
    virtual ~IModule();

    /**
     * Initialize module.
     * Called once on engine start up.
     */
    virtual void Initialize() = 0;

    /**
     * Process module.
     * Main module processing method, call once every frame.
     *
     * @param deltaTime Time elapsed since last process.
     * @param percent Percentage of the current tick frame.
     */
    virtual void Process(const float deltaTime, const float percent) = 0;

    /**
     * Deinitialize module.
     * Called once on module unload or engine shutdown.
     */
    virtual void Deinitialize() = 0;

    /**
     * Check if module is of a given type.
     *
     * @note Derivatives of this class *must* override this method
     *       and do the following:
     *
     *       1. Compare their own type with \a inf.
     *
     *       2. If the two types are not equal call \a IsTypeOf(inf)
     *          on the immediate super class. This way the test is
     *          carried out recursively until the entire hierarchy 
     *          has been taken into consideration, or the type
     *          we are looking for matches.
     *
     * If one of the types inside the hierarchy matches the \a inf 
     * argument, the method (or overridden sub implementations) must
     * return true. If the type we are looking for does not
     * match any type in the hierarchy false is returned.
     * 
     * @code
     * // example implementation for a module with one parent
     * return (typeid(MyModule) == inf 
     *         || MyParent::IsTypeOf(inf));
     *
     * // example implementation for a module using multiple inheritance
     * return (typeid(MyModule) == inf 
     *         || MyFisrtParent::IsTypeOf(inf)
     *         || ...
     *         || MyNthParent::IsTypeOf(inf));
     * @endcode
     *
     * @param inf Type info as returned by typeid(class)
     * @return true if this is of type or subtype of \a inf
     *         otherwise false.
     */
     virtual bool IsTypeOf(const std::type_info& inf) = 0;

};

} // NS Core
} // NS OpenEngine

#endif // _INTERFACE_MODULE_H_
