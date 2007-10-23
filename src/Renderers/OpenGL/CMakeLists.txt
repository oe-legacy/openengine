
# depends on the glew library
IF(GLEW_FOUND)

ADD_LIBRARY(OpenEngine_Renderers_OpenGL
	    Renderer.cpp
	    RenderingView.cpp
	    TextureLoader.cpp
	    ShaderLoader.cpp
	    )

TARGET_LINK_LIBRARIES(OpenEngine_Renderers_OpenGL
		      OpenEngine_Scene
		      OpenEngine_Geometry
			  OpenEngine_Renderers
		      ${OPENGL_LIBRARY}
		      ${GLEW_LIBRARIES})

ENDIF(GLEW_FOUND)