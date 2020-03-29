#include "image_io.h"

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include <vector>


int main()
{
	const uint32_t IMAGE_WIDTH = 800;
	const uint32_t IMAGE_HEIGHT = 600;
	const uint32_t IMAGE_CHANNELS = 4;
	const uint32_t IMAGE_PIXEL_BYTES = IMAGE_WIDTH * IMAGE_HEIGHT * IMAGE_CHANNELS;
	const char* filename = "image.png";

	std::vector<uint8_t> data(IMAGE_PIXEL_BYTES);
	for (uint32_t y = 0; y < IMAGE_HEIGHT; ++y)
	{
		fprintf(stderr, "frame scanline: %u\n", y);
		for (uint32_t x = 0; x < IMAGE_WIDTH; ++x)
		{
			uint64_t offset = (y * IMAGE_WIDTH + x) * IMAGE_CHANNELS;

			float r = 1.0f * x / IMAGE_WIDTH;
			float g = 1.0f * y / IMAGE_HEIGHT;
			float b = 0.2f;

			uint8_t ir = (uint8_t)(255.999f * r);
			uint8_t ig = (uint8_t)(255.999f * g);
			uint8_t ib = (uint8_t)(255.999f * b);

			data[offset] = ir;//r
			data[offset + 1] = ig;//g
			data[offset + 2] = ib;//b
			data[offset + 3] = 255; //a
		}
	}

	bool succeed = image_io_write_png_file(filename, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_CHANNELS, IMAGE_WIDTH * IMAGE_CHANNELS, data.data());

	assert(succeed && "write png file failed!");

	return 0;
}

