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
	//m_pPlayerにはSceneMainで既にメモリを確保したPlayerが
	//どこに置かれているのか、の情報を取得したいためここではメモリ確保をしない
}

EnemyToPlayer::~EnemyToPlayer()
{
	//m_pPlayerの確保解放はSceneMainが管理するので
	//同様に解放も行わない
}

void EnemyToPlayer::Update()
{
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;

	m_pos += m_vec;

	//当たり判定の更新
	UpdateCollision();

	//画面外に出たら存在を消す
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//"左に移動している敵が"画面左から完全に出きった敵を消す
	if ((m_vec.x < 0.0f) &&				//左に移動している敵が 
		(m_pos.x < 0.0f - width / 2))	//左から画面外に出た
	{
		m_isExist = false;
	}

	//"右に移動している敵が"画面右から完全に出きった敵を消す
	if ((m_vec.x > 0.0f) &&				//右に移動している敵が 
		(m_pos.x > Game::kScreenWidth + width / 2))	//右から画面外に出た
	{
		m_isExist = false;
	}

	//"上に移動している敵が"画面上から完全に出きった敵を消す
	if ((m_vec.y < 0.0f) &&				//上に移動している敵が 
		(m_pos.y < 0.0f - height / 2))	//上から画面外に出た
	{
		m_isExist = false;
	}

	//"下に移動している敵が"画面下から完全に出きった敵を消す
	if ((m_vec.y > 0.0f) &&				//下に移動している敵が 
		(m_pos.y > Game::kScreenHeight + height / 2))	//下から画面外に出た
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

	//画面の上下左右いずれかから登場する
	//どこからでてくるかわからない(ランダム)

	//GetRand()関数を利用
	//		0 ~ ()の中の数字の間でランダムな数字を生成する

	int num = GetRand(3);
	switch (num)
	{
	case 0:	//上から
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width) + width / 2);
		m_pos.y = static_cast<float>(-height / 2);
		break;

	case 1:	//左から
		m_pos.x = static_cast<float>(-width / 2);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);
		break;

	case 2:	//下から
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width) + width / 2);
		m_pos.y = static_cast<float>(Game::kScreenHeight + height / 2);
		break;

	case 3:	//右から
		m_pos.x = static_cast<float>(Game::kScreenWidth + width / 2);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height) + height / 2);

		break;

	default:
		assert(false);
		break;
	}

	//画面中央を経由して画面外まで一定速度で移動する

	//コンストラクタでnullptrが設定されて、それ以降変更されていなければ止まる
	assert(m_pPlayer);

	//ターゲット位置
	//const Vec2 target = Vec2{ Game::kScreenWidth / 2, Game::kScreenHeight / 2 };
	const Vec2 target = m_pPlayer->GetPos();

	//敵の初期位置からターゲット位置に向かうベクトルを生成する
	//始点から終点に向かうベクトルを求める場合、終点の座標 - 始点の座標
	Vec2 toTarget = target - m_pos;

	//ベクトルの長さをkSpeedにする

	//ベクトルの正規化、長さを1にする
	toTarget.normalize();

	//kSpeedをかける

	m_vec = toTarget * kSpeed;

}