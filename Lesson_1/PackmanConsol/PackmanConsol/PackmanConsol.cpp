// PackmanConsol.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

//�}�b�v�̍����B
const int MAP_HEIGHT = 15;
//�}�b�v�̕��B
const int MAP_WIDTH = 15;

//�}�b�v�̒�`�B1�͕ǁB0�͉a�B
static int sMap[MAP_HEIGHT][MAP_WIDTH] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

//�t���[���o�b�t�@�E�E�E�̂悤�Ȃ��́B
static char sFrameBuffer[MAP_HEIGHT][MAP_WIDTH];

void EndFrame()
{
	Sleep(100);	//100�~���b����B
	HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = 0;
	pos.Y = 0;

	SetConsoleCursorPosition(hCons, pos);
}

/*!
 *@brief	�v���C���[�N���X�B
 */
class CPlayer {
private:
	int m_posX;			//!<x���W�B
	int m_posY;			//!<y���W�B
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CPlayer()
	{
		//���������s���B
		m_posX = 0;
		m_posY = 0;
	}
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~CPlayer()
	{

	}
	/*!
	*@brief	�v���C���[�̕`�揈���B
	*/
	void Draw()
	{
		//�t���[���o�b�t�@�Ƀh���[�B
		sFrameBuffer[m_posY][m_posX] = 'P';
	}
	/*!
	 *@brief	�X�V�����B
	 */
	void Update()
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			m_posY--;
			if (m_posY < 0) {
				m_posY = 0;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			m_posX--;
			if (m_posX < 0) {
				m_posX = 0;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			m_posY++;
			if (m_posY > MAP_HEIGHT - 1) {
				m_posY = MAP_HEIGHT - 1;
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			m_posX++;
			if (m_posX > MAP_WIDTH - 1) {
				m_posX = MAP_WIDTH - 1;
			}
		}
	}
	/*!
	 *@brief	X���W���擾�B
	 */
	int GetPositionX()
	{
		return m_posX;
	}
	/*!
	 *@brief	Y���W���擾�B
	 */
	int GetPositionY()
	{
		return m_posY;
	}
	/*!
	 *@brief	���W��ݒ�B
	 *@param	x		x���W�B
	 *@param	y		y���W�B
	 */
	void SetPosition(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
};
CPlayer g_player;

/*!
*@brief	�H�ו��N���X�B
*/
class CFood {
private:
	int m_posX;		//!<x���W�B
	int m_posY;		//!<y���W
	bool m_isDead;	//!<���S�t���O�B
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CFood() :
		m_isDead(false)
	{
		m_posX = 0;
		m_posY = 0;
	}
	/*!
	*@brief	�ǂ̕`�揈���B
	*/
	void Draw()
	{
		if (!m_isDead) {
			//�t���[���o�b�t�@�Ƀh���[�B
			sFrameBuffer[m_posY][m_posX] = 'F';
		}
	}
	/*!
	*@brief	���W��ݒ�B
	*/
	void SetPosition(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
	/*!
	*@brief	�X�V�����B
	*/
	void Update()
	{
		//�v���C���[�ƐG�ꂽ��H�ו���������悤�ɂ��Ă݂悤�E�E�E
		//�v���C���[��g_player�ŃA�N�Z�X�ł���B
		//�v���C���[��CFood�̍��W�������ɂȂ������ɁA������悤�ɂ���΂����͂��B
		//�v���C���[�̍��W��g_player.GetPositionX()��g_player.GetPositionY()�Ŏ擾�ł���B
		//�Ⴆ�΃v���C���[��X���W���~�����Ȃ炱��Ȋ����B
		//int pos_x = g_player.GetPositionX();
	}
};
/*!
*@brief	�ǃN���X�B
*/
class CWall {
private:
	int	m_posX;		//!<x���W�B
	int m_posY;		//!<y���W
public:
	/*!
	*@brief	�R���X�g���N�^�B
	*/
	CWall()
	{
		m_posX = 0;
		m_posY = 0;
	}
	/*!
	*@brief	�ǂ̕`�揈���B
	*/
	void Draw()
	{
		//�t���[���o�b�t�@�Ƀh���[�B
		sFrameBuffer[m_posY][m_posX] = 'W';
	}
	/*!
	*@brief	���W��ݒ�B
	*/
	void SetPosition(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
};

/*!
 *@brief	���C���֐��B
 */
int main()
{
	//�v���C���[�̏����ʒu������B
	g_player.SetPosition(7, 7);
	//��
	int numWall = 0;	//�ǂ̐��B
	CWall walls[MAP_HEIGHT*MAP_WIDTH];
	//�H�ו�
	int numFood = 0;
	CFood foods[MAP_HEIGHT*MAP_WIDTH];
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (sMap[i][j] == 1) {
				//�ǁB
				walls[numWall].SetPosition(j, i);
				//�ǂ��������̂ŃJ�E���g�A�b�v�B
				numWall++;
			}
			else if (sMap[i][j] == 0) {
				//�H�ו�
				foods[numFood].SetPosition(j, i);
				//�H�ו����������̂ŃJ�E���g�A�b�v�B
				numFood++;
			}
		}
	}
	//�Q�[�����[�v�B
	while (true) {
		//�t���[���o�b�t�@���N���A�B
		memset(sFrameBuffer, 0, sizeof(sFrameBuffer));
		//�v���C���[�̈ړ������B
		g_player.Update();
		//�H�ו��̍X�V�����B
		for (int i = 0; i < numFood; i++) {
			foods[i].Update();
		}
		//�H�ו��̕`�揈���B
		for (int i = 0; i < numFood; i++) {
			foods[i].Draw();
		}
		//�ǂ̕`�揈���B
		for (int i = 0; i < numWall; i++) {
			walls[i].Draw();
		}
		//�v���[���[�̕`�揈���B
		g_player.Draw();
		//�t���[���o�b�t�@�̓��e����ʂɕ\������B
		for (int i = 0; i < MAP_HEIGHT; i++) {
			for (int j = 0; j < MAP_WIDTH; j++) {
				std::cout << sFrameBuffer[i][j];
			}
			std::cout << "\n";
		}
		EndFrame();	//�t���[���̍Ō�ɌĂ�łˁB���܂��Ȃ��B
	}
    return 0;
}

