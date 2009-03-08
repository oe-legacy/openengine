// Search tool for finding nodes in a scene.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/SearchTool.h>
#include <Scene/SceneNodes.h>

namespace OpenEngine {
namespace Scene {

using std::list;
using std::string;

#define SCENE_NODE(type)                                                \
    type* SearchTool::Child##type(ISceneNode* r) {                      \
        if (r == NULL) return NULL;                                     \
        return Child##type(list<ISceneNode*>(1, r));                    \
    }                                                                   \
    type* SearchTool::Child##type(list<ISceneNode*> rs) {               \
        class Finder : public ISceneNodeVisitor {                       \
        public:                                                         \
        type* found;                                                    \
        Finder() : found(NULL) { }                                      \
        void DefaultVisitNode(ISceneNode* node) { }                     \
        void Visit##type(type* node) {                                  \
            if (found == NULL) found = node;                            \
        }                                                               \
        };                                                              \
        Finder finder;                                                  \
        list<ISceneNode*>::iterator itr;                                \
        for (itr = rs.begin(); itr != rs.end(); itr++) {                \
            (*itr)->VisitSubNodes(finder);                              \
            if (finder.found != NULL) return finder.found;              \
        }                                                               \
        return NULL;                                                    \
    }                                                                   \
    list<type*> SearchTool::Child##type##s(ISceneNode* r) {             \
        if (r == NULL) return list<type*>();                            \
        return Child##type##s(list<ISceneNode*>(1, r));                 \
    }                                                                   \
    list<type*> SearchTool::Child##type##s(list<ISceneNode*> rs) {      \
        class Finder : public ISceneNodeVisitor {                       \
        public:                                                         \
        list<type*> found;                                              \
        void DefaultVisitNode(ISceneNode* node) { }                     \
        void Visit##type(type* node) { found.push_back(node); }         \
        };                                                              \
        Finder finder;                                                  \
        list<ISceneNode*>::iterator itr;                                \
        for (itr = rs.begin(); itr != rs.end(); itr++)                  \
            (*itr)->VisitSubNodes(finder);                              \
        return finder.found;                                            \
    }                                                                   \
    type* SearchTool::Descendant##type(ISceneNode* r) {                 \
        if (r == NULL) return NULL;                                     \
        return Descendant##type(list<ISceneNode*>(1,r));                \
    }                                                                   \
    type* SearchTool::Descendant##type(list<ISceneNode*> rs) {          \
        class Finder : public ISceneNodeVisitor {                       \
        public:                                                         \
        type* found;                                                    \
        Finder() : found(NULL) { }                                      \
        void DefaultVisitNode(ISceneNode* node) {                       \
            if (found == NULL) node->VisitSubNodes(*this);              \
        }                                                               \
        void Visit##type(type* node) {                                  \
            if (found == NULL) found = node;                            \
        }                                                               \
        };                                                              \
        Finder finder;                                                  \
        list<ISceneNode*>::iterator itr;                                \
        for (itr = rs.begin(); itr != rs.end(); itr++) {                \
            (*itr)->VisitSubNodes(finder);                              \
            if (finder.found != NULL) return finder.found;              \
        }                                                               \
        return NULL;                                                    \
    }                                                                   \
    list<type*> SearchTool::Descendant##type##s(ISceneNode* r) {        \
        if (r == NULL) return list<type*>();                            \
        return Descendant##type##s(list<ISceneNode*>(1,r));             \
    }                                                                   \
    list<type*> SearchTool::Descendant##type##s(list<ISceneNode*> rs) { \
        class Finder : public ISceneNodeVisitor {                       \
        public:                                                         \
        list<type*> found;                                              \
        void Visit##type(type* node) {                                  \
            found.push_back(node);                                      \
            node->VisitSubNodes(*this);                                 \
        }                                                               \
        };                                                              \
        Finder finder;                                                  \
        list<ISceneNode*>::iterator itr;                                \
        for (itr = rs.begin(); itr != rs.end(); itr++)                  \
            (*itr)->VisitSubNodes(finder);                              \
        return finder.found;                                            \
    }                                                                   \
    type* SearchTool::Ancestor##type(ISceneNode* r) {                   \
        if (r == NULL) return NULL;                                     \
        return Ancestor##type(list<ISceneNode*>(1,r));                  \
    }                                                                   \
    type* SearchTool::Ancestor##type(list<ISceneNode*> rs) {            \
        class Finder : public ISceneNodeVisitor {                       \
        public:                                                         \
        type* found;                                                    \
        Finder() : found(NULL) { }                                      \
        void DefaultVisitNode(ISceneNode* node) {                       \
            if (node->GetParent() != NULL)                              \
                node->GetParent()->Accept(*this);                       \
        }                                                               \
        void Visit##type(type* node) {                                  \
            if (found == NULL) found = node;                            \
        }                                                               \
        };                                                              \
        Finder finder;                                                  \
        list<ISceneNode*>::iterator itr;                                \
        for (itr = rs.begin(); itr != rs.end(); itr++) {                \
            finder.DefaultVisitNode(*itr);                              \
            if (finder.found != NULL) return finder.found;              \
        }                                                               \
        return NULL;                                                    \
    }                                                                   \
    list<type*> SearchTool::Ancestor##type##s(ISceneNode* r) {          \
        if (r == NULL) return list<type*>();                            \
        return Ancestor##type##s(list<ISceneNode*>(1,r));               \
    }                                                                   \
    list<type*> SearchTool::Ancestor##type##s(list<ISceneNode*> rs) {   \
        class Finder : public ISceneNodeVisitor {                       \
        public:                                                         \
        list<type*> found;                                              \
        void DefaultVisitNode(ISceneNode* node) {                       \
            if (node->GetParent() != NULL)                              \
                node->GetParent()->Accept(*this);                       \
        }                                                               \
        void Visit##type(type* node) {                                  \
            found.push_back(node);                                      \
            DefaultVisitNode(node);                                     \
        }                                                               \
        };                                                              \
        Finder finder;                                                  \
        list<ISceneNode*>::iterator itr;                                \
        for (itr = rs.begin(); itr != rs.end(); itr++)                  \
            finder.DefaultVisitNode(*itr);                              \
        return finder.found;                                            \
    }
