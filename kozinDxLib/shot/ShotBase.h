#pragma once
#include "Vec2.h"
#include "Rect.h"

//プレイヤーの攻撃の基底クラス
class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool isExist() const { return m_isExist; }

	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

	//弾をスタートさせる
	//発射位置を引数として指定する
	virtual void Start(Vec2 pos) = 0;

protected:
	bool m_isExist;	//存在するかフラグ(使用中かどうか)

	//表示位置
	Vec2 m_pos;

	//当たり判定の矩形
	Rect m_colRect;

	//移動量	1フレーム当たりの移動ベクトルを入れる
	Vec2 m_vec;
};