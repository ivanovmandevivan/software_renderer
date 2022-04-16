
#ifndef __RENDERER_H__
#define __RENDERER_H__ 1

#include "buffer.h"
#include "model.h"

class RenderTarget {

public:
				RenderTarget();
				~RenderTarget();

				bool Initialize(int width, int height);
				void Shutdown();
				
				void drawTriangularMesh(Model *model);

				Buffer<u32>* getRenderTarget();
				void clearBuffers();

private:

				bool createBuffers(int w, int h);
				void packDataIntoTris(Vector3i &index, Vector3f *primitive, std::vector<Vector3f> &vals);

				bool startUpComplete = false;
				Buffer<u32> *pixelBuffer;


};

#endif