#pragma once
#include <vector>

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

private:
	//敵キャラクターの生成
	void createEnemyLeft();
	void createEnemyRight();
	void createEnemyToPlayer();

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