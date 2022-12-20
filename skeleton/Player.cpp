#include "Player.h"
#include <iostream>

Player::Player(WorldManager* wm, ParticleSystem* ps)
{
	player_ = wm->createPlayer(this);
	vel_ = 400;

	sizePlayer = 10;
	sizeEnemies = 20;
}

void Player::updatePlayer(double t)
{
	

}

void Player::inputPlayer(char key)
{
	Vector3 vel = { 0,0,0 };

	switch (toupper(key))
	{
	case 'A':
	{
		vel -= {0, 0, 1};
		break;
	}
	case 'S':
	{
		vel -= {1, 0, 0};
		break;
	}
	case 'D':
	{
		vel += {0, 0, 1};
		break;
	}
	case 'W':
	{
		vel += {1, 0, 0};
		break;
	}
	default:
		break;
	}

	player_->addForce(vel * vel_);

}

void Player::moveInicial()
{
	player_->setGlobalPose(PxTransform({ 120, 10, 180 }));
	player_->setLinearVelocity({ 0,0,0 });
	player_->setAngularVelocity({ 0, 0, 0 });
}

bool Player::collision(PxTransform bombs)
{
	if (abs(bombs.p.x - player_->getGlobalPose().p.x) > sizeEnemies + sizePlayer
		|| abs(bombs.p.y - player_->getGlobalPose().p.y) > sizeEnemies + sizePlayer ||
		abs(bombs.p.z - player_->getGlobalPose().p.z) > sizeEnemies + sizePlayer)
		return false;

	float dx = bombs.p.x - player_->getGlobalPose().p.x;
	float dy = bombs.p.y - player_->getGlobalPose().p.y;
	float dz = bombs.p.z - player_->getGlobalPose().p.z;
	float distance = sqrt(dx * dx + dy * dy + dz * dz);

	return distance < (sizePlayer + sizeEnemies);
}

bool Player::final(PxTransform final)
{
	if (abs(final.p.x - player_->getGlobalPose().p.x) > sizeEnemies + sizePlayer
		|| abs(final.p.y - player_->getGlobalPose().p.y) > sizeEnemies + sizePlayer ||
		abs(final.p.z - player_->getGlobalPose().p.z) > sizeEnemies + sizePlayer)
		return false;

	float dx = fabs(player_->getGlobalPose().p.x - final.p.x);
	float dy = fabs(player_->getGlobalPose().p.y - final.p.y);
	float dz = fabs(player_->getGlobalPose().p.z - final.p.z);
	float distance = sqrt(dx * dx + dy * dy + dz * dz);

	return distance < sizePlayer + 40;
}
