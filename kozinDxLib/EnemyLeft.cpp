#include "EnemyLeft.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	constexpr float kSpeed = 4.0f;

	constexpr float kWaveRange = 32.0f;
	constexpr float kWaveSpeed = 1.2f;
}

EnemyLeft::EnemyLeft() : 
	EnemyBase(),
	m_sinRate(0.0f)
//EnemyLeft()	//�����I�ɌĂ�
{
	//���N���X(EnemyBase)�̃R���X�g���N�^��
	// �����I�ɌĂ΂Ȃ��Ă������ŌĂ΂��
}

EnemyLeft::~EnemyLeft()
{
	//�f�X�g���N�^�̌Ă΂��(�͂�)
}

void EnemyLeft::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist)
		return;

	m_basePos += m_vec;

	m_pos = m_basePos;

	m_sinRate += kWaveSpeed;
	m_pos.y += sinf(m_sinRate) * kWaveRange;
	//�����蔻��̍X�V
	UpdateCollision();

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_pos.x > Game::kScreenWidth + width / 2)
	{
		m_isExist = false;
	}
}

void EnemyLeft::Start()
{
	//��ʒ����ɓG�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	m_basePos.x = static_cast<float>(0 - width / 2);
	m_basePos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);

	/*m_pos.x = static_cast<float>(0 - width / 2);
	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);*/

	//1�t���[��������̈ړ��x�N�g�������肷��
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}
