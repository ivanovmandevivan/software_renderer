

#include "app.h"

Application::Application() {}

Application::~Application() {}

// Initialize individual members for the application, in case any returns null, shutdown application.
bool Application::Initialize()
{
				bool isSuccessful = true;

				if (!display.Initialize()) {
								isSuccessful = false;
								fprintf(stderr, "Could not initialize window. [Display Class]\n");
				}
				else {
								// Only if Display is initialized we can continue.


				}


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
								case SDLK_w:
												printf("Pressed W\n");
												break;
								case SDLK_a:
												printf("Pressed A\n");
												break;
								case SDLK_s:
												printf("Pressed S\n");
												break;
								case SDLK_d:
												printf("Pressed D\n");
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


								deltaTime = SDL_GetTicks() - start;
								printf("[F%d]: Delta Time (ms): %d\n", countFrames, deltaTime);
								total += deltaTime;
				}
				printf("Shutting down...\n");
				printf("Average frame time over %d frames: %2.fms \n", countFrames, total/(float)countFrames);
}

void Application::Shutdown()
{
}
