#pragma once
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw() const;

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

public:
	//�����Ă����
	enum Dir
	{
		kDirDown,   //��
		kDirLeft,   //��
		kDirRight,   //�E
		kDirUp,     //��
	};

private:
	int m_handle;   //�O���t�B�b�N�̃n���h��

	float m_posX;
	float m_posY;
	//�����Ă������
	Dir m_dir;
	//�����A�j���[�V����
	int m_warkAnimFrame;
	int m_warkAnimCount;
};;

