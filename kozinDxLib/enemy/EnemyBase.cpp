#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyBase::EnemyBase() :
	m_handle(-1),
	m_isExist(false)
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
	//‘¶İ‚µ‚È‚¢“G‚Ìˆ—‚Í‚µ‚È‚¢
	if (!m_isExist) return;
}

void EnemyBase::Draw()
{
	//‘¶İ‚µ‚È‚¢“G‚Í•`‰æ‚µ‚È‚¢
	if (!m_isExist) return;

	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
}

void EnemyBase::Start()
{
	m_isExist = false;
}
