/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/
#pragma once
#include "Ogre.h"

class Platform
{
private:
	
	Ogre::Vector3 m_Position;
	Ogre::Entity* m_pPlatform;
	Ogre::SceneNode* m_pPlatformNode;

public:

	Platform();
	Platform(Ogre::SceneManager* scnMan, Ogre::Vector3 pos , Ogre::MaterialPtr mat, float x, float y);
	~Platform() {};
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getScale();


};

