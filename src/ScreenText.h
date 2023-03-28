#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

namespace screenText{
	inline const char* getScoreText(int score)
	{
		string s = to_string(score);
		s = "Score: " + s;
		return s.c_str();
	}

	inline const char* getStateText(int state)
	{
		string s;
		switch(state)
		{
			case 0:
				s = "Press anywhere to play!";
				break;
			case 2:
				s = "ded xD! Click to restart lel";
				break;
		}
		return s.c_str();
	}

	inline const char* getCurrentBest(int currentBest)
	{
		string s = to_string(currentBest);
		s = "Current best: " + s;
		return s.c_str();
	}
}