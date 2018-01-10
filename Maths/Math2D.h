/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Math2D.h
Purpose: skeleton for 2D collision library
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
Creation date: September 13, 2017.
- End Header --------------------------------------------------------*/
#ifndef MATH2D_H
#define MATH2D_H


#include "Vector2D.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius);


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height);

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1);

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1);


#endif