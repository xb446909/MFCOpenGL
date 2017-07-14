#include "stdafx.h"
#include "OpenGL.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "../GL/lib/glew32s.lib")

COpenGL::COpenGL()
	: m_validModelviewMatrix(false)
	, m_validProjectionMatrix(false)
	, m_verticalRotationLocked(false)
	, m_bubbleViewModeEnabled(false)
{
}


COpenGL::~COpenGL()
{
	glDeleteBuffers(1, &m_vertexbuffer);
	glDeleteBuffers(1, &m_uvbuffer);
	glDeleteTextures(1, &m_texture);
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


void COpenGL::OutputString(char * fmt, ...)
{
	char szOutput[2048] = { 0 };
	va_list args;
	va_start(args, fmt);
	vsprintf_s(szOutput, 2048, fmt, args);
	va_end(args);
	OutputDebugStringA(szOutput);
}

BEGIN_MESSAGE_MAP(COpenGL, CView)
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_SIZE()
ON_WM_ERASEBKGND()
ON_WM_MOUSEMOVE()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


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

	m_vecCamera = vec3(4, 0, 0);
	m_vecView = vec3(0, 0, 0);
	m_vecHead = vec3(0, 0, 1);

	m_ratio = 1;
	m_width = 1;
	m_height = 1;
	m_vecTranslate = vec3(0.0f);

	m_vecAxisY = vec3(0, 1, 0);
	m_vecAxisZ = m_vecCamera - m_vecView;
	m_vecAxisX = cross(m_vecAxisY, m_vecAxisZ);
	m_vecAxisX = normalize(m_vecAxisX);

	m_view = lookAt(
		m_vecCamera, // Camera is at (4,3,3), in World Space
		m_vecView, // and looks at the origin
		m_vecHead  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Get a handle for our "MVP" uniform
	m_matrixID = glGetUniformLocation(m_programID, "MVP");

	m_textureID = glGetUniformLocation(m_programID, "myTextureSampler");

	//m_texture = loadBMP_custom("uvtemplate.bmp");
	m_texture = loadDDS("uvtemplate.DDS");

	static const GLfloat g_vertex_buffer_data[] =
	{
		0.0f, 0.0f, 0.0f,
		2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 2.0f,
		//-1.0f, 1.0f, -1.0f,
		//-1.0f, -1.0f, -1.0f,
		//1.0f,  -1.0f, -1.0f,
		//-1.0f, 1.0f, -1.0f,
		//1.0f, 1.0f, -1.0f,
		//1.0f, -1.0f, -1.0f,

		//-1.0f, 1.0f, 1.0f,
		//-1.0f, -1.0f, 1.0f,
		//1.0f,  -1.0f, 1.0f,
		//-1.0f, 1.0f, 1.0f,
		//1.0f, 1.0f, 1.0f,
		//1.0f, -1.0f, 1.0f,

		//-1.0f, 1.0f, -1.0f,
		//-1.0f, -1.0f, -1.0f,
		//-1.0f, -1.0f, 1.0f,
		//-1.0f, 1.0f, -1.0f,
		//-1.0f, 1.0f, 1.0f,
		//-1.0f, -1.0f, 1.0f,

		//1.0f, 1.0f, -1.0f,
		//1.0f, -1.0f, -1.0f,
		//1.0f, -1.0f, 1.0f,
		//1.0f, 1.0f, -1.0f,
		//1.0f, 1.0f, 1.0f,
		//1.0f, -1.0f, 1.0f,

		//-1.0f, -1.0f, 1.0f,
		//-1.0f, -1.0f, -1.0f,
		//1.0f,  -1.0f, -1.0f,
		//-1.0f, -1.0f, 1.0f,
		//1.0f, -1.0f, 1.0f,
		//1.0f, -1.0f, -1.0f,

		//-1.0f, 1.0f, 1.0f,
		//-1.0f, 1.0f, -1.0f,
		//1.0f,  1.0f, -1.0f,
		//-1.0f, 1.0f, 1.0f,
		//1.0f, 1.0f, 1.0f,
		//1.0f, 1.0f, -1.0f

		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	// Two UV coordinatesfor each vertex. They were created withe Blender.
	static const GLfloat g_uv_buffer_data[] = {
		0.1f, 0.1f,
		0.1f, 0.1f,
		0.2f, 0.2f,
		0.2f, 0.2f,
		0.3f, 0.3f,
		0.3f, 0.3f,


		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	glGenBuffers(1, &m_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glLineWidth(3.0f);

	return TRUE;
}

void COpenGL::SetHDC(HDC hDC)
{
	m_hDC = hDC;
}

void COpenGL::RenderScene()
{
	// Dark blue background
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	//清除颜色缓冲区和深度缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_programID);

	// Send our transformation to the currently bound shader, 

	//m_projection = perspective(45.0f, m_width / m_height, 1.0f, 15.0f);
	if (m_width <= m_height)
		m_projection = ortho(-2.0f, 2.0f, -2.0f * (GLfloat)m_height / (GLfloat)m_width, 2.0f * (GLfloat)m_height / (GLfloat)m_width, 0.1f, 200.0f);
	else
		m_projection = ortho(-2.0f * (GLfloat)m_width / (GLfloat)m_height, 2.0f * (GLfloat)m_width / (GLfloat)m_height, -2.0f, 2.0f, 0.1f, 200.0f);
	m_view = lookAt(
		m_vecCamera, // Camera is at (4,3,3), in World Space
		m_vecView, // and looks at the origin
		m_vecHead  // Head is up (set to 0,-1,0 to look upside-down)
	);
	mat4 model = mat4(1.0f);

	//model = translate(model, m_vecTranslate);
	model = scale(model, vec3(m_ratio));

	m_MVP = m_projection * m_view * model;

	// in the "MVP" uniform
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_MVP[0][0]);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(m_textureID, 0);

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

	// 2nd attribute buffer : vertices
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvbuffer);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 6, 36); // 3 indices starting at 0 -> 1 triangle
	glDrawArrays(GL_LINES, 0, 6); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	SwapBuffers(wglGetCurrentDC());
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

bool COpenGL::InvertMatrix(const mat4& m, mat4& out)
{
	float wtmp[4][8];
	float m0, m1, m2, m3, s;
	float *r0, *r1, *r2, *r3;
	r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

	r0[0] = m[0][0], r0[1] = m[0][1],
		r0[2] = m[0][2], r0[3] = m[0][3],
		r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
		r1[0] = m[1][0], r1[1] = m[1][1],
		r1[2] = m[1][2], r1[3] = m[1][3],
		r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
		r2[0] = m[2][0], r2[1] = m[2][1],
		r2[2] = m[2][2], r2[3] = m[2][3],
		r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
		r3[0] = m[3][0], r3[1] = m[3][1],
		r3[2] = m[3][2], r3[3] = m[3][3],
		r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

	//choose pivot - or die
	if (std::abs(r3[0]) > std::abs(r2[0]))
	{
		float* r = r3;
		r3 = r2;
		r2 = r;
	}
	if (std::abs(r2[0]) > std::abs(r1[0]))
	{
		float* r = r2;
		r2 = r1;
		r1 = r;
	}
	if (std::abs(r1[0]) > std::abs(r0[0]))
	{
		float* r = r1;
		r1 = r0;
		r0 = r;
	}
	if (0.0 == r0[0])
		return false;

	//eliminate first variable
	m1 = r1[0] / r0[0];
	m2 = r2[0] / r0[0];
	m3 = r3[0] / r0[0];
	s = r0[1];
	r1[1] -= m1 * s;
	r2[1] -= m2 * s;
	r3[1] -= m3 * s;
	s = r0[2];
	r1[2] -= m1 * s;
	r2[2] -= m2 * s;
	r3[2] -= m3 * s;
	s = r0[3];
	r1[3] -= m1 * s;
	r2[3] -= m2 * s;
	r3[3] -= m3 * s;
	s = r0[4];
	if (s != 0.0)
	{
		r1[4] -= m1 * s;
		r2[4] -= m2 * s;
		r3[4] -= m3 * s;
	}
	s = r0[5];
	if (s != 0.0)
	{
		r1[5] -= m1 * s;
		r2[5] -= m2 * s;
		r3[5] -= m3 * s;
	}
	s = r0[6];
	if (s != 0.0)
	{
		r1[6] -= m1 * s;
		r2[6] -= m2 * s;
		r3[6] -= m3 * s;
	}
	s = r0[7];
	if (s != 0.0)
	{
		r1[7] -= m1 * s;
		r2[7] -= m2 * s;
		r3[7] -= m3 * s;
	}

	//choose pivot - or die
	if (std::abs(r3[1]) > std::abs(r2[1]))
	{
		float* r = r3;
		r3 = r2;
		r2 = r;
	}
	if (std::abs(r2[1]) > std::abs(r1[1]))
	{
		float* r = r2;
		r2 = r1;
		r1 = r;
	}
	if (0.0 == r1[1])
		return false;

	//eliminate second variable
	m2 = r2[1] / r1[1];
	m3 = r3[1] / r1[1];
	r2[2] -= m2 * r1[2];
	r3[2] -= m3 * r1[2];
	r2[3] -= m2 * r1[3];
	r3[3] -= m3 * r1[3];
	s = r1[4];
	if (0.0 != s)
	{
		r2[4] -= m2 * s;
		r3[4] -= m3 * s;
	}
	s = r1[5];
	if (0.0 != s)
	{
		r2[5] -= m2 * s;
		r3[5] -= m3 * s;
	}
	s = r1[6];
	if (0.0 != s)
	{
		r2[6] -= m2 * s;
		r3[6] -= m3 * s;
	}
	s = r1[7];
	if (0.0 != s)
	{
		r2[7] -= m2 * s;
		r3[7] -= m3 * s;
	}

	//choose pivot - or die
	if (std::abs(r3[2]) > std::abs(r2[2]))
	{
		float* r = r3;
		r3 = r2;
		r2 = r;
	}
	if (0.0 == r2[2])
		return false;

	//eliminate third variable
	m3 = r3[2] / r2[2];
	r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
		r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];

	//last check
	if (0.0 == r3[3])
		return false;

	s = 1.0 / r3[3]; //now back substitute row 3
	r3[4] *= s;
	r3[5] *= s;
	r3[6] *= s;
	r3[7] *= s;
	m2 = r2[3]; //now back substitute row 2
	s = 1.0 / r2[2];
	r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
		r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
	m1 = r1[3];
	r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
		r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
	m0 = r0[3];
	r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
		r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
	m1 = r1[2]; //now back substitute row 1
	s = 1.0 / r1[1];
	r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
		r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
	m0 = r0[2];
	r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
		r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
	m0 = r0[1]; //now back substitute row 0
	s = 1.0 / r0[0];
	r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
		r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

	out[0][0] = r0[4];
	out[0][1] = r0[5], out[0][2] = r0[6];
	out[0][3] = r0[7], out[1][0] = r1[4];
	out[1][1] = r1[5], out[1][2] = r1[6];
	out[1][3] = r1[7], out[2][0] = r2[4];
	out[2][1] = r2[5], out[2][2] = r2[6];
	out[2][3] = r2[7], out[3][0] = r3[4];
	out[3][1] = r3[5], out[3][2] = r3[6];
	out[3][3] = r3[7];

	return true;
}

bool COpenGL::Unproject(const vec3& input2D, const mat4& modelview, const mat4& projection, const int* viewport, vec3& output3D)
{
	//compute projection x modelview
	mat4 A = projection * modelview;
	mat4 m;

	if (!InvertMatrix(A, m))
	{
		return false;
	}

	mat4 mA = m * A;

	//Transformation of normalized coordinates between -1 and 1
	vec4 in;
	in.x = static_cast<float>((input2D.x - static_cast<float>(viewport[0])) / viewport[2] * 2 - 1);
	in.y = static_cast<float>((input2D.y - static_cast<float>(viewport[1])) / viewport[3] * 2 - 1);
	in.z = static_cast<float>(2 * input2D.z - 1);
	in.w = 1;

	//Objects coordinates
	vec4 out = m * in;
	if (out.w == 0)
	{
		return false;
	}

	output3D = vec3(out[0], out[1], out[2]) / out.w;

	return true;
}

bool COpenGL::Project(const vec3& input3D, const mat4& modelview, const mat4& projection, const int* viewport, vec3& output2D)
{
	//Modelview transform
	vec4 Pm;
	{
		Pm.x = static_cast<float>(modelview[0][0] * input3D.x + modelview[0][1] * input3D.y + modelview[0][2] * input3D.z + modelview[0][3]);
		Pm.y = static_cast<float>(modelview[1][0] * input3D.x + modelview[1][1] * input3D.y + modelview[1][2] * input3D.z + modelview[1][3]);
		Pm.z = static_cast<float>(modelview[2][0] * input3D.x + modelview[2][1] * input3D.y + modelview[2][2] * input3D.z + modelview[2][3]);
		Pm.w = static_cast<float>(modelview[3][0] * input3D.x + modelview[3][1] * input3D.y + modelview[3][2] * input3D.z + modelview[3][3]);
	};

	//Projection transform
	vec4 Pp;
	{
		Pp.x = static_cast<float>(projection[0][0] * Pm.x + projection[0][1] * Pm.y + projection[0][2] * Pm.z + projection[0][3] * Pm.w);
		Pp.y = static_cast<float>(projection[1][0] * Pm.x + projection[1][1] * Pm.y + projection[1][2] * Pm.z + projection[1][3] * Pm.w);
		Pp.z = static_cast<float>(projection[2][0] * Pm.x + projection[2][1] * Pm.y + projection[2][2] * Pm.z + projection[2][3] * Pm.w);
		Pp.w = static_cast<float>(projection[3][0] * Pm.x + projection[3][1] * Pm.y + projection[3][2] * Pm.z + projection[3][3] * Pm.w);
	};

	//The result normalizes between -1 and 1
	if (Pp.w == 0.0)
	{
		return false;
	}
	//Perspective division
	Pp.x /= Pp.w;
	Pp.y /= Pp.w;
	Pp.z /= Pp.w;
	//Window coordinates
	//Map x, y to range 0-1
	output2D.x = (1.0 + Pp.x) / 2 * viewport[2] + viewport[0];
	output2D.y = (1.0 + Pp.y) / 2 * viewport[3] + viewport[1];
	//This is only correct when glDepthRange(0.0, 1.0)
	output2D.z = (1.0 + Pp.z) / 2;	//Between 0 and 1

	return true;
}

vec3 COpenGL::convertMousePositionToOrientation(int x, int y)
{
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 557;
	rect.right = rect.left + 711;
	float xc = static_cast<double>(rect.Width() / 2);
	float yc = static_cast<double>(rect.Height() / 2);
	m_glViewport = rect;

	OutputString("xc: %d, yc: %d\r\n", rect.Width(), rect.Height());

	vec3 Q2D;
	if (m_viewportParams.objectCenteredView)
	{
		//project the current pivot point on screen
		CameraParam camera;
		getGLCameraParameters(camera);

		if (!camera.project(m_viewportParams.pivotPoint, Q2D))
		{
			//arbitrary direction
			return vec3(0, 0, 1);
		}
		OutputString("%f %f\r\n", Q2D.x, Q2D.y);
		//we set the virtual rotation pivot closer to the actual one (but we always stay in the central part of the screen!)
		Q2D.x = min<GLfloat>(Q2D.x, 3 * rect.Width() / 4);
		Q2D.x = max<GLfloat>(Q2D.x, rect.Width() / 4);

		Q2D.y = min<GLfloat>(Q2D.y, 3 * rect.Height() / 4);
		Q2D.y = max<GLfloat>(Q2D.y, rect.Height() / 4);


	}
	else
	{
		Q2D.x = static_cast<GLfloat>(xc);
		Q2D.y = static_cast<GLfloat>(yc);
	}

	//invert y
	y = rect.Height() - 1 - y;

	vec3 v(x - Q2D.x, y - Q2D.y, 0);

	v.x = max<float>(min<float>(v.x / xc, 1), -1);
	v.y = max<float>(min<float>(v.y / yc, 1), -1);

	if (m_verticalRotationLocked || m_bubbleViewModeEnabled)
	{
		v.y = 0;
	}

	//square 'radius'
	double d2 = v.x*v.x + v.y*v.y;

	//projection on the unit sphere
	if (d2 > 1)
	{
		double d = sqrt(d2);
		v.x /= d;
		v.y /= d;
	}
	else
	{
		v.z = sqrt(1.0 - d2);
	}

	return v;
}

vec3 COpenGL::getRealCameraCenter() const
{
	//the camera center is always defined in perspective mode
	OutputString("m_viewportParams.perspectiveView = %d\r\n", m_viewportParams.perspectiveView);
	if (m_viewportParams.perspectiveView)
	{
		return m_viewportParams.cameraCenter;
	}

	//in orthographic mode, we put the camera at the center of the
	//visible objects (along the viewing direction)

	//Add later
	//ccBBox box;
	//getVisibleObjectsBB(box);

	//return vec3(m_viewportParams.cameraCenter.x,
	//	m_viewportParams.cameraCenter.y,
	//	box.isValid() ? box.getCenter().z : 0);
	OutputString("%f %f\r\n", m_viewportParams.cameraCenter.x, m_viewportParams.cameraCenter.y);
	return vec3(m_viewportParams.cameraCenter.x,
		m_viewportParams.cameraCenter.y,
		0);
}


mat4 COpenGL::computeModelViewMatrix(const vec3& cameraCenter) const
{
	mat4 viewMatd;
	viewMatd[0][0] = viewMatd[1][1] = viewMatd[2][2] = viewMatd[3][3] = 1.0f;

	//apply current camera parameters (see trunk/doc/rendering_pipeline.doc)
	if (m_viewportParams.objectCenteredView)
	{
		//place origin on pivot point
		//viewMatd.setTranslation(/*viewMatd.getTranslationAsVec3D()*/ -m_viewportParams.pivotPoint);
		viewMatd[3] = vec4(-m_viewportParams.pivotPoint, 1.0f);

		//rotation (viewMat is simply a rotation matrix around the pivot here!)
		viewMatd = m_viewportParams.viewMat * viewMatd;

		//go back to initial origin
		//then place origin on camera center
		//viewMatd.setTranslation(viewMatd.getTranslationAsVec3D() + m_viewportParams.pivotPoint - cameraCenter);
		vec3 translation = vec3(viewMatd[3].x, viewMatd[3].y, viewMatd[3].z);
		viewMatd[3] = vec4(translation + m_viewportParams.pivotPoint - cameraCenter, 1.0f);
	}
	else
	{
		//place origin on camera center
		//viewMatd.setTranslation(/*viewMatd.getTranslationAsVec3D()*/ -cameraCenter);
		viewMatd[3] = vec4(-cameraCenter, 1.0f);

		//rotation (viewMat is the rotation around the camera center here - no pivot)
		viewMatd = m_viewportParams.viewMat * viewMatd;
	}

	mat4 scaleMatd;
	scaleMatd[0][0] = scaleMatd[1][1] = scaleMatd[2][2] = scaleMatd[3][3] = 1.0f;
	if (m_viewportParams.perspectiveView) //perspective mode
	{
		//for proper aspect ratio handling
		if (m_glViewport.Height() != 0)
		{
			float ar = m_glViewport.Width() / (m_glViewport.Height() * m_viewportParams.perspectiveAspectRatio);
			if (ar < 1.0f)
			{
				//glScalef(ar, ar, 1.0);
				scaleMatd[0][0] = ar;
				scaleMatd[1][1] = ar;
			}
		}
	}
	else //ortho. mode
	{
		//apply zoom
		float totalZoom = m_viewportParams.zoom / m_viewportParams.pixelSize;
		//glScalef(totalZoom,totalZoom,totalZoom);
		scaleMatd[0][0] = totalZoom;
		scaleMatd[1][1] = totalZoom;
		scaleMatd[2][2] = totalZoom;
	}

	return scaleMatd * viewMatd;
}

mat4 COpenGL::computeProjectionMatrix(const vec3 & cameraCenter, bool withGLfeatures, ProjectionMetrics * metrics, double * eyeOffset) const
{
#if 0
	double bbHalfDiag = 1.0;
	CCVector3d bbCenter(0, 0, 0);

	//compute center of visible objects constellation
	if (m_globalDBRoot || m_winDBRoot)
	{
		//get whole bounding-box
		ccBBox box;
		getVisibleObjectsBB(box);
		if (box.isValid())
		{
			//get bbox center
			bbCenter = CCVector3d::fromArray(box.getCenter().u);
			//get half bbox diagonal length
			bbHalfDiag = box.getDiagNormd() / 2;
		}
	}

	if (metrics)
	{
		metrics->bbHalfDiag = bbHalfDiag;
		metrics->cameraToBBCenterDist = (cameraCenter - bbCenter).normd();
	}

	//virtual pivot point (i.e. to handle viewer-based mode smoothly)
	CCVector3d pivotPoint = (m_viewportParams.objectCenteredView ? m_viewportParams.pivotPoint : cameraCenter);

	//distance between the camera center and the pivot point
	//warning: in orthographic mode it's important to get the 'real' camera center
	//(i.e. with z == bbCenter(z) and not z == anything)
	//otherwise we (sometimes largely) overestimate the distance between the camera center
	//and the displayed objects if the camera has been shifted in the Z direction (e.g. after
	//switching from perspective to ortho. view).
	//While the user won't see the difference this has a great influence on GL filters
	//(as normalized depth map values depend on it)
	double CP = (cameraCenter - pivotPoint).norm();

	//distance between the pivot point and DB farthest point
	double MP = (bbCenter - pivotPoint).norm() + bbHalfDiag;

	//pivot symbol should always be visible in object-based mode (if enabled)
	if (m_pivotSymbolShown && m_pivotVisibility != PIVOT_HIDE && withGLfeatures && m_viewportParams.objectCenteredView)
	{
		double pivotActualRadius = CC_DISPLAYED_PIVOT_RADIUS_PERCENT * std::min(m_glViewport.width(), m_glViewport.height()) / 2;
		double pivotSymbolScale = pivotActualRadius * computeActualPixelSize();
		MP = std::max<double>(MP, pivotSymbolScale);
	}
	MP *= 1.01; //for round-off issues

	if (withGLfeatures && m_customLightEnabled)
	{
		//distance from custom light to pivot point
		double distToCustomLight = (pivotPoint - CCVector3d::fromArray(m_customLightPos)).norm();
		MP = std::max<double>(MP, distToCustomLight);
	}

	if (m_viewportParams.perspectiveView)
	{
		//we deduce zNear et zFar
		//DGM: the 'zNearCoef' must not be too small, otherwise the loss in accuracy
		//for the detph buffer is too high and the display is jeopardized, especially
		//for entities with big coordinates)
		//double zNear = MP * m_viewportParams.zNearCoef;
		//DGM: what was the purpose of this?!
		//if (m_viewportParams.objectCenteredView)
		//	zNear = std::max<double>(CP-MP, zNear);
		double zFar = std::max(CP + MP, 1.0);
		double zNear = zFar * m_viewportParams.zNearCoef;

		if (metrics)
		{
			metrics->zNear = zNear;
			metrics->zFar = zFar;
		}

		//compute the aspect ratio
		double ar = static_cast<double>(m_glViewport.width()) / m_glViewport.height();

		float currentFov_deg = getFov();

		//DGM: take now 'frustumAsymmetry' into account (for stereo rendering)
		//return ccGLUtils::Perspective(currentFov_deg,ar,zNear,zFar);
		double yMax = zNear * tanf(currentFov_deg / 2 * CC_DEG_TO_RAD);
		double xMax = yMax * ar;

		double frustumAsymmetry = 0;
		if (eyeOffset)
		{
			//see 'NVIDIA 3D VISION PRO AND STEREOSCOPIC 3D' White paper (Oct 2010, p. 12)
			//on input 'eyeOffset' should be -1 or +1
			frustumAsymmetry = *eyeOffset * (2 * xMax) * (m_stereoParams.eyeSepFactor / 100.0);

			double convergence = m_stereoParams.focalDist;
			if (m_stereoParams.autoFocal)
			{
				convergence = fabs((cameraCenter - pivotPoint).dot(getCurrentViewDir())) / 2;
			}
			*eyeOffset = frustumAsymmetry * convergence / zNear;
		}

		return ccGL::Frustum(-xMax - frustumAsymmetry, xMax - frustumAsymmetry, -yMax, yMax, zNear, zFar);
	}
	else
	{
		//max distance (camera to 'farthest' point)
		double maxDist = CP + MP;

		double maxDist_pix = maxDist / m_viewportParams.pixelSize * m_viewportParams.zoom;
		maxDist_pix = std::max<double>(maxDist_pix, 1.0);

		double halfW = m_glViewport.width() / 2.0;
		double halfH = m_glViewport.height() / 2.0 * m_viewportParams.orthoAspectRatio;

		//save actual zNear and zFar parameters
		double zNear = -maxDist_pix;
		double zFar = maxDist_pix;

		if (metrics)
		{
			metrics->zNear = zNear;
			metrics->zFar = zFar;
		}

		return ccGL::Ortho(halfW, halfH, maxDist_pix);
	}
#endif
	return mat4();
}

void COpenGL::updateModelViewMatrix()
{
	//we save visualization matrix
	m_viewMatd = computeModelViewMatrix(getRealCameraCenter());

	m_validModelviewMatrix = true;
}

void COpenGL::updateProjectionMatrix()
{
	ProjectionMetrics metrics;

	m_projMatd = computeProjectionMatrix
	(
		getRealCameraCenter(),
		true,
		&metrics,
		0
	); //no stereo vision by default!

	m_viewportParams.zNear = metrics.zNear;
	m_viewportParams.zFar = metrics.zFar;
	//m_cameraToBBCenterDist = metrics.cameraToBBCenterDist;
	//m_bbHalfDiag = metrics.bbHalfDiag;

	m_validProjectionMatrix = true;
}

const mat4& COpenGL::getModelViewMatrix()
{
	if (!m_validModelviewMatrix)
		updateModelViewMatrix();

	return m_viewMatd;
}

const mat4& COpenGL::getProjectionMatrix()
{
	if (!m_validProjectionMatrix)
		updateProjectionMatrix();

	return m_projMatd;
}

void COpenGL::getGLCameraParameters(CameraParam & params)
{
	//get/compute the modelview matrix
	{
		params.modelViewMat = getModelViewMatrix();
	}

	//get/compute the projection matrix
	{
		params.projectionMat = getProjectionMatrix();
	}

	params.viewport[0] = m_glViewport.left;
	params.viewport[1] = m_glViewport.top;
	params.viewport[2] = m_glViewport.Width();
	params.viewport[3] = m_glViewport.Height();

	params.perspective = m_viewportParams.perspectiveView;
	params.fov_deg = m_viewportParams.fov;
	params.pixelSize = m_viewportParams.pixelSize;
}

int COpenGL::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);
	SetHDC(m_pDC->GetSafeHdc());
	if (!init())
		MessageBox(_T("Init opengl error"));
	return 0;
}


