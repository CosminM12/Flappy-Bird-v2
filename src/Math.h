#pragma once
#include <iostream>


struct Vector2f{

	Vector2f():x(0.0f), y(0.0f){}

	Vector2f(float p_x, float p_y):x(p_x), y(p_y){}

	float x, y;
};

namespace Math{
	inline bool checkCollision(Vector2f pos1, Vector2f scale1, Vector2f pos2, Vector2f scale2)
	{
		return pos1.x + 32*scale1.x > pos2.x && pos1.x < pos2.x + 32*scale2.x && pos1.y + 32*scale1.y > pos2.y && pos1.y < pos2.y + 32*scale2.y;
	}
}
