/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix2D.c
Purpose: 2D Matrix library implementation
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
#include "Matrix2D.h"


/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	pResult->m[0][0] = 1.0f;    pResult->m[0][1] = 0.0f;	pResult->m[0][2] = 0.0f;
	pResult->m[1][0] = 0.0f;	pResult->m[1][1] = 1.0f;	pResult->m[1][2] = 0.0f;
	pResult->m[2][0] = 0.0f;	pResult->m[2][1] = 0.0f;	pResult->m[2][2] = 1.0f;
	/*int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
				pResult->m[i][j] = 1;
			else
				pResult->m[i][j] = 0;
		}
	}*/

}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pResult->m[i][j] = pMtx->m[j][i];
		}
	}*/
	
	pResult->m[0][0] = pMtx->m[0][0];       pResult->m[0][1] = pMtx->m[1][0];       pResult->m[0][2] = pMtx->m[2][0];
	pResult->m[1][0] = pMtx->m[0][1];       pResult->m[1][1] = pMtx->m[1][1];       pResult->m[1][2] = pMtx->m[2][1];
	pResult->m[2][0] = pMtx->m[0][2];       pResult->m[2][1] = pMtx->m[1][2];       pResult->m[2][2] = pMtx->m[2][2];
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	
	/*int i, j, k;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			tempRes[i][j] = 0;
			for(k=0;k<3;k++)
				tempRes[i][j] =tempRes[i][j] + pMtx0->m[i][k] * pMtx1->m[k][j];
		}
	}*/
	  // Multiplication
	float tempRes[3][3];
	tempRes[0][0] = 0;
	tempRes[0][0] += pMtx0->m[0][0] * pMtx1->m[0][0];
	tempRes[0][0] += pMtx0->m[0][1] * pMtx1->m[1][0];
	tempRes[0][0] += pMtx0->m[0][2] * pMtx1->m[2][0];
	tempRes[0][1] = 0;
	tempRes[0][1] += pMtx0->m[0][0] * pMtx1->m[0][1];
	tempRes[0][1] += pMtx0->m[0][1] * pMtx1->m[1][1];
	tempRes[0][1] += pMtx0->m[0][2] * pMtx1->m[2][1];
	tempRes[0][2] = 0;
	tempRes[0][2] += pMtx0->m[0][0] * pMtx1->m[0][2];
	tempRes[0][2] += pMtx0->m[0][1] * pMtx1->m[1][2];
	tempRes[0][2] += pMtx0->m[0][2] * pMtx1->m[2][2];

	tempRes[1][0] = 0;
	tempRes[1][0] += pMtx0->m[1][0] * pMtx1->m[0][0];
	tempRes[1][0] += pMtx0->m[1][1] * pMtx1->m[1][0];
	tempRes[1][0] += pMtx0->m[1][2] * pMtx1->m[2][0];
	tempRes[1][1] = 0;
	tempRes[1][1] += pMtx0->m[1][0] * pMtx1->m[0][1];
	tempRes[1][1] += pMtx0->m[1][1] * pMtx1->m[1][1];
	tempRes[1][1] += pMtx0->m[1][2] * pMtx1->m[2][1];
	tempRes[1][2] = 0;
	tempRes[1][2] += pMtx0->m[1][0] * pMtx1->m[0][2];
	tempRes[1][2] += pMtx0->m[1][1] * pMtx1->m[1][2];
	tempRes[1][2] += pMtx0->m[1][2] * pMtx1->m[2][2];

	tempRes[2][0] = 0;
	tempRes[2][0] += pMtx0->m[2][0] * pMtx1->m[0][0];
	tempRes[2][0] += pMtx0->m[2][1] * pMtx1->m[1][0];
	tempRes[2][0] += pMtx0->m[2][2] * pMtx1->m[2][0];
	tempRes[2][1] = 0;
	tempRes[2][1] += pMtx0->m[2][0] * pMtx1->m[0][1];
	tempRes[2][1] += pMtx0->m[2][1] * pMtx1->m[1][1];
	tempRes[2][1] += pMtx0->m[2][2] * pMtx1->m[2][1];
	tempRes[2][2] = 0;
	tempRes[2][2] += pMtx0->m[2][0] * pMtx1->m[0][2];
	tempRes[2][2] += pMtx0->m[2][1] * pMtx1->m[1][2];
	tempRes[2][2] += pMtx0->m[2][2] * pMtx1->m[2][2];
	
	/*for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			 pResult->m[i][j]=tempRes[i][j];
			
		}
	}*/
	 // Copying final value in pResult
	pResult->m[0][0] = tempRes[0][0];
	pResult->m[0][0] = tempRes[0][0];
	pResult->m[0][0] = tempRes[0][0];
	pResult->m[0][1] = tempRes[0][1];
	pResult->m[0][1] = tempRes[0][1];
	pResult->m[0][1] = tempRes[0][1];
	pResult->m[0][2] = tempRes[0][2];
	pResult->m[0][2] = tempRes[0][2];
	pResult->m[0][2] = tempRes[0][2];

	pResult->m[1][0] = tempRes[1][0];
	pResult->m[1][0] = tempRes[1][0];
	pResult->m[1][0] = tempRes[1][0];
	pResult->m[1][1] = tempRes[1][1];
	pResult->m[1][1] = tempRes[1][1];
	pResult->m[1][1] = tempRes[1][1];
	pResult->m[1][2] = tempRes[1][2];
	pResult->m[1][2] = tempRes[1][2];
	pResult->m[1][2] = tempRes[1][2];

	pResult->m[2][0] = tempRes[2][0];
	pResult->m[2][0] = tempRes[2][0];
	pResult->m[2][0] = tempRes[2][0];
	pResult->m[2][1] = tempRes[2][1];
	pResult->m[2][1] = tempRes[2][1];
	pResult->m[2][1] = tempRes[2][1];
	pResult->m[2][2] = tempRes[2][2];
	pResult->m[2][2] = tempRes[2][2];
	pResult->m[2][2] = tempRes[2][2];
			
	
}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
	
	
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	float rad = Angle*Pi / 180;
	 Matrix2DIdentity(pResult);
	 pResult->m[0][0] = cosf(rad);
	 pResult->m[0][1] = -sinf(rad);
	 pResult->m[1][0] = sinf(rad);
	 pResult->m[1][1] = cosf(rad);
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = cosf(Angle);
	pResult->m[0][1] = -sinf(Angle);
	pResult->m[1][0] = sinf(Angle);
	pResult->m[1][1] = cosf(Angle);
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	float tempx, tempy;
	tempx = pVec->x;
	tempy = pVec->y;
	//pResult->x = 0.0f;
	//pResult->y = 0.0f;
	pResult->x = pMtx->m[0][0] * tempx + pMtx->m[0][1] * tempy+ pMtx->m[0][2];
	pResult->y = pMtx->m[1][0] * tempx + pMtx->m[1][1] * tempy+ pMtx->m[1][2];
}

// ---------------------------------------------------------------------------
