#include "EnemyLeft.h"
#include "game.h"

EnemyLeft::EnemyLeft() :
	EnemyBase()	//�����I�ɌĂԏꍇ
{
	//���N���X�̃R���X�g���N�^�𖾎��I�ɌĂ΂Ȃ��Ă������ŌĂ΂��
}

EnemyLeft::~EnemyLeft()
{
	//�f�X�g���N�^���Ă΂��	�͂�...
}

void EnemyLeft::Start()
{
	//��ʒ����ɓG�L�����N�^�[��o�ꂳ����
	m_isExsit = true;
	m_pos.x = Game::kScreenWidth / 2;
	m_pos.y = Game::kScreenHeight / 2;
}
