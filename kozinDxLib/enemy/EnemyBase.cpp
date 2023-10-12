#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"

#include <cassert>

namespace
{
	constexpr float kSpeed = 4.0f;
}

EnemyBase::EnemyBase() :
	m_handle(-1),
	m_isExist(false),
	m_pos()	//省略可
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
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;

	//m_pos += m_vec;

	////ベクトルをいじってみる
	////画面中央を超えたら加速する
	//if (m_pos.x < Game::kScreenWidth / 2)
	//{
	//	//移動ベクトルを変化させることで速度を上げる
	//	//左に移動する量を大きくすることで早く動いているように見せる
	//	m_vec.x -= kSpeed;
	//}

	////画面外に出たら存在を消す
	//int width = 0;
	//int height = 0;
	//GetGraphSize(m_handle, &width, &height);

	//if (m_pos.x < 0.0f - width)
	//{
	//	m_isExist = false;
	//}
}

void EnemyBase::Draw()
{
	//存在しない敵の処理はしない
	if (!m_isExist)
		return;

	assert(m_handle != -1);
	DrawTurnGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle, false);
	/*DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), double ExtRate, double Angle,
		int GrHandle, int TransFlag, int TurnFlag);*/
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);
	m_colRect.Set(m_pos.x, m_pos.y, width, height);
}

//void EnemyBase::Start()
//{
//	m_isExist = true;
//
//	int width = 0;
//	int height = 0;
//	GetGraphSize(m_handle, &width, &height);
//
//	m_pos.x = static_cast<float>(Game::kScreenWidth);
//	m_pos.y = static_cast<float>(GetRand(Game::kScreenHeight - height));
//
//	//1フレーム当たりの移動ベクトルを決定する
//	m_vec.x = -kSpeed;
//	m_vec.y = 0.0f;
//}