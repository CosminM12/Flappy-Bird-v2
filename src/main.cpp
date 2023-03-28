#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "RenderWindow.h"
#include "MenuScene.h"
#include "GameScene.h"

bool gameRunning = true;
int scene=0, prevScene=0;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
int startTicks, frameTicks;
double deltaTime;

//Vector2f screenSize = Vector2f(288, 512);
Vector2f screenSize = Vector2f(460.8, 819.2);

//initialize sdl
bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO)>0)
		std::cout << "SDL_Init has failed. Error: " << SDL_GetError() << "\n";
	if(!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << "\n";
	if(TTF_Init()==-1)
		std::cout << "TTF_Init has failed. Error: " << SDL_GetError() << "\n";
	return true;
}
bool SDLInit = init();

bool windowCreation = RenderWindow::createWindow("Flappy Bird v2", window, renderer, screenSize.x, screenSize.y);
//----------------------SCENES-------------
//create scenes
MenuScene menuScene;
GameScene gameScene;
Scene *currentScene = &menuScene;

//change scene
void changeScene(int sceneIdx)
{
	switch(sceneIdx)
	{
		case -1: //exit app
			gameRunning = false;
			break;
		case 0: //main menu
			currentScene = &menuScene;
			break;
		case 1:
			currentScene = &gameScene;
			break;
	}
	currentScene->init(renderer, scene);
}

int main(int argc, char *argv[])
{
	currentScene->init(renderer, scene);

	while(gameRunning)
	{
		//v-sync initialize
		startTicks = SDL_GetTicks();
		//calculate deltaTime
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick)*1000/(double)SDL_GetPerformanceFrequency());

		//update scene
		if(scene==prevScene)
			currentScene->update(scene, deltaTime, screenSize);
		else
		{
			currentScene->clear();
			changeScene(scene);
			prevScene = scene;		
		}
		currentScene->graphics(renderer);
		//v-sync
		frameTicks = SDL_GetTicks() - startTicks;
		//cout << RenderWindow::getRefreshRate(window) << "\n";
		if(frameTicks < 1000/RenderWindow::getRefreshRate(window))
			SDL_Delay(1000/RenderWindow::getRefreshRate(window)-frameTicks);
	}
	RenderWindow::cleanUp(window);
	return 0;
}