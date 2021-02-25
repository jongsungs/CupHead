#pragma once
#include "GameObject.h"
#include "Enemy.h"

class Animation;

class Carrot : public Enemy {
	Image* mBeamImage;
	Image* mChangeToBeamImage;
	float mAttackStartDelay;
	int mAttackCount;

	Animation* mChangeToBeamAnimation;
	Animation* mChangeFromBeamAnimation;
	Animation* mBeamAnimation;

public:
	Carrot(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};