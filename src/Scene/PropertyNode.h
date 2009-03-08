// Property node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_PROPERTY_NODE_H_
#define _OE_PROPERTY_NODE_H_

#include <Scene/ISceneNode.h>
#include <map>

namespace OpenEngine {
namespace Scene {

/**
 * A property node for the scene.
 * Contains a set of key/value properties.
 * All keys are of type \a string and values may be of type \a int, \a
 * float or \a string; and are wrapped in a Property container object.
 *
 * Usage examples may be found in tests/PropertyNode.cpp
 *
 * Special support for searching after special property nodes in a
 * scene graph is implemented by the scene SearchTool.
 *
 * @see Property
 * @see SearchTool
 * @see tests/PropertyNode.cpp
 *
 * @class PropertyNode PropertyNode.h Scene/PropertyNode.h
 */
class PropertyNode : public ISceneNode {
    OE_SCENE_NODE(PropertyNode, ISceneNode)

public:
    /**
     * A property value object.
     * Property objects are used in PropertyNode to map keys to values.
     * A property implements an option type along with run-time type
     * information and type conversion routines.
     *
     * It is safe to perform Property::Match operations on a \a None
     * property.  However, calling conversion routines on a \a None
     * property will throw an exception.
     *
     * @see PropertyNode
     *
     * @class Property PropertyNode.h Scene/PropertyNode.h
     */
    class Property {
    public:
        bool IsNone();
        bool IsSome();
        bool Match(int v);
        bool Match(float v);
        bool Match(double v);
        bool Match(std::string v);
        int AsInt();
        float AsFloat();
        std::string AsString();
    private:
        friend class PropertyNode;
        // needed for creating default entries in stl-maps
        friend class std::map<std::string,Property>;
        // type enum and field (for run-time types)
        enum PropertyType { NONE, INT, FLOAT, STRING };
        PropertyType type;
        float val;          // stores an int or float value
        std::string str;    // stores a string value
        // constructing is private to PropertyNode
        Property();
        Property(int v);
        Property(float v);
        Property(std::string v);
    };

    void SetProperty(std::string key, int value);
    void SetProperty(std::string key, float value);
    void SetProperty(std::string key, double value);
    void SetProperty(std::string key, std::string value);

    bool HasProperty(std::string key);
    Property GetProperty(std::string key);

private:
    std::map<std::string, Property> props;

};

} // NS Scene
} // NS OpenEngine

#endif // _OE_PROPERTY_NODE_H_
