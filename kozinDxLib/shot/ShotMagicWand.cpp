#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

namespace
{
	//�萔�̒�`
	constexpr float kSpeed = 4.0f;

	//	�V���b�g�̑傫��
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;
}

ShotMagicWand::ShotMagicWand()
{
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

	m_pos += m_vec;
	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	//��ʊO�ɏo������
	if ((m_vec.x < 0.0f) &&
		(m_pos.x < 0.0f - kWidth / 2))
	{
		m_isExist = false;
	}
	if ((m_vec.x > 0.0f) &&
		(m_pos.x > Game::kScreenWidth + kWidth / 2))
	{
		m_isExist = false;
	}

	if ((m_vec.y < 0.0f) &&
		(m_pos.y < 0.0f - kHeight / 2))
	{
		m_isExist = false;
	}

	if ((m_vec.y > 0.0f) &&
		(m_pos.y > Game::kScreenHeight + kHeight / 2))
	{
		m_isExist = false;
	}

}

void ShotMagicWand::Draw()
{
	if (!m_isExist) return;

	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, GetColor(255, 255, 0), true);

#ifdef _DEBUG
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
