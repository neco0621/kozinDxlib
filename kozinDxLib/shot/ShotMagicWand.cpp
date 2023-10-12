#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	//�萔�̒�`
	constexpr float kSpeed = 4.0f;

	//	�V���b�g�̑傫��
	constexpr float kWidth = 4.0f;
	constexpr float kHeight = 4.0f;
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
	m_colRect.Set(m_pos.x, m_pos.y, kWidth, kHeight);

	//��ʊO�ɏo������
	if ((m_vec.x < 0.0f) &&
		(m_pos.x < 0.0f - kWidth))
	{
		m_isExist = false;
	}
	if ((m_vec.x > 0.0f) &&
		(m_pos.x > Game::kScreenWidth))
	{
		m_isExist = false;
	}

	if ((m_vec.y < 0.0f) &&
		(m_pos.y < 0.0f - kHeight))
	{
		m_isExist = false;
	}

	if ((m_vec.y > 0.0f) &&
		(m_pos.y > Game::kScreenHeight))
	{
		m_isExist = false;
	}

}

void ShotMagicWand::Draw()
{
	if (!m_isExist) return;

	DrawBox(m_pos.x, m_pos.y, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);
}

void ShotMagicWand::Start(Vec2 pos)
{
	m_isExist = true;
	//�����z�u�̌���
	m_pos = pos;
	//�������@�E�����Ɉړ�������
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

}
