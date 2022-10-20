#pragma once
#pragma once
#include"SafeDelete.h"
#include <DirectXMath.h>
#include"input.h"
#include"Sprite.h"
#include"Audio.h"
#include"DXCommon.h"
#include"DebugText.h"
#include"Object3d.h"
#include "ParticleManager.h"
#include"Model.h"
#include "Camera.h"
#include "FbxObject.h"
#include"LightGroup.h"
#include"TitleScene.h"
#include"GameScene.h"
#include"ClearScene.h"
class SceneManager
{
public:
	enum Scene
	{
		TITLE, GAME, END,
	};
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize(DXCommon* dxCommon, Audio* audio);
	//���̃V�[����ʂ邽�тɉ��x���s���鏉����(�ʒu�Ȃ�)
	void Init();
	//�J��Ԃ�����
	void Update();
	//�w�i�摜�`��
	void DrawBG();
	//�I�u�W�F�N�g�`��
	void Draw();
	//�O�i�摜�`��
	void DrawFront();
	bool GetBFlag() { return Bflag; }
private:
	//�ŏ��̃V�[��
	Scene scene = TITLE;
	TitleScene* titleScene;
	GameScene* gameScene;
	ClearScene* clearScene;
	bool Bflag = false;
};

