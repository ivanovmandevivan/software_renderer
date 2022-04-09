
#ifndef __RENDERER_H__
#define __RENDERER_H__ 1

#include "buffer.h"

class RenderTarget {

public:
				RenderTarget();
				~RenderTarget();

				bool Initialize(int width, int height);
				void Shutdown();
				
				Buffer<u32>* getRenderTarget();
				void clearBuffers();

private:

				bool createBuffers(int w, int h);


				bool startUpComplete = false;
				Buffer<u32> *pixelBuffer;


};

#endif