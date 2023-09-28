#include "EnemyToPlayer.h"
#include "game.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyToPlayer::EnemyToPlayer() :
	m_handle(-1),
	m_isExist(false),
	m_pPlayer(nullptr)
	//m_pos�͈����Ȃ��̃R���X�g���N�^���Ă΂��
	//�����Ȃ��̃R���X�g���N�^���Ăԏꍇ�͏ȗ��ł���
{
	//m_pPlayer�ɂ�SceneMain�Ŋ��Ƀ��������m�ۂ���Player��
	//�ǂ��ɒu����Ă���̂��A�̏������Ă��������̂ł����ł̓������m�ۂ��Ȃ�
}

EnemyToPlayer::~EnemyToPlayer()
{
	//m_pPlayer�̊m�ۉ����SceneMain���Ǘ�����̂�
	//���l�ɉ�����s��Ȃ�
}

void EnemyToPlayer::Init()
{
}

void EnemyToPlayer::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	m_pos += m_vec;

	//��ʊO�ɏo���瑶�݂�����
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//"���Ɉړ����Ă���G��"��ʍ����犮�S�ɏo�������G������

	if ((m_vec.x < 0.0f) &&			//���Ɉړ����Ă���G
		(m_pos.x < 0.0f - width))	//�������ʊO�ɏo��
	{
		m_isExist = false;
	}

	//"�E�Ɉړ����Ă���G��"��ʉE���犮�S�ɏo�������G������
	if ((m_vec.x > 0.0f) &&				//���Ɉړ����Ă���G
		(m_pos.x > Game::kScreenWidth))	//�������ʊO�ɏo��
	{
		m_isExist = false;
	}
	//"��Ɉړ����Ă���G��"��ʏォ�犮�S�ɏo�������G������
	if ((m_vec.y < 0.0f) &&					//���Ɉړ����Ă���G
		(m_pos.y < 0.0f - height))	//�������ʊO�ɏo��
	{
		m_isExist = false;
	}
	//"���Ɉړ����Ă���G��"��ʉ����犮�S�ɏo�������G������
	if ((m_vec.y > 0.0f) &&					//���Ɉړ����Ă���G
		(m_pos.y > Game::kScreenWidth))		//�������ʊO�ɏo��
	{
		m_isExist = false;
	}
}

void EnemyToPlayer::Draw()
{
	// ���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;
	assert(m_handle != -1);
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
}

void EnemyToPlayer::Start()
{
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//m_pos.x = static_cast<float>(Game::kScreenWidth);
	//m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));

	int num = GetRand(3);

	switch (num)
	{
	case 0:
		m_pos.x = static_cast<float> (GetRand(Game::kScreenWidth - width));
		m_pos.y = static_cast<float>( - height);
		break;
	case 1:
		m_pos.x = static_cast<float>( - width);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));
		break;
	case 2:
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width));
		m_pos.y = static_cast<float>(Game::kScreenHeight);
		break;
	case 3:
		m_pos.x = static_cast<float>(Game::kScreenWidth);
		m_pos.y = static_cast<float> (GetRand(Game::kScreenHeight - height));
		break;
	default:
		assert(false);
		break;
	}

	//��ʒ������o�R���ĉ�ʔ����܂ň�葬�x�ňړ�����
	assert(m_pPlayer);

	//�^�[�Q�b�g�ʒu
	//const Vec2 target = Vec2{ Game::kScreenWidth / 2, Game::kScreenHeight / 2};
	const Vec2 target = m_pPlayer->GetPos();
	clsDx();
	//�G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�
	//�n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = target - m_pos;
	//�x�N�g���̒�����kSpeed�ɂ��Ă��
	toTarget.normalize();
	//kSpeed�ł�����
	m_vec = toTarget * kSpeed;
}



