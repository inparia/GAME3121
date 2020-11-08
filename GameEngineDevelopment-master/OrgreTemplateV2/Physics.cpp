/***********************************************
* Project            : Doodle Jump Game
* Author             : Joon Young Sun
* Student Number     : 101216511
* Description        : Doodle Jump Game
* Last modified      : 20/11/08
|***********************************************/

#include "Physics.h"

void Physics::setGravity(float newGravity)
{
	m_Gravity = newGravity;

}

float Physics::getGravity()
{

	return m_Gravity;
}

bool Physics::AABBCheck(Player* player, Platform* platform)
{
	if (
		player->getPosition().y - 0.4 <= platform->getPosition().y + 0.042 && player->getPosition().x >= -3 && player->getPosition().x <= 3)
	{
		return true;
	}
	else {
		return false;
	}
}
