#pragma once
#include <SDL2/SDL.h>
#include <iostream>

#include "Entity.h"
#include "Math.h"

class Button : public Entity{
public:
	Button(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, SDL_Rect p_atlasPos, int p_btnID);
	int getBtnID();
	bool isActive();
	void setActivation(bool p_active);
private:
	int btnID;
	bool active = false;
};