#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "EnemyRight.h"
#include "Bg.h"
#include <cassert>

SceneMain::SceneMain() :
	m_enemyFrameCount(0)
{
	//�O���t�B�b�N�̃��[�h
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/�Q�[���L�����Q.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/bg.png");
	assert(m_bgHandle != -1);
	//�v���C���[�̃������m��
	m_pPlayer = new Player;
	m_pPlayer->SetHandle(m_playerHandle);   //Player�ɃO���t�B�b�N�̃n���h����n��

	//�G�̃������m��
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemyRight[i] = new EnemyRight;
		m_pEnemyRight[i]->SetHandle(m_enemyHandle);
	}

	//�w�i�̃������m��
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
}

SceneMain::~SceneMain()
{
	//����������O���t�B�b�N���폜
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	//�������̉��
	delete m_pPlayer;
	m_pPlayer = nullptr;

	for (int i = 0; i < kEnemyNum; i++)
	{
		delete m_pEnemyRight[i];
		m_pEnemyRight[i] = nullptr;
	}
	delete m_pBg;
}

void SceneMain::Init()
{
	assert(m_pPlayer);   // m_pPlayer == nullptr�̏ꍇ�~�܂�

	m_pPlayer->Init();
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemyRight[i]->Init();
	}
	m_enemyFrameCount = 0;

	m_pBg->Init();
}

void SceneMain::End()
{

}

void SceneMain::Update()
{
	m_pPlayer->Update();
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemyRight[i]->Update();
	}
	m_pBg->Update();


	//�G�L�����N�^�[��o�ꐧ��
	m_enemyFrameCount++;
	if (m_enemyFrameCount >= 60)
	{
		m_enemyFrameCount = 0;

		for (int i = 0; i < kEnemyNum; i++)
		{
			if (!m_pEnemyRight[i]->isExist())
			{
				m_pEnemyRight[i]->Start();
				break;
			}
		}
	}

}

void SceneMain::Draw() const
{
	m_pBg->Draw();

	m_pPlayer->Draw();
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemyRight[i]->Draw();
	}
	//�f�o�b�O�\��
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));
}
