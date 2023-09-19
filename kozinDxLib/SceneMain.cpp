#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "EnemyRight.h"
#include "Bg.h"
#include <cassert>

SceneMain::SceneMain() :
	m_enemyFrameCount(0)
{
	//グラフィックのロード
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/ゲームキャラ２.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/bg.png");
	assert(m_bgHandle != -1);
	//プレイヤーのメモリ確保
	m_pPlayer = new Player;
	m_pPlayer->SetHandle(m_playerHandle);   //Playerにグラフィックのハンドルを渡す

	//敵のメモリ確保
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemyRight[i] = new EnemyRight;
		m_pEnemyRight[i]->SetHandle(m_enemyHandle);
	}

	//背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);
}

SceneMain::~SceneMain()
{
	//メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);
	//メモリの解放
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
	assert(m_pPlayer);   // m_pPlayer == nullptrの場合止まる

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


	//敵キャラクターを登場制御
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
	//デバッグ表示
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));
}
