// processing events
#include "EventHandler.h"
#include <ctime>
// creating a basic gameobject
#include "Objects/ColourBlock.h"
#include "../Graphics.h"

// GameState
bool GameRunning = true;

// argc and argv here are command line parameters passed to the program when running the program. 
// we won't actually use them but our 2D Graphics Library requires the main setup like this.
// Argc: the number of arguments pass
// argv[] : a char array of each of the params passed in ( each space is a new param)
int main( int argc, char *argv[] )
{
	srand(time(NULL));

	if (!Graphics::Init())
	{
		return false;
	}

	const int MAX_PATTERN_SIZE = 9;
	const int BOARDSIZE = 9;

	int indexOrder[MAX_PATTERN_SIZE];

	for (int i = 0; i < MAX_PATTERN_SIZE; i++)
	{
		indexOrder[i] = rand() % BOARDSIZE;
	}
	int lvl = 1;

	// 2D array
	ColourBlock ColourBlock[3][3];

	// where in the animation or entry is the current index
	int currentPatternIndex = 0;
	bool isAnimating = true;
	bool isBlankFrame = true;
	int currentPatternSize = 4;

	// Main game loop
	while (GameRunning) 
	{
		Graphics::StartRender();

		// handle button events
		GameRunning = EventHandler::Update();

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				// sets location and size
				int xStart = 50 + (50 * x) + (10 * x + 1);
				int yStart = 50 + (50 * y) + (10 * y + 1);
				int width = 50;
				int height = 50;

				ColourBlock[x][y].Init(xStart, yStart, width, height);

				// rgb values from hexadecimal, full colour = 0xFF no colour = 0x00
				ColourBlock[x][y].SetColor(0xFF, 0x0F, 0x00);

				// does nothing right now, but in the future may...
				ColourBlock[x][y].Update();

				// Update the drawn paddles
				if (isAnimating && !isBlankFrame)
				{
					bool filledInside = indexOrder[currentPatternIndex] == x + y * 3;

					if (filledInside) // filled inside
					{
						ColourBlock[x][y].SetColor(0x00, 0x0FF, 0x00);
					}

					ColourBlock[x][y].Draw(filledInside);
				}
				else
				{
					ColourBlock[x][y].Draw();
				}

				Graphics::DrawText("Jopa Slona", 0,0, 100, 50);
			}
		}

		// apply the changes to the screen 
		Graphics::EndRender();
		// toggle the blank frame on
		isBlankFrame = !isBlankFrame;

		SDL_Delay(500);

		if (isAnimating && !isBlankFrame)
		{
			currentPatternIndex++;
			if (currentPatternIndex >= MAX_PATTERN_SIZE ||currentPatternIndex >= currentPatternSize)
			{
				// loop for now
				currentPatternIndex = 0;
				SDL_Delay(500);
				currentPatternSize++;

				if (currentPatternSize >= MAX_PATTERN_SIZE)
				{
					lvl++;
					isAnimating = false;
				}
			}
		}
	}

	//close off the SDL window
	SDL_Quit();

	return true;
}
