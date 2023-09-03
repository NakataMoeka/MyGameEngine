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
#include"BaseScene.h"
class SceneChange
{
public:
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize();
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

	bool SetChangeSFlag(bool fadeIn) { return this->fadeIn = fadeIn; }
	bool GetChangeEFlag() { return fadeOut; }
private:
	std::unique_ptr<Sprite>ChangeS = nullptr;
	float fade = 0;
	bool fadeIn = false;//�t�F�[�h�C��
	bool fadeOut = false;//�t�F�[�h�A�E�g
};
