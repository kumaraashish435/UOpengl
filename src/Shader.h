#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

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