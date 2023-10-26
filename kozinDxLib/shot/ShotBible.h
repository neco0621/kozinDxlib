#pragma once
#include "ShotBase.h"
class ShotBible :
    public ShotBase
{
public:
    ShotBible();
    virtual ~ShotBible();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	//弾をスタートさせる
	virtual void Start(Vec2 pos) override;

private:

	//一定時間経過したら消すために生成してからのフレームを数える
	int m_frameCount;
};

