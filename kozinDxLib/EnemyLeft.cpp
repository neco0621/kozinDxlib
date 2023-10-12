#include "EnemyLeft.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyLeft::EnemyLeft()
//EnemyLeft()	//明示的に呼ぶ
{
	//基底クラス(EnemyBase)のコンストラクタを
	// 明示的に呼ばなくてもここで呼ばれる
}

EnemyLeft::~EnemyLeft()
{
	//デストラクタの呼ばれる(はず)
}

void EnemyLeft::Update()
{
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;

	m_pos += m_vec;
	//当たり判定の更新
	UpdateCollision();

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}

void EnemyLeft::Start()
{
	//画面中央に敵キャラクターを登場させる
	m_isExist = true;
	m_pos.x = Game::kScreenWidth / 2;
	m_pos.y = Game::kScreenHeight / 2;

	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	m_pos.x = static_cast<float>(0 - width);
	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));

	//1フレーム当たりの移動ベクトルを決定する
	m_vec.x = kSpeed;
	m_vec.y = 0.0f;
}
