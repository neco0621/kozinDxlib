#include "ShotBible.h"
#include "DxLib.h"
#include "Player.h"
#include <cassert>

namespace
{
	//ショットの大きさ
	constexpr int kWidth = 16;
	constexpr int kHeight = 24;
	//発生してから消えるまでのフレーム数
	constexpr int kExistFrame = 60 * 5;
	//プレイヤーの周りを1回転するのにかかるフレーム数
	constexpr float kRotFrame = 60;

	//プレイヤーの周りを回る時の半径
	constexpr float kRadius = 100.0f;

	//プレイヤーから見た相対位置をデータとして持つ
	const Vec2 k0ffset[] =
	{
		Vec2{kRadius	, 0.0f		},//右
		Vec2{0.0f		,kRadius	},//下
		Vec2{-kRadius	, 0.0f		},//左
		Vec2{0.0f		,-kRadius	},//上
	};
}

ShotBible::ShotBible() :
	m_frameCount(0),
	m_angle(0)
{
}

ShotBible::~ShotBible()
{
}

void ShotBible::Init()
{
}

void ShotBible::Update()
{
	if (!m_isExist) return;
	//プレイヤーのポインタが設定されいていない
	assert(m_pPlayer);	

	//一定時間経過したら消える
	m_frameCount++;
	if (m_frameCount > kExistFrame)
	{
		m_isExist = false;
		return; //終了が確定していたら以降の処理は行わない
	}

	//移動処理
	//プレイヤーの位置によって表示する場所が変わる
	//プレイヤーの位置情報が欲しい
	
	//プレイヤーから見た角度の更新
	//kRotFrame かけて1回転する
	m_angle += DX_TWO_PI_F / kRotFrame;

	//k0ffset[index] と プレイヤーの位置から最終的な所との位置を決定する
	//m_pos = m_pPlayer->GetPos() + k0ffset[index];
	//m_pos : ショットの位置	今回はこれをcos, sinで生成する
	//m_pPlayer->GetPos() : 回転の中心位置
	//m_angle : 真左を0とした場合の回転角度
	//kRadius : 回転半径

	Vec2 offset;	//プレイヤーから見た位置
	offset.x = cosf(m_angle) * kRadius;
	offset.y = sinf(m_angle) * kRadius;

	m_pos = m_pPlayer->GetPos() + offset;
}

void ShotBible::Draw()
{
	if (!m_isExist) return;

	DrawBox(m_pos.x - kWidth / 2, m_pos.y - kHeight / 2, m_pos.x + kWidth / 2, m_pos.y + kHeight / 2, GetColor(32,32,255), true);
}

void ShotBible::Start(Vec2 pos)
{
	m_isExist = true;

	m_pos = pos;
	m_frameCount = 0;
}
