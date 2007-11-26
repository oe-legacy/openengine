// OpenGL Shader Language resource.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// Modified by Anders Bach Nielsen <abachn@daimi.au.dk> - 21. Nov 2007
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#define printinfo false
#include <Resources/GLSLResource.h>
#include <Resources/ResourceManager.h>
#include <Resources/File.h>
#include <Resources/ITextureResource.h>
#include <Resources/Exceptions.h>
#include <Resources/File.h>
#include <Renderers/OpenGL/Renderer.h>
#include <Logging/Logger.h>
#include "boost/filesystem/operations.hpp"
#include "boost/timer.hpp"
#include <fstream>

namespace OpenEngine {
namespace Resources {

using namespace boost::filesystem;
using namespace OpenEngine::Renderers::OpenGL;

/**
 * Prints the OpenGL errors if any to logger.
 * Used as: PrintOpenGLError(string(__FILE__),__LINE__);   
 */
void PrintOpenGLError(string filename, int linenumber) {
    if(!printinfo) {
        GLenum glErr;
        glErr = glGetError();
        while (glErr != GL_NO_ERROR) {
            logger.error << "glError: " << gluErrorString(glErr) << " in: ";
            logger.error << filename << ", line: " << linenumber << logger.end;
            glErr = glGetError();
        }
    }
}

GLSLPlugin::GLSLPlugin() {
    this->AddExtension("glsl");
}

IShaderResourcePtr GLSLPlugin::CreateResource(string file) {
    return IShaderResourcePtr(new GLSLResource(file));
}

/**
 * Create a new shader resource from a file path
 *
 * @param resource Path to shader resource.
 */
GLSLResource::GLSLResource(string resource) : glslshader(NULL), resource(resource) {}

/**
 * Shader destructor.
 * Unloads the resource.
 */
GLSLResource::~GLSLResource() {
    if (glslshader != NULL)
        Unload();
}

/**
 * Reload the shader resource.
 * Checks the last modification time and reloads the resource if
 * necessary.
 */
void GLSLResource::Reload() {
	time_t new_timestamp, new_vertex_file_timestamp, new_fragment_file_timestamp;
    string filename = "";
    try {
        filename = resource;
        new_timestamp = last_write_time(filename);
        filename = ResourceManager::FindFileInPath(vertexShader);
        new_vertex_file_timestamp = last_write_time(filename);
        filename = ResourceManager::FindFileInPath(fragmentShader);
        new_fragment_file_timestamp = last_write_time(filename);
    } catch (...) {
        throw ResourceException("Error taking time stamp from file: " + filename);
    }

	if (new_timestamp!=timestamp ||
        new_vertex_file_timestamp!=vertex_file_timestamp ||
        new_fragment_file_timestamp!=fragment_file_timestamp ) {
        Unload();
        Load();
        timestamp = new_timestamp;
        logger.info << "Reloading shader: " << resource << logger.end;
	}
}

/**
 * Load the shader resource.
 */
void GLSLResource::Load() {
    if (glslshader!=NULL) return;
    LoadShaderResource(resource);

	// create the correct shader instance and load it
    GLSLVersion glslversion = Renderer::GetGLSLVersion();
    if (glslversion == GLSL_14)
        glslshader = new GLSL14Resource();
    else if (glslversion == GLSL_20)
        glslshader = new GLSL20Resource();
    else
        return;
    glslshader->Load(*this);
}

/*
 * Setting the strings vertexShader and fragmentShader according to content
 * in the file "resource", and checks if these are empty.
 */
void GLSLResource::LoadShaderResource(string resource) {
    vertexShader.clear();
    fragmentShader.clear();
    attributes.clear();

    // load file
    ifstream* in = File::Open(resource);

    char buf[255];
    int line = 0;
    while (!in->eof()) {
        ++line;
        in->getline(buf, 255);
        string type = string(buf,5);
        // stuff to ignore
        if (type.empty() ||
            buf[0] == '#')
            continue;

        char file[255];
        // set the vertex shader
        if (type == "vert:") {
            if (!vertexShader.empty())
                logger.warning << "Line("<<line<<") Multiple vertex shaders is not supported." << logger.end;
            else if (sscanf(buf, "vert: %s", file) == 1)
                vertexShader = string(file);
            else
                logger.warning << "Line("<<line<<") Invalid vertex shader." << logger.end;
        } 
        // set the fragment shader
        else if (type == "frag:") {
            if (!fragmentShader.empty())
                logger.warning << "Line("<<line<<") Multiple fragment shaders is not supported." << logger.end;
            else if (sscanf(buf, "frag: %s", file) == 1)
                fragmentShader = string(file);
            else
                logger.warning << "Line("<<line<<") Invalid fragment shader." << logger.end;
        }
        // set a texture resource
        else if (type == "text:") {
            const int maxlength = 300;
            char fileandname[maxlength];
            if (sscanf(buf, "text: %s", fileandname) == 1) {
                int seperator=0;
                for(int i=0;i<maxlength;i++) {
                    if(fileandname[i]=='|')
                        seperator=i;
                    if(fileandname[i]=='\0')
                        break;
                }
                if(seperator==0) {
                    logger.error << "no separetor(|) between texture name and file, texture not loaded" << logger.end;
                    continue;
                }
                string texname = string(fileandname,seperator);
                string texfile = string(fileandname+seperator+1);
                ITextureResourcePtr t = ResourceManager::CreateTexture(texfile);
                if (t != NULL)
                    textures[texname] = t;
                else
                    logger.error << "and error occurred while loading the following shader texture: " << texfile << logger.end;
            } else
                logger.warning << "Line("<<line<<") Invalid texture resource: '" << file << "'" << logger.end;
        }
        // set an attribute
        else if (type == "attr:") {
            char  name[255];
            float attr[4];
            int n = sscanf(buf, "attr: %s = %f %f %f %f", name, &attr[0], &attr[1], &attr[2], &attr[3])
                    - 1;
			attributes[string(name)].clear();
            for (int i=0; i<n; ++i)
                attributes[string(name)].push_back(attr[i]);
        }
    }
    in->close();
    delete in;

    string filename = "";
    try {
        filename = resource;
        timestamp = last_write_time(filename);
        filename = ResourceManager::FindFileInPath(vertexShader);
        vertex_file_timestamp = last_write_time(filename);
        filename = ResourceManager::FindFileInPath(fragmentShader);
        fragment_file_timestamp = last_write_time(filename);
    } catch (...) {
        throw ResourceException("Error taking time stamp from file: " + filename);
    }
}

void GLSLResource::GLSL20Resource::Load(GLSLResource& self) {
    if( self.vertexShader.empty() && self.fragmentShader.empty() ) return; // nothing to load
    shaderProgram = glCreateProgram();

    // attach vertex shader
    if(!self.vertexShader.empty()) {
        if(printinfo)
            logger.info << "loading vertexshader: " << self.vertexShader << logger.end;
			GLuint shader = LoadShader(self.vertexShader, GL_VERTEX_SHADER);
        if(shader != 0)
            glAttachShader(shaderProgram, shader);
		else {
            logger.error << "failed loading vertexshader" << logger.end;
			Unload();
			return;
		}
    }
    // attach fragment shader
    if(!self.fragmentShader.empty()) {
        if(printinfo)
            logger.info << "loading fragmentshader: " << self.fragmentShader << logger.end;
        GLuint shader = LoadShader(self.fragmentShader, GL_FRAGMENT_SHADER);
        if(shader!=0)
            glAttachShader(shaderProgram, shader);
		else {
            logger.error << "failed loading fragmentshader" << logger.end;
			Unload();
			return;
		}
    }
    // Link the program object and print out the info log
    glLinkProgram(shaderProgram);
    GLint linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);

