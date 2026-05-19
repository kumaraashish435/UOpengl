#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum pixelType)
{
    type = texType;

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(texType, ID);

    // wrapping
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtering
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format;
        if (nrChannels == 4)
            format = GL_RGBA;
        else if (nrChannels == 3)
            format = GL_RGB;
        else
            format = GL_RED;

        glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, data);
        glGenerateMipmap(texType);
    }
    else
    {
        std::cout << "Failed to load texture\n";
    }

    stbi_image_free(data);
}

void Texture::texUnit(Shader& shader, const char* uniform, unsigned int unit)
{
    shader.Activate(); 
    glUniform1i(glGetUniformLocation(shader.ID, uniform), unit);
}

void Texture::Bind(GLenum slot)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
    std::cout << "Texture deleted.\n";
}



