#include "SceneMain.h"
#include "DxLib.h"
#include "Player.h"
#include "Bg.h"
#include "Pad.h"
#include "Rect.h"

//登場する敵
//#include "EnemyBase.h"
#include "EnemyLeft.h"
#include "EnemyRight.h"
#include "EnemyToPlayer.h"

//登場するショット
#include "Shot/ShotMagicWand.h"

#include <cassert>

namespace
{
	//一度に登場できる最大の数
	constexpr int kEnemyMax = 64;
	//何フレーム沖に敵が登場するか
	constexpr int kEnemyInterval = 20;
}

SceneMain::SceneMain() :
	m_enemyInterval(0)
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
	m_pPlayer->SetHandle(m_playerHandle);	//Playerにグラフィックハンドルを渡す

	//背景のメモリ確保
	m_pBg = new Bg;
	m_pBg->SetHandle(m_bgHandle);

	//敵の準備
	//m_pEnemy(vector)何もしなければサイズは0
	//resize関数でkEnemyMaxだけデータを保存できるようにする
	m_pEnemy.resize(kEnemyMax);

	//いつもはコンストラクタでメモリを確保して
	//デストラクタで解放してた
	//ランダムにEnemyLeft,EnemyRight,EnemyToPlayerを確保したい
	//どれかわからないのであらかじめ確保することができない
	//→動的にメモリを確保する　Update()中に必要に応じて

	//初期状態ではメモリを確保していないことがわかるようにしておく
	//未使用状態にする　nullptrを入れておく
	//size()で現在使用可能な要素数を取得可能
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		m_pEnemy[i] = nullptr;

		//m_pEnemyのなかにはLeft,Right,ToPlayerのどれかが入る
		//現時点ではどれが入るのか決定できない
	}

	//ショットの準備
	m_pShot = new ShotMagicWand;
}

SceneMain::~SceneMain()
{
	//メモリからグラフィックを削除
	DeleteGraph(m_playerHandle);
	DeleteGraph(m_enemyHandle);

	//プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	//背景のメモリ解放
	delete m_pBg;
	m_pBg = nullptr;

	//メモリが確保されている敵を探して解放していく
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//nullptr以外のものが入っているということはそこにはポインタが入っている
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
	assert(m_pPlayer);	//m_pPlayer == nullptr の場合止まる

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
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!m_pEnemy[i]->isExist())
			{
				//メモリを解放する
				delete m_pEnemy[i];
				m_pEnemy[i] = nullptr;	//使っていないとわかるように
			}
			else
			{
				//存在している敵とプレイヤーの当たり判定
				Rect enemyRect = m_pEnemy[i]->GetColRect();
				if (playerRect.IsCollision(enemyRect))
				{
					//test
					//printfDx("当たっている\n");

					m_pPlayer->OnDamage();
				}

			}
		}
	}


	//敵キャラクターを登場させる
	//kEnemyIntervalフレーム経過するごとにランダムに敵を登場させる
	m_enemyInterval++;
	if (m_enemyInterval >= kEnemyInterval)
	{
		m_enemyInterval = 0;

		//ランダムに敵を選択
		switch (GetRand(2))		//0 or 1 or 2
		{
		case 0:		//Left
			createEnemyLeft();

			break;
		case 1:		//Right
			createEnemyRight();

			break;

		default:	assert(false);		//breakなし
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
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Draw();
		}
	}
	m_pShot->Draw();


	//Debag表示
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	//プレイヤーの位置をデバッグ表示する
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
}

void SceneMain::createEnemyLeft()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyLeft;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//メモリを確保したら以降はチェックしない
		}
	}
}

void SceneMain::createEnemyRight()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			m_pEnemy[i] = new EnemyRight;
			m_pEnemy[i]->Init();
			m_pEnemy[i]->SetHandle(m_enemyHandle);
			m_pEnemy[i]->Start();
			return;	//メモリを確保したら以降はチェックしない
		}
	}
}

void SceneMain::createEnemyToPlayer()
{
	//使われていない箱を探してそこにアドレスを保存する
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])	//nullptrであることをチェックする
		{
			//Baseが持たない独自の関数を呼びたい
			EnemyToPlayer* pEnemy = new EnemyToPlayer;

			pEnemy->Init();
			pEnemy->SetHandle(m_enemyHandle);
			pEnemy->SetPlayer(m_pPlayer);	//pPlayerはEnemyToPlayerなので呼べる
			pEnemy->Start();

			//pEnemyはすぐ消えるためm_pEnemyに確保したアドレスをコピーしておく
			m_pEnemy[i] = pEnemy;



			return;	//メモリを確保したら以降はチェックしない
		}
	}

}
