
/* Start Header -------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: RenderManager.cpp
Purpose: Renders game objects to the view port
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
Creation date: December 3, 2017.
- End Header --------------------------------------------------------*/
#include "RenderManager.h"
#include "../Graphics/shader.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern GameObjectManager *pGameObjectManager;
extern ResourceManager *pResourceManager;

RenderManager::RenderManager()
{

	mDebug = false;
	InitializeWindow();
	CreateShader();
	CreateQuad();
}


RenderManager::~RenderManager()
{
	delete pS1;
	glDeleteBuffers(1, &vBO);
	glDeleteBuffers(1, &iBO);
	// Close and destroy the window
	SDL_DestroyWindow(pWindow);
}

void RenderManager::InitializeWindow() {
	int error = 0;
	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return;
	}


	pWindow = SDL_CreateWindow("DryEngine demo",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);



	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return;
	}
	SDL_GLContext context = SDL_GL_CreateContext(pWindow);

	glewInit();
}

void RenderManager::Update() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto game_object : pGameObjectManager->m_GameObjects)
	{
		Transform *pTrans = static_cast<Transform*>(game_object->getComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		if (!pTrans)
			continue;

		Sprite *pSprite = static_cast<Sprite*>(game_object->getComponent(COMPONENT_TYPE::COMPONENT_Sprite));
		if (!pSprite)
			continue;

		SelectTexture(pSprite);

		glUniformMatrix4fv(glGetUniformLocation(pS1->ID, "uTrans"), 1, GL_FALSE, glm::value_ptr(pTrans->mTransform));
		// For position
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER ,vBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
		// enable textures
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		glAlphaFunc(GL_GREATER, 0.5f);
		glEnable(GL_ALPHA_TEST);
		
		

		{
			glUniform1i(glGetUniformLocation(pS1->ID, "is_debug"), 0);
			glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
		}
		if (mDebug)
		{
			glUniform1i(glGetUniformLocation(pS1->ID, "is_debug"), 1);
			glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, NULL);
		}

		
	}
	
	SDL_GL_SwapWindow(pWindow);
	
}


void RenderManager::CreateShader() {
	pS1 = new Shader("Graphics/Shaders/VertexShader1.vs", "Graphics/Shaders/FragmentShader1.fs");
	pS1->use();
	glUniform4f(glGetUniformLocation(pS1->ID, "shapeColor"), 0.0f, 0.7f, 0.4f, 1.0f);
}

void RenderManager::CreateQuad() {
	float meshVertices[] =
	{
		// first triangle // UV coord
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f,	// bottom left
		0.5f, -0.5f, 0.0f,	1.0f, 1.0f,	// bottom right
		0.5f,  0.5f, 0.0f,	1.0f, 0.0f,	// top right
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f	// top left 
	};

	unsigned int indices[] = {
		0, 1, 2, 3
	};

	// Create vBO and send to GPU
	glGenBuffers(1, &vBO);
	glBindBuffer(GL_ARRAY_BUFFER, vBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(meshVertices), meshVertices, GL_STATIC_DRAW);

	// Create iBO and send to GPU
	glGenBuffers(1, &iBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void RenderManager::SelectTexture(Sprite* pSprite) {
	STB_Surface* pSurface = pResourceManager->LoadSurface(pSprite->texturePath);
}
