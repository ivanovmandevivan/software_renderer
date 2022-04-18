
#include "rasterizer.h"
#include <algorithm>
#include "matrix.h"

void Rasterizer::makeCoolPattern(Buffer<u32>* buffer)
{
				for (int y = 0; y < buffer->height; ++y) {
								for (int x = 0; x < buffer->width; ++x) {
												u8 r = x * 2 % 256;
												u8 g = y / 8 % 256;
												u8 b = r * y % 256;
												u32 color = r << 16 | g << 8 | b; // Texel Color Construction
												(*buffer)(x, y) = color;
								}
				}

}

void Rasterizer::testPattern(Buffer<u32>* buffer)
{

				(*buffer)(600, 200) = 255 << 16 | 0 << 8 | 0;
}

void Rasterizer::drawLine(Buffer<u32>* buffer, Vector3f& p0, Vector3f& p1, const u32& color)
{
				u8 steep = 0;
				int x0 = (p0.x + 1) * buffer->width * 0.5f;
				int y0 = (-p0.y + 1) * buffer->height * 0.5f;
				int x1 = (p1.x + 1) * buffer->width * 0.5f;
				int y1 = (-p1.y + 1) * buffer->height * 0.5f;

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
												y += (y1 > y0) ? 1 : -1;
												error2 -= dx * 2;
								}
				}

}

