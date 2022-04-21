// processing events
#include "EventHandler.h"
#include <ctime>
// creating a basic gameobject
#include "Objects/ColourBlock.h"
#include "../Graphics.h"


// GameState
bool GameRunning = true;

void PositionFood(ColourBlock& foodType, int randomNumber);

void RePosFood(ColourBlock& foodType, ColourBlock& player);

bool checkCollision(ColourBlock A, ColourBlock B);

// argc and argv here are command line parameters passed to the program when running the program. 
// we won't actually use them but our 2D Graphics Library requires the main setup like this.
// Argc: the number of arguments pass
// argv[] : a char array of each of the params passed in ( each space is a new param)
int main(int argc, char* argv[])
{

	int currentScore = 0;
	char score[10];
	int currentLives = 5;
	char lives[10];
	int timer = 0;

	bool filled = true;

	SDL_Color Red = { 255, 0, 0 };
	SDL_Color Green = { 0, 255, 0 };
	SDL_Color Blue = { 0, 0, 255 };
	SDL_Color Yellow = { 255, 255, 0 };
	SDL_Color Cyan = { 0, 255, 255 };
	SDL_Color Magenta = { 255, 0, 255 };
	SDL_Color White = { 255, 255, 255 };

	srand(time(NULL));
	
	if (!Graphics::Init())
	{
		return false;
	}

	/*const int MAX_PATTERN_SIZE = 9;
	const int BOARDSIZE = 9;
	

	int indexOrder[MAX_PATTERN_SIZE];

	for (int i = 0; i < MAX_PATTERN_SIZE; i++)
	{
		indexOrder[i] = rand() % BOARDSIZE;
	}
	int lvl = 1;*/

	// Objects
	ColourBlock sumo;
	ColourBlock badFood[NUM_FOOD];
	ColourBlock goodFood[NUM_FOOD];
	ColourBlock blowfish;


	//// where in the animation or entry is the current index
	//int currentPatternIndex = 0;
	//bool isAnimating = true;
	//bool isBlankFrame = true;
	//int currentPatternSize = 4;
	

	// Initialize Player
	sumo.Init(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 50, 50, 50);
	sumo.SetColor(0x00, 0x00, 0xFF);

	for (int i = 0; i < NUM_FOOD; i++)
	{

		PositionFood(badFood[i], rand() % 4); // Initialize Positions and Speed of bad food
		badFood[i].SetColor(0xFF, 0x00, 0x00);

		PositionFood(goodFood[i], rand() % 4); // INitialize Positions Speed of good food
		goodFood[i].SetColor(0x00, 0xFF, 0x00);

	}

	//Initialize Blowfish
	PositionFood(blowfish, rand() % 4);
	blowfish.SetColor(0xFF, 0xFF, 0x00);

	// Main game loop
	while (GameRunning)
	{
		Graphics::StartRender();

		static Uint32 count = 0;

		// handle button events
		GameRunning = EventHandler::Update();

		// Render Player
		//////////////////////////////////////////////////
		// @todo: have to create a spritesheet class in order to make an animation of the sumo,
		// the sprite of the sumo does not look promising 
		//
		sumo.Draw(Graphics::sumo_sprite,filled);
		
		sumo.Move();



		////////////////////////////////////////////////////////////////
		
		////////////////////////////////////////////////////////////////
		// 
		// @todo: redo for loop for the render of all bad and good food,
		// right now it's rendering only bad and good apple rather than all three sprites (onigiri, apple, and fish),
		// 
		// Render Good and Bad Food
		for (int i = 0; i < NUM_FOOD; i++)
		{
			badFood[i].Update();
			goodFood[i].Update();

			if (i % 3 == 0)
			{
				badFood[i].Draw(Graphics::bFood_apple, filled);
				goodFood[i].Draw(Graphics::gFood_apple, filled);
			}

			if (i % 3 == 1)
			{
				badFood[i].Draw(Graphics::bFood_onigiri, filled);
				goodFood[i].Draw(Graphics::gFood_onigiri, filled);
			}

			if (i % 3 == 2)
			{
				badFood[i].Draw(Graphics::bFood_fish, filled);
				goodFood[i].Draw(Graphics::gFood_fish, filled);
			}

			// Collision Detecttion bad food
			if (checkCollision(sumo, badFood[i]))
			{
				currentScore -= 50;
			}

			// Collision Detecttion good food
			if (checkCollision(sumo, goodFood[i]))
			{
				currentScore += 100;
			}

			// Respawn Food
			RePosFood(badFood[i], sumo);
			RePosFood(goodFood[i], sumo);
		}
		////////////////////////////////////////////////////////////////
		// Render Blowfish
		blowfish.Update();
		blowfish.Draw(Graphics::bFood_blowFish,filled);

		// Collision Detecttion
		if (checkCollision(sumo, blowfish))
		{
			currentLives--;
			RePosFood(blowfish, sumo);
			sumo.Init(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 50, 50, 50);
		}

		// Respawn blowfish
		RePosFood(blowfish, sumo);

		// draw text
		_itoa_s(currentLives, lives, 10);
		_itoa_s(currentScore, score, 10);

		Graphics::DrawText("Score: ", 0, 0, 100, 50, Cyan);
		Graphics::DrawText(score, 110, 0, 100, 50, Cyan);

		Graphics::DrawText("Lives: ", WINDOW_WIDTH - 125, 0, 100, 50, Magenta);
		Graphics::DrawText(lives, WINDOW_WIDTH - 25, 0, 25, 50, Magenta);

		if (currentLives <= 0)
		{
			GameRunning = false;
		}

		Graphics::EndRender();

		SDL_Delay(16);
	}


	Graphics::DrawText("Game Over", WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 25, 100, 50, White);
	//close off the SDL window
	SDL_Quit();

	return true;
}

