#include "pch.h"

#include"Image.h"
#include"Animation.h"
#include "OnionProj.h"
#include "Camera.h"

void OnionProj::Init(){
	vector<GameObject*>* EnemyProj = ObjectManager::GetInstance()->GetObjectListPt(ObjectLayer::Enemy_Bullet);
	mName = to_string(EnemyProj->size());
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy_Bullet, this);

	NonParryAbleAImg = IMAGEMANAGER->FindImage(L"OnionNonParryAbleA");
	NonParryAbleBImg = IMAGEMANAGER->FindImage(L"OnionNonParryAbleB");
	NonParryAbleCImg = IMAGEMANAGER->FindImage(L"OnionNonParryAbleC");
	NonParryAbleDImg = IMAGEMANAGER->FindImage(L"OnionNonParryAbleD");
	NonParryAbleEImg = IMAGEMANAGER->FindImage(L"OnionNonParryAbleE");
	ParryAbleImg = IMAGEMANAGER->FindImage(L"OnionParryable");

	NonParryableASplashImg = IMAGEMANAGER->FindImage(L"OnionNonParryAbleASplash");

	NonParryAbleAAnimation = new Animation();
	NonParryAbleAAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	NonParryAbleAAnimation->SetIsLoop(true);
	NonParryAbleAAnimation->SetFrameUpdateTime(0.1f);

	NonParryAbleBAnimation = new Animation();
	NonParryAbleBAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	NonParryAbleBAnimation->SetIsLoop(true);
	NonParryAbleBAnimation->SetFrameUpdateTime(0.1f);

	NonParryAbleCAnimation = new Animation();
	NonParryAbleCAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	NonParryAbleCAnimation->SetIsLoop(true);
	NonParryAbleCAnimation->SetFrameUpdateTime(0.1f);

	NonParryAbleDAnimation = new Animation();
	NonParryAbleDAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	NonParryAbleDAnimation->SetIsLoop(true);
	NonParryAbleDAnimation->SetFrameUpdateTime(0.1f);

	NonParryAbleEAnimation = new Animation();
	NonParryAbleEAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	NonParryAbleEAnimation->SetIsLoop(true);
	NonParryAbleEAnimation->SetFrameUpdateTime(0.1f);

	ParryAbleAnimation = new Animation();
	ParryAbleAnimation->InitFrameByStartEnd(0, 0, 2, 0, false);
	ParryAbleAnimation->SetIsLoop(true);
	ParryAbleAnimation->SetFrameUpdateTime(0.1f);

	NonParryableASplashAnimation = new Animation();
	NonParryableASplashAnimation->InitFrameByStartEnd(0, 0, 6, 0, false);
	NonParryableASplashAnimation->SetIsLoop(false);
	NonParryableASplashAnimation->SetFrameUpdateTime(0.1f);
}

void OnionProj::Release(){
	SafeDelete(NonParryAbleAAnimation);
	SafeDelete(NonParryAbleBAnimation);
	SafeDelete(NonParryAbleCAnimation);
	SafeDelete(NonParryAbleDAnimation);
	SafeDelete(NonParryAbleEAnimation);
	SafeDelete(ParryAbleAnimation);
	SafeDelete(NonParryableASplashAnimation);
}

void OnionProj::Update(){
	if (mParryAble == true) {
		mImage = ParryAbleImg;
		mCurrentAnimation = ParryAbleAnimation;
		mCurrentAnimation->Play();
	}

	else {
		mImage = NonParryAbleAImg;
		mCurrentAnimation = NonParryAbleAAnimation;
		mCurrentAnimation->Play();
	}
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mX += cosf(mAngle) * mSpeed;
	mY += -sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCurrentAnimation->Update();
}

void OnionProj::Render(HDC hdc){
	RenderRect(hdc, mRect);

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
}