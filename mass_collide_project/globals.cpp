#include "globals.h"
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

// For DirExists()
#include <sys/types.h>
#include <sys/stat.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;
#include <glfw3.h>
#include <common/controls.hpp>

#if defined(_WIN32) || defined(WIN32)
// needed for OutputDebugStringA()
#   define WIN32_LEAN_AND_MEAN
#   include <Windows.h>
#else
// don't print to IDE on linux
void OutputDebugStringA(const char *file){}
#endif


int printOglError(const char *file, const int line)
{
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	if (glErr != GL_NO_ERROR)
	{
		std::cout << file << ":" << std::to_string(line) << " " << (char*)gluErrorString(glErr) << "\n";

		OutputDebugStringA(file);
		OutputDebugStringA(": ");
		OutputDebugStringA(std::to_string(line).c_str());
		OutputDebugStringA(": ");
		OutputDebugStringA((char*)gluErrorString(glErr));
		OutputDebugStringA("\n");
		retCode = 1;
	}
	return retCode;
}

double g_cursor_x, g_cursor_y; // get set by particle smasher

extern GLFWwindow* window;

glm::vec4 CursorToWorldspace(float depth)
{
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	auto inversed = ViewProjectionMatrix._inverse();

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glm::vec4 vector((g_cursor_x / width) * 2 - 1, (-g_cursor_y / height) * 2 + 1, 0.1, 0);
	return vector * inversed;
}

bool FileExists(const char* filename )
{
    std::ifstream openFile;
    openFile.open(filename);
    if( openFile ){
        return true;
    }
    return false;
    // openFile is on the stack and will be deleted here.
}

bool DirExists(const char* pathname){
    struct stat info;

    if( stat( pathname, &info ) != 0 ){
        printf( "cannot access %s\n", pathname );
        return false;
    }
    else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
        return true;
    else
        return false;
}

void ChangeDir(const char* dir)
{
    chdir(dir);
}

void LogCurrentDir()
{
    char * dir = getcwd(NULL, 0); // Platform-dependent...
    printf("Current dir: %s\n", dir);
}
