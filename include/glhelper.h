#ifndef GLHELPER_H
#define GLHELPER_H

#include <GL/glew.h>
//#include <GL/wglew.h>

#include <vector>
#include <string>

class GLHelper
{
public:
    static GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
    static GLuint CreateProgram(const std::vector<GLuint> &shaderList);
};

#endif // GLHELPER_H
