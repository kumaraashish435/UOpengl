#ifndef TEXTURE_H
#define TEXTURE_H


#include "Shader.h"

class Texture
{
public:
    unsigned int ID;
    GLenum type;
    Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);

    void texUnit(Shader &shader, const char* uniform, unsigned int unit);
    void Bind(GLenum slot);
    void Unbind();
    void Delete();
};
#endif