int Rasterizer::edgeOrientation(const Vector3f& a, const Vector3f& b, const Vector3f& c)
{
				return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
void Rasterizer::drawTriangle2D(Buffer<u32>* buffer, Vector3f& v0, Vector3f& v1, Vector3f& v2)
{

				Vector3f hiddenWs = Vector3f(1.0f / v0.w, 1.0f / v1.w, 1.0f / v2.w);

				////screenSpaceTransform(buffer, v0, v1, v2);
				v0 = Matrix4::NDCToScreenSpace(v0, buffer->width, buffer->height);
				v1 = Matrix4::NDCToScreenSpace(v1, buffer->width, buffer->height);
				v2 = Matrix4::NDCToScreenSpace(v2, buffer->width, buffer->height);

				// (Edge functions sump up the rea of a triangle) And we expect a signed area (usually positive-area), if negative, we don't draw it at all.
				// If v0,v1,v2 is counterclockwise the area will be positive, if clockwise, the area will be negative.
				// Backface Culling in essence.
				float area = edgeOrientation(v0, v1, v2);
				if (area <= 0) return;
				area = 1 / area;

				int xMin = std::min({ v0.x, v1.x, v2.x });
				int yMin = std::min({ v0.y, v1.y, v2.y });

				int xMax = std::max({ v0.x, v1.x, v2.x });
				int yMax = std::max({ v0.y, v1.y, v2.y });

				// Clip
				xMin = std::max(xMin, 0);
				yMin = std::max(yMin, 0);
				xMax = std::min(xMax, buffer->width - 1);
				yMax = std::min(yMax, buffer->height - 1);

				// We derivate this constants A01, B01, C01 | A12, B12 | A20, B20 from the equation:
				// (v0y - v1y)Px + (v1x - v0x)Py + (v0x * v1y - v0y * v1x) which translates to --> A01Px + B01Py + C01
				// From there we can extrapolate to all the vertices of the triangle, v0, v1 and v2.
				// We create the rows, for each pixel movement to the right, we sum AXX respectively (depending on the edge)
				// And for the Y coordinate, for each scanline row (JUMP in Y) we add BXX (depending on the edge)
				int a01 = v0.y - v1.y; int b01 = v1.x - v0.x;
				int a12 = v1.y - v2.y; int b12 = v2.x - v1.x;
				int a20 = v2.y - v0.y; int b20 = v0.x - v2.x;

				Vector3f p = Vector3f((float)xMin, (float)yMin, 0.0f);
				int w0_row = edgeOrientation(v1, v2, p);
				int w1_row = edgeOrientation(v2, v0, p);
				int w2_row = edgeOrientation(v0, v1, p);

				for (int y = yMin; y < yMax; ++y) {

								int w0 = w0_row;
								int w1 = w1_row;
								int w2 = w2_row;

								for (int x = xMin; x < xMax; ++x) {

												// To check the barycentric variables, we just need to check if any of the 3 bites is >= 0, thus we mask them with a bitwise OR and check the result.
												if ((w0 | w1 | w2) >= 0) {
																(*buffer)(x, y) = 255 << 16 | 255 << 8 | 255; // White Color Mask
												}
												w0 += a12;
												w1 += a20;
												w2 += a01;
								}
								w0_row += b12;
								w1_row += b20;
								w2_row += b01;
				}
}

void Rasterizer::drawTriangle3D(Buffer<u32>* buffer, IShader& shader, Vector3f* vertices)
{
				Vector3f hiddenWs = Vector3f(1.0f / vertices[0].w, 1.0f / vertices[1].w, 1.0f / vertices[2].w);

				////screenSpaceTransform(buffer, v0, v1, v2);
				vertices[0] = Matrix4::NDCToScreenSpace(vertices[0], buffer->width, buffer->height);
				vertices[1] = Matrix4::NDCToScreenSpace(vertices[1], buffer->width, buffer->height);
				vertices[2] = Matrix4::NDCToScreenSpace(vertices[2], buffer->width, buffer->height);

				// (Edge functions sump up the rea of a triangle) And we expect a signed area (usually positive-area), if negative, we don't draw it at all.
				// If v0,v1,v2 is counterclockwise the area will be positive, if clockwise, the area will be negative.
				float area = edgeOrientation(vertices[0], vertices[1], vertices[2]);
				if (area <= 0) return;
				area = 1 / area;

				int xMin = std::min({ vertices[0].x, vertices[1].x, vertices[2].x });
				int yMin = std::min({ vertices[0].y, vertices[1].y, vertices[2].y });

				int xMax = std::max({ vertices[0].x, vertices[1].x, vertices[2].x });
				int yMax = std::max({ vertices[0].y, vertices[1].y, vertices[2].y });

				// Clip
				xMin = std::max(xMin, 0);
				yMin = std::max(yMin, 0);
				xMax = std::min(xMax, buffer->width - 1);
				yMax = std::min(yMax, buffer->height - 1);

				// We derivate this constants A01, B01, C01 | A12, B12 | A20, B20 from the equation:
				// (v0y - v1y)Px + (v1x - v0x)Py + (v0x * v1y - v0y * v1x) which translates to --> A01Px + B01Py + C01
				// From there we can extrapolate to all the vertices of the triangle, v0, v1 and v2.
				// We create the rows, for each pixel movement to the right, we sum AXX respectively (depending on the edge)
				// And for the Y coordinate, for each scanline row (JUMP in Y) we add BXX (depending on the edge)
				int a01 = vertices[0].y - vertices[1].y; int b01 = vertices[1].x - vertices[0].x;
				int a12 = vertices[1].y - vertices[2].y; int b12 = vertices[2].x - vertices[1].x;
				int a20 = vertices[2].y - vertices[0].y; int b20 = vertices[0].x - vertices[2].x;

				Vector3f p = Vector3f((float)xMin, (float)yMin, 0.0f);
				int w0_row = edgeOrientation(vertices[1], vertices[2], p);
				int w1_row = edgeOrientation(vertices[2], vertices[0], p);
				int w2_row = edgeOrientation(vertices[0], vertices[1], p);

				Vector3f perspectiveCorrectedBarycentric;
				Vector3f uvw;
				float areaPerspective = 0.0f;
				Vector3f uvPerspectiveCorrected(0.0f);
				Vector3f outFragment(0.0f);
				for (int y = yMin; y < yMax; ++y) {

								int w0 = w0_row;
								int w1 = w1_row;
								int w2 = w2_row;

								for (int x = xMin; x < xMax; ++x) {

												// To check the barycentric variables, we just need to check if any of the 3 bites is >= 0, thus we mask them with a bitwise OR and check the result.
												if ((w0 | w1 | w2) >= 0) {

																// ZBufferCheck TODO<<

																// If it passes, Get Perspective Correct Barycentric Coords
																uvw = Vector3f(w0, w1, w2);
																perspectiveCorrectedBarycentric = uvw * hiddenWs;
																areaPerspective = 1.0f / (perspectiveCorrectedBarycentric.x + perspectiveCorrectedBarycentric.y + perspectiveCorrectedBarycentric.z);
																uvPerspectiveCorrected.x = perspectiveCorrectedBarycentric.y * areaPerspective;
																uvPerspectiveCorrected.y = perspectiveCorrectedBarycentric.z * areaPerspective;

																outFragment = shader.fragment(uvPerspectiveCorrected);

																int xColor = (int)outFragment.x;
																int yColor = (int)outFragment.y;
																int zColor = (int)outFragment.z;

																(*buffer)(x, y) = xColor << 16 | yColor << 8 | zColor;
												}
												w0 += a12;
												w1 += a20;
												w2 += a01;
								}
								w0_row += b12;
								w1_row += b20;
								w2_row += b01;
				}

}

void Rasterizer::drawWireframe(Buffer<u32>* buffer, Vector3f* vertices)
{
				const u32 whiteColor = 255 << 16 | 255 << 8 | 255;
				drawLine(buffer, vertices[0], vertices[1], whiteColor);
				drawLine(buffer, vertices[1], vertices[2], whiteColor);
				drawLine(buffer, vertices[0], vertices[2], whiteColor);

}

void Rasterizer::screenSpaceTransform(Buffer<u32>* buffer, Vector3f& v0, Vector3f& v1, Vector3f& v2)
{
				v0.x = ((v0.x + 1) * buffer->width * 0.5f) + 0.5f;
				v0.y = ((v0.y + 1) * buffer->height * 0.5f) + 0.5f;

				v1.x = ((v1.x + 1) * buffer->width * 0.5f) + 0.5f;
				v1.y = ((v1.y + 1) * buffer->height * 0.5f) + 0.5f;

				v2.x = ((v2.x + 1) * buffer->width * 0.5f) + 0.5f;
				v2.y = ((v2.y + 1) * buffer->height * 0.5f) + 0.5f;
}
