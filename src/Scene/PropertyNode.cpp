// Property node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/PropertyNode.h>
#include <Core/Exceptions.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Scene {

using std::map;
using std::string;
using Core::Exception;

// ============================================================
// Property implementation
// ============================================================

// protected constructors (used from PropertyNode)
PropertyNode::Property::Property() : type(NONE) { }
PropertyNode::Property::Property(int v) : type(INT), val(v) { }
PropertyNode::Property::Property(float v) : type(FLOAT), val(v) { }
PropertyNode::Property::Property(std::string v) : type(STRING), val(0), str(v) { }

/**
 * Is this a \a None property.
 * A \a None property is returned if the requested \a key was not
 * defined in the PropertyNode. Meaning there is no value associated
 * with the property.
 */
bool PropertyNode::Property::IsNone() {
    return type == NONE;
}

/**
 * Is this a \a Some property.
 * Meaning the property has an associated value and may be accessed
 * by the Match or AsType methods.
 */
bool PropertyNode::Property::IsSome() {
    return !IsNone();
}

/**
 * Is this an integer property of value \a v.
 * Matching with this method does not perform any implicit type
 * conversion.
 */
bool PropertyNode::Property::Match(int v) {
    return type == INT && v == (int)val;
}

/**
 * Is this a floating point property of value \a v.
 * Matching with this method does not perform any implicit type
 * conversion.
 */
bool PropertyNode::Property::Match(float v) {
    return type == FLOAT && v == (float)val;
}
//! Same as IsSome(float v), by casting \a v to a float.
bool PropertyNode::Property::Match(double v) { return Match((float)v); }

/**
 * Is this a string property of value \a v.
 * Matching with this method does not perform any implicit type
 * conversion.
 */
bool PropertyNode::Property::Match(std::string v) {
    return type == STRING && v == str;
}

/**
 * Get the property value as an integer.
 * Erroneous conversion will throw an exception, for example
 * conversion from a string.
 * @throws Exception
 */
int PropertyNode::Property::AsInt() {
    if (type != STRING) return (int)val;
    if (type == STRING)
        throw Exception("Invalid property conversion from string to int");
    throw Exception("Invalid property conversion from NONE to int");
}

/**
 * Get the property value as a floating point.
 * Erroneous conversion will throw an exception, for example
 * conversion from a string.
 * @throws Exception
 */
float PropertyNode::Property::AsFloat() {
    if (type != STRING) return (float)val;
    if (type == STRING)
        throw Exception("Invalid property conversion from string to float");
    throw Exception("Invalid property conversion from NONE to float");
}
/**
 * Get the property value as a string.
 * Erroneous conversion will throw an exception, for example
 * conversion from a NONE property.
 * @throws Exception
 */
std::string PropertyNode::Property::AsString() {
    if (type == STRING) return str;
    if (type == INT)    return Utils::Convert::ToString<int>((int)val);
    if (type == FLOAT)  return Utils::Convert::ToString<float>((float)val);
    throw Exception("Invalid property conversion from NONE to string");
}

// ============================================================
// Property node implementation
// ============================================================

/**
 * Set property \a key to the integer \a value.
 */
void PropertyNode::SetProperty(std::string key, int value) {
    props[key] = Property(value);
}

/**
 * Set property \a key to the float \a value.
 */
void PropertyNode::SetProperty(std::string key, float value) {
    props[key] = Property(value);
}

/**
 * Set property \a key to the float \a value.
 * Implicitly casts the double to a float.
 */
void PropertyNode::SetProperty(std::string key, double value) {
    SetProperty(key, (float)value);
}

/**
 * Set property \a key to the string \a value.
 */
void PropertyNode::SetProperty(std::string key, std::string value) {
    props[key] = Property(value);
}

/**
 * Test if the property for \a key is set.
 */
bool PropertyNode::HasProperty(std::string key) {
    return props.find(key) != props.end();
}

/**
 * Get the property for \a key.
 */
PropertyNode::Property PropertyNode::GetProperty(std::string key) {
    map<string,Property>::iterator it;
    it = props.find(key);
    if (it != props.end())
        return it->second;
    return Property();
}

} // NS Scene
} // NS OpenEngine