void PositionFood(ColourBlock& foodType, int randomNumber)
{
	switch (randomNumber)
	{
	case 0:
		foodType.Init(rand() % (WINDOW_WIDTH - 50), 0, 50, 50);
		foodType.SetVelocity(0, rand() % 5 + 5);
		break;
	case 1:
		foodType.Init(rand() % (WINDOW_WIDTH - 50), WINDOW_HEIGHT - 50, 50, 50);
		foodType.SetVelocity(0, (rand() % 5 + 5) * -1);
		break;
	case 2:
		foodType.Init(0, rand() % (WINDOW_HEIGHT - 50), 50, 50);
		foodType.SetVelocity(rand() % 5 + 5, 0);
		break;
	case 3:
		foodType.Init(WINDOW_WIDTH - 50, rand() % (WINDOW_HEIGHT - 50), 50, 50);
		foodType.SetVelocity((rand() % 5 + 5) * -1, 0);
		break;
	}
}

void RePosFood(ColourBlock& foodType, ColourBlock& player)
{
	Transform2D Pos = foodType.GetTransform();

	if ((foodType.GetVelocityX() > 0 && Pos.position.x > 800) || checkCollision(player, foodType))
	{
		PositionFood(foodType, rand() % 4);
	}
	if ((foodType.GetVelocityX() < 0 && Pos.position.x < 0) || checkCollision(player, foodType))
	{
		PositionFood(foodType, rand() % 4);
	}
	if ((foodType.GetVelocityY() > 0 && Pos.position.y > 600) || checkCollision(player, foodType))
	{
		PositionFood(foodType, rand() % 4);
	}
	if ((foodType.GetVelocityY() < 0 && Pos.position.y < 0) || checkCollision(player, foodType))
	{
		PositionFood(foodType, rand() % 4);
	}
}

bool checkCollision(ColourBlock A, ColourBlock B)
{

	Transform2D posA, posB;
	Vec2D dimA, dimB;
	int topA, topB;
	int botA, botB;
	int leftA, leftB;
	int rightA, rightB;

	posA = A.GetTransform();
	posB = B.GetTransform();
	dimA = A.GetDimensions();
	dimB = B.GetDimensions();

	topA = posA.position.y;
	botA = posA.position.y + dimA.y;
	leftA = posA.position.x;
	rightA = posA.position.x + dimA.x;

	topB = posB.position.y;
	botB = posB.position.y + dimB.y;
	leftB = posB.position.x;
	rightB = posB.position.x + dimB.x;

	if (botA <= topB)
	{
		return false;
	}
	if (topA >= botB)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}