    PrintOpenGLError(string(__FILE__),__LINE__);  // Check for OpenGL errors
    PrintProgramInfoLog(shaderProgram);
    
    if(linked==0)
		logger.error << "could not link shader program" << logger.end;
    //textures are loaded by the ShaderLoader visitor
}

/*
 * A return of 0 indicates that the shader was not loaded
 */
GLuint GLSLResource::GLSL20Resource::LoadShader(string filename,int type) {
    // Load shader
    GLuint shader=glCreateShader(type);
    const GLchar* Shader= File::ReadShader<GLchar>(ResourceManager::FindFileInPath(filename));
    if (Shader==NULL) return 0;
    glShaderSource(shader, 1, &Shader, NULL);

    // Compile shader
    glCompileShader(shader);
    GLint  compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled==0) {
        logger.error << "failed compiling shader program: " << filename << logger.end;
		GLsizei bufsize;
		const int maxBufSize = 100;
		char buffer[maxBufSize];
		glGetShaderInfoLog(shader, maxBufSize, &bufsize, buffer);
		logger.error << "compile errors: " << buffer << logger.end;
		glDeleteShader(shader);
		return 0;
	}
    PrintShaderInfoLog(shader);
    return shader;
}

/**
 * a return of 0 indicates that the shader was not constructed
 */
