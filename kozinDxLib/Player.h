#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw() const;

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

public:
	//向いてる方向
	enum Dir
	{
		kDirDown,   //下
		kDirLeft,   //左
		kDirRight,   //右
		kDirUp,     //上
	};

private:
	int m_handle;   //グラフィックのハンドル
	//表示位置
	Vec2 m_pos;
	//向いている方向
	Dir m_dir;
	//歩きアニメーション
	int m_warkAnimFrame;
	int m_warkAnimCount;
};;

