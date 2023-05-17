#pragma once
#include"Sprite.h"
#include"Audio.h"
#include<array>
#include <memory>
/// <summary>
/// �X�^�[�g���̖ڕW���\&�J�n�J�E���g�_�E���p�̃N���X
/// </summary>
class start
{
public:
	void Initialize();
	void Init();
	void Update();
	void Draw(int stage);
	bool GetStartFlag() { return startFlag; }
	bool SetStartFlag(bool startFlag) { return this->startFlag=startFlag; }
private:
	Audio* audio = Audio::GetInstance();
	SoundData sound1 = {};
	std::unique_ptr<Sprite> number = nullptr;
	std::unique_ptr<Sprite> Go = nullptr;
	std::array<std::unique_ptr<Sprite>, 3> message = {};
	std::unique_ptr<Sprite> messageUI = nullptr;
	//�^�C�}�[����
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	int tSC = 0;//�J�E���g�_�E���̕����p
	bool startFlag = false;//�J�n�J�E���g�_�E���I��������ۂ�
	bool GoFlag = false;
	int MCount = 0;
};

