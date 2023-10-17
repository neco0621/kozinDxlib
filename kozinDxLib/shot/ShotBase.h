#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;

//�v���C���[�̍U���̊��N���X
class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetMain(SceneMain* pMain) { m_pMain = pMain; }

	bool isExist() const { return m_isExist; }

	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

	//�e���X�^�[�g������
	//���ˈʒu�������Ƃ��Ďw�肷��
	virtual void Start(Vec2 pos) = 0;

protected:
	//SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	SceneMain* m_pMain;

	bool m_isExist;	//���݂��邩�t���O(�g�p�����ǂ���)

	//�\���ʒu
	Vec2 m_pos;

	//�����蔻��̋�`
	Rect m_colRect;

	//�ړ���	1�t���[��������̈ړ��x�N�g��������
	Vec2 m_vec;
};