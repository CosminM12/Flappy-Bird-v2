#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "Scene.h"
#include "Button.h"
#include "Entity.h"
#include "Math.h"

using namespace std;

class MenuScene : public Scene{
public:
	MenuScene();
	void init(SDL_Renderer* &renderer, int sceneIdx);
	void update(int &sceneIdx, double deltaTime, Vector2f screenSize);
	void exit_scene(int &scene, bool &done, double deltaTime, Vector2f screenSize);
	void graphics(SDL_Renderer* &renderer);
	void clear();
private:
	vector<Button> buttons = {};
	vector<SDL_Texture*> textures = {};
	int mouseX=0, mouseY=0;
};