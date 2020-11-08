/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#include "Platform.h"

Platform::Platform(Ogre::SceneManager* scnMan, Ogre::Vector3 _pos, Ogre::MaterialPtr mat, float x, float y)
{

	m_Position = _pos;
	m_pPlatform = scnMan->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);
	m_pPlatformNode = scnMan->getRootSceneNode()->createChildSceneNode();
	m_pPlatformNode->setPosition(m_Position);
	m_pPlatformNode->setScale(x, y, 0);
	m_pPlatformNode->attachObject(m_pPlatform);
	m_pPlatform->setMaterial(mat);
}

Ogre::Vector3 Platform::getPosition()
{
	return m_pPlatformNode->getPosition();
}

Ogre::Vector3 Platform::getScale()
{
	return m_pPlatformNode->getScale();
}





