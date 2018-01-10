/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemySpawner.cpp
Purpose: Spawns enemy missile
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
Creation date: December 5, 2017.
- End Header --------------------------------------------------------*/
#include "EnemySpawner.h"
#include "Body.h"
#include "../Managers/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "WrapAround.h"
#include "Transform.h"
#include "Sprite.h"
#include "../Managers/CollisionManager.h"
#include <cstdlib>
#include <ctime>
#include "../Maths/Math2D.h"
#include "../Maths/Vector2D.h"
#include "../Maths/Matrix2D.h"

#define MISSILE_SPEED 0.5
#define MISSILE_OFFSET 0.11
#define MISSILE_TURNRATE 4
extern GameObject* sgpShip;
GameObject *enemyMissile;
EnemySpawner::EnemySpawner():Component(COMPONENT_ENEMY_SPAWNER)
{
	missileCount = 0;
	missileTotalDestroyed = 0;
}


EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Update(float dt)
{
	
	if (missileCount <= 0)
	{
		spawnMisile();
		return;
	}
	if (target == NULL)
		target = sgpShip;
	

	Body *targetBody = static_cast<Body*>(sgpShip->getComponent(COMPONENT_BODY));
	Transform *targetTrans = static_cast<Transform*>(sgpShip->getComponent(COMPONENT_TRANSFORM));

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

void EnemySpawner::spawnMisile()
{
	target = sgpShip;
	missileCount++;
	enemyMissile = new GameObject();
	Body *pBody = new Body();
	WrapAround *pWrap = new WrapAround();
	enemyMissile->AddComponent(pWrap);
	Transform *pTrans = new Transform;

	//generate random  values
	pTrans->mAngle = rand() % 360 + 0;
	//gen values b/w 0-1
	missileSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	pTrans->mScale = glm::vec3(0.2f, 0.2f, 0.0f);
	enemyMissile->AddComponent(pTrans);
	/*pBody->mBodyPos.x = posX1[rand() % 10 + 0];
	pBody->mBodyPos.x = posY1[rand() % 10 + 0];*/
	pBody->mBodyPos = glm::vec3(-0.9f,-0.9f,0.0f);
	enemyMissile->mObjType = ObjectType::ENEMY;

	pBody->mpShape = new ShapeCircle();
	ShapeCircle *pCircle = static_cast<ShapeCircle*>(pBody->mpShape);
	pCircle->mRadius = 0.06f;
	pCircle->mpBodyOwner = pBody;

	pBody->mMass = 0.2f;

	pBody->mBodyVel.x = missileSpeed*cosf((pTrans->mAngle + 90) *3.14f / 180.0f);
	pBody->mBodyVel.y = missileSpeed*sinf((pTrans->mAngle + 90) *3.14f / 180.0f);

	//set looks
	Sprite *pSprite = new Sprite();
	pSprite->Serialize("Graphics/textures/enemy_missile.png");
	enemyMissile->AddComponent(pSprite);
	enemyMissile->AddComponent(pBody);
	//pAsteroid->AddComponent(this);
	pGameObjectManager->mPendingObjects.push_back(enemyMissile);
}
