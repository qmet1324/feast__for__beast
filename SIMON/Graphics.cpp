#include "Graphics.h"
#include <SDL_ttf.h>
#include <SDL_image.h>


SDL_Window* Graphics::window;
SDL_Renderer* Graphics::renderer;

SDL_Texture* Graphics::gFood_apple;
SDL_Texture* Graphics::gFood_onigiri;
SDL_Texture* Graphics::gFood_fish;

SDL_Texture* Graphics::bFood_apple;
SDL_Texture* Graphics::bFood_onigiri;
SDL_Texture* Graphics::bFood_fish;

SDL_Texture* Graphics::bFood_blowFish;

SDL_Texture* Graphics::bg_sprite;
SDL_Texture* Graphics::sumo_sprite;

int Graphics::sprite_w;
int Graphics::sprite_h;




bool Graphics::Init()
{
	// create little window with minimize and x to close 
	window = SDL_CreateWindow("Feast for Beast",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (!window)
	{
		throw false;
	}

	// fill in that window with a virtual canvas to draw on called a renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		throw false;
	}

	TTF_Init();

	// Initialize SDL_image Subsystem
	// throws a bool type variable to the main cpp (try/catch - exception handling) to see if all files have been loaded successfully
	// if not, it shows an error to the console, and exits the game 
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		throw false;
	}

	if (LoadSprite("background.png", renderer, bg_sprite) < 0)
	{
		throw false;
	}
	if (LoadSprite("sumo_idle.png", renderer, sumo_sprite) < 0)
	{
		throw false;
	}

	if (LoadSprite("health_apple.png", renderer, gFood_apple) < 0)
	{
		throw false;
	}
	if (LoadSprite("health_fish.png", renderer, gFood_fish) < 0)
	{
		throw false;
	}
	if (LoadSprite("health_onigiri.png", renderer, gFood_onigiri) < 0)
	{
		throw false;
	}

	if (LoadSprite("rotten_apple.png", renderer, bFood_apple) < 0)
	{
		throw false;
	}
	if (LoadSprite("rotten_fish.png", renderer, bFood_fish) < 0)
	{
		throw false;
	}
	if (LoadSprite("rotten_onigiri.png", renderer, bFood_onigiri) < 0)
	{
		throw false;
	}
	
	if (LoadSprite("blowfish.png", renderer, bFood_blowFish) < 0)
	{
		throw false;
	}

	return true;
}

void Graphics::StartRender()
{
	// clear the screen color
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
}

void Graphics::SetColor(Colour color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
}

void Graphics::DrawRect(SDL_Texture*& objSprite, Transform2D transform, Vec2D dimensions, bool isFilled)
{
	SDL_Rect Bounds;
	Bounds.x = transform.position.x;
	Bounds.y = transform.position.y;
	Bounds.w = dimensions.x;
	Bounds.h = dimensions.y;

	if (isFilled)
	{
		SDL_RenderCopy(renderer, objSprite, NULL, &Bounds);
	}
	else
	{
		SDL_RenderDrawRect(renderer, &Bounds);
	}
}

void Graphics::DrawLine(Transform2D transform, Vec2D dimensions)
{
	SDL_Rect Bounds;
	Bounds.x = transform.position.x;
	Bounds.y = transform.position.y;
	Bounds.w = dimensions.x;
	Bounds.h = dimensions.y;

	SDL_RenderDrawLine(renderer, transform.position.x, transform.position.y, dimensions.x, dimensions.y);
}

void Graphics::EndRender() 
{
	SDL_RenderPresent(renderer);
	// wait 2 frames
	SDL_Delay(2);
}

// example based on the code from: https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
void Graphics::DrawSDLText(const char * text, float x, float y, int width, int height, SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont("NipponLatin-Bold.ttf", 24);

	SDL_Color Red = { 255, 0, 0 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect;
	Message_rect.x = x;  
	Message_rect.y = y; 
	Message_rect.w = width; 
	Message_rect.h = height; 

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

int Graphics::LoadSprite(const char* file, SDL_Renderer* renderer, SDL_Texture*& somesprite)
{
	SDL_Surface* temp;

	// Load the sprite image
	temp = IMG_Load(file);
	if (temp == NULL)
	{
		fprintf(stderr, "Couldn't load %s: %s", file, SDL_GetError());
		return (-1);
	}
	sprite_w = temp->w;
	sprite_h = temp->h;

	// Set transparent pixel as the pixel at (0,0)
	if (temp->format->palette)
	{
		SDL_SetColorKey(temp, SDL_TRUE, *(Uint8*)temp->pixels);
	}
	else
	{
		switch (temp->format->BitsPerPixel)
		{
		case 15:
			SDL_SetColorKey(temp, SDL_TRUE, (*(Uint16*)temp->pixels) & 0x00007FFF);
			break;
		case 16:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint16*)temp->pixels);
			break;
		case 24:
			SDL_SetColorKey(temp, SDL_TRUE, (*(Uint32*)temp->pixels) & 0x00FFFFFF);
			break;
		case 32:
			SDL_SetColorKey(temp, SDL_TRUE, *(Uint32*)temp->pixels);
			break;
		}
	}

	// Create textures from the image
	somesprite = SDL_CreateTextureFromSurface(renderer, temp);
	if (!somesprite)
	{
		fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
		SDL_FreeSurface(temp);
		return (-1);
	}
	SDL_FreeSurface(temp);

	return 0;
}

