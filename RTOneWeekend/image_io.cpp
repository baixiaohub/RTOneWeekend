#include "image_io.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8
#include "stb_image_write.h"

bool image_io_write_png_file(const char* filePath, uint32_t width, uint32_t height, uint32_t channels, uint32_t widthStrideBytes, const uint8_t* data)
{
	int ret = stbi_write_png(filePath, width, height, channels, data, widthStrideBytes);

	return ret == 1;
}

