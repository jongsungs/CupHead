#pragma once
#include "Block.h"
class TutorialCube : public Block
{
	class Image* mImage;
	float mCenterX;
public:
	TutorialCube(string name, float x, float y, float sizeX, float sizeY,  Image* image);
	virtual void Init() override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc) override;
};

