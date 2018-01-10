/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.cpp
Purpose: Manages creation and deletion of game objects
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
Creation date: October 19, 2017.
- End Header --------------------------------------------------------*/
#include "GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../Managers/EventManager.h"
extern EventManager* pEventManager;

GameObjectManager::GameObjectManager()
{
	
}

GameObjectManager::~GameObjectManager()
{
	for (auto game_obj : m_GameObjects)
		delete game_obj;

	m_GameObjects.clear();
	
}

void GameObjectManager::Update(float dt) 
{
	/*for (auto gameObject : m_GameObjects) {
		gameObject->Update(dt);
	}
	*/

	for (int i = 0; i < m_GameObjects.size(); i++) {

		m_GameObjects[i]->Update(dt);
	}

}

//push game object after updating current state
void GameObjectManager::pushIntoGoQ()
{
	for (auto gameObject : mPendingObjects)
	{
		m_GameObjects.push_back(gameObject);
	}
	//clear vector after pushing into main Q
	mPendingObjects.clear();
}
//destroy game object that are out of bound or no longer needed
void GameObjectManager::DestroyOutOfBound()
{

	for (auto gameObject : mDestroyQ)
	{
		auto itr = std::find(m_GameObjects.begin(), m_GameObjects.end(), gameObject);
		if (itr !=m_GameObjects.end())
		{
		//	pEventManager->UnSubscribe(MISSILE_HIT, *itr);
 			delete *itr;
			m_GameObjects.erase(itr);
		}
	}
	//clear Q 
	mDestroyQ.clear();
}
