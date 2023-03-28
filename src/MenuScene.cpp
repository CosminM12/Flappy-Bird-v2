#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "MenuScene.h"
#include "RenderWindow.h"
#include "Button.h"
#include "Entity.h"
#include "Math.h"
#include "Events.h"


MenuScene::MenuScene(){}

void MenuScene::init(SDL_Renderer* &renderer, int sceneIdx)
{
	std::cout << "MenuScene initializing" << "\n";
	textures.push_back(RenderWindow::loadTexture("res/gfx/Buttons/play-button-light.png", renderer));
	textures.push_back(RenderWindow::loadTexture("res/gfx/Buttons/play-button-dark.png", renderer));
	textures.push_back(RenderWindow::loadTexture("res/gfx/Buttons/exit-button-light.png", renderer));
	textures.push_back(RenderWindow::loadTexture("res/gfx/Buttons/exit-button-light.png", renderer));

	buttons.push_back(Button(Vector2f(170, 100), textures.at(0), Vector2f(4, 1.8), SDL_Rect{0, 0, 1280, 720}, 1));
	buttons.push_back(Button(Vector2f(170, 300), textures.at(2), Vector2f(4, 1.8), SDL_Rect{0, 0, 1280, 720}, 0));
}

void MenuScene::update(int &sceneIdx, double deltaTime, Vector2f screenSize)
{
	//get events
	bool mousePressed = false;
	SDL_Event event;
	events::getEvents(event, sceneIdx, mousePressed);
	SDL_GetMouseState(&mouseX, &mouseY);

	//actions
	for(Button b : buttons)
	{ 
		if(b.getPos().x < mouseX && mouseX < b.getPos().x+32*b.getScale().x && b.getPos().y < mouseY && mouseY < b.getPos().y+32*b.getScale().y)
		{
			b.setActivation(true);
			if(mousePressed)
			{
				switch(b.getBtnID())
				{
					case 0: //exit button
						sceneIdx = -1;
						break;
					case 1: //play button
						sceneIdx = 1;
						cout << "Changing scenes" << "\n";
					default:
						std::cout << "A button has been clicked" << "\n";
						break;
				}
			}
		}
		else
		{
			b.setActivation(false);
		}
	}
}

void MenuScene::exit_scene(int &scene, bool &done, double deltaTime, Vector2f screenSize)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT){
			done = true;
			scene = -1;
			break;
		}
	}

	auto half = /*(int)*/buttons.size()/2;
	for(unsigned int i=0;i<half;i++)
	{
		buttons[i].setPos(Vector2f(buttons[i].getPos().x, buttons[i].getPos().y-deltaTime));
	}
	for(auto i=half;i<buttons.size();i++)
	{
		buttons[i].setPos(Vector2f(buttons[i].getPos().x, buttons[i].getPos().y+deltaTime));
	}
	
	if(buttons[half-1].getPos().y+32*buttons[half-1].getScale().y<0 && buttons[half].getPos().y>720)
	{
		done = true;
	}
}

void MenuScene::graphics(SDL_Renderer* &renderer)
{
	RenderWindow::clear(renderer);
	for(Button b : buttons){
		RenderWindow::render(b, renderer);
	}
	RenderWindow::display(renderer);
}

void MenuScene::clear()
{
	std::cout << "Cleared MenuScene" << "\n";
	buttons.clear();
	textures.clear();
}