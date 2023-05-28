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
#include"Ease.h"
#include "BaseScene.h"
/// <summary>
/// �^�C�g���\��
/// </summary>
class ClearScene:public BaseScene
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

	bool SetClearFlag(bool clearFlag) { return this->clearFlag = clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
	bool GetSCangeFlag()override;

private:
	Audio* audio = Audio::GetInstance();

	std::unique_ptr < Camera> camera = nullptr;
	std::unique_ptr < LightGroup> lightGroup = nullptr;
	SoundData sound1 = {};

	std::unique_ptr<Sprite> overTextSprite = nullptr;
	std::unique_ptr<Sprite> clearTextSprite = nullptr;
	std::unique_ptr<Sprite> overSprite = nullptr;
	std::unique_ptr<Sprite> clearSprite = nullptr;
	std::unique_ptr<Sprite> motherASprite = nullptr;
	std::unique_ptr<Sprite> motherSSprite = nullptr;
	std::unique_ptr<Sprite> Space = nullptr;
	std::unique_ptr<Sprite> back = nullptr;

	bool clearFlag = false;
	bool overFlag = false;
	XMFLOAT2 pos = { 300,800 };
	Eas* eas;
	float easeTimer = 0;//�C�[�W���O�̃^�C�}�[
	bool pushFlag = false;//�{�^����������悤�ɂ���
	bool SCangeFlag = false;
};

