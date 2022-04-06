#pragma once

#include "SDL.h"
#include "../Source/Objects/ObjData.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

#define NUM_FOOD		3

class Graphics
{
public:
	//////////////////////////////////////////////////////////////////////
	// 
	// @todo: Try to find the way how we can get the texture from private section rather than public one
	// as it is not good habit to keep such variables public. For the time being, we take an advantage from 
	// static variable, which gives an access to the whole project, that's why I want to make them unique,
	// to protect them.  
	// 
	// Good food sprites
	static SDL_Texture* gFood_apple;
	static SDL_Texture* gFood_onigiri;
	static SDL_Texture* gFood_fish;

	// Bad food sprites
	static SDL_Texture* bFood_apple;
	static SDL_Texture* bFood_onigiri;
	static SDL_Texture* bFood_fish;

	// Blowfish sprite
	static SDL_Texture* bFood_blowFish;

	// BG and Sumo sprites		   
	static SDL_Texture* bg_sprite;
	static SDL_Texture* sumo_sprite;

	//////////////////////////////////////////////////////////////////////
	static int sprite_w, sprite_h;
	// should be called only once on boot.
	static bool Init();

	// needs to be called once at the start and end of game loops rendering
	static void StartRender();
	static void EndRender();

	//drawing specific functions
	static void SetColor(Colour color);
	static void DrawRect(SDL_Texture*& objSprite, Transform2D transform, Vec2D dimensions, bool isFilled = false);
	static void DrawLine(Transform2D transform, Vec2D dimensions);
	static void DrawText(const char* text, float x, float y, int width, int height, SDL_Color color);

	static int LoadSprite(const char* file, SDL_Renderer* renderer, SDL_Texture*& somesprite);

private:
	// some SDL specific variables:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

};