void COpenGL::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if (m_pDC != NULL)
		delete m_pDC;
	m_pDC = NULL;
}


void COpenGL::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (cy == 0)
	{
		cy = 1;
	}
	glViewport(0, 0, cx, cy);
	m_width = cx;
	m_height = cy;
}


BOOL COpenGL::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


mat4 getRotateMatrix(float angle, const vec3 &vector)
{
	angle = angle / 2 * pi<float>() / 180;
	vec3 vec = normalize(vector);
	float cosa = cos(angle);
	float sina = sin(angle);

	double a = vec[0] * sina;
	double b = vec[1] * sina;
	double c = vec[2] * sina;

	mat4 matrix;

	matrix[0][0] = 1.0 - 2.0*(b*b + c*c);
	matrix[1][1] = 1.0 - 2.0*(c*c + a*a);
	matrix[2][2] = 1.0 - 2.0*(a*a + b*b);

	matrix[0][1] = 2.0 * (a*b - c*cosa);
	matrix[0][2] = 2.0 * (a*c + b*cosa);

	matrix[1][0] = 2.0 * (a*b + c*cosa);
	matrix[1][2] = 2.0 * (b*c - a*cosa);

	matrix[2][0] = 2.0 * (a*c - b*cosa);
	matrix[2][1] = 2.0 * (b*c + a*cosa);

	return matrix;
}

