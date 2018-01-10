/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ObjectFactory.cpp
Purpose: creates new game objects and assigns serialized properties to them.
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
Creation date: October 25, 2017.
- End Header --------------------------------------------------------*/
#include "ObjectFactory.h"
#include <iostream>
#include <cstdio>
#include "GameObject.h"
#include "../Managers/GameObjectManager.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include "../Components/Controller.h"
#include "../Components/UpDown.h"
#include "../Components/Body.h"
#include "serial-data.h"
#include "../Managers/CollisionManager.h"
#include "document.h"
#include "filereadstream.h"
#include "../Components/WrapAround.h"
#include "../Components/Component.h"
#include "../Components/AsteroidSpawner.h"
#include "../Components/EnemySpawner.h"

extern GameObjectManager *pGameObjectManager;

extern GameObject* sgpShip;
ObjectFactory::ObjectFactory()
{
	GameObjectManager *pGameObjectManager = new GameObjectManager();
}


ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::Loadlevel(const  char *pFilepath)
{
	rapidjson::Document d;
	FILE* fp = fopen(pFilepath, "rb"); 
	if (fp == NULL)
	{
		return ;
	}
	GameObject *pGameObject = nullptr;

	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	d.ParseStream(is);
	fclose(fp);

	for (rapidjson::Value::ConstMemberIterator lvl_itr = d.MemberBegin();lvl_itr != d.MemberEnd(); ++lvl_itr)
	{
		// for getting object values---------------------------------------------
		if (lvl_itr->value.IsObject())
		{
			std::cout << lvl_itr->name.GetString() << std::endl;
			auto obj1 = lvl_itr->value.GetObject();
			for (auto obj_itr = obj1.MemberBegin(); obj_itr != obj1.MemberEnd(); ++obj_itr)
			{
				
				//loading archetypes-------------------------------------------
				if (strcmp(obj_itr->name.GetString(), "archetype") == 0)
				{
					
					std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetString() << std::endl;
					pGameObject =Load_archetype(obj_itr->value.GetString());

					if (pGameObject->mObjType == ObjectType::SHIP)
					{
						sgpShip = pGameObject;
					}
					
				}
				 if (strcmp(obj_itr->name.GetString(), "transform") == 0)
				{
					Transform *pTrans = static_cast<Transform*>(pGameObject->getComponent(COMPONENT_TRANSFORM));
					if (!pTrans)
						continue;																						
					float coord[2];
					int i = 0;
					auto obj1 = obj_itr->value.GetObject();
					std::cout << "---------level values---------------------------------------------------" << std::endl;
					for (auto itr = obj1.MemberBegin(); itr != obj1.MemberEnd(); ++itr)
					{

						std::cout << itr->name.GetString() << ":\t" << itr->value.GetFloat() << std::endl;
						coord[i]= itr->value.GetFloat();
						i++;
					}
					std::cout << "-------------------------------------------------------------------------" << std::endl;

					
				}
				 if (strcmp(obj_itr->name.GetString(), "bulletcount") == 0)
				 {
					 std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetInt() << std::endl;

					 for (int i = 0; i < obj_itr->value.GetInt(); i++)
					 {
						 pGameObject = Load_archetype("Archetypes/bullet.json");
	
					 }
				 }
			}
		}
		
		// push back to a creation quee
		pGameObjectManager->mPendingObjects.push_back(pGameObject);
		//push back for each game object
	 }
	
	return;
}

void ObjectFactory::ResetLevel()
{
	
	for (auto gameObject : pGameObjectManager->m_GameObjects)
	{
		auto itr = std::find(pGameObjectManager->mDestroyQ.begin(), pGameObjectManager->mDestroyQ.end(), gameObject);
		if (itr == pGameObjectManager->mDestroyQ.end())
		{
			pGameObjectManager->mDestroyQ.push_back(gameObject);
		}
	}

}

