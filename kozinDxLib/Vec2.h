#pragma once
#include <cmath>

//ベクトルを便利に使うためのクラス
class Vec2
{

public:
	float x;
	float y;

public:
	Vec2() :
		x(0.0f),
		y(0.0f)
	{
	}

	Vec2(float posX, float posY) :
		x(posX),
		y(posY)
	{
	}

	//足し算
	Vec2 plus(Vec2 vec)
	{
		Vec2 result{ x + vec.x, y + vec.y };
		return result;
	}
	//掛け算
	Vec2 mul(float scale)
	{
		Vec2 result{ x * scale, y * scale };
		return result;
	}

	//ベクトルの長さの2乗を求める
	float sqLength()
	{
		return x * x + y * y;
	}
	//ベクトルの長さを求める
	float length()
	{
		return sqrtf(sqLength());
	}

	//自身の正規化を行う
	void normalize()
	{
		float len = length();
		if (len > 0.0f)
		{
			x /= len;
			y /= len;
		}
		//長さ0の場合は何もしない
	}

};

