#include "Shader.h"



Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    GLuint vertexShader = compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    compileErrors(ID, GL_PROGRAM);
    
    //delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

std::string Shader::loadShaderSource(const char* filePath)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filePath);
    if (file.is_open())    {
        buf << file.rdbuf();
        ret = buf.str();    
    }
    else    {
        std::cout << "Failed to open shader file: " << filePath << "\n";
    }

    return ret;
}

GLuint Shader::compileShader(const char* source, GLenum type)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    //check for shader compile errors
    compileErrors(shader, type);

    return shader;
}

void Shader::compileErrors(GLuint shader, GLenum type)
{
    int success;
    char infoLog[512];
    if (type != GL_PROGRAM)    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)    {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)    {
            glGetProgramInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
}

Shader::~Shader()
{
    glDeleteProgram(ID);
    std::cout << "Shader program deleted.\n";
}