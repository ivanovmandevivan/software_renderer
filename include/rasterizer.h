
#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__ 1

#include "SDL.h"
#include "buffer.h"
#include "vector3d.h"

class Rasterizer {

public:

				static void makeCoolPattern(Buffer<u32> *buffer);
				static void testPattern(Buffer<u32> *buffer);

				static void drawLine(Buffer<u32>* buffer, Vector3f &p1, Vector3f &p2, const u32 &color);

				static int edgeOrientation(const Vector3f &a, const Vector3f &b, const Vector3f &c);
				static void drawTriangle2D(Buffer<u32>* buffer, Vector3f &v0, Vector3f& v1, Vector3f& v2);
				static void drawWireframe(Buffer<u32>* buffer, Vector3f *vertices);

				static void screenSpaceTransform(Buffer<u32>* buffer, Vector3f &v0, Vector3f &v1, Vector3f& v2);

private:
				Rasterizer() {};
				~Rasterizer() {};

};

#endif