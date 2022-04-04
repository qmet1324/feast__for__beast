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

void ColourBlock::Draw(bool filled)
{
	// create a bounding box based on the dimensions and position.
	Graphics::SetColor(colour);
	Graphics::DrawRect(transform, dimensions, filled);
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

// Move function to move player character.
void ColourBlock::Move()
{
	if (inputs.events[0])
	{
		transform.position.y-=10;
	}
	if (inputs.events[1])
	{
		transform.position.y += 10;
	}
	if (inputs.events[2])
	{
		transform.position.x -= 10;
	}
	if (inputs.events[3])
	{
		transform.position.x += 10;
	}
}