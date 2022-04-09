
#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__ 1

#include "display.h"
#include "render_target.h"
#include "primitive.h"

class RenderManager {

public:
				RenderManager();
				~RenderManager();

				bool Initialize(Display &display);
				void Shutdown();

				void Render();

private:

				bool InitializeRenderTarget();

				Display *screen;
				RenderTarget mainRenderTarget;
				Primitive *basicPrimitive;

};

#endif