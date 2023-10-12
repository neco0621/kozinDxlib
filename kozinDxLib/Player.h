#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player
{
public:
	//�����Ă������
	enum Dir
	{
		kDirDown,	//��	= 0
		kDirLeft,	//��	= 1
		kDirRight,	//�E	= 2
		kDirUp,		//��	= 3
	};

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	//�v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	//�v���C���[���_���[�W���󂯂�
	void OnDamage();

private:
	int m_handle;	//�O���t�B�b�N�̃n���h��

	//�\���ʒu
	Vec2 m_pos;

	//�����蔻��p�̋�`
	Rect m_colRect;

	//�����Ă������
	Dir m_dir;

	//�����A�j���[�V����
	int m_walkAnimFrame;

	//�_���[�W���󂯂Ă���̃t���[����
	//�����������Ƀt���[������ݒ肵��
	//���t���[�����炵�Ă���
	int m_damageFrame;
};
