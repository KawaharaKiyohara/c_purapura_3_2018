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
	if (g_player.GetPosX() == posX
		&& g_player.GetPosY() == posY
	) {
		//�G�l�~�[�ƃv���C���[���������W�ɗ����̂ŃQ�[���I�[�o�[�ɂ���B
		g_gameOverFlag = true;
	}
}

