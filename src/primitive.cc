
#include "primitive.h"
#include "display.h"

Primitive::Primitive() {
				// Creation of Raster Buffer for xMin / xMax per height:
				scanBuffer = (u32*)malloc((Display::kSCREEN_HEIGHT * 2) * sizeof(u32));
}

Primitive::~Primitive() {}

void Primitive::DrawScanBuffer(int height, int xMin, int xMax)
{
				scanBuffer[height * 2] = xMin;
				scanBuffer[height * 2 + 1] = xMax;
}

void Primitive::FillShape(Buffer<u32>* buffer, int yMin, int yMax)
{
				for (int y = yMin; y < yMax; ++y) {
								u32 xMin = scanBuffer[y * 2];
								u32 xMax = scanBuffer[y * 2 + 1];

								for (int x = xMin; x < xMax; ++x) {
												(*buffer)(x, y) = 255 << 16 | 255 << 8 | 255; // White color mask building.
								}
				}
}

void Primitive::FillTriangle(Buffer<u32>* buffer, Vector3f& v1, Vector3f& v2, Vector3f& v3)
{
				Vector3f minYVert = v1;
				Vector3f midYVert = v2;
				Vector3f maxYVert = v3;

				if (maxYVert.y > midYVert.y) {
								Vector3f tmp = maxYVert;
								maxYVert = midYVert;
								midYVert = tmp;
				}

				if (midYVert.y < minYVert.y) {
								Vector3f tmp = midYVert;
								midYVert = minYVert;
								minYVert = tmp;
				}

				float area = minYVert.triangleAreaSquared(maxYVert, midYVert);
				int side = area >= 0 ? 1 : 0;

				ScanConvertTriangle(minYVert, midYVert, maxYVert, side);
				FillShape(buffer, (int)minYVert.y, (int)maxYVert.y);
}

void Primitive::ScanConvertLine(const Vector3f& minYVert, const Vector3f& maxYVert, int side)
{
				float yStart = minYVert.y;
				float yEnd = maxYVert.y;
				float xStart = minYVert.x;
				float xEnd = maxYVert.x;

				float yDist = yEnd - yStart;
				float xDist = xEnd - xStart;

				if (yDist < 0.0f) return;

				float xStep = xDist/yDist;
				float currX = xStart;
				for (int y = yStart; y < yEnd; ++y) {
								scanBuffer[y * 2 + side] = (int)currX;
								currX += xStep;
				}
}

void Primitive::ScanConvertTriangle(const Vector3f& minYVert, const Vector3f& midYVert, const Vector3f& maxYVert, int side)
{
				ScanConvertLine(minYVert, maxYVert, side);
				ScanConvertLine(minYVert, midYVert, 1 - side);
				ScanConvertLine(midYVert, maxYVert, 1 - side);
}

