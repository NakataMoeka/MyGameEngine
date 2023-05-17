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
/// <summary>
class Loading
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
private:
	Audio* audio = Audio::GetInstance();
	std::unique_ptr<Sprite> loadingS = nullptr;//���[�h���̕���
	std::unique_ptr<Sprite> loadBack = nullptr;//�w�i
	int loadCount = 0;//�����ʒu
	int LoadCountCount = 0;//loadCount�̐��l�𑝂₷���߂̂��
};

