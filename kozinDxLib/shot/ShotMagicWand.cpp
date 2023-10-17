#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	//定数の定義
	constexpr float kSpeed = 4.0f;

	//	ショットの大きさ
	constexpr float kWidth = 8.0f;
	constexpr float kHeight = 8.0f;
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
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);

	//画面外に出た処理
	if ((m_vec.x < 0.0f) &&
		(m_pos.x < 0.0f - kWidth / 2))
	{
		m_isExist = false;
	}
	if ((m_vec.x > 0.0f) &&
		(m_pos.x > Game::kScreenWidth + kWidth / 2))
	{
		m_isExist = false;
	}

	if ((m_vec.y < 0.0f) &&
		(m_pos.y < 0.0f - kHeight / 2))
	{
		m_isExist = false;
	}

	if ((m_vec.y > 0.0f) &&
		(m_pos.y > Game::kScreenHeight + kHeight / 2))
	{
		m_isExist = false;
	}

}

void ShotMagicWand::Draw()
{
	if (!m_isExist) return;

	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, GetColor(255, 255, 0), true);

#ifdef _DEBUG
	m_colRect.Draw(GetColor(0, 0, 0), false);
#endif
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
