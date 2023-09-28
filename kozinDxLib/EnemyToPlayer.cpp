#include "EnemyToPlayer.h"
#include "game.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyToPlayer::EnemyToPlayer() :
	m_handle(-1),
	m_isExist(false),
	m_pPlayer(nullptr)
	//m_posは引数なしのコンストラクタが呼ばれる
	//引数なしのコンストラクタを呼ぶ場合は省略できる
{
	//m_pPlayerにはSceneMainで既にメモリを確保したPlayerが
	//どこに置かれているのか、の情報を入れておきたいのでここではメモリ確保しない
}

EnemyToPlayer::~EnemyToPlayer()
{
	//m_pPlayerの確保解放はSceneMainが管理するので
	//同様に解放も行わない
}

void EnemyToPlayer::Init()
{
}

void EnemyToPlayer::Update()
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

void EnemyToPlayer::Draw()
{
	// 存在しない敵は描画しない
	if (!m_isExist) return;
	assert(m_handle != -1);
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
}

void EnemyToPlayer::Start()
{
	m_isExist = true;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	//m_pos.x = static_cast<float>(Game::kScreenWidth);
	//m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));

	int num = GetRand(3);

	switch (num)
	{
	case 0:
		m_pos.x = static_cast<float> (GetRand(Game::kScreenWidth - width));
		m_pos.y = static_cast<float>( - height);
		break;
	case 1:
		m_pos.x = static_cast<float>( - width);
		m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));
		break;
	case 2:
		m_pos.x = static_cast<float>(GetRand(Game::kScreenWidth - width));
		m_pos.y = static_cast<float>(Game::kScreenHeight);
		break;
	case 3:
		m_pos.x = static_cast<float>(Game::kScreenWidth);
		m_pos.y = static_cast<float> (GetRand(Game::kScreenHeight - height));
		break;
	default:
		assert(false);
		break;
	}

	//画面中央を経由して画面買いまで一定速度で移動する
	assert(m_pPlayer);

	//ターゲット位置
	//const Vec2 target = Vec2{ Game::kScreenWidth / 2, Game::kScreenHeight / 2};
	const Vec2 target = m_pPlayer->GetPos();
	clsDx();
	//敵の初期位置からターゲット位置に向かうベクトルを生成
	//始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = target - m_pos;
	//ベクトルの長さをkSpeedにしてやる
	toTarget.normalize();
	//kSpeedでかける
	m_vec = toTarget * kSpeed;
}