GLhandleARB GLSLResource::GLSL14Resource::LoadShader(string filename, int type) {
    GLhandleARB handle = glCreateShaderObjectARB(type);
    const GLcharARB* str = File::ReadShader<GLcharARB>(ResourceManager::FindFileInPath(filename));

    GLint compiled = 0;
    glShaderSourceARB(handle, 1, &str, NULL);
    glCompileShaderARB(handle);
    glGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);
    if (compiled==0) {
        logger.error << "failed compiling shader program: " << filename << logger.end;
                GLcharARB* buffer = (GLcharARB*)malloc(compiled);
                GLsizei charsWritten = 0;
                glGetInfoLogARB(handle, compiled, &charsWritten, buffer);
                logger.error << "compile errors: " << string(buffer) << logger.end;
                glDeleteObjectARB(handle);
                return 0;
        }
    return handle;
}

void GLSLResource::GLSL14Resource::Load(GLSLResource& self) {
    programObject = glCreateProgramObjectARB();

    // attach vertex shader
    if (!self.vertexShader.empty()) {
        GLhandleARB vhandle = LoadShader(self.vertexShader,GL_VERTEX_SHADER_ARB);
        if (vhandle!=0) {
            if (printinfo)
                logger.info << "loading vertexshader: " << self.vertexShader << logger.end;
            glAttachObjectARB(programObject, vhandle);
            glDeleteObjectARB(vhandle);
        }
    }
    // attach fragment shader
    if (!self.fragmentShader.empty()) {
        if (printinfo)
            logger.info << "loading fragmentshader: " << self.fragmentShader << logger.end;
        GLhandleARB fhandle = LoadShader(self.fragmentShader,GL_FRAGMENT_SHADER_ARB);
        if (fhandle!=0) {
            glAttachObjectARB(programObject, fhandle);
            glDeleteObjectARB(fhandle);
        }
    }

    GLint linked = 0;
    glLinkProgramARB(programObject);
    glGetObjectParameterivARB(programObject, GL_OBJECT_LINK_STATUS_ARB, &linked);

    PrintOpenGLError(string(__FILE__),__LINE__);  // Check for OpenGL errors
    PrintProgramInfoLog(programObject);

    if (linked == 0) {
        glDeleteObjectARB(programObject);
        programObject = 0;
        logger.error << "failed linking shader" << logger.end;
    }
    //textures are loaded by the ShaderLoader visitor
}

void GLSLResource::Unload() {
    if (glslshader == NULL) return;
    glslshader->Unload();
    delete glslshader;
    glslshader = NULL;
}

void GLSLResource::GLSL20Resource::Unload() {
    glDeleteShader(shaderProgram);
	shaderProgram = 0;
}

void GLSLResource::GLSL14Resource::Unload() {
    glDeleteObjectARB(programObject);
	programObject = 0;
}

