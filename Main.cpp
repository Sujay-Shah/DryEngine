/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: main game loop
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

Project: 		CS529_sujay.shah_1

Author: Name: Sujay Shah ;  Login: sujay.shah  ; Student ID : 60001517
Creation date: October 15, 2017.
- End Header --------------------------------------------------------*/
#include <SDL.h>
#include "stdio.h"
#include "Managers/InputManager.h"
#include "Managers/FrameRateController.h"
#include "Managers/RenderManager.h"
#include "Windows.h"
#include "Managers/ResourceManager.h"
#include "Managers/GameObjectManager.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "GameObject/GameObject.h"
#include "Components/Controller.h"
#include "GameObject/ObjectFactory.h"
#include "Components/Body.h"
#include "Managers/PhysicsManager.h"
#include "Managers/EventManager.h"
#include "GL\glew.h"
#include "Graphics\Shader.h"
#include <glm\glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <ctime>
//#define STBI_MALLOC
//#define  STBI_REALLOC
//#define STBI_FREE

EventManager *pEventManager;
Input_Manager *pInputManager; 
FrameRateController *pFrameRateController;
GameObjectManager *pGameObjectManager;
ResourceManager *pResourceManager;
PhysicsManager *pPhysicsManager;
RenderManager *pRenderManager;
ObjectFactory *objFactory;
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

//static global ship pointer
GameObject* sgpShip;

int PlayerLives = 3;


int main(int argc, char* args[])
{
	srand(static_cast <unsigned> (time(0)));

	//creating a console for debugging
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}

	bool appIsRunning = true;
	pGameObjectManager = new GameObjectManager();
	pInputManager= new Input_Manager();
	//Set desired frame rate in constructor
	pFrameRateController = new FrameRateController(60);
	pResourceManager = new ResourceManager();
	SDL_Surface *pWindowSurface = NULL;
	objFactory = new ObjectFactory();
	pPhysicsManager = new PhysicsManager();
	pEventManager = new EventManager();
	pRenderManager = new RenderManager();
	

	// Load game 
	objFactory->Loadlevel("Archetypes/Start/start.json");
	//objFactory->Loadlevel("Archetypes/level.json");

	// Game loop
	while(true == appIsRunning)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}
		}
		pFrameRateController->FrameStart();

		float dt = pFrameRateController->GetFrameTime() / 1000.0f;

		// put objected created in queue in main gameobject vector
		pInputManager->Update();
		pGameObjectManager->Update(dt);
		pPhysicsManager->Update(dt);
		pEventManager->Update(dt);
		pRenderManager->Update();
		pGameObjectManager->DestroyOutOfBound();
		pGameObjectManager->pushIntoGoQ();
		pFrameRateController->FrameEnd();
	}

	delete pPhysicsManager;
	delete pFrameRateController;
	delete pResourceManager;
	delete pInputManager;
	delete pGameObjectManager;
	delete pEventManager;
	delete pRenderManager;

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}