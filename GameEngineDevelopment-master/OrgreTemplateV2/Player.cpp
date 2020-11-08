/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#include "Player.h"
#include "Platform.h"

Player::Player(Ogre::SceneManager* scnMan, Ogre::Vector3 _pos, Ogre::MaterialPtr mat)
{
	m_PlayerSpeed = 1;
	m_Position = _pos;
	m_pPlayer = scnMan->createEntity(Ogre::SceneManager::PrefabType::PT_PLANE);
	m_pPlayerNode = scnMan->getRootSceneNode()->createChildSceneNode();
	m_pPlayerNode->setPosition(m_Position);
	m_pPlayerNode->setScale(0.01, 0.01, 0.0f);
	m_pPlayerNode->attachObject(m_pPlayer);
	m_pPlayer->setMaterial(mat);
	m_IsFalling = true;
}



void Player::MoveLeft()
{
	Ogre::Vector3 newPosition = m_pPlayerNode->getPosition() - Ogre::Vector3(0.5 * m_PlayerSpeed, 0, 0);
	m_pPlayerNode->setPosition(newPosition);
}

void Player::MoveRight()
{
	Ogre::Vector3 newPosition = m_pPlayerNode->getPosition() - Ogre::Vector3(-0.5 * m_PlayerSpeed, 0, 0);
	m_pPlayerNode->setPosition(newPosition);
}

void Player::Jump()
{
	if (!m_IsFalling) {
		Ogre::Vector3 newPosition = m_pPlayerNode->getPosition() + Ogre::Vector3(0, 5 * m_PlayerSpeed, 0);
		m_pPlayerNode->setPosition(newPosition);
	}
}

bool Player::getIsFalling()
{
	return m_IsFalling;
}

Ogre::Vector3 Player::getPosition()
{
	return m_pPlayerNode->getPosition();
}


void Player::setIsFalling(bool boolean)
{
	m_IsFalling = boolean;
}


void Player::Update()
{
	if (m_IsFalling) {
		m_pPlayerNode->setPosition(m_pPlayerNode->getPosition().x, m_pPlayerNode->getPosition().y - 0.05, m_pPlayerNode->getPosition().z);
	}

	else
	{
		m_pPlayerNode->setPosition(m_pPlayerNode->getPosition().x, m_pPlayerNode->getPosition().y, m_pPlayerNode->getPosition().z);
	}

	if (m_pPlayerNode->getPosition().x < -11) 
	{

		m_pPlayerNode->setPosition(-10.9, m_pPlayerNode->getPosition().y, m_pPlayerNode->getPosition().z);
	}

	if (m_pPlayerNode->getPosition().x > 11)
	{
		m_pPlayerNode->setPosition(10.9, m_pPlayerNode->getPosition().y, m_pPlayerNode->getPosition().z);
	}


}

