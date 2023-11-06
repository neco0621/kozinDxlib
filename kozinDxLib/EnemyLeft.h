#pragma once
#include "EnemyBase.h"

//継承の仕方 (継承元クラスをincludeしておくこと)
//作成するクラス名 : public 継承元クラス名
//private,protectedがアクセス修飾子としてあるが基本public
class EnemyLeft : public EnemyBase
{
public:
	EnemyLeft();
	virtual ~EnemyLeft();

	//今のところ継承元をそのまま使うので不要
	//void Init();
	//void Draw();

	virtual void Update() override;

	virtual void Start() override;

private:
	//基準座標 真右方向に移動する基準座標
	//y成分にsinの値を足して上下に動けるようにする
	Vec2 m_basePos;
	//sin()に与える引数
	float m_sinRate;

};

