#pragma once
#include "Vec2.h"
//右から出現する敵のクラス
class EnemyRight
{
public:
	EnemyRight();
	~EnemyRight();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	bool isExist() { return m_isExist; }

	//敵キャラクターをスタートさせる
	void Start();

private:
	int m_handle;   //グラフィックのハンドル

	bool m_isExist; //存在するかフラグ(使用中かどうか)

	Vec2 m_pos;
	Vec2 m_vec;
	
};

