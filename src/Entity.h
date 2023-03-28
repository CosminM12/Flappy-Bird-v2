#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Math.h"

class Entity{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, SDL_Rect p_atlasPos);
	Vector2f getPos();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	float getAngle();
	Vector2f getScale();
	void setScale(Vector2f p_scale);
	void setTex(SDL_Texture* p_tex);
	void setAngle(float p_angle);
	void setPos(Vector2f p_pos);
	void update(double deltaTime);
private:
	float angle;
	Vector2f pos;
	Vector2f scale;
	SDL_Rect currentFrame;
	SDL_Texture* tex = NULL;
};