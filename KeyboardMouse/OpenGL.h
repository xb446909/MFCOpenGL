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
	typedef struct tagViewportParam
	{
		tagViewportParam()
		{
			perspectiveView = false;
			zoom = 1.0f;
			pixelSize = 1.0f;
			fov = 30;
		}

		//! Current pixel size (in 'current unit'/pixel)
		/** This scale is valid eveywhere in ortho. mode
		or at the focal distance in perspective mode.
		Warning: doesn't take current zoom into account!
		**/
		float pixelSize;

		//! Current zoom
		float zoom;

		//! Visualization matrix (rotation only)
		mat4 viewMat;

		//! Point size
		float defaultPointSize;
		//! Line width
		float defaultLineWidth;

		//! Perspective view state
		bool perspectiveView;
		//! Whether view is centered on displayed scene (true) or on the user eye (false)
		/** Always true for ortho. mode.
		**/
		bool objectCenteredView;

		//! Theoretical perspective 'zNear' relative position
		double zNearCoef;
		//! Actual perspective 'zNear' value
		double zNear;
		//! Actual perspective 'zFar' value
		double zFar;

		//! Rotation pivot point (for object-centered view modes)
		vec3 pivotPoint;

		//! Camera center (for perspective mode)
		vec3 cameraCenter;

		//! Camera F.O.V. (field of view - for perspective mode only)
		float fov;
		//! Camera aspect ratio (perspective mode only)
		float perspectiveAspectRatio;

		//! 3D view aspect ratio (ortho mode only)
		/** AR = width / height
		**/
		float orthoAspectRatio;
	}ViewParam;

	typedef struct tagCameraParam
	{
		tagCameraParam()
			: perspective(false)
			, fov_deg(0)
			, pixelSize(0)
		{
			memset(viewport, 0, 4 * sizeof(int));
		}

		//! Projects a 3D point in 2D (+ normalized 'z' coordinate)
		inline bool project(const vec3& input3D, vec3& output2D) const { return COpenGL::Project(input3D, modelViewMat, projectionMat, viewport, output2D); }
		
		//! Unprojects a 2D point (+ normalized 'z' coordinate) in 3D
		inline bool unproject(const vec3& input2D, vec3& output3D) const { return COpenGL::Unproject(input2D, modelViewMat, projectionMat, viewport, output3D); }

		//! Model view matrix (GL_MODELVIEW)
		mat4 modelViewMat;
		//! Projection matrix (GL_PROJECTION)
		mat4 projectionMat;
		//! Viewport (GL_VIEWPORT)
		int viewport[4];
		//! Perspective mode
		bool perspective;
		//! F.O.V. (in degrees) - perspective mode only
		float fov_deg;
		//! Pixel size (i.e. zoom) - non perspective mode only
		float pixelSize;
	}CameraParam;

	//! Optional output metrics (from computeProjectionMatrix)
	struct ProjectionMetrics
	{
		ProjectionMetrics() : zNear(0), zFar(0), cameraToBBCenterDist(0), bbHalfDiag(0) {}
		double zNear, zFar, cameraToBBCenterDist, bbHalfDiag;
	};
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

	mat4 m_projection;
	mat4 m_view;
	float m_width;
	float m_height;
	float m_ratio;
	vec3 m_vecTranslate;
	
	int m_nOriginX;
	int m_nOriginY;

	vec3 m_vecCamera;
	vec3 m_vecView;
	vec3 m_vecHead;

	vec3 m_vecAxisX;
	vec3 m_vecAxisY;
	vec3 m_vecAxisZ;
	mat4 m_rotateMatrix;

	ViewParam m_viewportParams;

	bool m_verticalRotationLocked;
	bool m_bubbleViewModeEnabled;
	
	CRect m_glViewport;
	mat4 m_viewMatd;
	bool m_validModelviewMatrix;
	mat4 m_projMatd;
	bool m_validProjectionMatrix;

	BOOL SetupPixelFormat(HDC hDC);
	vec3 convertMousePositionToOrientation(int x, int y);
	void getGLCameraParameters(CameraParam& params);
	vec3 getRealCameraCenter() const;
	mat4 computeModelViewMatrix(const vec3 & cameraCenter) const;
	mat4 computeProjectionMatrix(const vec3& cameraCenter,
		bool withGLfeatures,
		ProjectionMetrics* metrics = 0,
		double* eyeOffset = 0) const;
	void updateModelViewMatrix();
	void updateProjectionMatrix();
	const mat4 & getModelViewMatrix();
	const mat4 & getProjectionMatrix();
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

	static bool Project(const vec3& input3D, const mat4& modelview, const mat4& projection, const int* viewport, vec3& output2D);
	static bool Unproject(const vec3& input2D, const mat4& modelview, const mat4& projection, const int* viewport, vec3& output3D);

	static bool InvertMatrix(const mat4& m, mat4& out);
};

