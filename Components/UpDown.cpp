/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Updown.cpp
Purpose: makes game objects go up and down
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
Creation date: October 6, 2017.
- End Header --------------------------------------------------------*/
#include "UpDown.h"
#include "Transform.h"
#include "Controller.h"
#include "../GameObject/GameObject.h"
#include "Body.h"

extern EventManager *pEventManager;
UpDown::UpDown():Component(COMPONENT_TYPE::COMPONENT_UPDOWN)
{
	 m_range = 0;
	 m_speed = 0;
	 m_counter = 0;
}


UpDown::~UpDown()
{
}

void UpDown::Update(float dt)
{
	

	Transform *pTrans = static_cast<Transform* >(m_pOwner->getComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	Body *pBody = static_cast<Body* >(m_pOwner->getComponent(COMPONENT_TYPE::COMPONENT_BODY));
	if (abs(m_counter)< m_range)
	{
		pBody->mBodyPos.y += m_speed;
		m_counter+=m_speed;
	}
	else
	{
		m_counter = 0;
		m_speed = -m_speed;
	}

}

void UpDown::Serialize(float range,float speed)
{
	m_range = range;
	m_speed = speed;
	pEventManager->Subscribe(EventType::PLAYER_HIT,this->m_pOwner);
}

void UpDown::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == EventType::PLAYER_HIT)
	{
		PlayerHitEvent *pRealEvent = (PlayerHitEvent*)pEvent;
		Body *pBody = static_cast<Body* >(m_pOwner->getComponent(COMPONENT_TYPE::COMPONENT_BODY));
		if (pBody)
			pBody->mBodyPos.x += 50.0f;
	}
}


