#include "EnemyLeft.h"
#include "game.h"

EnemyLeft::EnemyLeft() :
	EnemyBase()	//明示的に呼ぶ場合
{
	//基底クラスのコンストラクタを明示的に呼ばなくてもここで呼ばれる
}

EnemyLeft::~EnemyLeft()
{
	//デストラクタも呼ばれる	はず...
}

void EnemyLeft::Start()
{
	//画面中央に敵キャラクターを登場させる
	m_isExsit = true;
	m_pos.x = Game::kScreenWidth / 2;
	m_pos.y = Game::kScreenHeight / 2;
}
