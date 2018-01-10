/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: InputManager.cpp
Purpose: handling input  
Language: C/C++ using Visual Studio 2015
Platform: Visual Studio 2015,
Hardware Requirements: 	1.6 GHz or faster processor
1 GB of RAM (1.5 GB if running on a virtual machine)
4 GB of available hard disk space 5400 RPM hard disk drive
DirectX 9-capable video card (1024 x 768 or higher resolution)
Operating Systems:	Windows 10
Windows 8.1
Windows 8
Windows 7 SP 1
Windows Server 2012 R2
Windows Server 2012
Windows Server 2008 R2 SP1

Project: 		CS529_sujay.shah_FinalProject_Milestone1

Author: Name: Sujay Shah ;  Login: sujay.shah  ; Student ID : 60001517
Creation date: October 15, 2017.
- End Header --------------------------------------------------------*/
#include "InputManager.h"
#include "SDL_config.h"
#include "memory.h"
#include "SDL_keyboard.h"
Input_Manager::Input_Manager()
{
	// Initialize keyboard state 
	memset(mCurrentState,0,512*sizeof(Uint8));
	memset(mPreviousState, 0, 512 * sizeof(Uint8));
}

Input_Manager::~Input_Manager()
{

}

void Input_Manager::Update()
{
	int fetchedNum = 0;
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(&fetchedNum);
	
	if (fetchedNum > 512)fetchedNum = 512;

	//copy from current -> previous
	memcpy(mPreviousState, mCurrentState, 512 * sizeof(Uint8));
	//fill current with new data
	memcpy(mCurrentState,currentKeyStates,fetchedNum*sizeof(Uint8));
} 

bool Input_Manager::IsKeyPressed(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::IsKeyTriggered(unsigned int KeyScanCode)
{
	if(KeyScanCode>=512)
	return false;

	if (mCurrentState[KeyScanCode] && !mPreviousState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::IsKeyReleased(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (!mCurrentState[KeyScanCode] && mPreviousState[KeyScanCode])
		return true;

	return false;
}
