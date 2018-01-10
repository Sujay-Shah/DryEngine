/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Missile.cpp
Purpose: Spawns Player Missile
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
Creation date: December 2, 2017.
- End Header --------------------------------------------------------*/
#include "Missile.h"
#include "Body.h"
#include "../Managers/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "WrapAround.h"
#include "Transform.h"
#include "Sprite.h"
#include "../Managers/CollisionManager.h"

#include "../Maths/Math2D.h"
#include "../Maths/Vector2D.h"
#include "../Maths/Matrix2D.h"
#include "../Managers/EventManager.h"

#define MISSILE_SPEED 0.8
#define MISSILE_OFFSET 0.11
#define MISSILE_TURNRATE Pi/2.0f
extern GameObject* sgpShip;
extern EventManager *pEventManager;
glm::vec3 newVel;
Missile::Missile():Component(COMPONENT_HOMING_MISSILE)
{

	home_around_ = false;

	Body *shipBody = static_cast<Body*>(sgpShip->getComponent(COMPONENT_BODY));
	Transform *shipTrans = static_cast<Transform*>(sgpShip->getComponent(COMPONENT_TRANSFORM));

	GameObject *pMissile = new GameObject();
	Body *pBody = new Body();
	Transform *pTrans = new Transform;
	pTrans->mAngle = shipTrans->mAngle;
	pTrans->mScale = glm::vec3(0.1, 0.2, 0.0);
	pTrans->mPos = glm::vec3(9.1, 0.0, 0.0);
	pMissile->AddComponent(pTrans);
	pMissile->mObjType = ObjectType::MISSILE;

	pBody->mpShape = new ShapeCircle();
	ShapeCircle *pCircle = static_cast<ShapeCircle*>(pBody->mpShape);
	pCircle->mRadius = 0.06f;
	pCircle->mpBodyOwner = pBody;

	pBody->mBodyPos.x = shipBody->mBodyPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f)* MISSILE_OFFSET;
	pBody->mBodyPos.y = shipBody->mBodyPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f)* MISSILE_OFFSET;
	pBody->mMass = 0.2f;
	pBody->mBodyVel.x = MISSILE_SPEED*cosf((pTrans->mAngle + 90) *3.14f / 180.0f);
	pBody->mBodyVel.y = MISSILE_SPEED*sinf((pTrans->mAngle + 90) *3.14f / 180.0f);

	//set looks
	Sprite *pSprite = new Sprite();
	pSprite->Serialize("Graphics/textures/missileTexture.png");
	pMissile->AddComponent(pSprite);
	pMissile->AddComponent(pBody);
	pMissile->AddComponent(this);
	pGameObjectManager->mPendingObjects.push_back(pMissile);
	
}


Missile::~Missile()
{
}


void Missile::HandleEvent(Event* pEvent) {

	if (pEvent->mType == MISSILE_HIT) {

  		home_around_ = false;
		target = nullptr;
	}
}

void Missile::Update(float dt)
{
	// Hpming Missile Behaviour
	 {

		for (auto gameObjects : pGameObjectManager->m_GameObjects)
		{
			if (gameObjects->mObjType == ObjectType::ASTEROID)
			{
				home_around_ = true;
				if (!target) {

					target = gameObjects;
					break;
				}
			}
		}
	}


	 if (!home_around_) {

		 return;
	 }
	 home_around_ = false;


	 if (target == NULL)
	 {
		 for (auto gameObjects : pGameObjectManager->m_GameObjects)
		 {
			 if (gameObjects->mObjType == ObjectType::ASTEROID)
			 {
				 home_around_ = true;
				 if (!target) {

					 target = gameObjects;
					 break;
				 }
			 }
		 }
	 }
	Body *targetBody = static_cast<Body*>(target->getComponent(COMPONENT_BODY));
	Transform *targetTrans = static_cast<Transform*>(target->getComponent(COMPONENT_TRANSFORM));

	Body *missileBody = static_cast<Body*>(this->m_pOwner->getComponent(COMPONENT_BODY));
	Transform *missileTrans = static_cast<Transform*>(this->m_pOwner->getComponent(COMPONENT_TRANSFORM));

	Matrix2D rotation;
	Vector2D target_vector, normalized_target_vector, normal;
	float dist_target, cos_angle, angle, turn;
	

	Vector2D missileposition;
	Vector2DSet(&missileposition, missileBody->mBodyPos.x, missileBody->mBodyPos.y);


	Vector2D targetPosition;
	Vector2DSet(&targetPosition, targetBody->mBodyPos.x, targetBody->mBodyPos.y);


	// target vector
	Vector2DSub(&target_vector, &targetPosition, &missileposition);
	// unit vector in dir of target
	Vector2DNormalize(&normalized_target_vector, &target_vector);
	//distance between target and missile
//	Vector2DDistance(mis, mis->mpComponent_Target);
	//angle between normalized_target and missile

	Vector2D missileVel;
	Vector2DSet(&missileVel, missileBody->mBodyVel.x, missileBody->mBodyVel.y);
	cos_angle = Vector2DDotProduct(&normalized_target_vector, &missileVel);

	angle = glm::radians(acosf(cos_angle));
	//calculating normal
	Matrix2DRotRad(&rotation, 90);
	Matrix2DMultVec(&normal, &rotation, &missileVel);
	// DOT product for turning
	turn = Vector2DDotProduct(&normal, &target_vector);
	if (turn>0)
	{

		missileTrans->mAngle += glm::degrees(angle);

		Vector2D missinewVel;
		missinewVel.x = missileBody->mBodyVel.x;
		missinewVel.y = missileBody->mBodyVel.y;

		Vector2DFromAngleDeg(&missinewVel, (missileTrans->mAngle));
		Vector2DScale(&missinewVel, &missinewVel, .9f);
		missileBody->mBodyVel.x = missinewVel.x;
		missileBody->mBodyVel.y = missinewVel.y;
	}
	else
	{
		missileTrans->mAngle -= glm::degrees(angle);
		Vector2D missinewVel;
		missinewVel.x = missileBody->mBodyVel.x;
		missinewVel.y = missileBody->mBodyVel.y;

		Vector2DFromAngleDeg(&missinewVel, (missileTrans->mAngle));
		Vector2DScale(&missinewVel, &missinewVel, .9);
		missileBody->mBodyVel.x = missinewVel.x;
		missileBody->mBodyVel.y = missinewVel.y;

	}

	missileBody->mBodyVel.x = cosf((missileTrans->mAngle + 90)* 3.14 / 180.0f)*MISSILE_SPEED;
	missileBody->mBodyVel.y = sinf((missileTrans->mAngle + 90)* 3.14 / 180.0f)*MISSILE_SPEED;

}
