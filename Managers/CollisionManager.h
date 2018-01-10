/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollisionManager.h
Purpose: Skeleton for Collsion.cpp
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
#pragma once
#include "../Managers/CollisionManager.h"
#include "../Managers/GameObjectManager.h"
#include "../GameObject/GameObject.h"
#include "../Components/Body.h"
#include<vector>
#include <functional>
extern GameObjectManager *pGameObjectManager;
//class Body;
class Contact;

class Shape
{
public:
	enum SHAPE_TYPE
	{
		CIRCLE, AABB, TOTAL_SHAPES
	};

	Shape(SHAPE_TYPE Type);
	virtual ~Shape() {};
	virtual bool TestPoint(float pointX, float pointY) = 0;

	Body *mpBodyOwner;
	SHAPE_TYPE mShapeType;
};
class CollisionManager
{
public:
	std::vector<Contact*> mContacts;
	 bool(*fnptr[Shape::SHAPE_TYPE::TOTAL_SHAPES][Shape::SHAPE_TYPE::TOTAL_SHAPES])(Shape* shape1, float posX1, float posY1, Shape* shape2, float posX2, float posY2, std::vector<Contact *> &mContacts);
public:
	void test();
	CollisionManager();
	~CollisionManager(); 
	
	bool CheckCollisionAndGenerateContact(Shape * pShape1, float posX1, float posY1, Shape * pShape2, float posX2, float posY2);
	void Reset();

};



class ShapeCircle :public Shape
{
public:
	ShapeCircle():Shape(SHAPE_TYPE::CIRCLE) { mRadius = 0.0f; };
	~ShapeCircle() {};
	bool TestPoint(float pointX,float pointY);


public:
	float mRadius;

};

class ShapeAABB :public Shape
{
public:
	ShapeAABB():Shape(SHAPE_TYPE::AABB) { mWidth = mHeight = 0.0f; };
	~ShapeAABB() {};
	bool TestPoint(float pointX, float pointY);
public:
	float mWidth,mHeight;
};

class Contact
{
public:
	Contact();
	~Contact();

public:
	
	Body *mBodies[2];
};