
#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__ 1

#include "SDL.h"
#include "buffer.h"
#include "vector3d.h"

class Rasterizer {

public:



				static void makeCoolPattern(Buffer<u32> *buffer);
				static void testPattern(Buffer<u32> *buffer);

				static void drawLine(Vector3f &p1, Vector3f &p2, const u32 &color, Buffer<u32> *buffer);

private:
				Rasterizer() {};
				~Rasterizer() {};

};

#endif