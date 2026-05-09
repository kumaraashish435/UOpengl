#ifndef SHADER_H
#define SHADER_H

#include "Application.h"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    
    void Activate();
    std::string loadShaderSource(const char* filePath);
    GLuint compileShader(const char* source, GLenum type);
    void compileErrors(GLuint shader, GLenum type);

};




#endif