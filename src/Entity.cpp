#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Math.h"
#include "Entity.h"

using namespace std;

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, SDL_Rect p_atlasPos):tex(p_tex), scale(p_scale), currentFrame(p_atlasPos)
{
	pos.x = p_pos.x == INT_MAX ? 1280/2 - 32*scale.x/2 : p_pos.x;
	pos.y = p_pos.y == INT_MAX ? 720/2 - 32*scale.y/2 : p_pos.y;
}

Vector2f Entity::getPos()
{
	return pos;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

Vector2f Entity::getScale()
{
	return scale;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

float Entity::getAngle()
{
	return angle;
}

void Entity::setPos(Vector2f p_pos)
{
	pos.x = p_pos.x;
	pos.y = p_pos.y;
}

void Entity::setTex(SDL_Texture* p_tex)
{
	tex = p_tex;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

void Entity::setScale(Vector2f p_scale)
{
	scale.x = p_scale.x;
	scale.y = p_scale.y;
}

void Entity::update(double deltaTime){}