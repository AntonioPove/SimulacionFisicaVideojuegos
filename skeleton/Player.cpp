#include "Player.h"

Player::Player(WorldManager* wm)
{
	player_ = wm->createPlayer();
	vel_ = 50;
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
		player_->setAngularVelocity({ 0, 0, -vel_ });
		player_->setLinearVelocity({ 0, 0, -vel_ });
		break;
	}
	case 'S':
	{
		player_->setAngularVelocity({ -vel_, 0, 0 });
		player_->setLinearVelocity({ -vel_, 0, 0 });
		break;
	}
	case 'D':
	{
		player_->setAngularVelocity({ 0, 0, vel_ });
		player_->setLinearVelocity({ 0, 0, vel_ });
		break;
	}
	case 'W':
	{
		player_->setAngularVelocity({ vel_, 0, 0 });
		player_->setLinearVelocity({ vel_, 0, 0 });
		break;
	}
	default:
		break;
	}


}
