#include "stb_image.h"
#include <iostream>
#include "Texture.h"
#include <GLAD/glad.h>
#include "ShaderManager.h"

Texture::Texture(): texture(0), width(0), height(0), nrChannels(0), error(false), name("test")
{
}

void Texture::Create(std::string imagePath, std::string textureName,int type)
{   
    name = textureName;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // load and generate the texture
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(type, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        if (type == GL_TEXTURE_2D)
            glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        error = true;
        std::cout << "Failed to load texture " << textureName << std::endl;
    }
    stbi_image_free(data);
}

void Texture::Use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::Clear()
{
    if (texture!=0)
    {
        glDeleteTextures(1, &texture);
    }

}

Texture::~Texture()
{
    Clear();
}
