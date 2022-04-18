

#include "app.h"

Application::Application() {}

Application::~Application() {}

// Initialize individual members for the application, in case any returns null, shutdown application.
bool Application::Initialize()
{
				bool isSuccessful = true;

				if (!displayManager.Initialize()) {
								isSuccessful = false;
								fprintf(stderr, "Could not initialize window. [Display Class]\n");
				}
				else {
								// Only if Display is initialized we can continue.
								if (!renderManager.Initialize(displayManager)) {
												isSuccessful = false;
												fprintf(stderr, "Failed to initialize Render Manager. [Application.Initialize]\n");
								}
				}

				mainCamera = &renderManager.getCamera();

				return isSuccessful;
}

void Application::Input(u8 &end, u32 dt)
{
				SDL_Event event;
				while (SDL_PollEvent(&event)) {
								if (event.type == SDL_QUIT) {
												end = 1;
												return;
								}
								else
								{
												handleKeyCode(&event, end, dt);
								}
				}
}

void Application::handleKeyCode(SDL_Event* event, u8& end, u32 dt)
{
				if (event->type == SDL_KEYDOWN) {
								switch (event->key.keysym.sym) {
								case SDLK_ESCAPE:
												end = 1;
												break;
								case SDLK_w:
												printf("Pressed W\n");
												mainCamera->position += mainCamera->front * mainCamera->cameraSpeed;
												break;
								case SDLK_a:
												printf("Pressed A\n");
												mainCamera->position += mainCamera->side * mainCamera->cameraSpeed;
												break;
								case SDLK_s:
												printf("Pressed S\n");
												mainCamera->position -= mainCamera->front * mainCamera->cameraSpeed;
												break;
								case SDLK_d:
												printf("Pressed D\n");
												mainCamera->position -= mainCamera->side * mainCamera->cameraSpeed;
												break;
								case SDL_QUIT:
												end = 1;
												break;
								}
				}
}

void Application::Update()
{

				// Counters:
				u32 deltaTime = 0;
				u32 start = 0;
				u32 total = 0;
				u32 countFrames = 0;

				u8 end = 0;
				while (!end) {
								++countFrames;
								start = SDL_GetTicks();
								Input(end, deltaTime);

								renderManager.Render(deltaTime);

								deltaTime = SDL_GetTicks() - start;
								//printf("[F%d]: Delta Time (ms): %d\n", countFrames, deltaTime);
								printf("Current FPS: %f\n", countFrames / (total / 1000.0));
								total += deltaTime;
				}
				printf("Shutting down...\n");
				printf("Average frame time over %d frames: %2.fms \n", countFrames, (float)(total/countFrames));
				system("pause");
}

void Application::Shutdown()
{
				renderManager.Shutdown();
				displayManager.Shutdown();
}
