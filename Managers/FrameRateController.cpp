/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateConroller.cpp
Purpose: managing frames per second in the game
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
#include "FrameRateController.h"
#include "limits.h"
#include "SDL_timer.h"
FrameRateController::FrameRateController(unsigned int MaxFrameRate)
{
	if (MaxFrameRate == 0)
		MaxFrameRate = UINT_MAX;
	mMaxFrameRate = MaxFrameRate;
	mTicksPerFrame = 1000 / mMaxFrameRate;

	mTickStart = 0;
	mTickEnd = 0;
	mframeTime = 0;
}

FrameRateController::~FrameRateController()
{
}

void FrameRateController::FrameStart()
{
	mTickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd()
{
	//get ticks not very accurate
	mTickEnd = SDL_GetTicks();
	while (mTickEnd - mTickStart < mTicksPerFrame)
		mTickEnd = SDL_GetTicks();
	mframeTime = mTickEnd - mTickStart;
	//get performance query more accurate
}

unsigned int FrameRateController::GetFrameTime()
{
	return mframeTime;
}
