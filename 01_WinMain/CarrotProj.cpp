#include "pch.h"

#include"Image.h"
#include "CarrotProj.h"
#include "Animation.h"
#include "Camera.h"

CarrotProj::CarrotProj(const string & name, float x, float y, float speed, float angle, int weapontype)
	: EnemyProj(name, x, y, speed, angle, false)
{
	mX = x;
	mY = y;
	mSpeed = speed;
	mAngle = angle;
	mParryAble = false;
	mWeaponType = weapontype;
	mHP = 1;
}

void CarrotProj::Init(){
	CarrotMissileImage = IMAGEMANAGER->FindImage(L"CarrotMissile");
	CarrotBeamImage = IMAGEMANAGER->FindImage(L"CarrotBeamProj");

	vector<GameObject*>* EnemyProj = ObjectManager::GetInstance()->GetObjectListPt(ObjectLayer::Enemy_Bullet);
	mName = to_string(EnemyProj->size());

	CarrotMissileAnimation = new Animation();
	CarrotMissileAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	CarrotMissileAnimation->SetIsLoop(true);
	CarrotMissileAnimation->SetFrameUpdateTime(0.07f);
	
	CarrotBeamAnimation = new Animation();
	CarrotBeamAnimation->InitFrameByStartEnd(0, 0, 5, 0, false);
	CarrotBeamAnimation->SetIsLoop(false);
	CarrotBeamAnimation->SetFrameUpdateTime(0.15f);
}

void CarrotProj::Release(){
	SafeDelete(CarrotMissileAnimation);
	SafeDelete(CarrotBeamAnimation);
}

void CarrotProj::Update(){
	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	
	switch (mWeaponType) {
	case 1:
		mImage = CarrotMissileImage;
		mCurrentAnimation = CarrotMissileAnimation;
		mCurrentAnimation->Play();
		break;
	case 2:
		mImage = CarrotBeamImage;
		mCurrentAnimation = CarrotBeamAnimation;
		mCurrentAnimation->Play();
		break;
	}

	if (mWeaponType == 1 && mHP <= 0) {
		mIsActive = false;
		mIsDestroy = true;
	}

	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCurrentAnimation->Update();
}

void CarrotProj::Render(HDC hdc){
	//CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
		
	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}

void CarrotProj::InIntersectDamage(int dmage) {
	mHP -= 1;
	mIsActive = false;
	mIsDestroy = true;
}