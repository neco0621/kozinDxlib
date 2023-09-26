#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "EnemyRight.h"
#include "EnemyToPlayer.h"
#include "Bg.h"
#include <cassert>

SceneMain::SceneMain() :
	m_enemyFrameCount(0)
{
	//グラフィックのロード
	m_playerHandle = LoadGraph("data/player.png");
	assert(m_playerHandle != -1);
	m_enemyHandle = LoadGraph("data/enemy.png");
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

		m_pEnemyToPlayer[i] = new EnemyToPlayer;
		m_pEnemyToPlayer[i]->SetHandle(m_enemyHandle);
		m_pEnemyToPlayer[i]->SetPlayer(m_pPlayer);
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
		m_pEnemyToPlayer[i]->Init();
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
		m_pEnemyToPlayer[i]->Update();
	}
	m_pBg->Update();


	//敵キャラクターを登場制御
	m_enemyFrameCount++;
	if (m_enemyFrameCount >= 60)
	{
		m_enemyFrameCount = 0;

		for (int i = 0; i < kEnemyNum; i++)
		{
			/*if (!m_pEnemyRight[i]->isExist())
			{
				m_pEnemyRight[i]->Start();
				break;
			}*/
			if (!m_pEnemyToPlayer[i]->isExist())
			{
				m_pEnemyToPlayer[i]->Start();
				break;
			}
			
		}
	}

}

void SceneMain::Draw()
{
	m_pBg->Draw();
	m_pPlayer->Draw();
	for (int i = 0; i < kEnemyNum; i++)
	{
		m_pEnemyRight[i]->Draw();
		m_pEnemyToPlayer[i]->Draw();
	}
	////デバッグ表示
	//DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	////プレイヤーの座標をデバッグ表示する
	//Vec2 playerPos = m_pPlayer->GetPos();
	//DrawFormatString(8, 24, GetColor(255,255,255),
	//	"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);

	//for (int i = 0; i < kEnemyNum; i++)
	//{
	//	Vec2 enemyPos = m_pEnemyToPlayer[i]->GetPos();
	//	Vec2 enemyVec = m_pEnemyToPlayer[i]->GetVec();
	//	DrawFormatString(8, 40 + i*32, GetColor(255, 255, 255),
	//		"敵[%d]の座標(%.2f, %.2f)\n    ベクトル(%.2f, %.2f)", i, enemyPos.x, enemyPos.y, enemyVec.x, enemyVec.y);
	//}
}
