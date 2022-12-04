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
/// <summary>
/// �^�C�g���\��
/// </summary>
class ClearScene
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
	bool GetClearFlag() { return clearFlag; }
	bool GetOverFlag() { return overFlag; }
	bool SetClearFlag(bool clearFlag) { return this->clearFlag = clearFlag; }
	bool SetOverFlag(bool overFlag) { return this->overFlag = overFlag; }
	bool GetSCangeFlag() { return SCangeFlag; }

private:
	DXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	const int debugTextTexNumber = 0;
	Camera* camera = nullptr;
	LightGroup* lightGroup = nullptr;

	SoundData sound1 = {};

	Sprite* overTextSprite = nullptr;
	Sprite* clearTextSprite = nullptr;
	Sprite* overSprite = nullptr;
	Sprite* clearSprite = nullptr;
	Sprite* motherASprite = nullptr;
	Sprite* motherSSprite = nullptr;
	Sprite* Space = nullptr;
	Sprite* back = nullptr;

	bool clearFlag = false;
	bool overFlag = false;
	XMFLOAT2 pos = { 300,800 };
	Eas* eas;
	float easeTimer = 0;//�C�[�W���O�̃^�C�}�[
	bool pushFlag = false;//�{�^����������悤�ɂ���
	bool SCangeFlag = false;
};

