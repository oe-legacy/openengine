// OpenGL Shader Language resource.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _GLSL_RESOURCE_H_
#define _GLSL_RESOURCE_H_

#include <Resources/IShaderResource.h>
#include <Resources/ITextureResource.h>
#include <GL/glew.h>
#include <Meta/OpenGL.h>
#include "boost/timer.hpp"

#include <string>
#include <vector>
#include <map>

namespace OpenEngine {
namespace Resources {

using namespace std;

/**
 * OpenGL Shader Language resource.
 *
 * @class GLSLResource GLSLResource.h Resources/GLSLResource.h
 */
class GLSLResource : public IShaderResource {
private:
    class GLSLShader{
    public:
        GLSLShader() {};
        virtual void Load(GLSLResource& self) = 0;
		virtual void Unload() = 0;
        virtual void Apply(GLSLResource& self) = 0;
        virtual void Release() = 0;
        virtual void BindAttribute(int, string) = 0;
        virtual void VertexAttribute(int, Vector<3,float>) = 0;
		virtual int GetAttributeID(const string name)=0;
        virtual ~GLSLShader() {};
    };

    class GLSL14Resource : public GLSLShader{
    private:
        GLhandleARB programObject;
        void PrintProgramInfoLog(GLhandleARB program);
        GLhandleARB LoadShader(string, int);
        GLint GetUniLoc(GLhandleARB program, const GLchar *name);
    public:
        GLSL14Resource() : GLSLShader(), programObject(0) {}
        void Load(GLSLResource& self);
        void Unload();
        void Apply(GLSLResource& self);
        void Release();
        void BindAttribute(int, string);
        void VertexAttribute(int, Vector<3,float>);
		int GetAttributeID(const string name);
    };

    class GLSL20Resource : public GLSLShader{
    private:
        GLuint shaderProgram;
		string filename;
        void PrintShaderInfoLog(GLuint shader);
        void PrintProgramInfoLog(GLuint program);
        GLuint LoadShader(string, int);
        GLint GetUniLoc(GLuint program, const GLchar *name);
    public:
        GLSL20Resource() : GLSLShader(), shaderProgram(0) {}
        void Load(GLSLResource& self);
        void Unload();
        void Apply(GLSLResource& self);
        void Release();
        void BindAttribute(int, string);
        void VertexAttribute(int, Vector<3,float>);
		int GetAttributeID(const string name);
    };

private:
    
	GLSLShader* glslshader;
	string resource;
    string vertexShader;
    string fragmentShader;
    map<string, std::vector<float> > attributes;

    void LoadShaderResource(string resource);

	time_t timestamp; // timestamp for glsl file, used for automatic reload.
	time_t vertex_file_timestamp; // timestamp for glsl.vert file, used for automatic reload.
	time_t fragment_file_timestamp; // timestamp for glsl.frag file, used for automatic reload.
	boost::timer reload_timer; // timer, used to check modification of resource files every few seconds
public:
    GLSLResource();
    GLSLResource(string);
    ~GLSLResource();
	void Reload();
    void Load();
    void Unload();

    void ApplyShader();
    void ReleaseShader();
    void SetAttribute(string name, vector<float> value);
    void BindAttribute(int id, string name);
    void VertexAttribute(int id, Vector<3,float> vec);
	int GetAttributeID(const string name);
};

/**
 * OpenGL shader resource plug-in.
 *
 * @class GLSLPlugin GLSLResource.h Resources/GLSLResource.h
 */
class GLSLPlugin : public IShaderResourcePlugin {
public:
    IShaderResourcePtr CreateResource(string file);
    string GetExtension();
};

} //NS Resources
} //NS OpenEngine

#endif // _GLSL_RESOURCE_H_
