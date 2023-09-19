#pragma once
//�E����o������G�̃N���X
class EnemyRight
{
public:
	EnemyRight();
	~EnemyRight();

	void Init();
	void Update();
	void Draw() const;

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	bool isExist() const { return m_isExist; }

	//�G�L�����N�^�[���X�^�[�g������
	void Start();

private:
	int m_handle;   //�O���t�B�b�N�̃n���h��

	bool m_isExist; //���݂��邩�t���O(�g�p�����ǂ���)

	float m_posX;
	float m_posY;
};

