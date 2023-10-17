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
	constexpr int kEnemyInterval = 60;

	//画面内に一度に出てくる弾の最大数
	constexpr int kShotMax = 256;
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
	m_pPlayer = new Player{ this };
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
	m_pShot.resize(kShotMax);
	for (int i = 0; i < m_pShot.size(); i++)
	{
		m_pShot[i] = nullptr;	//未使用
	}

	//m_pShot = new ShotMagicWand;
	////SceneMainの関数を使いたいのでポインタを渡しておく
	////thisで自身のポインタを取得可能
	//m_pShot->SetMain(this);
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
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			//nullptrではない場合
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}
}

void SceneMain::Init()
{
	assert(m_pPlayer);	//m_pPlayer == nullptr の場合止まる

	m_pPlayer->Init();

	m_pBg->Init();
}

void SceneMain::End()
{

}

void SceneMain::Update()
{
	m_pPlayer->Update();

	m_pBg->Update();

	for (int i = 0; i < m_pShot.size(); i++)
	{
		//nullptrなら処理は行わない
		if (!m_pShot[i])		continue;

		m_pShot[i]->Update();
		//画面外に出たらメモリ解放
		if (!m_pShot[i]->isExist())
		{
			delete m_pShot[i];
			m_pShot[i] = nullptr;
		}
	}


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
			CreateEnemyLeft();

			break;
		case 1:		//Right
			CreateEnemyRight();

			break;

		default:	assert(false);		//breakなし
		case 2:		//ToPlayer
			CreateEnemyToPlayer();

			break;
		}
	}
}

void SceneMain::Draw()
{
	m_pBg->Draw();

	m_pPlayer->Draw();

	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (!m_pShot[i])		continue;
		m_pShot[i]->Draw();
	}

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (m_pEnemy[i])	//nullptrではないチェック
		{
			m_pEnemy[i]->Draw();
		}
	}
 
	//Debag表示
	DrawString(8, 8, "SceneMain", GetColor(255, 255, 255));

	//プレイヤーの位置をデバッグ表示する
	Vec2 playerPos = m_pPlayer->GetPos();
	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"プレイヤーの座標(%.2f, %.2f)", playerPos.x, playerPos.y);
}

Vec2 SceneMain::GetNearEnemyPos(Vec2 pos) const
{
	//敵がいない場合は適当な座標を返す
	Vec2 result{ 0,0 };
	//最初の敵チェック済みフラグ
	bool isFirst = false;


	//一番近い敵キャラクターの座標をresultに入れる
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		//使われていない敵はチェックしない
		if (!m_pEnemy[i])	continue;

		//ここにきている時点でm_pEnemy[i]はnullptrでないことは確定

		//すでに消えることが確定している敵はチェックしない
		if (!m_pEnemy[i]->isExist()) continue;

		//pos とm_pEnemy[i]の距離をチェックする

		if (isFirst)
		{
			//1体目の敵
			//距離がいくら離れていようとも現時点では一番近い敵
			result = m_pEnemy[i]->GetPos();
			isFirst = false;
		}
		else
		{
			//2体目以降の敵
			//resultの中には一番近い敵の座標が入ってくる

			//今までチェックした中で一番近い敵との距離
			Vec2 toNear = result - pos;	//posから暫定一位の座標に向かうベクトル

			//チェックする敵との距離
			Vec2 toEnemy = m_pEnemy[i]->GetPos() - pos;	//posからチェック中の敵に向かうベクトル

			//処理を軽くするため居y理の比較を行う場合は距離の2乗で比較を行う
			if (toNear.sqLength() > toEnemy.sqLength())
			{
				//今チェックしている敵への距離が暫定一位よりも短い場合
				//今チェックしている敵を暫定一位に
				result = m_pEnemy[i]->GetPos();
			}
			//暫定一位の方が今チェックしている敵より近い場合は何もしない
		}
	}
	//すべての敵のチェックを行ったのでこいつが一位で確定
	return result;
}

bool SceneMain::AddShot(ShotBase* pShot)
{
	for (int i = 0; i < m_pShot.size(); i++)
	{
		//使用中なら次のチェックへ
		if (m_pShot[i])	continue;

		//ここに来たということはm_pShot[i] == nullptr
		m_pShot[i] = pShot;
		//登録したら終了
		return true;
	}

	//ここに来た、ということはm_pShotにポインタを登録できなかった
	delete pShot;
	return false;
}

void SceneMain::CreateEnemyLeft()
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

void SceneMain::CreateEnemyRight()
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

void SceneMain::CreateEnemyToPlayer()
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
