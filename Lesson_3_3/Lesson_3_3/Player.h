#pragma once
class Player
{
public:
	Player();
	~Player();
	void Draw();
	void Move();
	int posX = 0;
	int posY = 0;
};
//�v���C���[�̃C���X�^���X��extern�錾�B
//extern�錾�́A��`�͂ǂ����ɂ��邩��A������g���Ȃ����ƁA
//�R���p�C���ɋ�������́B��`�ł͂Ȃ��̂Œ��ӁI
//����͒�`��Player.cpp�ɋL�q���Ă��܂��B
extern Player g_player;

