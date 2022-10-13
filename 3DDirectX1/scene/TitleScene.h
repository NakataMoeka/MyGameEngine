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
/// <summary>
/// �^�C�g���\��
/// </summary>
class TitleScene
{
public:
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
	//�p�[�e�B�N��
	void CreateParticles();
	bool GetSCangeFlag() { return SCangeFlag; }
private:
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	const int debugTextTexNumber = 0;
	Camera* camera = nullptr;
	LightGroup* lightGroup = nullptr;
	Sprite* TSprite = nullptr;
	Sprite* TBSprite = nullptr;
	Sprite* TB2Sprite = nullptr;
	Sprite* TSSprite = nullptr;
	Sprite* TS2Sprite = nullptr;
	bool SCangeFlag = false;
	int SceneNum = 0;
	int Scene = 0;


};

