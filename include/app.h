
#ifndef __APP_H__
#define __APP_H__ 1

#include <SDL.h>
#include <stdio.h>
#include "platform_types.h"

class Application {

public:

				Application();
				~Application();

				bool Initialize();
				
				void Input(u8 &end, u32 dt);
				void handleKeyCode(SDL_Event *event, u8 &end, u32 dt);

				void Update();
				void Shutdown();

};


#endif