#include "SceneNodes.def"
#undef SCENE_NODE

// ====================================================
// Special cases for with-selectors on property nodes.
// ====================================================

bool _has_prop(PropertyNode* n, string k, string v) {
    if (n == NULL) return false;
    return n->GetProperty(k).Match(v);
}

PropertyNode* SearchTool::ChildPropertyNodeWith(string k, string v, ISceneNode* r) {
    if (r == NULL) return NULL;
    return ChildPropertyNodeWith(k, v, list<ISceneNode*>(1,r));
}

PropertyNode* SearchTool::ChildPropertyNodeWith(string k, string v, list<ISceneNode*> rs) {
    class Finder : public ISceneNodeVisitor {
    public:
        PropertyNode* found;
        string k, v;
        Finder(string k, string v) : found(NULL), k(k), v(v) { }
        void DefaultVisitNode(ISceneNode* node) { }
        void VisitPropertyNode(PropertyNode* node) {
            if (found == NULL && _has_prop(node, k, v))
                found = node;
        }
    };
    Finder finder(k,v);
    list<ISceneNode*>::iterator itr;
    for (itr = rs.begin(); itr != rs.end(); itr++) {
        (*itr)->VisitSubNodes(finder);
        if (finder.found != NULL) return finder.found;
    }
    return NULL;
}

list<PropertyNode*> SearchTool::ChildPropertyNodesWith(string k, string v, ISceneNode* r) {
    if (r == NULL) return list<PropertyNode*>();
    return ChildPropertyNodesWith(k, v, list<ISceneNode*>(1, r));
}

list<PropertyNode*> SearchTool::ChildPropertyNodesWith(string k, string v, list<ISceneNode*> rs) {
    class Finder : public ISceneNodeVisitor {
    public:
        string k, v;
        Finder(string k, string v) : k(k), v(v) { }
        list<PropertyNode*> found;
        void DefaultVisitNode(ISceneNode* node) { }
        void VisitPropertyNode(PropertyNode* node) {
            if (_has_prop(node, k, v)) found.push_back(node);
        }
    };
    Finder finder(k,v);
    list<ISceneNode*>::iterator itr;
    for (itr = rs.begin(); itr != rs.end(); itr++)
        (*itr)->VisitSubNodes(finder);
    return finder.found;
}

