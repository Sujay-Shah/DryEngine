/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManager.cpp
Purpose: Generates and maintain events in game
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
Creation date: November 7, 2017.
- End Header --------------------------------------------------------*/
#include "EventManager.h"
#include "GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "FrameRateController.h"

extern FrameRateController *pFrameRateController;
extern GameObjectManager *pGameObjectManager;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
	for (auto e : mEvents)
	{
		delete e;
	}
	mEvents.clear(); 
}

void EventManager::AddTimedEvent(Event * pEvent)
{
	mEvents.push_back(pEvent);
}

void EventManager::BroadcastEvent(Event * pEvent)
{
	for (auto pGo : pGameObjectManager->m_GameObjects)
	{
		pGo->HandleEvent(pEvent);
	}
}

void EventManager::BroadcastEventToSubsrcibers(Event * pEvent)
{
	std::list<GameObject*>&listOfSubscribers = mSubscriptions[pEvent->mType];
	for (auto pGo : listOfSubscribers)
	{
		pGo->HandleEvent(pEvent);
	}
}

void EventManager::Update(float FrameTime)
{
	std::list<Event*>::iterator it, itEnd,itTemp;
	
	it = mEvents.begin();
	itEnd = mEvents.end();

	while (it!=itEnd)
	{
		Event *pEvent = *it;
		pEvent->mTimer -= FrameTime;
		if (pEvent->mTimer <= 0.0f)
		{
			//BroadcastEvent(pEvent);
			BroadcastEventToSubsrcibers(pEvent);
			delete pEvent;
			itTemp = it;
			++itTemp;
			mEvents.erase(it);
			it = itTemp;
		}
		else
			++it;
	}
}

void EventManager::Subscribe(EventType et, GameObject * pGO)
{
	std::list<GameObject*>&listOfSubscribers = mSubscriptions[et];
	if (std::find(listOfSubscribers.begin(), listOfSubscribers.end(), pGO) == listOfSubscribers.end())
	{
		listOfSubscribers.push_back(pGO);
	}
}

void EventManager::UnSubscribe(EventType et, GameObject *pObj) {

	std::list<GameObject*>&listOfSubscribers = mSubscriptions[et];
	std::list<GameObject*>::iterator it, itEnd, itTemp;


	while (it != itEnd)
	{
		
		if (*it ==pObj)
		{
			itTemp = it;
			++itTemp;
			listOfSubscribers.erase(it);
			it = itTemp;
		}
		else
			++it;
	}

}

Event::Event(EventType Type)
{ 
	mType = Type;
	mTimer = 0.0f;
	
}

MissileHitEvent::MissileHitEvent():Event(MISSILE_HIT)
{


}
