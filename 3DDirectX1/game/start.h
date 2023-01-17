#pragma once
#include"Sprite.h"
#include"Audio.h"
#include<array>
/// <summary>
/// �X�^�[�g���̖ڕW���\&�J�n�J�E���g�_�E���p�̃N���X
/// </summary>
class start
{
public:
	void Initialize(Audio* audio);
	void Init();
	void Update();
	void Draw();
	bool GetStartFlag() { return startFlag; }
	bool SetStartFlag(bool startFlag) { return this->startFlag=startFlag; }
private:
	Audio* audio = nullptr;
	SoundData sound1 = {};
	Sprite* number = nullptr;
	Sprite* Go = nullptr;
	std::array<Sprite*, 3> message = {};
	Sprite* messageUI = nullptr;
	//�^�C�}�[����
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	int tSC = 0;
	bool startFlag = false;//�J�n�J�E���g�_�E���I��������ۂ�
	bool GoFlag = false;
	int MCount = 0;
};

