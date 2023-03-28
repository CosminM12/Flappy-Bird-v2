#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Math.h"

class Scene{
public:
	Scene();
	virtual void init(SDL_Renderer* &renderer, int sceneIdx);
	virtual void update(int &sceneIdx, double deltaTime, Vector2f screenSize);
	virtual void exit_scene(int &scene, bool &done, double deltaTime, Vector2f screenSize);
	virtual void graphics(SDL_Renderer* &renderer);
	virtual void clear();
private:
};