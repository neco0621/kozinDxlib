#pragma once
#include "EnemyBase.h"

class Player;
//発生位置から発生した時のプレイヤーの位置に向かって移動する
class EnemyToPlayer : public EnemyBase
{
public:
	EnemyToPlayer();
	virtual ~EnemyToPlayer();

	virtual void Update() override;

	//メンバー変数にアクセスする
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	//敵キャラクターをスタートさせる
	virtual void Start() override;

private:
	Player* m_pPlayer;
};