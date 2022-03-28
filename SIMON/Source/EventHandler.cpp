#include "EventHandler.h"
#include <stdio.h>
#include <string.h>

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
		}
	}
	return success;
}

void EventHandler::SetButton(GameEvents eventNum, bool pressed)
{
	events[eventNum] = pressed;
}
