#include <iostream>
#include <Windows.h>
#include <sstream>
#include <fstream>

using namespace std;

void InsertLine(const char* szPathName, const char* pattern, const char* insertString);

int main(int argc, char** argv)
{
	string projectName;
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

	stringstream szCmd;
	szCmd << "copy /A /Y " << szPath << "OpenGL.cpp " << szPath << "..\\" << projectName << "\\";
	cout << "Copy file: OpenGL.cpp" << endl;
	system(szCmd.str().c_str());
	szCmd.clear();
	szCmd.str("");
	szCmd << "copy /A /Y " << szPath << "OpenGL.h " << szPath << "..\\" << projectName << "\\";
	cout << "Copy file: OpenGL.h" << endl;
	system(szCmd.str().c_str());

	stringstream szFileName;
	szFileName << szPath << "..\\" << projectName << "\\" << projectName << ".vcxproj";
	cout << "Update file: " << szFileName.str() << endl;

	stringstream szPattern;
	szPattern << "<ClInclude Include=\"" << projectName << "View.h";
	InsertLine(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClInclude Include=\"OpenGL.h\" />");

	szPattern.clear();
	szPattern.str("");
	szPattern << "<ClCompile Include=\"" << projectName << "View.cpp";
	InsertLine(szFileName.str().c_str(), szPattern.str().c_str(), "    <ClInclude Include=\"OpenGL.cpp\" />");

	szFileName.clear();
	szFileName.str("");
	szFileName << szPath << "..\\" << projectName << "\\" << projectName << "View.h";
	cout << "Update file: " << szFileName.str() << endl;

	InsertLine(szFileName.str().c_str(), "#pragma once", "#include \"OpenGL.h\"");
	InsertLine(szFileName.str().c_str(), "OnEndPrinting", "\tCOpenGL m_opengl;");
	InsertLine(szFileName.str().c_str(), "OnEndPrinting", "\tCDC* m_pDC;");

	return 0;
}

void InsertLine(const char* szPathName, const char* pattern, const char* insertString)
{
	string szTemp;
	fstream fs;
	stringstream ss;
	int inserted = 0;
	int found = 0;
	fs.open(szPathName, ios::in);
	if (!fs.bad())
	{
		while (getline(fs, szTemp))
		{
			ss << szTemp << endl;
			if (szTemp.find(pattern, 0) != string::npos)
			{
				ss << insertString << endl;
				found = 1;
			}
			if (szTemp.find(insertString, 0) != string::npos)
			{
				inserted = 1;
				break;
			}
		}
	}
	fs.close();
	if ((inserted == 0) && (found == 1))
	{
		fs.open(szPathName, ios::out | ios::trunc);
		fs << ss.str();
		fs.close();
	}
}
