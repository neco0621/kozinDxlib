#pragma once
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

	float m_posX;
	float m_posY;
	//向いている方向
	Dir m_dir;
	//歩きアニメーション
	int m_warkAnimFrame;
	int m_warkAnimCount;
};;

