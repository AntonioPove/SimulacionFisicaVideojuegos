#include "Player.h"

Player::Player(WorldManager* wm)
{
	player_ = wm->createPlayer(this);
	vel_ = 50;
	velJump_ = 30;

	sizePlayer = 10;
	sizeEnemies = 30;
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

bool Player::collision(std::list<PxRigidDynamic*> bombs)
{
	for (auto e : bombs)
	{
		if (abs(e->getGlobalPose().p.x - player_->getGlobalPose().p.x) > sizeEnemies + sizePlayer
			|| abs(e->getGlobalPose().p.y - player_->getGlobalPose().p.y) > sizeEnemies + sizePlayer ||
			abs(e->getGlobalPose().p.z - player_->getGlobalPose().p.z) > sizeEnemies + sizePlayer)
			return false;

		float dx = e->getGlobalPose().p.x - player_->getGlobalPose().p.x;
		float dy = e->getGlobalPose().p.y - player_->getGlobalPose().p.y;
		float dz = e->getGlobalPose().p.z - player_->getGlobalPose().p.z;
		float distance = sqrt(dx * dx + dy * dy + dz * dz);

		return distance < (sizePlayer + sizeEnemies);



	}
}

