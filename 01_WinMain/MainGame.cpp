﻿#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "Scene2.h"
#include "Scene1.h"
#include "SceneBoss1.h"
#include "SceneBoss2.h"
#include "LoadingScene.h"
#include "Scene_OverWorld.h"
#include "Animation.h"
#include "Scene_Start1.h"
#include "Scene_Start2.h"
#include "Scene_ElderHouse.h"
#include "Scene_Shop.h"
#include "SceneTutorial.h"
/*
Scene : 스테이지 단위를 씬이라고 함
*/

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*///
void MainGame::Init()
{
	ImageSet::GetInstance()->SetFxImage();
	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	SceneManager::GetInstance()->AddScene(L"Tutorial", new SceneTutorial);
	SceneManager::GetInstance()->AddScene(L"BotanicPanic", new SceneBoss1);
	SceneManager::GetInstance()->AddScene(L"FloralFury", new SceneBoss2);
	SceneManager::GetInstance()->AddScene(L"OverWorld", new Scene_OverWorld);
	SceneManager::GetInstance()->AddScene(L"Scene_Start2", new Scene_Start2);
	SceneManager::GetInstance()->AddScene(L"Scene_Start1", new Scene_Start1);
	SceneManager::GetInstance()->AddScene(L"ElderHouse", new Scene_ElderHouse);
	SceneManager::GetInstance()->AddScene(L"Shop", new Scene_Shop);
	//ThreadManager::GetInstance()->SetFunts([]()->void {ImageSet::GetInstance()->SetImage(); });
	LoadingScene* mLoading = new LoadingScene;
	mLoading->AddLoadFunc([]()->void {ImageSet::GetInstance()->SetImage(); });
	mLoading->AddLoadFunc([]()->void {ImageSet::GetInstance()->SetOverWorldImage(); });
	mLoading->AddLoadFunc([]()->void {SoundSet::GetInstance()->SetSound(); });

	SceneManager::GetInstance()->AddScene(L"Start1LoadingScene", mLoading);
	SceneManager::GetInstance()->AddScene(L"OverWorldLoadingScene", mLoading);

	SceneManager::GetInstance()->LoadSceneLoading(L"Scene_Start1", L"Start1LoadingScene");

	//SceneManager::GetInstance()->LoadScene(L"Shop");
	//ThreadManager::GetInstance()->LoadStartFunts();
	IntersectManager::GetInstance()->SetObjectPt();
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);

}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	ThreadManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
	IntersectManager::GetInstance()->IntersectPlayerAndFloor();
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		SceneManager::GetInstance()->Render(backDC);
		RenderTime(backDC);
		RenderFilter(backDC);
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}

void MainGame::RenderTime(HDC hdc)
{
	//float worldTime = Time::GetInstance()->GetWorldTime();
	//float deltaTime = Time::GetInstance()->DeltaTime();
	ULONG fps = Time::GetInstance()->GetmFrameRate();
	//wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	//wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	//wstring strFPS = L"FPS : " + to_wstring(fps);

	//TextOut(hdc, 10, 10, strWorldTime.c_str(), strWorldTime.length());
	//TextOut(hdc, 10, 25, strDeltaTime.c_str(), strDeltaTime.length());
	//TextOut(hdc, 10, 40, strFPS.c_str(), strFPS.length());
}
void MainGame::RenderFilter(HDC hdc)
{
	mFilter = ImageManager::GetInstance()->FindImage(L"FX_" + to_wstring((int)mFilterNumber));
	mFilter->AlphaScaleRender(hdc , 0 , 0,WINSIZEX,WINSIZEY,0.25f);
	mFilterNumber += Time::GetInstance()->DeltaTime() * 10;
	if (mFilterNumber > 126) {
		mFilterNumber = 0;
	}
}