void GLSLResource::ApplyShader() {
	if (reload_timer.elapsed() > 2) {
	    this->Reload();
		reload_timer.restart();
	}
	if (glslshader != NULL)
        glslshader->Apply(*this);
}

void GLSLResource::GLSL20Resource::Apply(GLSLResource& self) {
    if (shaderProgram == 0) return;

    // Install program object as part of current state
    glUseProgram(shaderProgram);

    // Set up initial uniform values
    map<string,vector<float> >::iterator itr = self.attributes.begin();
    while (itr != self.attributes.end()) {
        string attribute = (*itr).first;
        vector<float> vec = (*itr).second;
        switch (vec.size()) {
        case 2:
            glUniform2f(GetUniLoc(shaderProgram, attribute.c_str()), vec[0], vec[1] );
            break;
        case 3:
            glUniform3f(GetUniLoc(shaderProgram, attribute.c_str()), vec[0], vec[1],vec[2]);
            break;
        default:
            logger.error << "Unsupported number of attributes: " << vec.size() << logger.end;
            break;
        }
        itr++;
    }
    //Setup uniform textures
    int counter=0;
    ShaderTextureMap::const_iterator itr2 = self.textures.begin();
    while( itr2 != self.textures.end() ){
        string texname = (*itr2).first;
        ITextureResourcePtr texture = (*itr2).second;
        glActiveTexture(GL_TEXTURE0 + counter);
        glBindTexture(GL_TEXTURE_2D, texture->GetID() );
        glUniform1i(GetUniLoc(shaderProgram, texname.c_str()),counter); // Bind texture to TU = counter
        counter++;
        itr2++;
    }
    glActiveTexture(GL_TEXTURE0);//reset active texture
}

void GLSLResource::GLSL14Resource::Apply(GLSLResource& self) {
    if (programObject == 0) return;

    // Install program object as part of current state
    glUseProgramObjectARB(programObject);
    
	// Set up initial uniform values
    map<string,vector<float> >::iterator itr = self.attributes.begin();
    while (itr != self.attributes.end()) {
        string attribute = (*itr).first;
        vector<float> vec = (*itr).second;
        switch (vec.size()) {
        case 2:
            glUniform2fARB(GetUniLoc(programObject, attribute.c_str()), vec[0], vec[1]);
            break;
        case 3:
            glUniform3fARB(GetUniLoc(programObject, attribute.c_str()), vec[0], vec[1], vec[2]);
            break;
        default:
            logger.error << "unsupported number of attributes: " << vec.size() << logger.end;
            break;
        }
        itr++;
    }
    //Setup uniform textures
    int counter=0;
    ShaderTextureMap::const_iterator itr2 = self.textures.begin();
    while( itr2 != self.textures.end() ){
        string texname = (*itr2).first;
        ITextureResourcePtr texture = (*itr2).second;
        glActiveTextureARB(GL_TEXTURE0_ARB + counter);
        glBindTexture(GL_TEXTURE_2D, texture->GetID() );
        glUniform1iARB(GetUniLoc(programObject, texname.c_str()),counter); // Bind texture to TU = counter
        counter++;
        itr2++;
    }
    glActiveTextureARB(GL_TEXTURE0_ARB);//reset active texture
}

void GLSLResource::GLSL14Resource::PrintProgramInfoLog(GLhandleARB program) {
    if(!printinfo) return;
    GLint infologLength = 0, charsWritten = 0;
    GLcharARB* infoLog;
    glGetObjectParameterivARB(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);
    if (infologLength > 0) {
        infoLog = (GLcharARB*)malloc(infologLength);
        if (infoLog==NULL) {
            logger.error << "Could not allocate InfoLog buffer" << logger.end;
            exit(1);
        }
        glGetInfoLogARB(program, infologLength, &charsWritten, infoLog);
        logger.info << "Shader InfoLog:\n \"" << infoLog << "\"" << logger.end;
        free(infoLog);
    }
}

