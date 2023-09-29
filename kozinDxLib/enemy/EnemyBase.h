#pragma once
#include "Vec2.h"
//すべての敵の基底クラス
// 継承元となるクラススを基底クラスと呼ぶ
//右から出現する敵のクラス
class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	void Init();
	void Update();
	void Draw();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	bool isExist() { return m_isExist; }

	//敵キャラクターをスタートさせる
	void Start();

//private:	//継承先からも参照できない
protected:	//継承先から参照できる
	int m_handle;   //グラフィックのハンドル

	bool m_isExist; //存在するかフラグ(使用中かどうか)

	Vec2 m_pos;
	Vec2 m_vec;
	
};

