#include "Player.h"

Player::Player(WorldManager* wm)
{
	player_ = wm->createPlayer();
	vel_ = 20;
	velJump_ = 30;
}

void Player::updatePlayer(double t)
{
	//wm_->update(t);
}

void Player::inputPlayer(char key)
{
	switch (toupper(key))
	{
	case 'A':
	{
		player_->setLinearVelocity({ vel_, 0, 0 });
		break;
	}
	case 'S':
	{
		player_->setLinearVelocity({ 0, 0, -vel_ });
		break;
	}
	case 'D':
	{
		player_->setLinearVelocity({ -vel_, 0, 0 });
		break;
	}
	case 'W':
	{
		player_->setLinearVelocity({ 0, 0, vel_ });
		break;
	}
	case 'E':
	{
		player_->setLinearVelocity({ 0, velJump_, 0 });
		break;
	}
	default:
		break;
	}


}
