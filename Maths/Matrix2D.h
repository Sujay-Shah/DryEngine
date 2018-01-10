/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix2D.h
Purpose: skeleton for 2D Matrix library
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
#ifndef MATRIX2D_H
#define MATRIX2D_H
#define Pi     3.1415926535897932384626433832795

#include "Vector2D.h"

typedef struct Matrix2D
{
	float m[3][3];
}Matrix2D;


/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult);

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx);

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1);

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y);

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y);

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle);

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle);

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec);


#endif