#include "stdafx.h"
#include "Player.h"

//�v���C���[�̃C���X�^���X�B
Player g_player;

Player::Player()
{
}



Player::~Player()
{
}

void Player::Draw()
{
	//�v���C���[���t���[���o�b�t�@�ɕ`��B
	DrawMoji(posX, posY, 'P');

}
void Player::Move()
{
	//�v���C���[�̈ړ������B
	if (GetAsyncKeyState(VK_UP)) {
		posY--;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		posY++;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		posX++;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		posX--;
	}
}

