
#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__ 1

#include "display.h"
#include "render_target.h"

class RenderManager {

public:
				RenderManager();
				~RenderManager();

				bool Initialize(Display &display);
				void Shutdown();

				void Render(float dt);

private:

				bool InitializeRenderTarget();

				Display *screen;
				RenderTarget mainRenderTarget;
				float rotCount;

};

#endif