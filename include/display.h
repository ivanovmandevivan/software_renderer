
#ifndef __DISPLAY_H__
#define __DISPLAY_H__ 1

#include "SDL.h"
#include "buffer.h"

class Display {

public:
				
				static const u32 kSCREEN_WIDTH = 640;
				static const u32 kSCREEN_HEIGHT = 480;
				static const u32 SCREEN_PITCH = kSCREEN_HEIGHT * sizeof(u32);
				constexpr static const float SCREEN_ASPECT_RATIO = kSCREEN_WIDTH / (float)kSCREEN_HEIGHT;

				Display();
				~Display();

				bool Initialize();
				void Shutdown();

				void SwapBuffers(Buffer<u32> *buff);

private:

				bool StartSDL();
				bool CreateWindow();
				bool CreateScreenSurface();

				SDL_Surface *surface;
				SDL_Window *window;

};


#endif