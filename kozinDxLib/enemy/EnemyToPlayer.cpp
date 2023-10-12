#include "EnemyToPlayer.h"
#include "DxLib.h"
#include "Game.h"
#include "Player.h"

#include <cmath>
#include <cassert>

namespace
{
	constexpr float kSpeed = 3.0f;
}

EnemyToPlayer::EnemyToPlayer() :
	m_pPlayer(nullptr)
{
	//m_pPlayer�ɂ�SceneMain�Ŋ��Ƀ��������m�ۂ���Player��
	//�ǂ��ɒu����Ă���̂��A�̏����擾���������߂����ł̓������m�ۂ����Ȃ�
}

EnemyToPlayer::~EnemyToPlayer()
{
	//m_pPlayer�̊m�ۉ����SceneMain���Ǘ�����̂�
	//���l�ɉ�����s��Ȃ�
}

void EnemyToPlayer::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist)
		return;

	m_pos += m_vec;

	//�����蔻��̍X�V
	UpdateCollision();

	////�x�N�g�����������Ă݂�
	////��ʒ����𒴂������������
	//if (m_pos.x < Game::kScreenWidth / 2)
	//{
	//	//�ړ��x�N�g����ω������邱�Ƃő��x���グ��
	//	//���Ɉړ�����ʂ�傫�����邱�Ƃő��������Ă���悤�Ɍ�����
	//	m_vec *= kSpeed;
	//}

	//��ʊO�ɏo���瑶�݂�����
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//"���Ɉړ����Ă���G��"��ʍ����犮�S�ɏo�������G������
	//if (m_pos.x < 0.0f - width)
	if ((m_vec.x < 0.0f) &&				//���Ɉړ����Ă���G�� 
		(m_pos.x < 0.0f - width))	//�������ʊO�ɏo��
	{
		m_isExist = false;
	}

	//"�E�Ɉړ����Ă���G��"��ʉE���犮�S�ɏo�������G������
	if ((m_vec.x > 0.0f) &&				//�E�Ɉړ����Ă���G�� 
		(m_pos.x > Game::kScreenWidth))	//�E�����ʊO�ɏo��
	{
		m_isExist = false;
	}

	//"��Ɉړ����Ă���G��"��ʏォ�犮�S�ɏo�������G������
	if ((m_vec.y < 0.0f) &&				//��Ɉړ����Ă���G�� 
		(m_pos.y < 0.0f - height))	//�ォ���ʊO�ɏo��
	{
		m_isExist = false;
	}

	//"���Ɉړ����Ă���G��"��ʉ����犮�S�ɏo�������G������
	if ((m_vec.y > 0.0f) &&				//���Ɉړ����Ă���G�� 
		(m_pos.y > Game::kScreenHeight))	//�������ʊO�ɏo��
	{
		m_isExist = false;
	}
}

void EnemyToPlayer::Start()
{
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//��ʂ̏㉺���E�����ꂩ����o�ꂷ��
	//�ǂ�����łĂ��邩�킩��Ȃ�(�����_��)

	//GetRand()�֐��𗘗p
	//		0 ~ ()�̒��̐����̊ԂŃ����_���Ȑ����𐶐�����

	int num = GetRand(3);
	switch (num)
	{
	case 0:	//��
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width));
		m_pos.y = static_cast<float>(-height);
		break;

	case 1:	//��
		m_pos.x = static_cast<float>(-width);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));
		break;

	case 2:	//��
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width));
		m_pos.y = static_cast<float>(Game::kScreenHeight);
		break;

	case 3:	//�E
		m_pos.x = static_cast<float>(Game::kScreenWidth);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));

		break;

	default:
		assert(false);
		break;
	}

	//��ʒ������o�R���ĉ�ʊO�܂ň�葬�x�ňړ�����

	//�R���X�g���N�^��nullptr���ݒ肳��āA����ȍ~�ύX����Ă��Ȃ���Ύ~�܂�
	assert(m_pPlayer);

	//�^�[�Q�b�g�ʒu
	//const Vec2 target = Vec2{ Game::kScreenWidth / 2, Game::kScreenHeight / 2 };
	const Vec2 target = m_pPlayer->GetPos();

	//�G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	//�n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W - �n�_�̍��W
	Vec2 toTarget = target - m_pos;

	//�x�N�g���̒�����kSpeed�ɂ���

	//�x�N�g���̐��K���A������1�ɂ���
	toTarget.normalize();

	//kSpeed��������

	m_vec = toTarget * kSpeed;

}