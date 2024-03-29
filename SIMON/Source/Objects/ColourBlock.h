#pragma once
#include "ObjData.h"

class ColourBlock 
{
public:
	ColourBlock();
	~ColourBlock();

	void Update();

	// used to render the object to the screen
	void Draw(SDL_Texture*& objSprite, bool filled = false);

	void Init(float x, float y, int width, int height);	

	void SetColor(int r, int g, int b);

	void SetVelocity(int x, int y);

	void SetPosition(int x, int y);


	void Move();

	void MoveController();

	Transform2D GetTransform() { return transform; }
	Vec2D GetDimensions() { return dimensions; }
	Colour GetColor() { return colour; }

	int GetVelocityX() { return velocityX; }
	int GetVelocityY() { return velocityY; }
	int GetPositionX() { return transform.position.x; }
	int GetPositionY() { return transform.position.y; }
	

private:

	// pos, rot, scale
	Transform2D transform;

	// width and height
	Vec2D dimensions;

	// colour to draw with
	Colour colour;

	int velocityX = 0;
	int velocityY = 0;

};

