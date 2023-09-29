#pragma once
#include "EnemyBase.h"
// 作成するクラス名 : public 継承元
//public以外にもprivate,protectedが使用できる
class EnemyLeft :	public EnemyBase
{
public:
	EnemyLeft();
	~EnemyLeft();

	void Start();
};

