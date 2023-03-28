#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "Scene.h"
#include "Entity.h"
#include "Bird.h"
#include "Math.h"

class GameScene : public Scene{
public:
	GameScene();
	void init(SDL_Renderer* &renderer, int sceneIdx);
	void update(int &sceneIdx, double deltaTime, Vector2f screenSize);
	void graphics(SDL_Renderer* &renderer);
	void clear();
private:
	bool clicked = false;
	std::vector<SDL_Texture*> textures;
	std::vector<Entity*> entities;
	std::vector<SDL_Color> colors;
	std::vector<TTF_Font*> fonts;
	Bird* bird = nullptr;
	float horizontalVelocity = 0;
	float distanceStep = 300;
	int actualClosest = 1;
	//float acceleration = 0.001;
	float depreciation = 0.5;
	int steps = 0, currentBest = -1;
	int state = 0; //0=click to start, 1=play, 2=click to respawn
};