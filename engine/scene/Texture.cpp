
#include "Texture.hpp"

Texture::Texture(std::string path)
{
    path = "../res/" + path + ".png";

    std::vector<unsigned char> buffer, image;
    core::loadPNG(buffer, path.c_str());
    int error = pico::decodePNG(image, width, height, buffer.empty() ? nullptr : &buffer[0], (unsigned long)buffer.size(), true);

    if(error != 0)
    {
        std::cout << "error: " << error << std::endl;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(image[0]));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    printf("Loading PNG file %s...\n", path);
}

Texture Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
    return *this;
}

Texture Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    return *this;
}
