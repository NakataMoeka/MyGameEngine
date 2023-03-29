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
/// <summary>
/// �X�e�[�W�Z���N�g�@
/// </summary>
class SelectScene
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
	int GetStageNum() { return stageNum; }
	bool GetSCangeFlag() { return SCangeFlag; }
private:
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	const int debugTextTexNumber = 0;
	Camera* camera = nullptr;
	LightGroup* lightGroup = nullptr;

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

