#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;

namespace events
{
	inline void getEvents(SDL_Event &event, int &sceneIdx, bool &mousePressed)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					sceneIdx = -1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT)
						mousePressed = true;
					break;
			}
		}
	}
	inline void getEvents(SDL_Event &event, int &sceneIdx, bool &mousePressed, std::vector<bool> &buys)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					sceneIdx = -1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event.button.button == SDL_BUTTON_LEFT)
						mousePressed = true;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
					case SDLK_1:
						buys[0] = true;
						break;
					case SDLK_2:
						buys[2] = true;
						break;
					case SDLK_3:
						buys[1] = true;
						break;
					case SDLK_4:
						buys[3] = true;
						break;
					}
			}
		}
	}
}