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

	//����̍��W�����ԋ߂��ɂ���G�̍��W��Ԃ��֐�
	Vec2 GetNearEnemyPos(Vec2 pos) const;

private:
	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();
	void CreateEnemyToPlayer();

private:
	//�O���t�B�b�N�̃n���h��
	int m_playerHandle;
	int m_enemyHandle;
	int m_bgHandle;

	//�v���C���[
	Player* m_pPlayer;

	//�w�i
	Bg* m_pBg;

	//�G
	std::vector<EnemyBase*> m_pEnemy;	//�z��̃T�C�Y�͎��s���Ɍ��߂�(����̓R���X�g���N�^)
	//EnemyBase* m_pEnemy[16];   <-���܂ł̏�����

	//�V���b�g
	ShotBase* m_pShot;


	//�G�̓o��Ԋu
	int m_enemyInterval;
};