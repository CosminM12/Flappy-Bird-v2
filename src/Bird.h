#pragma once
#include <SDL2/SDL.h>
#include <SDl2/SDL_image.h>
#include <iostream>
#include <vector>

#include "Entity.h"
#include "Math.h"


class Bird : public Entity
{
public:
	//Cube();
	Bird(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, SDL_Rect p_atlasPos);
	float getVelocity();
	float getHorizontalVelocity();
	void setVelocity(float p_velocity);
	void setHorizontalVelocity(float p_velocity);
	void update(double deltaTime, bool clicked, Vector2f screenSize);
	void checkCollision(Vector2f screenSize, int &state, int steps, int &currentBest);
	void calculateAngle(float horizontalVelocity);
private:
	Vector2f velocity;
	float friction=0.008;
};
