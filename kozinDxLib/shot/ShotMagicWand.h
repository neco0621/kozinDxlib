#pragma once
#include "ShotBase.h"
#include "vec2.h"

class ShotMagicWand :
	public ShotBase
{
public:
	ShotMagicWand();
	virtual ~ShotMagicWand();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	//�e���X�^�[�g������
	virtual void Start(Vec2 pos) override;
};

