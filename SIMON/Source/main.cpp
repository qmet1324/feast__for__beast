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
	bool filled = true;

	srand(time(NULL));

	if (!Graphics::Init())
	{
		return false;
	}

	const int MAX_PATTERN_SIZE = 9;
	const int BOARDSIZE = 9;
	const int numFood = 3;

	int indexOrder[MAX_PATTERN_SIZE];

	for (int i = 0; i < MAX_PATTERN_SIZE; i++)
	{
		indexOrder[i] = rand() % BOARDSIZE;
	}
	int lvl = 1;

	// 2D array
	ColourBlock sumo;
	ColourBlock badFood[numFood];
	ColourBlock goodFood[numFood];
	ColourBlock ColorBlock[3][3];


	// where in the animation or entry is the current index
	int currentPatternIndex = 0;
	bool isAnimating = true;
	bool isBlankFrame = true;
	int currentPatternSize = 4;
	int randomNumberBad = 0;
	int randomNumberGood = 0;

	sumo.Init(800 / 2 - 25, 600 / 2 - 25, 25, 25);

	sumo.SetColor(0x00, 0x00, 0xFF);

	for (int i = 0; i < numFood; i++)
	{
		/*randomNumberBad = rand() % 4;
		switch (randomNumberBad)
		{
		case 0:
			badFood[i].Init(rand() % (800 - 25), 0, 25, 25);
			badFood[i].SetVelocity(0, rand() % 5 + 5);
			break;
		case 1:
			badFood[i].Init(rand() % (800 - 25), 600 - 25, 25, 25);
			badFood[i].SetVelocity(0, (rand() % 5 + 5) * -1);
			break;
		case 2:
			badFood[i].Init(0, rand() % (600 - 25), 25, 25);
			badFood[i].SetVelocity(rand() % 5 + 5, 0);
			break;
		case 3:
			badFood[i].Init(800 - 25, rand() % (600 - 25), 25, 25);
			badFood[i].SetVelocity((rand() % 5 + 5) * -1, 0);
			break;
		}

		randomNumberGood = rand() % 4;
		switch (randomNumberGood)
		{
		case 0:
			goodFood[i].Init(rand() % (800 - 25), 0, 25, 25);
			goodFood[i].SetVelocity(0, rand() % 5 + 5);
			break;
		case 1:
			goodFood[i].Init(rand() % (800 - 25), 600 - 25, 25, 25);
			goodFood[i].SetVelocity(0, (rand() % 5 + 5) * -1);
			break;
		case 2:
			goodFood[i].Init(0, rand() % (600 - 25), 25, 25);
			goodFood[i].SetVelocity(rand() % 5 + 5, 0);
			break;
		case 3:
			goodFood[i].Init(800 - 25, rand() % (600 - 25), 25, 25);
			goodFood[i].SetVelocity((rand() % 5 + 5) * -1, 0);
			break;
		}*/

		PositionFood(badFood[i], rand() % 4); // INitialize Positions and Speed of bad food
		badFood[i].SetColor(0xFF, 0x00, 0x00);

		PositionFood(goodFood[i], rand() % 4); // INitialize Positions Speed of good food
		goodFood[i].SetColor(0x00, 0xFF, 0x00);

	}

	// Main game loop
	while (GameRunning)
	{
		Graphics::StartRender();

		// handle button events
		GameRunning = EventHandler::Update();

		sumo.Draw(filled);
		for (int i = 0; i < numFood; i++)
		{
			badFood[i].Update();
			badFood[i].Draw(filled);
			goodFood[i].Update();
			goodFood[i].Draw(filled);

			//Transform2D badPos = badFood[i].GetTransform();
			//Transform2D goodPos = goodFood[i].GetTransform();

			//// Restarts positions and speed of bad food to random again
			//if (badFood[i].GetVelocityX() > 0 && badPos.position.x > 800)
			//{
			//	PositionFood(badFood[i], rand() % 4);
			//}
			//if (badFood[i].GetVelocityX() < 0 && badPos.position.x < 0)
			//{
			//	PositionFood(badFood[i], rand() % 4);
			//}
			//if (badFood[i].GetVelocityY() > 0 && badPos.position.y > 600)
			//{
			//	PositionFood(badFood[i], rand() % 4);
			//}
			//if (badFood[i].GetVelocityY() < 0 && badPos.position.y < 0)
			//{
			//	PositionFood(badFood[i], rand() % 4);
			//}

			//// Restarts positions and speed of good food to random again
			//if (goodFood[i].GetVelocityX() > 0 && goodPos.position.x > 800)
			//{
			//	PositionFood(goodFood[i], rand() % 4);
			//}
			//if (goodFood[i].GetVelocityX() < 0 && goodPos.position.x < 0)
			//{
			//	PositionFood(goodFood[i], rand() % 4);
			//}
			//if (goodFood[i].GetVelocityY() > 0 && goodPos.position.y > 600)
			//{
			//	PositionFood(goodFood[i], rand() % 4);
			//}
			//if (goodFood[i].GetVelocityY() < 0 && goodPos.position.y < 0)
			//{
			//	PositionFood(goodFood[i], rand() % 4);
			//}

			RePosFood(badFood[i]);
			RePosFood(goodFood[i]);
		}

		//for (int x = 0; x < 3; x++)
		//{
		//	for (int y = 0; y < 3; y++)
		//	{
		//		// sets location and size
		//		int xStart = 50 + (50 * x) + (10 * x + 1);
		//		int yStart = 50 + (50 * y) + (10 * y + 1);
		//		int width = 50;
		//		int height = 50;

		//		ColorBlock[x][y].Init(xStart, yStart, width, height);

		//		// rgb values from hexadecimal, full colour = 0xFF no colour = 0x00
		//		ColorBlock[x][y].SetColor(0xFF, 0x0F, 0x00);

		//		// does nothing right now, but in the future may...
		//		ColorBlock[x][y].Update();

		//		// Update the drawn paddles
		//		if (isAnimating && !isBlankFrame)
		//		{
		//			bool filledInside = indexOrder[currentPatternIndex] == x + y * 3;

		//			if (filledInside) // filled inside
		//			{
		//				ColorBlock[x][y].SetColor(0x00, 0x0FF, 0x00);
		//			}

		//			ColorBlock[x][y].Draw(filledInside);
		//		}
		//		else
		//		{
		//		ColorBlock[x][y].Draw();
		//		}

		//		Graphics::DrawText("Score: ", 0,0, 100, 50);
		//	}
		//}


		// apply the changes to the screen 
		Graphics::EndRender();
		// toggle the blank frame on
		isBlankFrame = !isBlankFrame;

		SDL_Delay(16);

		//if (isAnimating && !isBlankFrame)
		//{
		//	currentPatternIndex++;
		//	if (currentPatternIndex >= MAX_PATTERN_SIZE ||currentPatternIndex >= currentPatternSize)
		//	{
		//		// loop for now
		//		currentPatternIndex = 0;
		//		SDL_Delay(500);
		//		currentPatternSize++;

		//		if (currentPatternSize >= MAX_PATTERN_SIZE)
		//		{
		//			lvl++;
		//			isAnimating = false;
		//		}
		//	}
		//}
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