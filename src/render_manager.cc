
#include "render_manager.h"
#include "rasterizer.h"
#include "matrix.h"
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

				rotCount = 0.0f;
				monkeyModel = new Model("../data/obj/monkey.obj");
				mainCamera = new Camera(Vector3f(2.0f, 0.0f, 4.0f), Vector3f(0.0f), Vector3f(0.0f, 1.0f, 0.0f), Vector3f(0.0f, 0.0f, -1.0f));
				mainRenderTarget.setRenderTargetCamera(mainCamera);
				monkeyModel->getGeometry()->debugVertices();

				return true;
}

void RenderManager::Shutdown()
{
				screen = nullptr;
				mainRenderTarget.Shutdown();
}

void RenderManager::Render(float dt)
{
				mainRenderTarget.clearBuffers();

				Vector3f minYVert = Vector3f(1.0f, 1.0f, 0.0f);
				Vector3f midYVert = Vector3f(-1.0f, 1.0f, 0.0f);
				Vector3f maxYVert = Vector3f(0.0f, -1.0f, 0.0f);


				//Vector3f minYVert = Vector3f(100.0f, 100.0f, 0.0f);
				//Vector3f midYVert = Vector3f(150.0f, 200.0f, 0.0f);
				//Vector3f maxYVert = Vector3f(80.0f, 300.0f, 0.0f);



				// Here we can draw all the different models we pretend to draw:
				//Rasterizer::testPattern(mainRenderTarget.getRenderTarget());

				//for (int j = 100; j < 200; ++j) {
				//				basicPrimitive->DrawScanBuffer(j, 300 - j, 300 + j);
				//}
				//basicPrimitive->FillShape(mainRenderTarget.getRenderTarget(), 100, 200);



				/*Matrix4 model = Matrix4::identity();
				model = model * Matrix4::transformMat(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f));
				Matrix4 view = Matrix4::identity();
				view = view * Matrix4::translateMat(0.0f, 0.0f, -3.0f);
				float degToRadFOV = 90.0f * (M_PI / 180.0f);
				Matrix4 proj = Matrix4::projectionMat(90.0f, Display::SCREEN_ASPECT_RATIO, 0.1f, 1000.0f);
				//Matrix4 proj = Matrix4::orthoMat((float)Display::kSCREEN_WIDTH, 0, (float)Display::kSCREEN_HEIGHT, 0, -1.0f, 1.0f);
				proj.print();
								

				Matrix4 mvMat = view * model;
				Vector3f transformedMin = mvMat.matMultVec(minYVert);
				Vector3f transformedMid = mvMat.matMultVec(midYVert);
				Vector3f transformedMax = mvMat.matMultVec(maxYVert);

				transformedMin = proj.matMultVec(transformedMin);
				transformedMid = proj.matMultVec(transformedMid);
				transformedMax = proj.matMultVec(transformedMax);

				basicPrimitive->FillTriangle(mainRenderTarget.getRenderTarget(), transformedMax, transformedMid, transformedMin);
				*/

				// # LINE RENDERING:

				u32 whiteColor = 255 << 16 | 255 << 8 | 255;
				u32 redColor = 255 << 16 | 0 << 8 | 0;
				Rasterizer::drawLine(mainRenderTarget.getRenderTarget(), Vector3f(50.0f, 100.0f, 0.0f), Vector3f(200.0f, 300.0f, 0.0f), redColor);
				Rasterizer::drawLine(mainRenderTarget.getRenderTarget(), Vector3f(90.0f, 100.0f, 0.0f), Vector3f(120.0f, 300.0f, 0.0f), whiteColor);

				// # LINE RENDERING ^^

				// # TRIANGLE 2D DRAWING: 

				/*rotCount += (dt * 0.05f);
				Matrix4 model = Matrix4::identity();
				model = Matrix4::transformMat(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.5f, 0.5f, 0.5f));
				Matrix4 view = Matrix4::translateMat(0.0f, 0.0f, -3.0f);
				Matrix4 proj = Matrix4::projectionMat(90.0f, Display::SCREEN_ASPECT_RATIO, 0.1f, 1000.0f);

				Matrix4 res = proj * view * model;

				Vector3f transformedMin = res.matMultVec(minYVert);
				Vector3f transformedMid = res.matMultVec(midYVert);
				Vector3f transformedMax = res.matMultVec(maxYVert);

				Rasterizer::drawTriangle2D(mainRenderTarget.getRenderTarget(), transformedMin, transformedMid, transformedMax);
				*/

				// # TRIANGLE 2D DRAWING ^^
				
				mainCamera->Update(dt);
				bool isVisible = mainCamera->checkFrustumCulling(*monkeyModel->getBoundaryBox());
				if (isVisible) {
								rotCount += (dt * 0.05f);
								monkeyModel->update(rotCount);
								mainRenderTarget.drawTriangularMesh(monkeyModel);
				}

				screen->SwapBuffers(mainRenderTarget.getRenderTarget());

				
}

bool RenderManager::InitializeRenderTarget()
{
				int width = Display::kSCREEN_WIDTH;
				int height = Display::kSCREEN_HEIGHT;
				return mainRenderTarget.Initialize(width, height);
}
