#include "image.hpp"

nodeWebp::Image::Image(
	Format format,
	uint32_t width,
	uint32_t height,
	uint64_t size
) :
	data(new uint8_t[size]),
	format(format),
	height(height),
	size(size),
	width(width)
{}

nodeWebp::Image::~Image() {
	delete[] data;
}
