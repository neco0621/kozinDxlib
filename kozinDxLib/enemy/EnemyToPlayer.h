#pragma once
#include "Vec2.h"

class Player;

class EnemyToPlayer
{
public:
	EnemyToPlayer();
	~EnemyToPlayer();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	bool isExist() { return m_isExist; }

	Vec2 GetPos() { return m_pos; }
	Vec2 GetVec() { return m_vec; }

	//敵キャラクターをスタートさせる
	void Start();

private:
	int m_handle;   //グラフィックのハンドル

	bool m_isExist; //存在するかフラグ(使用中かどうか)

	Player* m_pPlayer;

	Vec2 m_pos;
	Vec2 m_vec;
};

