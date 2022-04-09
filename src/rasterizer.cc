
#include "rasterizer.h"

void Rasterizer::makeCoolPattern(Buffer<u32> *buffer)
{
				for (int y = 0; y < buffer->height; ++y) {
								for (int x = 0; x < buffer->width; ++x) {
												u8 r = x * 2 % 256;
												u8 g = y/8 % 256;
												u8 b = r*y % 256;
												u32 color = r << 16 | g << 8 | b; // Texel Color Construction
												(*buffer)(x, y) = color;
								}
				}

}

void Rasterizer::testPattern(Buffer<u32>* buffer)
{
				
				(*buffer)(600, 200) = 255 << 16 | 0 << 8 | 0;
}
