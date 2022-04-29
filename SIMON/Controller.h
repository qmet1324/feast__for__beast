#define  WIN32_LEAN_AND_MEAN 1
//
#include "windows.h"
#include "xinput.h"

#pragma once
class Controller
{
	const float MAX_TRIGGER_VALUE = 255.0f;
	const float MAX_THUMB_VALUE = 32767.0f;

public:
	Controller();
	~Controller();

	void Update();

	// A
	bool IsAPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A); }

	// B
	bool IsBPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_B); }

	// X
	bool IsXPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_X); }

	// Y
	bool IsYPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_Y); }

	// Right Bumper
	bool IsRbPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER); }

	// Left Bumper
	bool IsLbPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER); }

	// start
	bool IsStartPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_START); }

	// back
	bool IsBackPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK); }

	// left thumbstick pressed
	bool IsLsPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB); }

	// right thumbstick pressed
	bool IsRsPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB); }

	//Dpad: 
	// up
	bool IsUpPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP); }

	// down
	bool IsDownPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN); }

	// left
	bool IsLeftPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT); }

	// right
	bool IsRightPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT); }

	//		Triggers:
	//			right trigger
	float GetRightTriggerValue() { return controllerState.Gamepad.bRightTrigger; }
	//			left trigger
	float GetLeftTriggerValue() { return controllerState.Gamepad.bLeftTrigger; }
	//		Analog Sticks
	//			analog right X
	float GetRightStickXValue() { return controllerState.Gamepad.sThumbRX; }
	//			analog right Y
	float GetRightStickYValue() { return controllerState.Gamepad.sThumbRY; }
	//			analog left X
	float GetLeftStickXValue() { return controllerState.Gamepad.sThumbLX; }
	//			analog left Y
	float GetLeftStickYValue() { return controllerState.Gamepad.sThumbLY; }

private:

	XINPUT_STATE controllerState;
	bool ControllerConnected;
};

