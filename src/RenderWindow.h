#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.h"
#include "Math.h"

namespace RenderWindow
{
	inline bool createWindow(const char* p_title, SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight)
	{
		SDL_DisplayMode screenSize;
		SDL_GetCurrentDisplayMode(0, &screenSize);
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

		if(window==NULL)
			std::cout << "Window has failed to init. Error: " << SDL_GetError() << "\n";

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);

		return true;
	}

	inline SDL_Texture* loadTexture(const char* p_filePath, SDL_Renderer* &renderer)
	{
		SDL_Texture* texture = NULL;
		texture = IMG_LoadTexture(renderer, p_filePath);
		if(texture==NULL)
			std::cout << "Texture has failed to load. Error: " << SDL_GetError() << "\n";

		return texture;
	}

	inline void render(Entity& p_entity, SDL_Renderer* &renderer)
	{
		SDL_Rect src;
		src.x=p_entity.getCurrentFrame().x;
		src.y=p_entity.getCurrentFrame().y;
		src.w=p_entity.getCurrentFrame().w;
		src.h=p_entity.getCurrentFrame().h;

		SDL_Rect dst;
		dst.x = p_entity.getPos().x;
		dst.y = p_entity.getPos().y;
		dst.w = /*p_entity.getCurrentFrame().w*/32*p_entity.getScale().x;
		dst.h = /*p_entity.getCurrentFrame().h*/32*p_entity.getScale().y;

		SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
	}
	

	inline void render_angle(Entity& p_entity, SDL_Renderer* &renderer)
	{
		SDL_Rect src;
		src.x=p_entity.getCurrentFrame().x;
		src.y=p_entity.getCurrentFrame().y;
		src.w=p_entity.getCurrentFrame().w;
		src.h=p_entity.getCurrentFrame().h;

		SDL_Rect dst;
		dst.x = p_entity.getPos().x;
		dst.y = p_entity.getPos().y;
		dst.w = /*p_entity.getCurrentFrame().w*/32*p_entity.getScale().x;
		dst.h = /*p_entity.getCurrentFrame().h*/32*p_entity.getScale().y;

		if(p_entity.getAngle()<=90 || p_entity.getAngle()>=270)
			SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
		else
			SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
	}

	inline void renderText_center(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* &renderer)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = 460.8/2 - src.w/2 + p_x;
		dst.y = 819.2/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
	}

	inline void renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* &renderer)
	{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = p_x;
		dst.y = p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
	}

	inline int getRefreshRate(SDL_Window *window)
	{
		int displayIndex = SDL_GetWindowDisplayIndex(window);

		SDL_DisplayMode mode;
		SDL_GetDisplayMode(displayIndex, 0, &mode);

		return mode.refresh_rate;
	}

	inline void cleanUp(SDL_Window *window)
	{
		SDL_DestroyWindow(window);
	}

	inline void clear(SDL_Renderer* &renderer)
	{
		SDL_RenderClear(renderer);
	}

	inline void display(SDL_Renderer* &renderer)
	{
		SDL_RenderPresent(renderer);
	}
}