
#include "display.h"
#include <stdio.h>

Display::Display() {}

Display::~Display() {}

bool Display::Initialize()
{
				bool isSuccessfull = true;
				if (!StartSDL()) {
								isSuccessfull = false;
				}
				else {

								// Window & Surface Creation
								if (!CreateWindow()) {
												isSuccessfull = false;
								}
								else {
												if (!CreateScreenSurface()) isSuccessfull = false;
								}
				}

				return isSuccessfull;
}

void Display::Shutdown()
{
				SDL_DestroyWindow(window);
				window = nullptr;
				SDL_Quit();
}

void Display::SwapBuffers(Buffer<u32> *buff)
{
				SDL_LockSurface(surface);
				memcpy(surface->pixels, buff->buffer, buff->height * buff->pitch);
				SDL_UnlockSurface(surface);

				SDL_UpdateWindowSurface(window);
}

bool Display::StartSDL()
{
				if (SDL_Init(SDL_INIT_VIDEO) < 0) {
								fprintf(stderr, "Can't initialize STDL: %s\n", SDL_GetError());
								return false;
				}
				return true;
}

bool Display::CreateWindow()
{
				window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kSCREEN_WIDTH, kSCREEN_HEIGHT, 0);
				if (window == nullptr) {
								fprintf(stderr, "Can't create window. [SDL]: %s\n", SDL_GetError());
								return false;
				}
				return true;
}

bool Display::CreateScreenSurface()
{
				surface = SDL_GetWindowSurface(window);
				if (surface == nullptr) {
								fprintf(stderr, "Could not create surface, [SDL]: %s\n", SDL_GetError());
								return false;
				}
				return true;
}

