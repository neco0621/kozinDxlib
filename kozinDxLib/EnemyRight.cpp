#include "EnemyRight.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyRight::EnemyRight() :
	m_handle(-1),
	m_isExist(false)
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

void EnemyRight::Draw()
{
	//���݂��Ȃ��G�͕`�悵�Ȃ�
	if (!m_isExist) return;

	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
}

void EnemyRight::Start()
{
	m_isExist = true;
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);


	m_pos.x = static_cast<float>(Game::kScreenWidth);
	m_pos.y = static_cast<float>(Game::kScreenHeight);
}
