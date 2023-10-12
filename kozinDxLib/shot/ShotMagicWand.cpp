#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	//定数の定義
	constexpr float kSpeed = 4.0f;

	//	ショットの大きさ
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
	//当たり判定の更新
	m_colRect.Set(m_pos.x, m_pos.y, kWidth, kHeight);

	//画面外に出た処理
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
	//初期配置の決定
	m_pos = pos;
	//仮実装　右方向に移動させる
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

}
