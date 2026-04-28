#ifndef SHADER_H
#define SHADER_H

#include "Application.h"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void Activate();

    std::string loadShaderSource(const char* filePath);
    GLuint compileShader(const char* source, GLenum type);

    //uniform functions
    void setMat4(const std::string &name, const glm::mat4 &mat);
};




#endif