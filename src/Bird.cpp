#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "Entity.h"
#include "Bird.h"
#include "Math.h"

#define PI 3.14159265

using namespace std;


Bird::Bird(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, SDL_Rect p_atlasPos):Entity(p_pos, p_tex, p_scale, p_atlasPos)
{
	velocity.x = 0;
	velocity.y = 0;
}

float Bird::getVelocity()
{
	return velocity.y;
}

float Bird::getHorizontalVelocity()
{
	return velocity.x;
}

void Bird::setVelocity(float p_velocity)
{
	velocity.y = p_velocity;
}

void Bird::setHorizontalVelocity(float p_velocity)
{
	velocity.x = p_velocity;
}

void Bird::update(double deltaTime, bool clicked, Vector2f screenSize)
{
	//0=upMove, 1=downMove, 2=leftMove, 3=rightMove
	
	if(clicked)
	{
		setVelocity(-1.1f);
	}
	else
	{
		setVelocity(getVelocity()+friction*deltaTime*0.25);
	}
	setPos(Vector2f(getPos().x, getPos().y+getVelocity()*deltaTime*0.25));
}

void Bird::checkCollision(Vector2f screenSize, int &state, int steps, int &currentBest)
{
	if(getPos().y<=0 || getPos().y+32>=screenSize.y)
	{
		state = 2;
		currentBest = steps;
	}
}

void Bird::calculateAngle(float horizontalVelocity)
{
	float p_angle;
	p_angle = atan2(getVelocity(), horizontalVelocity)*180/PI;
	p_angle = 180-p_angle;
	setAngle(p_angle);
}