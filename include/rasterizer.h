
#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__ 1

#include "SDL.h"
#include "buffer.h"

class Rasterizer {

public:



				static void makeCoolPattern(Buffer<u32> *buffer);
				static void testPattern(Buffer<u32> *buffer);

private:
				Rasterizer() {};
				~Rasterizer() {};

};

#endif