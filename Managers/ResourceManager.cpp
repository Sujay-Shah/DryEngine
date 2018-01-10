/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.cpp
Purpose: Managing assets 
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

Project: 		CS529_sujay.shah_FinalProject_Milestone1

Author: Name: Sujay Shah ;  Login: sujay.shah  ; Student ID : 60001517
Creation date: October 15, 2017.
- End Header --------------------------------------------------------*/
#include "ResourceManager.h"
#include "stdio.h"
#include "SDL_surface.h"
#include "../Graphics/stb_image.h"
#include <GL\glew.h>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto &it : mSurfaces) {
		stbi_image_free(it.second->data);
		glDeleteTextures(1, &it.second->textureBuffer);
	}
}

STB_Surface * ResourceManager::LoadSurface(std::string filePath)
{
	/*set images*/
	STB_Surface *pSurface = mSurfaces[filePath];

	if (pSurface) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pSurface->textureBuffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		return pSurface;
	}

	pSurface = new STB_Surface;

	pSurface->data = stbi_load(filePath.c_str(), &pSurface->width, &pSurface->height, &pSurface->comp, 0);
	glGenTextures(1, &pSurface->textureBuffer);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, pSurface->textureBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->width, pSurface->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pSurface->data);
	/*loads image assets only once*/
	mSurfaces[filePath] = pSurface;
	return pSurface;
}
