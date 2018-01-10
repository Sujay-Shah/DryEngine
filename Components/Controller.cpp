
/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Controller.cpp
Purpose:  Controller component for enabling input
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
- End Header --------------------------------------------------------*/#include "Controller.h"
#include "../Managers/InputManager.h"
#include "SDL_keyboard.h"
#include "../GameObject/GameObject.h"
#include "Transform.h"
#include "Component.h"
#include <iostream>
#include "Body.h"
#include "../Managers/FrameRateController.h"
#include "../Managers/EventManager.h"
#include "../Managers/PhysicsManager.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/CollisionManager.h"
#include "../Components/WrapDestroy.h"
#include "../Components/WrapAround.h"
#include "../Components/Missile.h"
#include "../GameObject/ObjectFactory.h"
#include "../GameObject/GameObject.h"
#include "../Managers/RenderManager.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm\glm.hpp>
#include "Sprite.h"

#define MISSILE_SPEED 0.8
#define MISSILE_OFFSET 0.11
#define MISSILE_TURNRATE 1
#define ACCELERATION 2
#define TURNRATE 2.5
#define BULLET_OFFSET 0.11
float  BULLET_SPEED = 1.6f;
extern Input_Manager *pInputManager;
extern FrameRateController *pFrameRateController;
extern EventManager *pEventManager;
extern GameObjectManager *pGameObjectManager;
extern GameObject* sgpShip;
extern ObjectFactory *objFactory;
extern RenderManager *pRenderManager;
bool fired=false;
int count = 1;

Controller::Controller() : Component(COMPONENT_TYPE::COMPONENT_CONTROLLER)
{
	m_pOwner = NULL;
}

Controller::~Controller()
{
	
}



void Controller::Update(float dt)
{
	
	if (pInputManager->IsKeyTriggered(SDL_SCANCODE_S))
	{
		objFactory->ResetLevel();
		objFactory->Loadlevel("Archetypes/level.json");
		return;
	}
	Transform *pTrans = static_cast<Transform* >(m_pOwner->getComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
	if (pTrans == NULL)
		return;
	
	Body *pBody=NULL;
	if (this->m_pOwner->mObjType != ObjectType::GUI)
	{
		pBody = static_cast<Body*>(m_pOwner->getComponent(COMPONENT_BODY));
		if (pBody == NULL)
			return;


		if (pInputManager->IsKeyPressed(SDL_SCANCODE_UP))
		{
			if (pBody != NULL)
			{
				pBody->mBodyForce.x = cosf((pTrans->mAngle + 90) *3.14 / 180);
				pBody->mBodyForce.y = sinf((pTrans->mAngle + 90) *3.14 / 180);

			}

		}
		if (pInputManager->IsKeyPressed(SDL_SCANCODE_DOWN))
		{

			pBody->mBodyForce.x = -cosf((pTrans->mAngle + 90) *3.14 / 180);
			pBody->mBodyForce.y = -sinf((pTrans->mAngle + 90) *3.14 / 180);
		}
		if (pInputManager->IsKeyPressed(SDL_SCANCODE_LEFT))
		{
			pTrans->mAngle += TURNRATE;

		}
		if (pInputManager->IsKeyPressed(SDL_SCANCODE_RIGHT))
		{
			pTrans->mAngle -= TURNRATE;

		}
		if (pInputManager->IsKeyPressed(SDL_SCANCODE_W))
		{
			pTrans->mScale.x += 0.01;
			pTrans->mScale.y += 0.01;
		}
		if (pInputManager->IsKeyTriggered(SDL_SCANCODE_P))
		{
			PowerUpEvent pe;
			pEventManager->BroadcastEvent(&pe);
		}

		if (pInputManager->IsKeyTriggered(SDL_SCANCODE_D))
		{
			count++;
			if (count % 2 == 0)
				pRenderManager->mDebug = true;
			else
				pRenderManager->mDebug = false;
		}
		if (pInputManager->IsKeyTriggered(SDL_SCANCODE_F))
		{
			std::cout << "Frame time is " << pFrameRateController->GetFrameTime() << " ms\n";
		}

		if (pInputManager->IsKeyTriggered(SDL_SCANCODE_SPACE))
		{
			FireBullets();

		}
		if (pInputManager->IsKeyTriggered(SDL_SCANCODE_M))
		{
			FireMissile();
			fired = true;
		}
	}
}
float dotProduct;
glm::vec3 normal, missileDir,normalizedVel;

void Controller::FireMissile()
{
	Missile *pMissile = new Missile();
}
void Controller::FireBullets()
{
	GameObject *pBullet = new GameObject();
	Transform *pTrans = new Transform();
	WrapDestroy *pWrapDestroy = new WrapDestroy();
	pBullet->AddComponent(pWrapDestroy);
	Body *pBody = new Body();
	Body *shipBody = static_cast<Body*>(sgpShip->getComponent(COMPONENT_BODY));
	Transform *shipTrans = static_cast<Transform*>(sgpShip->getComponent(COMPONENT_TRANSFORM));
	pBullet->mObjType = ObjectType::BULLET;
	//need to add shape before adding it to gameObject
	pBody->mpShape = new ShapeCircle();
	ShapeCircle *pCircle = static_cast<ShapeCircle*>(pBody->mpShape);
	pCircle->mRadius = 0.06f;
	pCircle->mpBodyOwner = pBody;

	//set bullet attrib
	pTrans->mAngle = shipTrans->mAngle;
	pTrans->mScale = glm::vec3(0.1, 0.1, 0.0);
	//pBody->mBodyPos = shipBody->mBodyPos;
	pTrans->mPos = glm::vec3(9.1, 0.0, 0.0);
	pBody->mBodyPos= glm::vec3(9.1, 0.0, 0.0);
	pBody->mBodyPos.x = shipBody->mBodyPos.x+ cosf((shipTrans->mAngle + 90) *3.14f / 180.0f)* BULLET_OFFSET;
	pBody->mBodyPos.y = shipBody->mBodyPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f)* BULLET_OFFSET;
	pBody->mMass = 0.2f;
	pBody->mBodyVel.x = BULLET_SPEED*cosf((pTrans->mAngle + 90) *3.14f / 180.0f);
	pBody->mBodyVel.y = BULLET_SPEED*sinf((pTrans->mAngle + 90) *3.14f / 180.0f);

	//set looks
	Sprite *pSprite = new Sprite();
	pSprite->Serialize("Graphics/textures/bulletTexture.png");
	pBullet->AddComponent(pSprite);
	pBullet->AddComponent(pTrans);
	pBullet->AddComponent(pBody);
	pGameObjectManager->mPendingObjects.push_back(pBullet);

	
}
void Controller::HandleEvent(Event * pEvent)
{
	
}

PlayerHitEvent::PlayerHitEvent() :Event(EventType::PLAYER_HIT)
{

}

PowerUpEvent::PowerUpEvent():Event(EventType::POWER_UP)
{
	
}
