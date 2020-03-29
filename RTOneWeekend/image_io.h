#pragma once

#include <stdint.h>

bool image_io_write_png_file(const char* filePath, uint32_t width, uint32_t height, uint32_t channels, uint32_t widthStrideBytes, const uint8_t* data);

