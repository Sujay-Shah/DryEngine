/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Body.cpp
Purpose: RigidBody component for game object through which physics can be applied
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
Creation date: November 5, 2017.
- End Header --------------------------------------------------------*/

#include "Body.h"
#include "Transform.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/serial-data.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/EventManager.h"
#include "../Managers/PhysicsManager.h"
#include<iostream>
#include "../GameObject/ObjectFactory.h"
#include "../Managers/RenderManager.h"
#include "../Components/AsteroidSpawner.h"
#include "../Components/EnemySpawner.h"

extern ObjectFactory *objFactory;
extern RenderManager* pRenderManager;
extern EventManager* pEventManager;
//extern int asteroidCount;
extern GameObject* sgpShip;
float drag = 0.99f;
extern int PlayerLives;


Body::Body() :Component(COMPONENT_BODY)
{
	m_pOwner = NULL;

	mMass = mInvMass = 0.0f;
	mBodyPos = glm::vec3(0.0f);
	mBodyVel = glm::vec3(0.0f);
	mBodyAcc = glm::vec3(0.0f);
	mBodyForce = glm::vec3(0.0f);
	mPrevBodyPos = glm::vec3(0.0f);
	mpShape = NULL;
}
Body::~Body()
{
}

void Body::Update(float dt)
{
}

void Body::Integrate(float g, float dT)
{
	
	mPrevBodyPos = mBodyPos;

	mBodyForce.y += g;

	mBodyAcc = mBodyForce*mInvMass;

	if (this->m_pOwner->mObjType == ::ObjectType::SHIP)
		mBodyVel = (mBodyAcc*dT + mBodyVel)*drag;
	else
		mBodyVel = mBodyAcc*dT + mBodyVel;

	mBodyPos = mBodyVel*dT + mBodyPos;
	mBodyForce = glm::vec3(0.0f);
	Transform *pTrans = static_cast<Transform*>(m_pOwner->getComponent(COMPONENT_TRANSFORM));
	if(pTrans!=NULL)
	{ 
		pTrans->mPos = mBodyPos;
	}
}

void Body::Serialize(struct bodyval* sbody)
{
	mMass = sbody->bmass;
	if (mMass)
		mInvMass = 1.0f / mMass;
	else
		mInvMass = 0.0f;
	
	if (strcmp(sbody->bshape, "circle") == 0)
	{
		mpShape = new ShapeCircle();
		mpShape->mpBodyOwner = this;
		ShapeCircle *pCircle = static_cast<ShapeCircle*>(mpShape);
		pCircle->mRadius = sbody->bradius;
	}
	//init with the object's transform
	Initialise();
}

void Body::Initialise()
{
	Transform *pTrans = static_cast<Transform*>(m_pOwner->getComponent(COMPONENT_TRANSFORM));
	if (pTrans!=NULL)
	{
		mBodyPos = mPrevBodyPos = pTrans->mPos;
	}
}

void Body::HandleEvent(Event * pEvent)
{
	AsteroidSpawner *pAsteroidSpawner = static_cast<AsteroidSpawner*>(sgpShip->getComponent(COMPONENT_ASTEROID_SPAWNER));
	
	//Handle Collide Events between gameobjects containing body
	if (pEvent->mType == EventType::COLLIDE)
	{
		CollideEvent *pCollide = (CollideEvent*)pEvent;
		
		Body *pBody;
		if (pCollide->mpObj1->mObjType == ObjectType::SHIP && pCollide->mpObj2->mObjType == ObjectType::ASTEROID||
			pCollide->mpObj1->mObjType == ObjectType::SHIP && pCollide->mpObj2->mObjType == ObjectType::ENEMY)
		{
			
			MissileHitEvent me;
			pEventManager->BroadcastEvent(&me);

				pBody = static_cast<Body*>(pCollide->mpObj1->getComponent(COMPONENT_BODY));
				EnemySpawner *pEnemySpawner = static_cast<EnemySpawner*>(pCollide->mpObj2->getComponent(COMPONENT_ENEMY_SPAWNER));
			if (pBody)
			{
				PlayerLives--;
				
				pBody->mBodyPos = glm::vec3(0.0f);
				std::cout << "Remaining Lives: " << PlayerLives << std::endl;
			}
	
				pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj2);

			//--asteroidCount;
				if (pCollide->mpObj2->mObjType == ObjectType::ASTEROID)
				{
					pAsteroidSpawner->asteroidCount--;
					pAsteroidSpawner->totalDestroyed++;
				}
				/*if (pCollide->mpObj2->mObjType == ObjectType::ENEMY)
				{
					pEnemySpawner->missileCount--;
					pEnemySpawner->missileTotalDestroyed++;
				}*/
			if (PlayerLives <= 0)
			{
				pRenderManager->mDebug = false;
				printf("Congrats! Total Asteroids Destroyed : %d\n", pAsteroidSpawner->totalDestroyed);
				objFactory->ResetLevel();
				objFactory->Loadlevel("Archetypes/GameOver/gameOver.json");

			}
		}
		
		if (pCollide->mpObj2->mObjType == ObjectType::ASTEROID&&pCollide->mpObj1->mObjType == ObjectType::BULLET)
		{
	 		pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj1);
			pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj2);
			//--asteroidCount;
			pAsteroidSpawner->asteroidCount--;
			pAsteroidSpawner->totalDestroyed++;

			MissileHitEvent me;
			pEventManager->BroadcastEvent(&me);
		}

		if (pCollide->mpObj1->mObjType == ObjectType::ASTEROID&&pCollide->mpObj2->mObjType == ObjectType::MISSILE)
		{
			pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj1);
			pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj2);


			pAsteroidSpawner->asteroidCount--;
			pAsteroidSpawner->totalDestroyed++;
			//--asteroidCount;
			MissileHitEvent me;
	 		pEventManager->BroadcastEvent(&me);
		}
		if(pCollide->mpObj1->mObjType == ObjectType::ENEMY&&pCollide->mpObj2->mObjType == ObjectType::BULLET)
		{
			EnemySpawner *pEnemySpawner = static_cast<EnemySpawner*>(pCollide->mpObj2->getComponent(COMPONENT_ENEMY_SPAWNER));
	
			pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj1);
			pGameObjectManager->mDestroyQ.push_back(pCollide->mpObj2);
			
			/*pEnemySpawner->missileCount--;
			pEnemySpawner->missileTotalDestroyed++;*/
		}
	}
}
