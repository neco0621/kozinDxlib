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
	//�O���t�B�b�N�n���h��
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	//�v���C���[
	Player* m_pPlayer;

	//�G�L�����N�^�[
	//EnemyRight* m_pEnemyRight;
	EnemyRight* m_pEnemyRight[kEnemyNum];

	int m_enemyFrameCount;

	//�w�i
	Bg* m_pBg;
};

