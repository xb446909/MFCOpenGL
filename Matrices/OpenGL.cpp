#include "stdafx.h"
#include "OpenGL.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "../GL/lib/glew32s.lib")

COpenGL::COpenGL(HDC hDC)
	: m_hDC(hDC)
{
}

COpenGL::~COpenGL()
{
	glDeleteBuffers(1, &m_vertexbuffer);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);

	HGLRC hrc = wglGetCurrentContext();
	if (wglMakeCurrent(0, 0) == FALSE)
	{
		OutputDebugString(_T("Could not make RC non-current\r\n"));
	}

	if (hrc)
	{
		if (::wglDeleteContext(hrc) == FALSE)
		{
			OutputDebugString(_T("Could not delete RC\r\n"));
		}
	}
}

BOOL COpenGL::init()
{
	ASSERT(m_hDC != NULL);

	if (!SetupPixelFormat(m_hDC)) return FALSE;

	PIXELFORMATDESCRIPTOR pfd;

	int iPixelFormat = GetPixelFormat(m_hDC);

	DescribePixelFormat(m_hDC, iPixelFormat,
		sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	HGLRC  hglrc = wglCreateContext(m_hDC);
	if (!hglrc) return FALSE;
	if (!wglMakeCurrent(m_hDC, hglrc)) return FALSE;

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		OutputDebugString(_T("Failed to initialize GLEW\r\n"));
		return FALSE;
	}

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("SimpleTransform.vertexshader", "SingleColor.fragmentshader");

	// Get a handle for our "MVP" uniform
	m_matrixID = glGetUniformLocation(m_programID, "MVP");

	mat4 projection = perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	mat4 view = lookAt(
		glm::vec3(3, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	mat4 model = mat4(1.0f);
	m_MVP = projection * view * model;
	static const GLfloat g_vertex_buffer_data[] = {
		-0.9f, -0.9f, 0.0f,
		0.85f, -0.9f, 0.0f,
		-0.9f,  0.85f, 0.0f,
		0.9f, -0.85f, 0.0f,
		0.9f, 0.9f, 0.0f,
		-0.85f, 0.9f, 0.0f,
	};

	glGenBuffers(1, &m_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	return TRUE;
}

void COpenGL::SetHDC(HDC hDC)
{
	m_hDC = hDC;
}

void COpenGL::RenderScene()
{
	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//清除颜色缓冲区和深度缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_programID);

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

	SwapBuffers(wglGetCurrentDC());
}

void COpenGL::SetSize(int nWidth, int nHeight)
{
	if (nHeight == 0)
	{
		nHeight = 1;
	}
	glViewport(0, 0, nWidth, nHeight);
}

BOOL COpenGL::SetupPixelFormat(HDC hDC)
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd 
		1,                     // version number 
		PFD_DRAW_TO_WINDOW |   // support window 
		PFD_SUPPORT_OPENGL |   // support OpenGL 
		PFD_DOUBLEBUFFER,      // double buffered 
		PFD_TYPE_RGBA,         // RGBA type 
		24,                    // 24-bit color depth 
		0, 0, 0, 0, 0, 0,      // color bits ignored 
		0,                     // no alpha buffer 
		0,                     // shift bit ignored 
		0,                     // no accumulation buffer 
		0, 0, 0, 0,            // accum bits ignored 
		32,                    // 32-bit z-buffer 
		0,                     // no stencil buffer 
		0,                     // no auxiliary buffer 
		PFD_MAIN_PLANE,        // main layer 
		0,                     // reserved 
		0, 0, 0                // layer masks ignored 
	};
	int  iPixelFormat;

	// get the best available match of pixel format for the device context  
	if ((iPixelFormat = ChoosePixelFormat(hDC, &pfd)) == 0) return FALSE;
	if (!SetPixelFormat(hDC, iPixelFormat, &pfd)) return FALSE;
	return TRUE;
}
