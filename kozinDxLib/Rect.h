#pragma once
#include "Vec2.h"
//矩形の座標を管理するクラス
class Rect
{
public:
	Rect();
	virtual ~Rect();

	//左上座標と幅高さを指定
	void Set(float left, float top, float width, float height);
	//ゲームによっては中心座標で指定したり足元の座標で指定する
	//set関数があったほうが便利かもしれない

	//必要な情報を取得する
	float GetWidth() const;		//幅
	float GetHeight() const;	//高さ
	Vec2 GetCenter() const;		//中心座標

	//矩形同士の当たり判定
	bool IsCollision(const Rect& rect);

private:
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;

};