PropertyNode* SearchTool::DescendantPropertyNodeWith(string k, string v, ISceneNode* r) {
    if (r == NULL) return NULL;
    return DescendantPropertyNodeWith(k, v, list<ISceneNode*>(1,r));
}

PropertyNode* SearchTool::DescendantPropertyNodeWith(string k, string v, list<ISceneNode*> rs) {
    class Finder : public ISceneNodeVisitor {
    public:
        PropertyNode* found;
        string k, v;
        Finder(string k, string v) : found(NULL), k(k), v(v) { }
        void DefaultVisitNode(ISceneNode* node) {
            if (found == NULL) node->VisitSubNodes(*this);
        }
        void VisitPropertyNode(PropertyNode* node) {
            if (found == NULL && _has_prop(node, k, v)) found = node;
        }
    };
    Finder finder(k,v);
    list<ISceneNode*>::iterator itr;
    for (itr = rs.begin(); itr != rs.end(); itr++) {
        (*itr)->VisitSubNodes(finder);
        if (finder.found != NULL) return finder.found;
    }
    return NULL;
}

list<PropertyNode*> SearchTool::DescendantPropertyNodesWith(string k, string v, ISceneNode* r) {
    if (r == NULL) return list<PropertyNode*>();
    return DescendantPropertyNodesWith(k, v, list<ISceneNode*>(1,r));
}

list<PropertyNode*> SearchTool::DescendantPropertyNodesWith(string k, string v, list<ISceneNode*> rs) {
    class Finder : public ISceneNodeVisitor {
    public:
        list<PropertyNode*> found;
        string k, v;
        Finder(string k, string v) : k(k), v(v) { }
        void VisitPropertyNode(PropertyNode* node) {
            if (_has_prop(node, k, v)) found.push_back(node);
            node->VisitSubNodes(*this);
        }
    };
    Finder finder(k,v);
    list<ISceneNode*>::iterator itr;
    for (itr = rs.begin(); itr != rs.end(); itr++)
        (*itr)->VisitSubNodes(finder);
    return finder.found;
}

PropertyNode* SearchTool::AncestorPropertyNodeWith(string k, string v, ISceneNode* r) {
    if (r == NULL) return NULL;
    return AncestorPropertyNodeWith(k, v, list<ISceneNode*>(1,r));
}

PropertyNode* SearchTool::AncestorPropertyNodeWith(string k, string v, list<ISceneNode*> rs) {
    class Finder : public ISceneNodeVisitor {
    public:
        PropertyNode* found;
        string k, v;
        Finder(string k, string v) : found(NULL), k(k), v(v) { }
        void DefaultVisitNode(ISceneNode* node) {
            if (node->GetParent() != NULL)
                node->GetParent()->Accept(*this);
        }
        void VisitPropertyNode(PropertyNode* node) {
            if (found == NULL && _has_prop(node, k, v)) found = node;
        }
    };
    Finder finder(k,v);
    list<ISceneNode*>::iterator itr;
    for (itr = rs.begin(); itr != rs.end(); itr++) {
        finder.DefaultVisitNode(*itr);
        if (finder.found != NULL) return finder.found;
    }
    return NULL;
}

list<PropertyNode*> SearchTool::AncestorPropertyNodesWith(string k, string v, ISceneNode* r) {
    if (r == NULL) return list<PropertyNode*>();
    return AncestorPropertyNodesWith(k, v, list<ISceneNode*>(1,r));
}

list<PropertyNode*> SearchTool::AncestorPropertyNodesWith(string k, string v, list<ISceneNode*> rs) {
    class Finder : public ISceneNodeVisitor {
    public:
        list<PropertyNode*> found;
        string k, v;
        Finder(string k, string v) : k(k), v(v) { }
        void DefaultVisitNode(ISceneNode* node) {
            if (node->GetParent() != NULL)
                node->GetParent()->Accept(*this);
        }
        void VisitPropertyNode(PropertyNode* node) {
            if (_has_prop(node, k, v)) found.push_back(node);
            DefaultVisitNode(node);
        }
    };
    Finder finder(k,v);
    list<ISceneNode*>::iterator itr;
    for (itr = rs.begin(); itr != rs.end(); itr++)
        finder.DefaultVisitNode(*itr);
    return finder.found;
}

} // NS Scene
} // NS OpenEngine
