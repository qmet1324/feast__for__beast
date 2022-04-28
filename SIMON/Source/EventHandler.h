#pragma once
#include "SDL.h"

enum GameEvents
{
	W_PRESSED,
	S_PRESSED,
	A_PRESSED,
	D_PRESSED,
	UP_PRESSED,
	DOWN_PRESSED,
	LEFT_PRESSED,
	RIGHT_PRESSED,

	NUM_GAME_EVENTS

};

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	static bool Update();

	static const int NUM_EVENTS = 10;
 
	static bool events[GameEvents::NUM_GAME_EVENTS];

	static void ControllerInput();

private:

	static void SetButton(GameEvents eventNum, bool pressed);
};


