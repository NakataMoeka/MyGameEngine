#pragma once
#include"Sprite.h"
#include"Audio.h"
/// <summary>
/// 321�X�^�[�g�p�̃N���X
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

	Sprite* number = nullptr;
	Sprite* Go = nullptr;
	//�^�C�}�[����
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	int tSC = 0;
	bool startFlag = false;//�J�n�J�E���g�_�E���I��������ۂ�
};

