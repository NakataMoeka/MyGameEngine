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
#include "BaseScene.h"
/// <summary>
/// �^�C�g���\��
/// </summary>
class TitleScene :public BaseScene
{
public:
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize()override;
	//���̃V�[����ʂ邽�тɉ��x���s���鏉����(�ʒu�Ȃ�)
	void Init()override;
	void InitStageNum(int stageNum)override;
	//�J��Ԃ�����
	void Update()override;
	//�w�i�摜�`��
	void DrawBG()override;
	//�I�u�W�F�N�g�`��
	void Draw()override;
	//�O�i�摜�`��
	void DrawFront()override;

	void Finalize()override;

	bool GetSCangeFlag()override;
private:


	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	Audio* audio = Audio::GetInstance();
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

