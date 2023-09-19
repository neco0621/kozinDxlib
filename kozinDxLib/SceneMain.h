#pragma once

class Player;
class EnemyRight;
class Bg;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw() const;
private:
	static constexpr int kEnemyNum = 16;

private:
	//グラフィックハンドル
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	//プレイヤー
	Player* m_pPlayer;

	//敵キャラクター
	//EnemyRight* m_pEnemyRight;
	EnemyRight* m_pEnemyRight[kEnemyNum];

	int m_enemyFrameCount;

	//背景
	Bg* m_pBg;
};

