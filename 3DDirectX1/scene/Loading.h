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
#include"BaseScene.h"
/// <summary>
class Loading:public BaseScene
{
public:
	//�N���������񂵂��s���Ȃ�������(���f���̓ǂݍ��݂Ȃ�)
	void Initialize()override;
	//���̃V�[����ʂ邽�тɉ��x���s���鏉����(�ʒu�Ȃ�)
	void Init()override;
	//�J��Ԃ�����
	void Update()override;
	//�w�i�摜�`��
	void DrawBG()override;
	//�I�u�W�F�N�g�`��
	void Draw()override;
	//�O�i�摜�`��
	void DrawFront()override;
private:
	Audio* audio = Audio::GetInstance();
	std::unique_ptr<Sprite> loadingS = nullptr;//���[�h���̕���
	std::unique_ptr<Sprite> loadBack = nullptr;//�w�i
	int loadCount = 0;//�����ʒu
	int LoadCountCount = 0;//loadCount�̐��l�𑝂₷���߂̂��
};

