#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>

using namespace std;

void InsertString(const char* szPathName, const char* pattern, const char* insertString);

int main(int argc, char** argv)
{
	string projectName;
	stringstream szPattern;
	stringstream szFileName;
	stringstream szInsert;
	if (argc > 1)
	{
		projectName = string(argv[1]);
	}
	else
	{
		cout << "Please enter MFC (MDI) project name: ";
		cin >> projectName;
	}

	char szPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	strrchr(szPath, '\\')[1] = '\0';

#pragma region Copy files

	stringstream szCmd;
	szCmd << "copy /A /Y " << szPath << "OpenGL.cpp " << szPath << "..\\" << projectName << "\\";
	cout << "Copy file: OpenGL.cpp" << endl;
	system(szCmd.str().c_str());
	szCmd.clear();
	szCmd.str("");
	szCmd << "copy /A /Y " << szPath << "OpenGL.h " << szPath << "..\\" << projectName << "\\";
	cout << "Copy file: OpenGL.h" << endl;
	system(szCmd.str().c_str());

#pragma endregion

#pragma region OpenGL.h

	szFileName.clear();
	szFileName.str("");
	szPattern.clear();
	szPattern.str("");
	szInsert.clear();
	szInsert.str("");
	szFileName << szPath << "..\\" << projectName << "\\OpenGL.h";
	cout << "Update file: " << szFileName.str() << endl;
	szInsert << "#include \"" << projectName << "View.h\"" << endl;
	InsertString(szFileName.str().c_str(), "#include", szInsert.str().c_str());

#pragma endregion

#pragma region Update project file(.vcxproj)

	szFileName.clear();
	szFileName.str("");
	szPattern.clear();
	szPattern.str("");
	szFileName << szPath << "..\\" << projectName << "\\" << projectName << ".vcxproj";
	cout << "Update file: " << szFileName.str() << endl;

	szPattern << "<ClInclude Include=\"" << projectName << "View.h";
	InsertString(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClInclude Include=\"OpenGL.h\" />");
	InsertString(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClInclude Include=\"..\\common\\shader.hpp\" />");
	InsertString(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClInclude Include=\"..\\common\\texture.hpp\" />");

	szPattern.clear();
	szPattern.str("");
	szPattern << "<ClCompile Include=\"" << projectName << "View.cpp";
	InsertString(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClCompile Include=\"OpenGL.cpp\" />");
	InsertString(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClCompile Include=\"..\\common\\shader.cpp\" />");
	InsertString(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClCompile Include=\"..\\common\\texture.cpp\" />");

#pragma endregion

#pragma region Update CXXXView.h

	szFileName.clear();
	szFileName.str("");
	szFileName << szPath << "..\\" << projectName << "\\" << projectName << "View.h";
	cout << "Update file: " << szFileName.str() << endl;

	InsertString(szFileName.str().c_str(), "#pragma once", "#include \"OpenGL.h\"");
	InsertString(szFileName.str().c_str(), "OnEndPrinting", "\tCOpenGL m_opengl;");
	InsertString(szFileName.str().c_str(), "OnEndPrinting", "\tCDC* m_pDC;");

	InsertString(szFileName.str().c_str(), "DECLARE_MESSAGE_MAP", "\tafx_msg void OnSize(UINT nType, int cx, int cy);");
	InsertString(szFileName.str().c_str(), "DECLARE_MESSAGE_MAP", "\tafx_msg BOOL OnEraseBkgnd(CDC* pDC);");
	InsertString(szFileName.str().c_str(), "DECLARE_MESSAGE_MAP", "\tafx_msg void OnDestroy();");
	InsertString(szFileName.str().c_str(), "DECLARE_MESSAGE_MAP", "\tafx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);");


#pragma endregion

#pragma region Update CXXXView.cpp

	szFileName.clear();
	szFileName.str("");
	szFileName << szPath << "..\\" << projectName << "\\" << projectName << "View.cpp";
	cout << "Update file: " << szFileName.str() << endl;

	stringstream ss;
	ss << "\tON_WM_CREATE()" << endl;
	ss << "\tON_WM_DESTROY()" << endl;
	ss << "\tON_WM_ERASEBKGND()" << endl;
	ss << "\tON_WM_SIZE()" << endl;
	InsertString(szFileName.str().c_str(), "ID_FILE_PRINT_PREVIEW", ss.str().c_str());


	ss.clear();
	ss.str("");

	ss << endl;
	ss << "int C" << projectName << "View::OnCreate(LPCREATESTRUCT lpCreateStruct)" << endl;
	ss << "{" << endl;
	ss << "\tif (CView::OnCreate(lpCreateStruct) == -1)" << endl;
	ss << "\t\treturn -1;" << endl;
	ss << endl;
	ss << "\t// TODO:  在此添加您专用的创建代码" << endl;
	ss << "\tm_pDC = new CClientDC(this);" << endl;
	ss << "\tm_opengl.SetHDC(m_pDC->GetSafeHdc());" << endl;
	ss << "\tif (!m_opengl.init())" << endl;
	ss << "\t\tMessageBox(_T(\"Init opengl error\"));" << endl;
	ss << endl;
	ss << "\treturn 0;" << endl;
	ss << "}" << endl;
	ss << endl;
	ss << "void C" << projectName << "View::OnDestroy()" << endl;
	ss << "{" << endl;
	ss << "\tCView::OnDestroy();" << endl;
	ss << endl;
	ss << "\t// TODO: 在此处添加消息处理程序代码" << endl;
	ss << endl;
	ss << "\tif (m_pDC != NULL)" << endl;
	ss << "\t\tdelete m_pDC;" << endl;
	ss << "\tm_pDC = NULL;" << endl;
	ss << "}" << endl;
	ss << endl;
	ss << "BOOL C" << projectName << "View::OnEraseBkgnd(CDC * pDC)" << endl;
	ss << "{" << endl;
	ss << "\treturn TRUE;" << endl;
	ss << "}" << endl;
	ss << endl;
	ss << "void C" << projectName << "View::OnSize(UINT nType, int cx, int cy)" << endl;
	ss << "{" << endl;
	ss << "\tCView::OnSize(nType, cx, cy);" << endl;
	ss << endl;
	ss << "\t// TODO: 在此处添加消息处理程序代码" << endl;
	ss << "\tm_opengl.SetSize(cx, cy);" << endl;
	ss << "}" << endl;

	InsertString(szFileName.str().c_str(), "消息处理程序", ss.str().c_str());

	InsertString(szFileName.str().c_str(), "在此处为本机数据添加绘制代码", "\tm_opengl.RenderScene();\n");


#pragma endregion
	return 0;
}

void InsertString(const char* szPathName, const char* pattern, const char* insertString)
{
	fstream fs;
	stringstream ss;
	size_t pos_n;
	int inserted = 0;
	int found = 0;
	fs.open(szPathName, ios::in);
	if (!fs.bad())
	{
		string szTemp;
		while (getline(fs, szTemp))
		{
			ss << szTemp << endl;
		}
		size_t pos = ss.str().find(pattern);
		if (pos != string::npos)
		{
			found = 1;
			pos_n = ss.str().find_first_of('\n', pos);
		}
		if (ss.str().find(insertString, 0) != string::npos)
		{
			inserted = 1;
		}
	}
	fs.close();
	if ((inserted == 0) && (found == 1))
	{
		string sz_write = ss.str();
		sz_write.insert(pos_n + 1, insertString);
		fs.open(szPathName, ios::out | ios::trunc);
		fs << sz_write;
		fs.close();
	}
}