GameObject* ObjectFactory::Load_archetype(const char * path)
{
	rapidjson::Document d;
	FILE* fp = fopen(path, "rb");
	if (fp == NULL)
	{
		return NULL;
	}
	GameObject *pGo = new GameObject();
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	d.ParseStream(is);
	fclose(fp);
	//auto obj = lvl_itr->value.GetObject();
	for (rapidjson::Value::ConstMemberIterator lvl_itr = d.MemberBegin(); lvl_itr != d.MemberEnd(); ++lvl_itr)
	{
		// for getting object values---------------------------------------------
		if (lvl_itr->value.IsObject())
		{
			std::cout << lvl_itr->name.GetString() << std::endl;
			//if its a transform-----------------------------------------------------------------------------
			if (strcmp(lvl_itr->name.GetString(), "transform") == 0)
			{
				Transform *pTrans = new Transform();
				pGo->AddComponent(pTrans);
				float coord[4];
				int i = 0;
				auto obj1 = lvl_itr->value.GetObject();
				for (auto obj_itr = obj1.MemberBegin(); obj_itr != obj1.MemberEnd(); ++obj_itr)
				{

					std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetFloat() << std::endl;
					coord[i] = obj_itr->value.GetFloat();
					i++;
				}
				//could pass i
				pTrans->Serialize(coord,i);
			}
			// UPDown Component-------------------------------------------------------------------------------
			else if (strcmp(lvl_itr->name.GetString(), "updown") == 0)
			{
				UpDown *pUpdown = new UpDown();
				pGo->AddComponent(pUpdown);
				float val[2];
				int i = 0;
				auto obj1 = lvl_itr->value.GetObject();
				for (auto obj_itr = obj1.MemberBegin(); obj_itr != obj1.MemberEnd(); ++obj_itr)
				{
					//range of up down
					std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetFloat() << std::endl;
					val[i] = obj_itr->value.GetFloat();
					i++;
				}
				pUpdown->Serialize(val[0], val[1]);
			}
			// If its a BODY=====================================================================
			else if (strcmp(lvl_itr->name.GetString(), "body") == 0)
			{
				bodyval sbody;

				Body *pBody = new Body();
				pGo->AddComponent(pBody);

				auto obj1 = lvl_itr->value.GetObject();
				for (auto obj_itr = obj1.MemberBegin(); obj_itr != obj1.MemberEnd(); ++obj_itr)
				{

					//std::cout << obj_itr->name.GetString() << std::endl;
					if (strcmp(obj_itr->name.GetString(), "mass") == 0)
					{
						sbody.bmass = obj_itr->value.GetFloat();
						std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetFloat() << std::endl;
					}
						
					else if (strcmp(obj_itr->name.GetString(), "shape") == 0)
					{
						sbody.bshape = obj_itr->value.GetString();
						std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetString() << std::endl;
					}
					else if (strcmp(obj_itr->name.GetString(), "radius") == 0)
					{
						sbody.bradius = obj_itr->value.GetFloat();
						std::cout << obj_itr->name.GetString() << ":\t" << obj_itr->value.GetFloat() << std::endl;
					}
				}
				pBody->Serialize(&sbody);
				std::cout << std::endl;
			}
		}
		//FOR NORMAL COMPONENTS
		//for Sprite values------------------------------------------------------------------------------ -
		
	
		if (strcmp(lvl_itr->name.GetString(),"ObjectType")==0)
		{
			std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.GetString() << std::endl;
			if (strcmp(lvl_itr->value.GetString(), "ship") == 0)
				pGo->mObjType = 0;
			else if (strcmp(lvl_itr->value.GetString(), "bullet") == 0)
				pGo->mObjType = 1;
			else if (strcmp(lvl_itr->value.GetString(), "asteroid") == 0)
			{
				pGo->mObjType = 2;
				//asteroidCount++;
			}
				
			else if (strcmp(lvl_itr->value.GetString(), "missile") == 0)
				pGo->mObjType = 3;
			else if (strcmp(lvl_itr->value.GetString(), "gui") == 0)
				pGo->mObjType = 4;
			else if (strcmp(lvl_itr->value.GetString(), "enemy") == 0)
				pGo->mObjType = 5;
		}
		else if (strcmp(lvl_itr->name.GetString(), "sprite") == 0 )
		{
			Sprite *pSprite = new Sprite();
			//const char *SpriteName = lvl_itr->value.GetString();
			auto obj1 = lvl_itr->value.GetObject();
			std::string tpath;
			for (auto obj_itr = obj1.MemberBegin(); obj_itr != obj1.MemberEnd(); ++obj_itr)
			{
				if (strcmp(obj_itr->name.GetString(), "texturePath") == 0)
				{
					tpath = obj_itr->value.GetString();
				}
			}
			pGo->AddComponent(pSprite);
			pSprite->Serialize(tpath);
			//std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.Get() << std::endl;
		}
		//for getting controller component-------------------------------------------------------------------
		else if (lvl_itr->value.IsBool())
		{
			
			if (strcmp(lvl_itr->name.GetString(), "controller") == 0&& lvl_itr->value.GetBool()==true)
			{
				Controller *pCntrl = new Controller();
				pGo->AddComponent(pCntrl);
				std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.GetBool() << std::endl;
			}
			else if (strcmp(lvl_itr->name.GetString(), "wraparound") == 0 && lvl_itr->value.GetBool() == true)
			{
				WrapAround *pWrap = new WrapAround();
				pGo->AddComponent(pWrap);
				std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.GetBool() << std::endl;
			}
			else if (strcmp(lvl_itr->name.GetString(), "asteroid_spawner") == 0 && lvl_itr->value.GetBool() == true)
			{
				AsteroidSpawner *pAsteroidSpawner = new AsteroidSpawner();
				pGo->AddComponent(pAsteroidSpawner);
				std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.GetBool() << std::endl;
			}
			else if (strcmp(lvl_itr->name.GetString(), "enemy_spawner") == 0 && lvl_itr->value.GetBool() == true)
			{
				EnemySpawner *pEnemySpawner = new EnemySpawner();
				pGo->AddComponent(pEnemySpawner);
				std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.GetBool() << std::endl;
			}
			/*else if (strcmp(lvl_itr->name.GetString(), "subscribe") == 0 && lvl_itr->value.GetBool() == true)
			{
				
				pGo->AddComponent(pCntrl);
				std::cout << lvl_itr->name.GetString() << ":\t" << lvl_itr->value.GetBool() << std::endl;
			}*/
			
		}
	}
	return pGo;
}