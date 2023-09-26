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

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	bool isExist() { return m_isExist; }

	Vec2 GetPos() { return m_pos; }
	Vec2 GetVec() { return m_vec; }

	//�G�L�����N�^�[���X�^�[�g������
	void Start();

private:
	int m_handle;   //�O���t�B�b�N�̃n���h��

	bool m_isExist; //���݂��邩�t���O(�g�p�����ǂ���)

	Player* m_pPlayer;

	Vec2 m_pos;
	Vec2 m_vec;
};

