// processing events
#include "EventHandler.h"
#include <ctime>
// creating a basic gameobject
#include "Objects/ColourBlock.h"
#include "../Graphics.h"

// GameState
bool GameRunning = true;

void PositionFood(ColourBlock& foodType, int randomNumber);

void RePosFood(ColourBlock& foodType);

// argc and argv here are command line parameters passed to the program when running the program. 
// we won't actually use them but our 2D Graphics Library requires the main setup like this.
// Argc: the number of arguments pass
// argv[] : a char array of each of the params passed in ( each space is a new param)
int main(int argc, char* argv[])
{
	int currentScore = 0;
	const int numFood = 3;
	bool filled = true;

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
	ColourBlock badFood[numFood];
	ColourBlock goodFood[numFood];
	ColourBlock blowfish;


	//// where in the animation or entry is the current index
	//int currentPatternIndex = 0;
	//bool isAnimating = true;
	//bool isBlankFrame = true;
	//int currentPatternSize = 4;
	int randomNumberBad = 0;
	int randomNumberGood = 0;

	// Initialize Player
	sumo.Init(800 / 2 - 25, 600 / 2 - 25, 25, 25);
	sumo.SetColor(0x00, 0x00, 0xFF);

	for (int i = 0; i < numFood; i++)
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

		// handle button events
		GameRunning = EventHandler::Update();

		// Render Player
		sumo.Draw(filled);
		sumo.Move();


		// Render Good and Bad Food
		for (int i = 0; i < numFood; i++)
		{
			badFood[i].Update();
			badFood[i].Draw(filled);
			goodFood[i].Update();
			goodFood[i].Draw(filled);

			RePosFood(badFood[i]);
			RePosFood(goodFood[i]);
		}

		//  Render Blowfish
		blowfish.Update();
		blowfish.Draw(filled);
		RePosFood(blowfish);

		Graphics::EndRender();

		SDL_Delay(16);
	}

	//close off the SDL window
	SDL_Quit();

	return true;
}

void PositionFood(ColourBlock& foodType, int randomNumber)
{
	switch (randomNumber)
	{
	case 0:
		foodType.Init(rand() % (800 - 25), 0, 25, 25);
		foodType.SetVelocity(0, rand() % 5 + 5);
		break;
	case 1:
		foodType.Init(rand() % (800 - 25), 600 - 25, 25, 25);
		foodType.SetVelocity(0, (rand() % 5 + 5) * -1);
		break;
	case 2:
		foodType.Init(0, rand() % (600 - 25), 25, 25);
		foodType.SetVelocity(rand() % 5 + 5, 0);
		break;
	case 3:
		foodType.Init(800 - 25, rand() % (600 - 25), 25, 25);
		foodType.SetVelocity((rand() % 5 + 5) * -1, 0);
		break;
	}
}

void RePosFood(ColourBlock& foodType)
{
	Transform2D Pos = foodType.GetTransform();

	if (foodType.GetVelocityX() > 0 && Pos.position.x > 800)
	{
		PositionFood(foodType, rand() % 4);
	}
	if (foodType.GetVelocityX() < 0 && Pos.position.x < 0)
	{
		PositionFood(foodType, rand() % 4);
	}
	if (foodType.GetVelocityY() > 0 && Pos.position.y > 600)
	{
		PositionFood(foodType, rand() % 4);
	}
	if (foodType.GetVelocityY() < 0 && Pos.position.y < 0)
	{
		PositionFood(foodType, rand() % 4);
	}
}