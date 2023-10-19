#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

namespace
{
	//�萔�̒�`
	constexpr float kSpeed = 6.0f;

	//	�V���b�g�̑傫��
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;

	//�o���Ă����ߋ��̈ʒu���̐�
	constexpr int kPosLogNum = 12;
}

ShotMagicWand::ShotMagicWand()
{
	m_posLog.resize(kPosLogNum);
}

ShotMagicWand::~ShotMagicWand()
{
}

void ShotMagicWand::Init()
{
}

void ShotMagicWand::Update()
{
	if (!m_isExist) return;

	//�ʒu�̃��O�����炷
	for (int i = m_posLog.size() - 1; i >= 1; i--)
	{
		m_posLog[i] = m_posLog[i - 1];
	}
	//1�t���[�����̈ʒu��������
	m_posLog[0] = m_pos;

	m_pos += m_vec;
	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	//��ʊO�ɏo������
	//�ߋ��̕\���ʒu���܂߂Ă��ׂĉ�ʊO�ɏo����I��
	bool isOut = false;	//�`�F�b�N���̍��W����ʊO���ǂ����t���O
	

	//�ߋ����O����ʓ��ɂ��邩���`�F�b�N����
	for (int i = 0; i < m_posLog.size(); i++)
	{
		isOut = false;
		if (m_posLog[i].x < 0.0f - kWidth / 2)	isOut = true;
		if (m_posLog[i].x > Game::kScreenWidth + kWidth / 2)	isOut = true;
		if (m_posLog[i].y < 0.0f - kHeight / 2) isOut = true;
		if (m_posLog[i].y > Game::kScreenHeight + kHeight / 2)	isOut = true;

		//�`�F�b�N���̍��W����ʓ��Ȃ炱���ŏI��
		if (!isOut) return;
	}

	//�����ɗ����Ƃ������Ƃ͉�ʊO�ɂ���
	m_isExist = false;
}

void ShotMagicWand::Draw()
{
	if (!m_isExist) return;

	//�c���̕\��

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i < m_posLog.size(); i++)
	{
		for (int lineNum = 0; lineNum < 16; lineNum++)
		{
			int startX = m_pos.x;
			int startY = m_pos.y;
			int endX = m_posLog[i].x;
			int endY = m_posLog[i].y;
			
			//��������͂���ĂȂ����e
			//�������悭���邽�߂Ɏg��
			float angle = GetRand(359) /  360.0f * DX_TWO_PI_F;
			float len = GetRand(10) - 2;
			startX += cosf(angle) * len;
			startY += sinf(angle) * len;
			endX += cosf(angle) * len;
			endY += cosf(angle) * len;

			DrawLine(startX, startY, endX, endY, GetColor(1, 2, 16), kWidth);

		}
		
	}
	//�\�����[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//int alpha = 255;
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//DrawLine(m_pos.x,m_pos.y, m_posLog[0].x, m_posLog[1].y,GetColor(255,255,0),kWidth);

	//for (int i = 1; i < m_posLog.size(); i++)
	//{
	//	alpha -= 20;
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	//	DrawLine(m_posLog[i - 1].x, m_posLog[i - 1].y, m_posLog[i].x, m_posLog[i].y, GetColor(255, 255, 0), kWidth);
	//}
	////�\�����[�h�����ɖ߂�
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	//�e�̓����蔻��f�o�b�O�\��
	m_colRect.Draw(GetColor(0, 0, 0), false);
#endif
}

void ShotMagicWand::Start(Vec2 pos)
{
	//SceneMain�̐ݒ�Y��`�F�b�N
	assert(m_pMain);	//m_pMain == nullptr�Ȃ�~�܂�


	m_isExist = true;
	//�����z�u�̌���
	m_pos = pos;
	//��ԋ߂��G�̕����Ɉړ�����

	//�ߋ��̈ʒu�������������_�ł͏����ʒu�Ɠ����ɂ��Ă��܂�
	//�c�����ςȈʒu�ɕ\������Ȃ��悤�ɂ��邽��
	for (int i = 0; i < m_posLog.size(); i++)
	{
		m_posLog[i] = m_pos;
	}

	//�^�[�Q�b�g�ʒu
	//�e�̔��ˈʒu�����ԋ߂��ɂ���G�̍��W���擾����
	//SceneMain�Ɏ��������֐��𗘗p����
	const Vec2 target = m_pMain->GetNearEnemyPos(m_pos);

	//���ˈʒu����^�[�Q�b�g�Ɍ������x�N�g��
	Vec2 toTarget = target - m_pos;
	//���K���@totarget���M�𐳋K��(������1��)
	toTarget.normalize();
	//�e�̑��x��kSpeed��
	m_vec = toTarget * kSpeed;

}
