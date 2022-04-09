
#include "render_manager.h"
#include "rasterizer.h"
#include <stdio.h>

RenderManager::RenderManager() {}

RenderManager::~RenderManager() {}

bool RenderManager::Initialize(Display& display)
{
				screen = &display;
				if (!InitializeRenderTarget()) {
								printf("Could not initialize main render target!\n");
								return false;
				}

				basicPrimitive = new Primitive();

				return true;
}

void RenderManager::Shutdown()
{
				screen = nullptr;
				mainRenderTarget.Shutdown();
}

void RenderManager::Render()
{
				mainRenderTarget.clearBuffers();

				// Here we can draw all the different models we pretend to draw:
				//Rasterizer::testPattern(mainRenderTarget.getRenderTarget());

				//for (int j = 100; j < 200; ++j) {
				//				basicPrimitive->DrawScanBuffer(j, 300 - j, 300 + j);
				//}
				//basicPrimitive->FillShape(mainRenderTarget.getRenderTarget(), 100, 200);

				basicPrimitive->FillTriangle(mainRenderTarget.getRenderTarget(), Vector3f(100.0f, 100.0f, 0.0f), Vector3f(150.0f, 200.0f, 0.0f), Vector3f(80.0f, 300.0f, 0.0f));

				screen->SwapBuffers(mainRenderTarget.getRenderTarget());

				
}

bool RenderManager::InitializeRenderTarget()
{
				int width = Display::kSCREEN_WIDTH;
				int height = Display::kSCREEN_HEIGHT;
				return mainRenderTarget.Initialize(width, height);
}
