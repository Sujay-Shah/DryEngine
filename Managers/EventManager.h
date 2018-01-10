/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManager.h
Purpose: Skeleton for EventManager.cpp
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
#pragma once
#include <vector>
#include <unordered_map>
class GameObject;
enum  EventType
{
	COLLIDE,
	PLAYER_HIT,
	POWER_UP,
	MISSILE_HIT,
	TOTAL_EVENTS
};

class Event
{
public:
	Event(EventType Type);
	virtual ~Event() {}

public:
	EventType mType;
	float mTimer;
}; 

class MissileHitEvent :public Event {

public:
	MissileHitEvent();
	~MissileHitEvent() = default;

};


class EventManager
{
public:
	EventManager();
	~EventManager();

	void AddTimedEvent(Event *pEvent);
	void BroadcastEvent(Event *pEvent);
	void BroadcastEventToSubsrcibers(Event *pEvent);
	void Update(float FrameTime);
	void Subscribe(EventType et,GameObject *pObj);
	void UnSubscribe(EventType et, GameObject *pObj);
public:
	std::list<Event*> mEvents;
	std::unordered_map < EventType, std::list<GameObject*>>mSubscriptions;
};