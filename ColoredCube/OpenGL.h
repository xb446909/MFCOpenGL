#pragma once

#define	GLEW_STATIC		1

#include "../GL/include/glew.h"
#include <gl/GLU.h>
#include "../common/shader.hpp"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

using namespace glm;

class COpenGL
{
public:
	COpenGL(HDC hDC = NULL);
	~COpenGL();

	BOOL init();
	void SetHDC(HDC hDC);
	void RenderScene();
	void SetSize(int nWidth, int nHeight);
private:
	HDC m_hDC;
	mat4 m_MVP;
	GLuint m_matrixID;
	GLuint m_programID;
	GLuint m_vertexArrayID;
	GLuint m_vertexbuffer;

	BOOL SetupPixelFormat(HDC hDC);
};

