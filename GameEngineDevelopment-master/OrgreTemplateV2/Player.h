/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#pragma once
#include<Ogre.h>

class Player
{

private:

	float m_PlayerSpeed;
	bool m_IsFalling = false;

	Ogre::Vector3 m_Position;
	Ogre::Entity* m_pPlayer;
	Ogre::MaterialPtr m_pPlayerMaterial; 
	Ogre::SceneNode* m_pPlayerNode;


public:

	Player() {};
	Player(Ogre::SceneManager* scnMan, Ogre::Vector3 _pos, Ogre::MaterialPtr mat);
	~Player() {};

	void MoveLeft();
	void MoveRight();
	void Jump();
	void Update();



	bool getIsFalling();
	void setIsFalling(bool boolean);
	Ogre::Vector3 getPosition();

};

