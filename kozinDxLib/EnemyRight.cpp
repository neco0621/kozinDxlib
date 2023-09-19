#include "EnemyRight.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyRight::EnemyRight() :
	m_handle(-1),
	m_isExist(false),
	m_posX(static_cast<float>(GetRand(Game::kScreenWidth))),
	m_posY(static_cast<float>(GetRand(Game::kScreenHeight)))
{
}

EnemyRight::~EnemyRight()
{
}

void EnemyRight::Init()
{
}

void EnemyRight::Update()
{
	//���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	m_posX -= kSpeed;

	//��ʊO�ɏo���瑶�݂�����
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_posX < 0.0f - width)
	{
		m_isExist = false;
	}
}

void EnemyRight::Draw() const
{
	//���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;

	DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), m_handle, false);
}

void EnemyRight::Start()
{
	m_isExist = true;
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);


	m_posX = static_cast<float>(Game::kScreenWidth);
	m_posY = static_cast<float>(Game::kScreenHeight);
}
