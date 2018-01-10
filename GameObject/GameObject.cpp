/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Purpose: Container of Gameobjects
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
#include "GameObject.h"
#include <stdio.h>
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include "../Components/Controller.h"
#include "../Components/UpDown.h"
#include "../Components/Body.h"
GameObject::GameObject()
{
	
} 

GameObject::~GameObject()
{

	for (auto component : m_Components) {

		delete component;
	}

	m_Components.clear();
}

void GameObject::AddComponent(Component * pComponent)
{
	pComponent->m_pOwner = this;
	m_Components.push_back(pComponent);
}

void GameObject::Update(float dt)
{
	for (auto component : m_Components)
		component->Update(dt);
}

Component* GameObject::getComponent(unsigned int type)
{
	for (auto component : m_Components)
		if(component->m_type==type)
			return component;
		
	
	return NULL;
}

void GameObject::HandleEvent(Event *pEvent)
{

	for (auto comp : m_Components)
	{
		comp->HandleEvent(pEvent);   
	}


}
