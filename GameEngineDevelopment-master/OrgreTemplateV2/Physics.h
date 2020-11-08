/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#pragma once
#include "Player.h"
#include "Platform.h"

class Physics
{
private:
	float m_Gravity = 0.05f;
public:
	
	Physics() {};
	void setGravity(float newGravity);

	float getGravity();

	bool AABBCheck(Player* player, Platform* platform);
};

