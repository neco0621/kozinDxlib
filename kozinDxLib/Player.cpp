#include "Player.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "SceneMain.h"
#include "ShotMagicWand.h"
#include "ShotBible.h"

#include <cmath>

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

	//�A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;

	//�A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	//�_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;

	//���@�̏�̔��ˊԊu
	constexpr int kMagicWandFrame = 30;
}

Player::Player(SceneMain* pMain) :
	m_pMain(pMain),
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight / 2),
	m_dir(kDirDown),
	m_walkAnimFrame(0),
	m_magicWandFrame(0),
	m_damageFrame(0)
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
	//�_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;

	//pad�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	/* (pad & PAD_INPUT_UP) == 0 �̌���*/
	//0000 0000 0000 0000 0000 0000 0000 0000�@��{
	//0000 0000 0000 0000 0000 0000 0000 1000�@��L�[�������ꂽ�Ƃ�

	bool isMove = false;	//�ړ����Ă��邩�ǂ���

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	if ((pad & PAD_INPUT_UP) != 0)
	{
		//m_pos.y -= kSpeed;
		move.y -= kSpeed;
		m_dir = kDirUp;
		isMove = true;
	}
	if ((pad & PAD_INPUT_DOWN) != 0)
	{
		//m_pos.y += kSpeed;
		move.y += kSpeed;
		m_dir = kDirDown;
		isMove = true;
	}
	if ((pad & PAD_INPUT_LEFT) != 0)
	{
		//m_pos.x -= kSpeed;
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if ((pad & PAD_INPUT_RIGHT) != 0)
	{
		//m_pos.x += kSpeed;
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���

	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= kSpeed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	if (isMove)
	{
		//�����A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	else
	{
		m_walkAnimFrame = kAnimFrameNum;
	}

	//�V���b�g
	m_magicWandFrame++;
	if (m_magicWandFrame >= kMagicWandFrame)
	{
		m_magicWandFrame = 0;

		//���@�̏񐶐�
		ShotMagicWand* pShot = new ShotMagicWand;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		//�ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pMain->AddShot(pShot);
	}

	//�����e�X�g����
	//�{�^�����������甭������悤�ɂ���
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		//�����������̊m��
		ShotBible* pShot = new ShotBible;

		pShot->Init();
		pShot->SetMain(m_pMain);
		pShot->SetPlayer(this);
		pShot->Start(GetPos());
		//�ȍ~�X�V�⃁�����̉����SceneMain�ɔC����
		m_pMain->AddShot(pShot);

	}


}

void Player::Draw()
{
	//�_���[�W���o   2�t���[���Ԋu�ŕ\����\���؂�ւ�
	//0:�\�������
	//1:�\�������
	//2:��\��
	//3:��\��
	//4:�\��
	//%4 ���邱�Ƃ�01230123...�ɕϊ�����
	if (m_damageFrame % 4 >= 2) return;


	int animFrame = m_walkAnimFrame / kAnimFrameNum;

	int srcX = kWidth * kUseFrame[animFrame];
	int srcY = kHeight * m_dir;

	//DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		//srcX, srcY, kWidth, kHeight, m_handle, true);

	//DX���C�u�����ɂ̓��t�@�����X�y�[�W�ɏ�����ĂȂ��֐����������݂���
	//DxLib.h���m�F���Ă�����ۂ��֐���T�����茟�������肵�Ă݂悤
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY, kWidth, kHeight,
		1.0, 0.0,
		m_handle, true, false);

#ifdef _DEBUG
	//�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Player::OnDamage()
{
	//�_���[�W���o���͍ēx�_���[�W��H���Ȃ�
	if (m_damageFrame > 0)	return;
	//���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;
}
