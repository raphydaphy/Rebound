#ifndef REBOUND_PICOPNG_H
#define REBOUND_PICOPNG_H

#include <vector>
#include <GL/gl3w.h>

namespace pico
{
    int decodePNG(std::vector<unsigned char> &out_image, GLsizei &image_width, GLsizei &image_height,
                  const unsigned char *in_png, size_t in_size, bool convert_to_rgba32 = true);
}

#endif