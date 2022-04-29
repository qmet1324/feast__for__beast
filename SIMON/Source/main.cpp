// processing events
#include "EventHandler.h"
#include <ctime>

// creating a basic gameobject
#include "Objects/ColourBlock.h"
#include "../Graphics.h"

#include <iostream>
#include <fstream>
#include <string>
#include "../Controller.h"

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
	string scoreString;
	int bestScore = 0;
	char bScore[10];
	string bScoreString;
	int currentLives = 5;
	char lives[10];
	int timer = 0;
	int level = 1;
	int scoreRemember = 0;
	Controller* xboxController = new Controller;

	bool filled = true;

	SDL_Color Red = { 255, 0, 0 };
	SDL_Color Green = { 0, 255, 0 };
	SDL_Color Blue = { 0, 0, 255 };
	SDL_Color Yellow = { 255, 255, 0 };
	SDL_Color Cyan = { 0, 255, 255 };
	SDL_Color Magenta = { 255, 0, 255 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	srand(time(NULL));
	

	//
	// @todo: i have made an exception, which checks if all subsystems have been loaded successfully, but it doesn't show anything,
	// i was trying to find where i can see the console when we compile the program as we usually have in James labs,
	// but i didn't find out how you can see it when compiling it. Maybe it's a specific setting, who knows.
	//
	try
	{
		Graphics::Init();
	}
	catch (bool)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		GameRunning = false;
	}

	// Objects
	ColourBlock sumo;
	ColourBlock badFood[NUM_FOOD];
	ColourBlock goodFood[NUM_FOOD];
	ColourBlock* blowfish = new ColourBlock[level];
	ColourBlock background;
	
	// Initialize Background Image
	background.Init(0, 0, 800, 600);
	background.SetColor(0xFF, 0x00, 0x00);

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
	PositionFood(blowfish[0], rand() % 4);
	blowfish[0].SetColor(0xFF, 0xFF, 0x00);

	//Initialize Best score
	ifstream inFile;
	inFile.open("Best_Score.txt");
	getline(inFile, bScoreString, '\n');
	inFile.close();
	bestScore = std::stoi(bScoreString);

	// Main game loop
	while (GameRunning)
	{
		Graphics::StartRender();

		static Uint32 count = 0;

		// handle button events
		GameRunning = EventHandler::Update();

		background.Draw(Graphics::bg_sprite, filled); // Draw background

		sumo.Draw(Graphics::sumo_sprite,filled); // Draw Player
		
		// Move with keyboard (WSAD)
		sumo.Move();

		// Move with xbox controller (d-pad and Left Analog Stick) // Added a deadzone of 0.5 to the joystick so the character won't move with a small move of the joystick and to compensate my own controller drift.
		xboxController->Update();

		if ((xboxController->IsUpPressed() || xboxController->GetLeftStickYValue() / 32767.0f > 0.5) && sumo.GetPositionY() > 0)
		{
			sumo.SetPosition(0, -10);
		}
		if ((xboxController->IsDownPressed() || xboxController->GetLeftStickYValue() / 32767.0f < -0.5) && sumo.GetPositionY() < WINDOW_HEIGHT - 50)
		{
			sumo.SetPosition(0, 10);
		}
		if ((xboxController->IsLeftPressed() || xboxController->GetLeftStickXValue() / 32767.0f < -0.5) && sumo.GetPositionX() > 0)
		{
			sumo.SetPosition(-10, 0);
		}
		if ((xboxController->IsRightPressed() || xboxController->GetLeftStickXValue() / 32767.0f > 0.5) && sumo.GetPositionX() < WINDOW_WIDTH - 50)
		{
			sumo.SetPosition(10, 0);
		}

		for (int i = 0; i < NUM_FOOD; i++)
		{
			badFood[i].Update();
			goodFood[i].Update();

			if (i % 3 == 0) // Draw apples
			{
				badFood[i].Draw(Graphics::bFood_apple, filled);
				goodFood[i].Draw(Graphics::gFood_apple, filled);
			}

			if (i % 3 == 1) // Draw onigiri
			{
				badFood[i].Draw(Graphics::bFood_onigiri, filled);
				goodFood[i].Draw(Graphics::gFood_onigiri, filled);
			}

			if (i % 3 == 2) // Draw fish
			{
				badFood[i].Draw(Graphics::bFood_fish, filled);
				goodFood[i].Draw(Graphics::gFood_fish, filled);
			}

			// Collision Detecttion bad food
			if (checkCollision(sumo, badFood[i]) && currentScore > 0)
			{
				currentScore -= 50;
			}

			// Collision Detecttion good food
			if (checkCollision(sumo, goodFood[i]))
			{
				currentScore += 100;
				// Increase difficulty
				if (currentScore % 1000 >= 0 && currentScore % 1000 <= 50 && currentScore > 0)
				{
					if (scoreRemember <= currentScore)
					{
						// Initialize more blowfish

						scoreRemember = currentScore;
						level++;
						PositionFood(blowfish[level-1], rand() % 4);
						blowfish[level-1].SetColor(0xFF, 0xFF, 0x00);
					}
				}
			}

			// Respawn Food
			RePosFood(badFood[i], sumo);
			RePosFood(goodFood[i], sumo);
		}

		

		// Render Blowfish
		
		for (int i = 0; i < level; i++)
		{
			if (currentLives != 0)
			{
				blowfish[i].Update();
				blowfish[i].Draw(Graphics::bFood_blowFish, filled);
				if (checkCollision(sumo, blowfish[i]))
				{
					RePosFood(blowfish[i], sumo);
					currentLives--;
					sumo.Init(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 50, 50, 50);
				}
				RePosFood(blowfish[i], sumo);
			}
		}

		

		// Collision Detecttion

		// Draw text
		// Score Text
		_itoa_s(currentScore, score, 10);
		if (strlen(score) == 1)
		{
			scoreString = "000";
			scoreString.append(score);
			strcpy_s(score, scoreString.c_str());
		}		
		else if (strlen(score) == 2)
		{
			scoreString = "00";
			scoreString.append(score);
			strcpy_s(score, scoreString.c_str());
		}
		else if (strlen(score) == 3)
		{
			scoreString = "0";
			scoreString.append(score);
			strcpy_s(score, scoreString.c_str());
		}

		Graphics::DrawSDLText("scorE: ", 0, 10, 100, 50, Yellow);
		Graphics::DrawSDLText(score, 110, 10, 100, 50, Yellow);

		// Lives Text
		_itoa_s(currentLives, lives, 10);
		Graphics::DrawSDLText("LivEs: ", WINDOW_WIDTH - 125, 10, 100, 50, Red);
		Graphics::DrawSDLText(lives, WINDOW_WIDTH - 25, 10, 25, 50, Red);


		// Best Score Text
		if (currentScore >= bestScore)
		{
			bestScore = currentScore;
		}

		_itoa_s(bestScore, bScore, 10);

		if (strlen(bScore) == 1)
		{
			bScoreString = "000";
			bScoreString.append(bScore);
			strcpy_s(bScore, bScoreString.c_str());
		}
		else if (strlen(bScore) == 2)
		{
			bScoreString = "00";
			bScoreString.append(bScore);
			strcpy_s(bScore, bScoreString.c_str());
		}
		else if (strlen(bScore) == 3)
		{
			bScoreString = "0";
			bScoreString.append(bScore);
			strcpy_s(bScore, bScoreString.c_str());
		}

		Graphics::DrawSDLText("BEst sCORE: ", 0, 60, 200, 50, Black);
		Graphics::DrawSDLText(bScore, 220, 60, 100, 50, Black);

		if (currentLives <= 0)
		{
			GameRunning = false;
		}

		Graphics::EndRender();

		SDL_Delay(16);
	}


	Graphics::DrawSDLText("Game Over", WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 25, 100, 50, White);

	// Send Best Score to Score text file
	ofstream outFile;
	outFile.open("Best_Score.txt");
	outFile << bestScore;
	outFile.close();

	// Delete heap memory
	

	//close off the SDL window
	SDL_Quit();

	// Delete Heap Memory
	delete xboxController;
	delete[] blowfish;
	return true;
}

void PositionFood(ColourBlock& foodType, int randomNumber) // Position Food at random spawnpoints and velocities.
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

void RePosFood(ColourBlock& foodType, ColourBlock& player) // RePosition Food at random spawnpoints and velocities after player collision or food leaving the screen.
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

bool checkCollision(ColourBlock A, ColourBlock B) // Collision detector
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