#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Draw();
	int posX = 0;		//�G�l�~�[��X���W�B
	int posY = 0;		//�G�l�~�[��Y���W�B
	int moveDir = 1;	//�G�l�~�[�̈ړ������B
};

