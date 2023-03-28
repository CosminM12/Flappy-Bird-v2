#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdlib.h>

#include "GameScene.h"
#include "RenderWindow.h"
#include "Entity.h"
#include "Bird.h"
#include "Math.h"
#include "Events.h"
#include "ScreenText.h"


GameScene::GameScene(){}

void GameScene::init(SDL_Renderer* &renderer, int sceneIdx)
{
	std::cout << "GameScene initializing" << "\n";
	//init textures
	textures.push_back(RenderWindow::loadTexture("res/sprites/background-day.png", renderer));
	textures.push_back(RenderWindow::loadTexture("res/sprites/yellowbird-midflap.png", renderer));
	textures.push_back(RenderWindow::loadTexture("res/sprites/pipe-green.png", renderer));

	TTF_Font* auxFont = TTF_OpenFont("res/font/OpenSans-Bold.ttf", 35);
	fonts.push_back(auxFont);
	auxFont = TTF_OpenFont("res/font/OpenSans-Bold.ttf", 28);
	fonts.push_back(auxFont);
	SDL_Color colorWhite = {255, 255, 255};
	SDL_Color colorBlack = {0, 0, 0};
	colors.push_back(colorWhite);
	colors.push_back(colorBlack);

	Entity* aux;
	aux = new Entity(Vector2f(0, 0), textures.at(0), Vector2f(288/19, 512/19), SDL_Rect{0, 0, 288, 512});
	entities.push_back(aux);
	//first sprites
	aux = new Entity(Vector2f(500, 500), textures.at(2), Vector2f(52/16, 20), SDL_Rect{0, 0, 52, 320});
	entities.push_back(aux);
	aux = new Entity(Vector2f(500, -320), textures.at(2), Vector2f(52/16, 20), SDL_Rect{0, 0, 52, 320});
	entities.push_back(aux);
	entities[2]->setAngle(180);
	//second sprites
	aux = new Entity(Vector2f(800, 500), textures.at(2), Vector2f(52/16, 20), SDL_Rect{0, 0, 52, 320});
	entities.push_back(aux);
	//third sprites
	aux = new Entity(Vector2f(800, -320), textures.at(2), Vector2f(52/16, 20), SDL_Rect{0, 0, 52, 320});
	entities.push_back(aux);
	entities[4]->setAngle(180);
	//third sprites
	aux = new Entity(Vector2f(1100, 500), textures.at(2), Vector2f(52/16, 20), SDL_Rect{0, 0, 52, 320});
	entities.push_back(aux);
	aux = new Entity(Vector2f(1100, -320), textures.at(2), Vector2f(52/16, 20), SDL_Rect{0, 0, 52, 320});
	entities.push_back(aux);
	entities[6]->setAngle(180);

	//bird
	bird = new Bird(Vector2f(83, 276), textures.at(1), Vector2f(34/28.5, 24/28.5), SDL_Rect{0, 0, 34, 24});
}

void GameScene::update(int &sceneIdx, double deltaTime, Vector2f screenSize)
{
	bool mousePressed = false;
	std::vector<bool> buys = {false};
	SDL_Event event;

	events::getEvents(event, sceneIdx, mousePressed, buys);

	if(state==1)
	{
		//update bird
		bird->update(deltaTime, mousePressed, screenSize);
		bird->checkCollision(screenSize, state, steps, currentBest);
		bird->calculateAngle(horizontalVelocity);
		//update sprites
		for(unsigned int i=1;i<7;i++)
			entities[i]->setPos(Vector2f(entities[i]->getPos().x+horizontalVelocity*deltaTime*0.25, entities[i]->getPos().y));

		//check collision
		if(Math::checkCollision(bird->getPos(), bird->getScale(), entities[actualClosest]->getPos(), entities[actualClosest]->getScale()) || Math::checkCollision(bird->getPos(), bird->getScale(), entities[actualClosest+1]->getPos(), entities[actualClosest+1]->getScale()))
		{
			state = 2;
			currentBest = steps;
		}
		//update sprites
		if(bird->getPos().x>entities[actualClosest]->getPos().x)
		{
			distanceStep = distanceStep>30 ? distanceStep-depreciation : distanceStep;
			float newMaxDistance = max(entities[1]->getPos().x, max(entities[3]->getPos().x, entities[5]->getPos().x));
			newMaxDistance += distanceStep;
			float randomDistance = rand()%320;
			float newY = randomDistance + 400;
			entities[actualClosest]->setPos(Vector2f(newMaxDistance, newY));
			newY = randomDistance - 420;
			entities[actualClosest+1]->setPos(Vector2f(newMaxDistance, newY));
			actualClosest = actualClosest==5 ? 1 : actualClosest+2;
			steps++;
		}
	}
	else
	{
		if(mousePressed)
		{
			if(state==0)
			{
				state = 1;
				horizontalVelocity = -0.75f;
			}
			else
			{
				state = 0;
				steps = 0;
				bird->setPos(Vector2f(83, 276));
				bird->setAngle(0);
				bird->setVelocity(0);
				entities[1]->setPos(Vector2f(500, 500));
				entities[2]->setPos(Vector2f(500, -320));
				entities[3]->setPos(Vector2f(800, 500));
				entities[4]->setPos(Vector2f(800, -320));
				entities[5]->setPos(Vector2f(1100, 500));
				entities[6]->setPos(Vector2f(1100, -320));
				actualClosest = 1;
				distanceStep = 300;
			}
		}
	}
}

void GameScene::graphics(SDL_Renderer* &renderer)
{
	RenderWindow::clear(renderer);
	for(unsigned int i=0;i<entities.size();i++)
	{
		RenderWindow::render_angle(*entities[i], renderer);
	}
	RenderWindow::render_angle(*bird, renderer);
	RenderWindow::renderText_center(0, -300, screenText::getScoreText(steps), fonts[0], colors[0], renderer);
	if(state!=1)
		RenderWindow::renderText_center(0, 200, screenText::getStateText(state), fonts[1], colors[1], renderer);
	if(currentBest != -1)
		RenderWindow::renderText(25, 725, screenText::getCurrentBest(currentBest), fonts[1], colors[0], renderer);
	RenderWindow::display(renderer);
}

void GameScene::clear()
{
	
}