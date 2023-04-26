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
	bool GetSCangeFlag() { return SCangeFlag; }
private:
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	const int debugTextTexNumber = 0;
	std::unique_ptr < Camera> camera = nullptr;
	std::unique_ptr < LightGroup> lightGroup = nullptr;

	std::unique_ptr < Sprite> TSprite;
	std::unique_ptr < Sprite> TBSprite;
	std::unique_ptr < Sprite> TB2Sprite;
	std::unique_ptr<Sprite> TSSprite;
	std::unique_ptr<Sprite> TS2Sprite;

	bool SCangeFlag = false;
	int SceneNum = 0;
	int Scene = 0;
	float TaCount = 0;
	int testCount = 0;
};

