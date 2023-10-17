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
	//SceneMain�̊֐����g�������̂Ń|�C���^��n���Ă���
	//this�Ŏ��g�̃|�C���^���擾�\
	m_pShot->SetMain(this);
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
			CreateEnemyLeft();

			break;
		case 1:		//Right
			CreateEnemyRight();

			break;

		default:	assert(false);		//break�Ȃ�
		case 2:		//ToPlayer
			CreateEnemyToPlayer();

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

	m_pShot->Draw();

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptr�ł͂Ȃ��`�F�b�N
		{
			m_pEnemy[i]->Draw();
		}
	}
 
	//Debag�\��
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	//�v���C���[�̈ʒu���f�o�b�O�\������
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"�v���C���[�̍��W(%.2f, %.2f)", playerPos.x, playerPos.y);
}

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) const
{
	//�G�����Ȃ��ꍇ�͓K���ȍ��W��Ԃ�
	Vec2 result{ 0,0 };
	//�ŏ��̓G�`�F�b�N�ς݃t���O
	bool isFirst = false;


	//��ԋ߂��G�L�����N�^�[�̍��W��result�ɓ����
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//�g���Ă��Ȃ��G�̓`�F�b�N���Ȃ�
		if (!m_pEnemy[i])	continue;

		//�����ɂ��Ă��鎞�_��m_pEnemy[i]��nullptr�łȂ����Ƃ͊m��

		//���łɏ����邱�Ƃ��m�肵�Ă���G�̓`�F�b�N���Ȃ�
		if (!m_pEnemy[i]->isExist()) continue;

		//pos ��m_pEnemy[i]�̋������`�F�b�N����

		if (isFirst)
		{
			//1�̖ڂ̓G
			//�����������痣��Ă��悤�Ƃ������_�ł͈�ԋ߂��G
			result = m_pEnemy[i]->GetPos();
			isFirst = false;
		}
		else
		{
			//2�̖ڈȍ~�̓G
			//result�̒��ɂ͈�ԋ߂��G�̍��W�������Ă���

			//���܂Ń`�F�b�N�������ň�ԋ߂��G�Ƃ̋���
			Vec2 toNear = result - pos;	//pos����b���ʂ̍��W�Ɍ������x�N�g��

			//�`�F�b�N����G�Ƃ̋���
			Vec2 toEnemy = m_pEnemy[i]->GetPos() - pos;	//pos����`�F�b�N���̓G�Ɍ������x�N�g��

			//�������y�����邽�ߋ�y���̔�r���s���ꍇ�͋�����2��Ŕ�r���s��
			if (toNear.sqLength() > toEnemy.sqLength())
			{
				//���`�F�b�N���Ă���G�ւ̋������b���ʂ����Z���ꍇ
				//���`�F�b�N���Ă���G���b���ʂ�
				result = m_pEnemy[i]->GetPos();
			}
			//�b���ʂ̕������`�F�b�N���Ă���G���߂��ꍇ�͉������Ȃ�
		}
	}
	//���ׂĂ̓G�̃`�F�b�N���s�����̂ł�������ʂŊm��
	return result;
}

void SceneMain::CreateEnemyLeft()
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

void SceneMain::CreateEnemyRight()
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

void SceneMain::CreateEnemyToPlayer()
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
