#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "Bg.h"
#include "Pad.h"
#include "Rect.h"

//�o�ꂷ��G
//#include "EnemyBase.h"
#include "EnemyLeft.h"
#include "EnemyRight.h"
#include "EnemyToPlayer.h"

//�o�ꂷ��V���b�g
#include "Shot/ShotMagicWand.h"

#include <cassert>

namespace
{
	//��x�ɓo��ł���ő�̐�
	constexpr int kEnemyMax = 64;
	//���t���[�����ɓG���o�ꂷ�邩
	constexpr int kEnemyInterval = 20;
}

SceneMain::SceneMain() :
	m_enemyInterval(0)
{
	//�O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/bg.png");
	assert(m_bgHandle != -1);

	//�v���C���[�̃������m��
	m_pPlayer = new Player;
	m_pPlayer->SetHandle(m_playerHandle);	//Player�ɃO���t�B�b�N�n���h����n��

	//�w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);

	//�G�̏���
	//m_pEnemy(vector)�������Ȃ���΃T�C�Y��0
	//resize�֐���kEnemyMax�����f�[�^��ۑ��ł���悤�ɂ���
	m_pEnemy.resize(kEnemyMax);

	//�����̓R���X�g���N�^�Ń��������m�ۂ���
	//�f�X�g���N�^�ŉ�����Ă�
	//�����_����EnemyLeft,EnemyRight,EnemyToPlayer���m�ۂ�����
	//�ǂꂩ�킩��Ȃ��̂ł��炩���ߊm�ۂ��邱�Ƃ��ł��Ȃ�
	//�����I�Ƀ��������m�ۂ���@Update()���ɕK�v�ɉ�����

	//������Ԃł̓��������m�ۂ��Ă��Ȃ����Ƃ��킩��悤�ɂ��Ă���
	//���g�p��Ԃɂ���@nullptr�����Ă���
	//size()�Ō��ݎg�p�\�ȗv�f�����擾�\
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;

		//m_pEnemy�̂Ȃ��ɂ�Left,Right,ToPlayer�̂ǂꂩ������
		//�����_�ł͂ǂꂪ����̂�����ł��Ȃ�
	}

	//�V���b�g�̏���
	m_pShot = new ShotMagicWand;
}

SceneMain::~SceneMain()
{
	//����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);

	//�v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;

	//�w�i�̃��������
	delete m_pBg;
	m_pBg = nullptr;

	//���������m�ۂ���Ă���G��T���ĉ�����Ă���
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//nullptr�ȊO�̂��̂������Ă���Ƃ������Ƃ͂����ɂ̓|�C���^�������Ă���
		if (m_pEnemy[i] != nullptr)
		{
			delete m_pEnemy[i];
			m_pEnemy[i] = nullptr;
		}
	}

	delete m_pShot;
	m_pShot = nullptr;
}

void SceneMain::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr �̏ꍇ�~�܂�

	m_pPlayer->Init();

	m_pBg->Init();

	m_pShot->Init();


}

void SceneMain::End()
{

}

void SceneMain::Update()
{
	m_pPlayer->Update();

	m_pBg->Update();

	m_pShot->Update();


	Rect playerRect = m_pPlayer->GetColRect();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Update();

			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!m_pEnemy[i]->isExist())
			{
				//���������������
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
			}
			else
			{
				//���݂��Ă���G�ƃv���C���[�̓����蔻��
				Rect enemyRect = m_pEnemy[i]->GetColRect();
				if (playerRect.IsCollision(enemyRect))
				{
					//test
					//printfDx("�������Ă���\n");

					m_pPlayer->OnDamage();
				}

			}
		}
	}


	//�G�L�����N�^�[��o�ꂳ����
	//kEnemyInterval�t���[���o�߂��邲�ƂɃ����_���ɓG��o�ꂳ����
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		//�����_���ɓG��I��
		switch (GetRand(2))		//0 or 1 or 2
		{
		case 0:		//Left
			createEnemyLeft();

			break;
		case 1:		//Right
			createEnemyRight();

			break;

		default:	assert(false);		//break�Ȃ�
		case 2:		//ToPlayer
			createEnemyToPlayer();

			break;
		}
	}

	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_pShot->Start(m_pPlayer->GetPos());
	}

}

void SceneMain::Draw()
{
	m_pBg->Draw();

	m_pPlayer->Draw();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Draw();
		}
	}
	m_pShot->Draw();


	//Debag�\��
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	//�v���C���[�̈ʒu���f�o�b�O�\������
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"�v���C���[�̍��W(%.2f, %.2f)", playerPos.x, playerPos.y);
}

void SceneMain::createEnemyLeft()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}

void SceneMain::createEnemyRight()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}
}

void SceneMain::createEnemyToPlayer()
{
	//�g���Ă��Ȃ�����T���Ă����ɃA�h���X��ۑ�����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptr�ł��邱�Ƃ��`�F�b�N����
		{
			//Base�������Ȃ��Ǝ��̊֐����Ăт���
			EnemyToPlayer* pEnemy = new EnemyToPlayer;

			pEnemy->Init();
			pEnemy->SetHandle(m_enemyHandle);
			pEnemy->SetPlayer(m_pPlayer);	//pPlayer��EnemyToPlayer�Ȃ̂ŌĂׂ�
			pEnemy->Start();

			//pEnemy�͂��������邽��m_pEnemy�Ɋm�ۂ����A�h���X���R�s�[���Ă���
			m_pEnemy[i] = pEnemy;



			return;	//���������m�ۂ�����ȍ~�̓`�F�b�N���Ȃ�
		}
	}

}
