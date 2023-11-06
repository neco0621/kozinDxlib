#include "ShotBible.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>

namespace
{
	//�V���b�g�̑傫��
	constexpr int kWidth = 16;
	constexpr int kHeight = 24;
	//�������Ă��������܂ł̃t���[����
	constexpr int kExistFrame = 60 * 5;
	//�v���C���[�̎����1��]����̂ɂ�����t���[����
	constexpr float kRotFrame = 60;

	//�v���C���[�̎������鎞�̔��a
	constexpr float kRadius = 100.0f;

	//�v���C���[���猩�����Έʒu���f�[�^�Ƃ��Ď���
	const Vec2 k0ffset[] =
	{
		Vec2{kRadius	, 0.0f		},//�E
		Vec2{0.0f		,kRadius	},//��
		Vec2{-kRadius	, 0.0f		},//��
		Vec2{0.0f		,-kRadius	},//��
	};
}

ShotBible::ShotBible() :
	m_frameCount(0),
	m_angle(0)
{
}

ShotBible::~ShotBible()
{
}

void ShotBible::Init()
{
}

void ShotBible::Update()
{
	if (!m_isExist) return;
	//�v���C���[�̃|�C���^���ݒ肳�ꂢ�Ă��Ȃ�
	assert(m_pPlayer);	

	//��莞�Ԍo�߂����������
	m_frameCount++;
	if (m_frameCount > kExistFrame)
	{
		m_isExist = false;
		return; //�I�����m�肵�Ă�����ȍ~�̏����͍s��Ȃ�
	}

	//�ړ�����
	//�v���C���[�̈ʒu�ɂ���ĕ\������ꏊ���ς��
	//�v���C���[�̈ʒu��񂪗~����
	
	//�v���C���[���猩���p�x�̍X�V
	//kRotFrame ������1��]����
	m_angle += DX_TWO_PI_F / kRotFrame;

	//k0ffset[index] �� �v���C���[�̈ʒu����ŏI�I�ȏ��Ƃ̈ʒu�����肷��
	//m_pos = m_pPlayer->GetPos() + k0ffset[index];
	//m_pos : �V���b�g�̈ʒu	����͂����cos, sin�Ő�������
	//m_pPlayer->GetPos() : ��]�̒��S�ʒu
	//m_angle : �^����0�Ƃ����ꍇ�̉�]�p�x
	//kRadius : ��]���a

	Vec2 offset;	//�v���C���[���猩���ʒu
	offset.x = cosf(m_angle) * kRadius;
	offset.y = sinf(m_angle) * kRadius;

	m_pos = m_pPlayer->GetPos() + offset;
}

void ShotBible::Draw()
{
	if (!m_isExist) return;

	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, GetColor(32,32,255), true);
}

void ShotBible::Start(Vec2 pos)
{
	m_isExist = true;

	m_pos = pos;
	m_frameCount = 0;
}
