#include "Rect.h"
#include <cassert>

Rect::Rect() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f)
{

}

Rect::~Rect()
{
}

void Rect::Set(float left, float top, float width, float height)
{
	m_left = left;			//�����X���W
	m_top = top;			//�����Y���W
	m_right = left + width;	//�E����X���W
	m_bottom = top + height;//�E����Y���W
}

float Rect::GetWidth() const
{
	assert(m_right >= m_left);	//���E�̍��W�̓���ւ��`�F�b�N

	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_bottom >= m_top);	//�㉺�̍��W�̓���ւ��`�F�b�N

	return m_bottom - m_top;
}

Vec2 Rect::GetCenter() const
{
	//���S���W
	float x = 0.0f;
	float y = 0.0f;

	x = (m_right + m_left) / 2;
	y = (m_top + m_bottom) / 2;

	return Vec2{ x,y };
}

bool Rect::IsCollision(const Rect& rect)
{
	//��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > rect.m_right)	return false;
	if (m_top > rect.m_bottom)	return false;
	if (m_right < rect.m_left)	return false;
	if (m_bottom < rect.m_top)	return false;

	//������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}
