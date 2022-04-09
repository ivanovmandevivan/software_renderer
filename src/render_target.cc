
#include "render_target.h"
#include <stdio.h>

RenderTarget::RenderTarget() {}

RenderTarget::~RenderTarget() {}

bool RenderTarget::Initialize(int width, int height)
{
				if (!createBuffers(width, height)) {
								return false;
				}

				startUpComplete = true;
				return startUpComplete;
}

void RenderTarget::Shutdown()
{
				if (startUpComplete) {
								delete pixelBuffer;
				}
}

Buffer<u32>* RenderTarget::getRenderTarget()
{
				return pixelBuffer;
}

void RenderTarget::clearBuffers()
{
				pixelBuffer->Clear(0x00);
}

bool RenderTarget::createBuffers(int w, int h)
{
				u32 pixelCount = w * h;
				bool isSuccessful = true;
				pixelBuffer = new Buffer<u32>(w, h, new u32[pixelCount]);
				if (pixelBuffer == nullptr) {
								printf("Could not build pixel buffer. [Renderer].\n");
								isSuccessful = false;
				}

				return isSuccessful;
}
