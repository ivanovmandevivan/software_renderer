
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

void Rasterizer::drawLine(Vector3f& p0, Vector3f& p1, const u32& color, Buffer<u32>* buffer)
{
				u8 steep = 0;
				int x0 = p0.x;
				int y0 = p0.y;
				int x1 = p1.x;
				int y1 = p1.y;

				// More different values of X compared to Y ones?
				if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
								std::swap(x0, y0);
								std::swap(x1, y1);
								steep = 1;
				}
				// Left to Right:
				if (x0 > y1) {
								std::swap(x0, x1);
								std::swap(y0, y1);
				}

				int dx = x1 - x0;
				int dy = y1 - y0;

				// We assume that the error margin per pixel is dy * 2, and we correct accordingly.
				int derror2 = std::abs(dy) * 2;
				int error2 = 0;
				int y = y0;

				for (int x = x0; x <= x1; ++x) {
								if (steep) (*buffer)(y, x) = color;
								else
												(*buffer)(x, y) = color;

								error2 += derror2;
								if (error2 > dx) {
												y += (y1> y0) ? 1: -1;
												error2 -= dx*2;
								}
				}

}
