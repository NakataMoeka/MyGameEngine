#include "NMGame.h"

void NMGame::Initialize()
{
	Framework::Initialize();

	//ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxcommon, audio);

}

void NMGame::Update()
{
	Framework::Update();
	//ゲームシーンの毎フレーム処理
	gameScene->Update();
}

void NMGame::Draw()
{
	//描画
	postEffect->PreDrawScene(dxcommon->GetCmdList());

	gameScene->Draw();
	postEffect->PostDrawScene(dxcommon->GetCmdList());

	dxcommon->preDraw();
	gameScene->DrawBG();
	postEffect->Draw(dxcommon->GetCmdList());
	gameScene->DrawFront();
	//gameScene->Draw();
	dxcommon->postDraw();
}

void NMGame::Finalize()
{
	// 各種解放
	Framework::Finalize();
	safe_delete(gameScene);
}
