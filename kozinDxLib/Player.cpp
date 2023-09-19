#include "Player.h"
#include "Game.h"
#include "DxLib.h"

//Player�Ŏg�p����萔
namespace
{
	//�ړ����x
	constexpr float kSpeed = 3.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,1 };
	//�L�����N�^�[�P�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;
	//�A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Player::Player() :
	m_handle(-1),
	m_posX(Game::kScreenWidth / 2),
	m_posY(Game::kScreenHeight / 2),
	m_dir(kDirDown),
	m_warkAnimFrame(0),
	m_warkAnimCount(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{



	//�p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;   //�ړ������ǂ���

	if (pad & PAD_INPUT_UP)
	{
		m_posY -= kSpeed;
		m_dir = kDirUp;
		isMove = true;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		m_posY += kSpeed;
		m_dir = kDirDown;
		isMove = true;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		m_posX -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_posX += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	if (isMove)
	{
		//�����A�j���[�V����
		m_warkAnimFrame++;
		if (m_warkAnimFrame >= kAnimFrameCycle) m_warkAnimFrame = 0;
	}
}

void Player::Draw() const
{
	int animFrame = m_warkAnimFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	//DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), static_cast<int>(m_handle), true);
#if false
	switch (m_dir)
	{
	case kDirDown:
		srcY = 32 * 0;
		break;
	case kDirLeft:
		srcY = 32 * 1;
		break;
	case kDirRight:
		srcY = 32 * 2;
		break;
	case kDirUp:
		srcY = 32 * 3;
		break;
	}
#endif
	DrawRectGraph(static_cast<int>(m_posX), static_cast<int>(m_posY),
		srcX, srcY, kWidth, kHeight, m_handle, true);

}
