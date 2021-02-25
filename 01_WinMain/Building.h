#pragma once
#include "GameObject.h"
class Building :public GameObject
{
	Image* mImage;
	//�ǹ������� zŰ������� ��ǳ���߰���.
	Image* mZImage;
	int mZImageSizeX;
	int mZImageSizeY;
	bool mIsClear;
	bool mIsTalk;

public :
	Building(const string& name, Image* image,float x, float y);
	
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetIsClear(bool b) { mIsClear = b; };
};
