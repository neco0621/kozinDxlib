#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class Bg;
class EnemyBase;
class ShotBase;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	void Update();
	void Draw();

	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEnemyPos(Vec2 pos) const;

private:
	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();
	void CreateEnemyToPlayer();

private:
	//グラフィックのハンドル
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	//プレイヤー
	Player* m_pPlayer;

	//背景
	Bg* m_pBg;

	//敵
	std::vector<EnemyBase*> m_pEnemy;	//配列のサイズは実行時に決める(今回はコンストラクタ)
	//EnemyBase* m_pEnemy[16];   <-今までの書き方

	//ショット
	ShotBase* m_pShot;


	//敵の登場間隔
	int m_enemyInterval;
};