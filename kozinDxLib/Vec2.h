#pragma once
#include <cmath>

//�x�N�g����֗��Ɏg�����߂̃N���X
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

	//�����Z
	Vec2 plus(Vec2 vec)
	{
		Vec2 result{ x + vec.x, y + vec.y };
		return result;
	}
	//�|���Z
	Vec2 mul(float scale)
	{
		Vec2 result{ x * scale, y * scale };
		return result;
	}

	//�x�N�g���̒�����2������߂�
	float sqLength()
	{
		return x * x + y * y;
	}
	//�x�N�g���̒��������߂�
	float length()
	{
		return sqrtf(sqLength());
	}

	//���g�̐��K�����s��
	void normalize()
	{
		float len = length();
		if (len > 0.0f)
		{
			x /= len;
			y /= len;
		}
		//����0�̏ꍇ�͉������Ȃ�
	}

};

