#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
void Enemy::Move()
{
	//X���W��ňړ�������B
	posX += moveDir;
	//�ړ������𔽓]�B
	moveDir *= -1;
}
void Enemy::Draw()
{
	DrawMoji(posX, posY, 'E');
	if (g_player.posX == posX
		&& g_player.posY == posY
	) {
		//�G�l�~�[�ƃv���C���[���������W�ɗ����̂ŃQ�[���I�[�o�[�ɂ���B
		g_gameOverFlag = true;
	}
}

