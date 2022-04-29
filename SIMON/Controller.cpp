#include "Controller.h"
#include <string>
#include <iostream>


using namespace std;

Controller::Controller()
{
	ControllerConnected = false;
}


Controller::~Controller()
{

}

void Controller::Update()
{

	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
	{
		printf("Controller %d connected\n", 0);
	}
}