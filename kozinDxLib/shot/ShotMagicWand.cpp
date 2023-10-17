#include "ShotMagicWand.h"
#include "Game.h"
#include "DxLib.h"
#include "SceneMain.h"
#include <cassert>

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
	//SceneMainの設定忘れチェック
	assert(m_pMain);	//m_pMain == nullptrなら止まる


	m_isExist = true;
	//初期配置の決定
	m_pos = pos;
	//一番近い敵の方向に移動する

	//ターゲット位置
	//弾の発射位置から一番近くにいる敵の座標を取得する
	//SceneMainに実装した関数を利用する
	const Vec2 target = m_pMain->GetNearEnemyPos(m_pos);

	//発射位置からターゲットに向かうベクトル
	Vec2 toTarget = target - m_pos;
	//正規化　totarget自信を正規化(長さを1に)
	toTarget.normalize();
	//弾の速度をkSpeedに
	m_vec = toTarget * kSpeed;

}
