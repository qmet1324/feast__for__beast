#include "ColourBlock.h"

// processing events
#include "../EventHandler.h"
#include "../Graphics.h"

EventHandler inputs;

ColourBlock::ColourBlock()
{
	
}

ColourBlock::~ColourBlock()
{
}



void ColourBlock::SetColor(int r, int g, int b)
{
	colour.r = r;
	colour.g = g;
	colour.b = b;
}

void ColourBlock::Init(float x, float y, int width, int height)
{
	transform.position.x = x;
	transform.position.y = y;

	dimensions.x = width;
	dimensions.y = height;
}

void ColourBlock::Draw(SDL_Texture*& objSprite, bool filled)
{
	// create a bounding box based on the dimensions and position.
	Graphics::SetColor(colour);
	Graphics::DrawRect(objSprite, transform, dimensions, filled);
}

void ColourBlock::Update()
{
	transform.position.x += velocityX;
	transform.position.y += velocityY;
}

void ColourBlock::SetVelocity(int x, int y)
{
	velocityX = x;
	velocityY = y;
}

void ColourBlock::SetPosition(int x, int y)
{
	transform.position.x += x;
	transform.position.y += y;
}

// Move function to move player character.
void ColourBlock::Move()
{
	// keyboard inputs
	if (inputs.events[0] && transform.position.y > 0)
	{
		transform.position.y -= 10;
	}
	if (inputs.events[1] && transform.position.y < 600 - 50)
	{
		transform.position.y += 10;
	}
	if (inputs.events[2] && transform.position.x > 0)
	{
		transform.position.x -= 10;
	}
	if (inputs.events[3] && transform.position.x < 800 - 50)
	{
		transform.position.x += 10;
	}

}

void ColourBlock::MoveController() 
{

}
