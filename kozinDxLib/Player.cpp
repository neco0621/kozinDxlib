#include "Player.h"
#include "Game.h"
#include "DxLib.h"
#include <cmath>

//Playerで使用する定数
namespace
{
	//移動速度
	constexpr float kSpeed = 3.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,1 };
	//キャラクター１コマのフレーム数
	constexpr int kAnimFrameNum = 8;
	//アニメーション１サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Player::Player() :
	m_handle(-1),
	m_pos(Game::kScreenWidth / 2, Game::kScreenHeight / 2),
	m_dir(kDirDown),
	m_warkAnimFrame(0)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{



	//パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	bool isMove = false;   //移動中かどうか
	//移動量を持つようにする
	Vec2 move{ 0.0f, 0.0f };

	if (pad & PAD_INPUT_UP)
	{
		//m_pos.y -= kSpeed;
		move.y -= kSpeed;
		m_dir = kDirUp;
		isMove = true;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		//m_pos.y += kSpeed;
		move.y += kSpeed;
		m_dir = kDirDown;
		isMove = true;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		//m_pos.x -= kSpeed;
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		//m_pos.x += kSpeed;
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}


	//斜め移動の場合でも同じ速さで移動するようにする
	
	//ベクトルの正規化を行うためにベクトルの長さを求める
	float moveLength = move.length();	

	//moveLength(ベクトルの長さ)が0.0になる可能性がある	

	if (moveLength > 0.0f)
	{
		//斜め移動の場合も同じ速さで移動するようにする
		//ベクトルの正規化
		move.normalize();
		//ベクトルの長さをkSpeedにする
		//move.x *= kSpeed;
		//move.y *= kSpeed;
		move = move.mul(kSpeed);

		//座標とベクトルの足し算
		//m_pos.x += move.x;
		//m_pos.y += move.y;
		m_pos = m_pos.plus(move);
	}	

	if (isMove)
	{
		//歩きアニメーション
		m_warkAnimFrame++;
		if (m_warkAnimFrame >= kAnimFrameCycle) m_warkAnimFrame = 0;
	}
}

void Player::Draw() const
{
	int animFrame = m_warkAnimFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	//DrawGraph(static_cast<int>(m_posX), static_cast<int>(m_posY), static_cast<int>(m_handle), true);
#if false
	switch (m_dir)
	{
	case kDirDown:
		srcY = 32 * 0;
		break;
	case kDirLeft:
		srcY = 32 * 1;
		break;
	case kDirRight:
		srcY = 32 * 2;
		break;
	case kDirUp:
		srcY = 32 * 3;
		break;
	}
#endif
	DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY, kWidth, kHeight, m_handle, true);

}
