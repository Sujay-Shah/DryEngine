/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Transform.cpp
Purpose: Component for placing game objects in the scene
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
#include <iostream>
#include<stdio.h>
#include "../Components/Transform.h"
#include "../Managers/EventManager.h"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class GameObject;

glm::vec3 axis(0.0f, 0.0f, 1.0f);
Transform::Transform() : Component (COMPONENT_TYPE ::COMPONENT_TRANSFORM)
{
	
	mPos = glm::vec3(0.0f);
	mScale = glm::vec3(0.0f);
	mAngle = 0.0f;
}

Transform::~Transform()
{
}

void Transform::Update(float dt)
{

	mTransform = glm::mat4(1.0f);
	mTransform = glm::translate(mTransform, mPos);
	mTransform = glm::rotate(mTransform, glm::radians(mAngle), axis);
	mTransform = glm::scale(mTransform, glm::vec3(mScale.x, mScale.y, 1.0f));
}

void Transform::Serialize(float *coord,int num)
{

	mPos.x = coord[0];
	mPos.y = coord[1];
	if (num == 4)
	{
		mScale.x = coord[2];
		mScale.y = coord[3];
	}

}

void Transform::HandleEvent(Event * pEvent)
{
	
}
