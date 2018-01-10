/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: AsteroidSpawner.cpp
Purpose: Spawns Asteroids at random objects
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
Creation date: December 3, 2017.
- End Header --------------------------------------------------------*/

#include "AsteroidSpawner.h"
#include "Body.h"
#include "../Managers/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "WrapAround.h"
#include "Transform.h"
#include "Sprite.h"
#include "../Managers/CollisionManager.h"
#include <cstdlib>
#include <ctime>


// pool of spawn co-ordinates to choose from
float posX[10] = { 0.69f,-0.45f,0.42f,-0.14f ,-0.1f,0.202f,-0.8,0.0f,0.39f,0.11f };
float posY[10] = { -0.70f,-0.9f,0.97f,-0.81f,0.72f,0.62f,-0.98f,0.99f,-0.89f,0.69f };



AsteroidSpawner::AsteroidSpawner():Component(COMPONENT_ASTEROID_SPAWNER)
{
	asteroidCount = 0;
	totalDestroyed = 0;
}


AsteroidSpawner::~AsteroidSpawner()
{
}


void AsteroidSpawner::Update(float dt)
{
	if (asteroidCount <= 0)
	{
		int num = rand() % 5 + 3;
		for(int i=0;i<num;i++)
		SpawnAstroids();
	}
}

void AsteroidSpawner::SpawnAstroids()
{
		asteroidCount++;
		GameObject *pAsteroid = new GameObject();
		Body *pBody = new Body();
		WrapAround *pWrap = new WrapAround();
		pAsteroid->AddComponent(pWrap);
		Transform *pTrans = new Transform;

		//generate random  values
		pTrans->mAngle = rand() % 360 + 0;
		//gen values b/w 0-1
		asteroidSpeed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		pTrans->mScale = glm::vec3(0.2f,0.2f,0.0f);
		pAsteroid->AddComponent(pTrans);
		//generate random spawn locations for asteroids
		pBody->mBodyPos.x = posX[rand() % 10 + 0];
		pBody->mBodyPos.x = posY[rand() % 10 + 0];

		pAsteroid->mObjType = ObjectType::ASTEROID;

		pBody->mpShape = new ShapeCircle();
		ShapeCircle *pCircle = static_cast<ShapeCircle*>(pBody->mpShape);
		pCircle->mRadius = 0.06f;
		pCircle->mpBodyOwner = pBody;
		pBody->mMass = 0.2f;

		pBody->mBodyVel.x = asteroidSpeed*cosf((pTrans->mAngle + 90) *3.14f / 180.0f);
		pBody->mBodyVel.y = asteroidSpeed*sinf((pTrans->mAngle + 90) *3.14f / 180.0f);

		//set looks
		Sprite *pSprite = new Sprite();
		pSprite->Serialize("Graphics/textures/asteroidTexture.png");
		pAsteroid->AddComponent(pSprite);
		pAsteroid->AddComponent(pBody);
		//pAsteroid->AddComponent(this);
		pGameObjectManager->mPendingObjects.push_back(pAsteroid);
}
