#pragma once
#include "EnemyBase.h"

//�p���̎d�� (�p�����N���X��include���Ă�������)
//�쐬����N���X�� : public �p�����N���X��
//private,protected���A�N�Z�X�C���q�Ƃ��Ă��邪��{public
class EnemyLeft : public EnemyBase
{
public:
	EnemyLeft();
	virtual ~EnemyLeft();

	//���̂Ƃ���p���������̂܂܎g���̂ŕs�v
	//void Init();
	//void Draw();

	virtual void Update() override;

	virtual void Start() override;
};

