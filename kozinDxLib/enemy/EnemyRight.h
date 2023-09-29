#pragma once
#include "Vec2.h"
//�E����o������G�̃N���X
class EnemyRight
{
public:
	EnemyRight();
	~EnemyRight();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	bool isExist() { return m_isExist; }

	//�G�L�����N�^�[���X�^�[�g������
	void Start();

private:
	int m_handle;   //�O���t�B�b�N�̃n���h��

	bool m_isExist; //���݂��邩�t���O(�g�p�����ǂ���)

	Vec2 m_pos;
	Vec2 m_vec;
	
};

