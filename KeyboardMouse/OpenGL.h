#pragma once
#include "afxwin.h"

#define	GLEW_STATIC		1

#include "../GL/include/glew.h"
#include <gl/GLU.h>
#include "../common/shader.hpp"
#include "../common/texture.hpp"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

using namespace glm;

class COpenGL :
	public CView
{
public:
	COpenGL();
	virtual ~COpenGL();
	static void OutputString(char * fmt, ...);
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	BOOL init();
	void SetHDC(HDC hDC);
	void RenderScene();
	void SetSize(int nWidth, int nHeight);

private:
	CDC* m_pDC;
	HDC m_hDC;
	mat4 m_MVP;
	GLuint m_matrixID;
	GLuint m_programID;
	GLuint m_textureID;
	GLuint m_texture;
	GLuint m_vertexArrayID;
	GLuint m_vertexbuffer;
	GLuint m_uvbuffer;

	BOOL m_bLBtnDown;

	mat4 m_projection;
	mat4 m_view;
	float m_width;
	float m_height;
	float m_ratio;

	BOOL SetupPixelFormat(HDC hDC);
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

