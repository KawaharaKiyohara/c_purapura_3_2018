#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Draw();
	void SetPos(int x, int y) 
	{
		posX = x;
		posY = y;
	}
private:
	int posX = 0;		//�G�l�~�[��X���W�B
	int posY = 0;		//�G�l�~�[��Y���W�B
	int moveDir = 1;	//�G�l�~�[�̈ړ������B
};

