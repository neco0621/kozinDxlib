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
	//存在しない敵の処理はしない
	if (!m_isExist) return;

	m_pos += m_vec;

	//画面外に出たら存在をけす
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//"左に移動している敵が"画面左から完全に出きった敵を消す

	if ((m_vec.x < 0.0f) &&			//左に移動している敵
		(m_pos.x < 0.0f - width))	//左から画面外に出た
	{
		m_isExist = false;
	}

	//"右に移動している敵が"画面右から完全に出きった敵を消す
	if ((m_vec.x > 0.0f) &&				//左に移動している敵
		(m_pos.x > Game::kScreenWidth))	//左から画面外に出た
	{
		m_isExist = false;
	}
	//"上に移動している敵が"画面上から完全に出きった敵を消す
	if ((m_vec.y < 0.0f) &&					//左に移動している敵
		(m_pos.y < 0.0f - height))	//左から画面外に出た
	{
		m_isExist = false;
	}
	//"下に移動している敵が"画面下から完全に出きった敵を消す
	if ((m_vec.y > 0.0f) &&					//左に移動している敵
		(m_pos.y > Game::kScreenWidth))		//左から画面外に出た
	{
		m_isExist = false;
	}
}

void EnemyRight::Draw()
{
	//存在しない敵は描画しない
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
