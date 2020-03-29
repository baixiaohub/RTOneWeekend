#include "image_io.h"
#include "math_vec.h"

#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#include <vector>

real hit_sphere(const vec3& center, real radius, const ray& r)
{
	vec3 oc = r.origin - center;
	real a = dot(r.dir, r.dir);
	real b = 2.0f * dot(oc, r.dir);
	real c = dot(oc, oc) - radius * radius;
	real discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return -1.0f;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}

vec3 ray_color(const ray& r)
{
	real t = hit_sphere(vec3(0, 0, -1.0f), 0.5f, r);
	if (t > 0.0f) 
	{
		vec3 N = normalize(ray_at(r, t) - vec3(0, 0, -1.0f));
		return 0.5f * (N + vec3(1.0));
	}

	vec3 unit_dir = normalize(r.dir);
	real e = 0.5f * (unit_dir.y + 1.0f);
	return (1.0f - e) * vec3(1.0f, 1.0f, 1.0f) + e * vec3(0.5f, 0.7f, 1.0f);
}

void write_color_rgba(int32_t x, int32_t y, uint32_t image_width, uint32_t image_height,
	bool flipY, const vec3& color, uint8_t* data)
{
	const uint32_t IMAGE_CHANNELS = 4;
	uint8_t ir = (uint8_t)(255.999f * color.x);
	uint8_t ig = (uint8_t)(255.999f * color.y);
	uint8_t ib = (uint8_t)(255.999f * color.z);

	uint64_t offset = 0;
	if (flipY) {
		offset = ((image_height - y - 1) * image_width + x)* IMAGE_CHANNELS;
	}
	else {
		offset = (y * image_width + x)* IMAGE_CHANNELS;
	}
	data[offset] = ir;//r
	data[offset + 1] = ig;//g
	data[offset + 2] = ib;//b
	data[offset + 3] = 255; //a
}

int main()
{
	const uint32_t IMAGE_WIDTH = 400;
	const uint32_t IMAGE_HEIGHT = 200;
	const uint32_t IMAGE_CHANNELS = 4;
	const uint32_t IMAGE_PIXEL_BYTES = IMAGE_WIDTH * IMAGE_HEIGHT * IMAGE_CHANNELS;
	const char* filename = "image.png";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	std::vector<uint8_t> buffer(IMAGE_PIXEL_BYTES);
	for (int32_t y = 0; y < IMAGE_HEIGHT; ++y)
	{
		fprintf(stderr, "Scanlines remaining: %u\n", y);
		for (int32_t x = 0; x < IMAGE_WIDTH; ++x)
		{
			real u = 1.0f * x / IMAGE_WIDTH;
			real v = 1.0f * y / IMAGE_HEIGHT;
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);

			vec3 color = ray_color(r);
			//color = vec3_pow(color, 2.2f);

			write_color_rgba(x, y, IMAGE_WIDTH, IMAGE_HEIGHT, true, color, buffer.data());
		}
	}

	bool succeed = image_io_write_png_file(filename, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_CHANNELS, IMAGE_WIDTH * IMAGE_CHANNELS, buffer.data());
	assert(succeed && "write png file failed!");

	fprintf(stderr, "Done.\n");
	system(filename);

	return 0;
}