vec3 product(const mat4 &matrix, const vec3 &vector)
{
	float x, y, z;
	x = vector[0] * matrix[0][0] +
		vector[1] * matrix[0][1] +
		vector[2] * matrix[0][2];

	y = vector[0] * matrix[1][0] +
		vector[1] * matrix[1][1] +
		vector[2] * matrix[1][2];

	z = vector[0] * matrix[2][0] +
		vector[1] * matrix[2][1] +
		vector[2] * matrix[2][2];

	return vec3(x, y, z);
}

void COpenGL::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nDiffX = point.x - m_nOriginX;
	int nDiffY = point.y - m_nOriginY;
	m_nOriginX = point.x;
	m_nOriginY = point.y;

	vec3 dirH = vec3(0.0f, 0.0f, 1.0f);
	vec3 dirV = vec3(0.0f, 1.0f, 0.0f);

	float fDiffX = (float)nDiffX;
	float fDiffY = (float)nDiffY * -1.0f;


	if (nFlags & MK_LBUTTON)
	{
		vec3 t = convertMousePositionToOrientation(1, 10);
		OutputString("(1, 10) --> (%lf, %lf, %lf)\r\n", t.x, t.y, t.z);
		vec3 mouse = m_vecAxisY * fDiffY + m_vecAxisX * fDiffX;
		vec3 rotateVec = cross(mouse, m_vecAxisZ);
		rotateVec = rotateVec + m_vecView;
		float angle = sqrt(mouse[0] * mouse[0] + mouse[1] * mouse[1] + mouse[2] * mouse[2]);
		m_rotateMatrix = getRotateMatrix(angle, rotateVec);
		m_vecCamera = product(m_rotateMatrix, m_vecCamera);
		m_vecHead = product(m_rotateMatrix, m_vecHead);
		m_vecHead = normalize(m_vecHead);
		m_vecAxisY = m_vecHead;
		m_vecAxisZ = m_vecCamera - m_vecView;
		m_vecAxisX = cross(m_vecAxisY, m_vecAxisZ);
		m_vecAxisX = normalize(m_vecAxisX);
	}
	if (nFlags & MK_RBUTTON)
	{
		vec3 vec(0, fDiffX * 0.005f, fDiffY * 0.005f);
		m_vecTranslate = m_vecTranslate + vec;
		m_vecTranslate = product(m_rotateMatrix, m_vecTranslate);
		//m_vecView = m_vecView + vec;
		//m_vecCamera = m_vecCamera + vec;
		OutputString("%lf, %lf, %lf\r\n", vec[0], vec[1], vec[2]);
		OutputString("%lf, %lf, %lf\r\n", m_vecTranslate[0], m_vecTranslate[1], m_vecTranslate[2]);
	}

	

	RenderScene();
	CView::OnMouseMove(nFlags, point);
}


BOOL COpenGL::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ratio *= (zDelta > 0) ? 0.9f : 1.1f;
	RenderScene();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
