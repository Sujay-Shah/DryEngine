/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.h
Purpose: skeleton for ResourceManager.cpp
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
#pragma once
#include<string>
#include<unordered_map>

struct STB_Surface {
	unsigned char* data = 0;
	unsigned int textureBuffer;
	int width = 0;
	int height = 0;
	int comp = 0;
};

class ResourceManager
{
	public:
		ResourceManager();
		~ResourceManager();

	public:
		STB_Surface *LoadSurface(std::string filePath);

	private:
		std::unordered_map<std::string, STB_Surface* > mSurfaces;
};



