#include <iostream>

#include "Scene.h"
#include "Math.h"

Scene::Scene(){}

void Scene::init(SDL_Renderer* &renderer, int sceneIdx)
{
	std::cout << "Scene initializing" << "\n";
}

void Scene::update(int &sceneIdx, double deltaTime, Vector2f screenSize){}

void Scene::exit_scene(int &scene, bool &done, double deltaTime, Vector2f screenSize){}

void Scene::graphics(SDL_Renderer* &renderer){}

void Scene::clear(){}