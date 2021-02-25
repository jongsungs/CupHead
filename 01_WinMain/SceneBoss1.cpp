#include "pch.h"
#include "SceneBoss1.h"

#include "PlatformerPlayer.h"
#include "Camera.h"
#include "GameEvent.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Potato.h"
#include "Onion.h"
#include "Carrot.h"

void SceneBoss1::Init(){
	mBackGround1 = IMAGEMANAGER->FindImage(L"BotanicPanicBackground1");
	mBackGround2 = IMAGEMANAGER->FindImage(L"BotanicPanicBackground2");
	mBackGround3 = IMAGEMANAGER->FindImage(L"BotanicPanicBackground3");

	PlatformerPlayer* player = new PlatformerPlayer("Player", WINSIZEX / 4, WINSIZEY * 3 / 4);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player);

	Enemy* potato = new Potato("Potato", WINSIZEX * 3 / 4, WINSIZEY / 2);
	Enemy* carrot = new Carrot("Carrot", WINSIZEX / 2, WINSIZEY * 3 / 8 + 549);
	Enemy* onion = new Onion("Onion", WINSIZEX / 2, WINSIZEY * 3 / 8);

	ObjectManager::GetInstance()->AddObject(ObjectLayer::Boss, potato);
	potato->SetPlayerPtr(player);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Boss, carrot);
	carrot->SetPlayerPtr(player);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Boss, onion);
	onion->SetPlayerPtr(player);

	potato->SetIsActive(true);
	if (potato->GetIsActive() == false)
		onion->SetIsActive(true);
	if (potato->GetIsActive() == false && onion->GetIsActive() == false)
		carrot->SetIsActive(true);

	SoundPlayer::GetInstance()->Play(L"BotanicPanicBGM", 0.2f);

	Camera* camera = new Camera(Camera::Mode::Boss,WINSIZEX/2,WINSIZEY/2);
	camera->SetCamerArea(RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX + 10,WINSIZEY));
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, camera);
	ObjectManager::GetInstance()->Init();
}

void SceneBoss1::Release(){
	ObjectManager::GetInstance()->Release();
}

void SceneBoss1::Update(){
	ObjectManager::GetInstance()->Update();
}

void SceneBoss1::Render(HDC hdc){
	CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mBackGround1, -5, 0, WINSIZEX + 10, WINSIZEY);

	if (ObjectManager::GetInstance()->FindObject("Carrot")->GetIsActive()) {
		ObjectManager::GetInstance()->FindObject("Carrot")->Render(hdc);
	}

	CameraManager::GetInstance()->GetMainCamera()->ScaleRender(hdc, mBackGround2, -5, 0, WINSIZEX + 10, WINSIZEY);

	ObjectManager::GetInstance()->Render(hdc);

	mBackGround3->ScaleRender(hdc, -5, 0, WINSIZEX + 10, WINSIZEY);
}