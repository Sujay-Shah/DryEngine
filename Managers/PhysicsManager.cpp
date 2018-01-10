
/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsManager.cpp
Purpose: Resolves changes to the gameobject caused by physical forces
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
Creation date: November 9, 2017.
- End Header --------------------------------------------------------*/
#include<iostream>
#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "..\GameObject\GameObject.h"
#include "..\Components\Body.h"
#include "CollisionManager.h"
#include "..\Components\Transform.h"

bool Collide;
extern GameObjectManager *pGameObjectManager; 
PhysicsManager::PhysicsManager()
{
	mpCollisionManager = new CollisionManager();

}


PhysicsManager::~PhysicsManager()
{
	delete mpCollisionManager;
}

void PhysicsManager::Update(float dT)
{
	// Physics integration 
	for (auto game_object : pGameObjectManager->m_GameObjects)
	{
		Body *pBody = static_cast<Body*>(game_object->getComponent(COMPONENT_BODY));
		if (pBody != NULL)
		{
			pBody->Integrate(0.0f, dT);
		}
	}

	//clear prev contacts
	mpCollisionManager->Reset();

	//Check for collisions
	unsigned int go1,go2,goNum= pGameObjectManager->m_GameObjects.size();
	for (go1=0;go1<goNum;++go1)
	{
		Body *pBody1 = static_cast<Body*>(pGameObjectManager->m_GameObjects[go1]->getComponent(COMPONENT_BODY));
		if (pBody1 == NULL)
			continue;

		for (go2 = go1+1; go2 < goNum; ++go2)
		{
			Body *pBody2 = static_cast<Body*>(pGameObjectManager->m_GameObjects[go2]->getComponent(COMPONENT_BODY));
			if (pBody2 == NULL)
				continue;

 			if ((pBody1->m_pOwner->mObjType == ObjectType::BULLET && pBody2->m_pOwner->mObjType == ObjectType::SHIP) && (pBody2->m_pOwner->mObjType == ObjectType::BULLET && pBody1->m_pOwner->mObjType == ObjectType::SHIP))
				continue;
				Collide = mpCollisionManager->CheckCollisionAndGenerateContact(pBody1->mpShape,pBody1->mBodyPos.x,pBody1->mBodyPos.y, pBody2->mpShape, pBody2->mBodyPos.x, pBody2->mBodyPos.y);

		}
	}

	//advanced phys resolution
	//std::cout << "Number of contacts is\t" << mpCollisionManager->mContacts.size() << std::endl;



	for (auto contacs : mpCollisionManager->mContacts)
	{
		CollideEvent ce;
		ce.mpObj1 = contacs->mBodies[0]->m_pOwner; 
		ce.mpObj2 = contacs->mBodies[1]->m_pOwner;

		contacs->mBodies[0]->m_pOwner->HandleEvent(&ce);

		ce.mpObj1 = contacs->mBodies[1]->m_pOwner;
		ce.mpObj2 = contacs->mBodies[0]->m_pOwner;

		contacs->mBodies[1]->m_pOwner->HandleEvent(&ce);
	}




	//commit changes
	for (GameObject *pObj : pGameObjectManager->m_GameObjects)
	{
		Body *pBody=NULL;
		if(pObj->mObjType!=ObjectType::GUI)
		pBody = (Body*)pObj->getComponent(COMPONENT_BODY);

		Transform *pTrans = (Transform *)pObj->getComponent(COMPONENT_TRANSFORM);

		if (pBody&&pTrans)
		{
			pTrans->mPos.x = pBody->mBodyPos.x;
			pTrans->mPos.y= pBody->mBodyPos.y;
		}
	}
}

CollideEvent::CollideEvent():Event(EventType::COLLIDE)
{
	mpObj1 = mpObj2 = NULL;
}

CollideEvent::~CollideEvent()
{
}
