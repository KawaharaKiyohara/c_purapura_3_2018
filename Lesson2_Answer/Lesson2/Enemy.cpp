#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
void Enemy::Move()
{
	//X座標上で移動させる。
	posX += moveDir;
	//移動方向を反転。
	moveDir *= -1;
}
void Enemy::Draw()
{
	DrawMoji(posX, posY, 'E');
}

