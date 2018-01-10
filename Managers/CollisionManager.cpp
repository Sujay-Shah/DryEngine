/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollisionManager.cpp
Purpose: Checks and manages Collisions
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
Creation date: November 7, 2017.
- End Header --------------------------------------------------------*/
#include "CollisionManager.h"
#include <iostream>

bool CheckCollisionCircle2Circle(Shape *pCircleShape1, float posX1, float posY1, Shape *pCircleShape2, float posX2, float posY2, std::vector<Contact*> &mContacts)
{
	float c1c2SqDist;
	float r1, r2;

	c1c2SqDist = (posX1 - posX2)*(posX1 - posX2) + (posY1 - posY2)*(posY1 - posY2);
	r1 = ((ShapeCircle*)pCircleShape1)->mRadius;
	r2 = ((ShapeCircle*)pCircleShape2)->mRadius;
	
	if (c1c2SqDist > (r1+r2)*(r1+r2))
		return false;

	//collison occured, add colliding bodies
	Contact *pNewContact = new Contact();
	pNewContact->mBodies[0] = pCircleShape1->mpBodyOwner;
	pNewContact->mBodies[1] = pCircleShape2->mpBodyOwner;
	mContacts.push_back(pNewContact);
	
	return true;
}

bool CheckCollisionAABB2AABB(Shape *pAABBShape1, float posX1, float posY1, Shape *pAABBShape2, float posX2, float posY2, std::vector<Contact*> &mContacts)
{
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	ShapeAABB *pAABB1 = (ShapeAABB *)pAABBShape1;
	ShapeAABB *pAABB2 = (ShapeAABB *)pAABBShape2;

	left1 = posX1 - pAABB1->mWidth/2;
	right1 = posX1 + pAABB1->mWidth / 2;
	top1 = posY1 + pAABB1->mHeight/2;
	bottom1 = posY1 - pAABB1->mHeight / 2;

	left2 = posX2 - pAABB2->mWidth / 2;
	right2 = posX2 + pAABB2->mWidth / 2;
	top2 = posY2 + pAABB2->mHeight / 2;
	bottom2 = posY2 - pAABB2->mHeight / 2;

	if (left1>right1 || left2>right2 || top1>bottom2 || top2>bottom1)
		return false;

	//collison occured, add colliding bodies
	Contact *pNewContact = new Contact();
	pNewContact->mBodies[0] = pAABBShape1->mpBodyOwner;
	pNewContact->mBodies[1] = pAABBShape2->mpBodyOwner;
	mContacts.push_back(pNewContact);

	return true;
	
}

bool CheckCollisionCircle2AABB(Shape *pCircleShape1, float posX1, float posY1, Shape *pAABBShape2, float posX2, float posY2, std::vector<Contact*> &mContacts)
{
	ShapeCircle *pCircle1 = (ShapeCircle*)pCircleShape1;
	ShapeAABB *pAABB2 = (ShapeAABB*)pAABBShape2;
	float left2, right2, top2, bottom2;

	left2 = posX2 - pAABB2->mWidth / 2;
	right2 = posX2 + pAABB2->mWidth / 2;
	top2 = posY2 + pAABB2->mHeight / 2;
	bottom2= posY2 - pAABB2->mHeight / 2;

	float snappedX, snappedY;

	if (posX1 < left2)
		snappedX = left2;
	else if (posX1 > right2)
		snappedX = right2;
	else
		snappedX = posX2;

	if (posY1 < top2)
		snappedY = top2;
	else if (posY1 > bottom2)
		snappedY = bottom2;
	else
		snappedY = posY2;

	if (pCircle1->TestPoint(snappedX, snappedY) == false)
		return false;

	//add colliding bodies
	Contact *pNewContact = new Contact();
	pNewContact->mBodies[0] = pCircleShape1->mpBodyOwner;
	pNewContact->mBodies[1] = pAABBShape2->mpBodyOwner;
	mContacts.push_back(pNewContact);

	return true;
}

Shape::Shape(SHAPE_TYPE Type)
{
	mShapeType = Type;
	mpBodyOwner= NULL;
}


void CollisionManager::test() {

	std::cout << "testing function binding";
}

CollisionManager::CollisionManager() :mContacts()
{
	fnptr[Shape::SHAPE_TYPE::CIRCLE][Shape::SHAPE_TYPE::CIRCLE] =CheckCollisionCircle2Circle;
	fnptr[Shape::SHAPE_TYPE::CIRCLE][Shape::SHAPE_TYPE::AABB] =CheckCollisionCircle2AABB;
	fnptr[Shape::SHAPE_TYPE::AABB][Shape::SHAPE_TYPE::AABB] = CheckCollisionAABB2AABB;
	fnptr[Shape::SHAPE_TYPE::AABB][Shape::SHAPE_TYPE::CIRCLE] = CheckCollisionCircle2AABB;
}

CollisionManager::~CollisionManager()
{
	Reset();
}

bool ShapeCircle::TestPoint(float pointX, float pointY)
{
	float sqDist = (pointX - mpBodyOwner->mBodyPos.x)*(pointX - mpBodyOwner->mBodyPos.x) + (pointY - mpBodyOwner->mBodyPos.y)*(pointY - mpBodyOwner->mBodyPos.y);
	
	if(sqDist>mRadius*mRadius)
	return false;

	return true;
}

bool ShapeAABB::TestPoint(float pointX, float pointY)
{
	float left, right, top, bottom;
	left = mpBodyOwner->mBodyPos.x - mWidth / 2;
	right = mpBodyOwner->mBodyPos.x + mWidth / 2;
	top = mpBodyOwner->mBodyPos.y + mHeight / 2;
	bottom = mpBodyOwner->mBodyPos.y - mHeight / 2;

	if (pointX<left || pointX>right || pointY<top || pointY>bottom)
		return false;

	return true;
}


bool CollisionManager::CheckCollisionAndGenerateContact(Shape * pShape1, float posX1, float posY1, Shape * pShape2, float posX2, float posY2)
{

	return fnptr[pShape1->mShapeType][pShape2->mShapeType](pShape1, posX1, posY1, pShape2, posX2, posY2, mContacts);
}



void CollisionManager::Reset()
{
	for (auto cont : mContacts)
	{
		delete cont;
	}
	mContacts.clear(); 
}

Contact::Contact()
{
	mBodies[0] = NULL;
	mBodies[1] = NULL;
}

Contact::~Contact()
{
}
