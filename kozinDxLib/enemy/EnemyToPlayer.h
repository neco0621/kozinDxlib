#pragma once
#include "EnemyBase.h"

class Player;
//�����ʒu���甭���������̃v���C���[�̈ʒu�Ɍ������Ĉړ�����
class EnemyToPlayer : public EnemyBase
{
public:
	EnemyToPlayer();
	virtual ~EnemyToPlayer();

	virtual void Update() override;

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	//�G�L�����N�^�[���X�^�[�g������
	virtual void Start() override;

private:
	Player* m_pPlayer;
};