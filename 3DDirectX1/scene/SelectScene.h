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
#include<array>
#include"BaseScene.h"
/// <summary>
/// �X�e�[�W�Z���N�g�@
/// </summary>
class SelectScene:public BaseScene
{
public:
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize()override;
	//���̃V�[����ʂ邽�тɉ��x���s���鏉����(�ʒu�Ȃ�)
	void Init()override;
	void InitTH()override;
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

	//�p�[�e�B�N��
	void CreateParticles();
	int GetStageNum() { return stageNum; }
	bool GetSCangeFlag()override;
private:
	Audio* audio = Audio::GetInstance();
	std::unique_ptr <Camera> camera = nullptr;
	std::unique_ptr <LightGroup> lightGroup = nullptr;

	SoundData sound1 = {};
	SoundData sound2 = {};
	SoundData sound3 = {};
	SoundData sound4 = {};
	std::array <std::unique_ptr<Sprite>, 6> backSprite = {};
	std::unique_ptr<Sprite> SelectUI = nullptr;
	std::unique_ptr<Sprite> SelectNumber = nullptr;
	std::unique_ptr<Sprite> TutorialS = nullptr;
	float spriteCount = 0;
	int stageNum = 0;
	bool SCangeFlag = false;
	int SAFlag = 0;//�A�j���[�V�����p�̃t���O

};

