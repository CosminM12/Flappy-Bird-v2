#include <SDL2/SDL.h>
#include <iostream>

#include "Button.h"

Button::Button(Vector2f p_pos, SDL_Texture* p_tex, Vector2f p_scale, SDL_Rect p_atlasPos, int p_btnID):Entity(p_pos, p_tex, p_scale, p_atlasPos)
{
	btnID = p_btnID;
}

int Button::getBtnID()
{
	return btnID;
}

bool Button::isActive()
{
	return active;
}

void Button::setActivation(bool p_active)
{
	if(p_active)
	{
		setScale(Vector2f(getScale().x+1, getScale().y+0.5));
		setPos(Vector2f(getPos().x-32, getPos().y-16));
	}
	else
	{
		setScale(Vector2f(getScale().x-1, getScale().y-0.5));
		setPos(Vector2f(getPos().x+32, getPos().y+16));
	}
	active = p_active;
}