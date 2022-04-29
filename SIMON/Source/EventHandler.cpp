#include "EventHandler.h"

#include <stdio.h>
#include <string.h>

using namespace std;

bool EventHandler::events[];

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::Update()
{
	bool success = true;

	SDL_Event currEvents;
	// JD 13 - 
	while(	SDL_PollEvent(&currEvents))
	{
		switch (currEvents.key.keysym.sym)
		{
		case SDLK_w:
		{
			SetButton(GameEvents::W_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_s:
		{
			SetButton(GameEvents::S_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_a: //added 'a' for left 
		{
			SetButton(GameEvents::A_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_d: //added 'd' for right
		{
			SetButton(GameEvents::D_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_UP:
		{
			SetButton(GameEvents::UP_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		case SDLK_DOWN:
		{
			SetButton(GameEvents::DOWN_PRESSED, currEvents.key.type == SDL_KEYDOWN);
			break;
		}
		// press escape to quit the game
		case SDLK_ESCAPE:
		{
			success = false;
			break;
		}
		}
	}
	return success;
}

void EventHandler::SetButton(GameEvents eventNum, bool pressed)
{
	events[eventNum] = pressed;
}

void EventHandler::ControllerInput()
{
	
}