void GLSLResource::GLSL20Resource::PrintProgramInfoLog(GLuint program) {
    if(!printinfo) return;
    GLint infologLength = 0, charsWritten = 0;
    GLchar* infoLog;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0) {
        infoLog = (GLchar *)malloc(infologLength);
        if (infoLog==NULL) {
            logger.error << "Could not allocate InfoLog buffer" << logger.end;
            return;
        }
        glGetProgramInfoLog(program, infologLength, &charsWritten, infoLog);
        logger.info << "Program InfoLog:\n \"" << infoLog << "\"" << logger.end;
        free(infoLog);
    }
}

void GLSLResource::GLSL20Resource::PrintShaderInfoLog(GLuint shader) {
    if(!printinfo) return;
    GLint infologLength = 0, charsWritten = 0;
    GLchar *infoLog;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0) {
        infoLog = (GLchar *)malloc(infologLength);
        if (infoLog==NULL) {
            logger.error << "Could not allocate InfoLog buffer" << logger.end;
            exit(1);
        }
        glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
        logger.info << "Shader InfoLog:\n \"" << infoLog << "\"" << logger.end;
        free(infoLog);
    }
}

void GLSLResource::SetAttribute(string str, vector<float> vec) {
    attributes[str] = vec;
}

void GLSLResource::BindAttribute(int id, string name) {
    if(glslshader==NULL) return;
    glslshader->BindAttribute(id,name);
}

void GLSLResource::GLSL14Resource::BindAttribute(int id, string name) {
    if (programObject==0) return;
    glBindAttribLocationARB(programObject, id, name.c_str());
}

void GLSLResource::GLSL20Resource::BindAttribute(int id, string name) {
    if (shaderProgram==0) return;
    glBindAttribLocation(shaderProgram, id, name.c_str());
}

void GLSLResource::VertexAttribute(int id, Vector<3,float> vec) {
    if(glslshader==NULL) return;
    glslshader->VertexAttribute(id,vec);
}

void GLSLResource::GLSL14Resource::VertexAttribute(int id, Vector<3,float> vec) {
    if (programObject==0) return;
    glVertexAttrib3fARB(id, vec[0], vec[1], vec[2]);
}

void GLSLResource::GLSL20Resource::VertexAttribute(int id, Vector<3,float> vec) {
    if (shaderProgram==0) return;
    glVertexAttrib3f(id, vec[0], vec[1], vec[2]);
}

void GLSLResource::ReleaseShader() {
    if(glslshader==NULL) return;
    glslshader->Release();
}

void GLSLResource::GLSL14Resource::Release() {
    if (programObject==0) return;
    glUseProgramObjectARB(0);
}

void GLSLResource::GLSL20Resource::Release() {
    if (shaderProgram==0) return;
    glUseProgram(0);
}

GLint GLSLResource::GLSL14Resource::GetUniLoc(GLhandleARB program, const GLchar *name){
    GLint loc = glGetUniformLocationARB(program, name);
    if (loc == -1)
        logger.error << "No such uniform named \"" << name << "\"" << logger.end;
    return loc;
}

GLint GLSLResource::GLSL20Resource::GetUniLoc(GLuint program, const GLchar *name){
    GLint loc = glGetUniformLocation(program, name);
    if (loc == -1)
        logger.error << "No such uniform named \"" << name << "\"" << logger.end;
    return loc;
}

/*
 * A return of -1 indicates that the attribute was not found
 */
int GLSLResource::GetAttributeID(const string name) {
    if(glslshader==NULL) return -1;
	return glslshader->GetAttributeID(name);
}

/*
 * A return of -1 indicates that the attribute was not found
 */
int GLSLResource::GLSL14Resource::GetAttributeID(const string name) {
    if (programObject==0) return -1;
	return glGetAttribLocationARB(programObject,name.c_str());
}

/*
 * A return of -1 indicates that the attribute was not found
 */
int GLSLResource::GLSL20Resource::GetAttributeID(const string name) {
    if (shaderProgram==0) return -1;
	return glGetAttribLocation(shaderProgram,name.c_str());
}

} //NS Loaders
} //NS Open Engine
