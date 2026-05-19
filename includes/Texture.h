#ifndef TEXTURE_H
#define TEXTURE_H


#include "Shader.h"

class Texture
{
public:
    unsigned int ID;
    GLenum type;
    GLuint unit;

    Texture(const char* image, GLenum texType, GLuint slot, GLenum pixelType);
    ~Texture();

    void texUnit(Shader &shader, const char* uniform, unsigned int unit);
    void Bind(GLenum slot);
    void Unbind();
};
#endif