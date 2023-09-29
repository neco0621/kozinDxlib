#pragma once
#include "Vec2.h"
//���ׂĂ̓G�̊��N���X
// �p�����ƂȂ�N���X�X�����N���X�ƌĂ�
//�E����o������G�̃N���X
class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	bool isExist() { return m_isExist; }

	//�G�L�����N�^�[���X�^�[�g������
	void Start();

//private:	//�p���悩����Q�Ƃł��Ȃ�
protected:	//�p���悩��Q�Ƃł���
	int m_handle;   //�O���t�B�b�N�̃n���h��

	bool m_isExist; //���݂��邩�t���O(�g�p�����ǂ���)

	Vec2 m_pos;
	Vec2 m_vec;
	
};

