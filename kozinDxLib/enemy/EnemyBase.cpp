#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyBase::EnemyBase() :
	m_handle(-1),
	m_isExist(false),
	m_pos()	//�ȗ���
{

}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Init()
{

}

void EnemyBase::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist)
		return;

	//m_pos += m_vec;

	////�x�N�g�����������Ă݂�
	////��ʒ����𒴂������������
	//if (m_pos.x < Game::kScreenWidth / 2)
	//{
	//	//�ړ��x�N�g����ω������邱�Ƃő��x���グ��
	//	//���Ɉړ�����ʂ�傫�����邱�Ƃő��������Ă���悤�Ɍ�����
	//	m_vec.x -= kSpeed;
	//}

	////��ʊO�ɏo���瑶�݂�����
	//int width = 0;
	//int height = 0;
	//GetGraphSize(m_handle, &width, &height);

	//if (m_pos.x < 0.0f - width)
	//{
	//	m_isExist = false;
	//}
}

void EnemyBase::Draw()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist)
		return;

	assert(m_handle != -1);
	DrawTurnGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
	/*DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), double ExtRate, double Angle,
		int GrHandle, int TransFlag, int TurnFlag);*/
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	m_colRect.Set(m_pos.x, m_pos.y, width, height);
}

//void EnemyBase::Start()
//{
//	m_isExist = true;
//
//	int width = 0;
//	int height = 0;
//	GetGraphSize(m_handle, &width, &height);
//
//	m_pos.x = static_cast<float>(Game::kScreenWidth);
//	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));
//
//	//1�t���[��������̈ړ��x�N�g�������肷��
//	m_vec.x = -kSpeed;
//	m_vec.y = 0.0f;
//}