#pragma once

class Player;
class EnemyRight;
class EnemyToPlayer;
class Bg;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();
private:
	static constexpr int kEnemyNum = 16;

private:
	//�O���t�B�b�N�n���h��
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	//�v���C���[
	Player* m_pPlayer;

	//�G�L�����N�^�[
	//EnemyRight* m_pEnemyRight;
	EnemyRight* m_pEnemyRight[kEnemyNum];
	EnemyToPlayer* m_pEnemyToPlayer[kEnemyNum];

	int m_enemyFrameCount;

	//�w�i
	Bg* m_pBg;
};

