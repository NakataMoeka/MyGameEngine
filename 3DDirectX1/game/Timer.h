#pragma once
#include"Sprite.h"
#include <array>
/// <summary>
/// �^�C�}�[�\��(�Q�[���V�[������̕���)
/// </summary>
class Timer
{
public:
	void Initialize();//��񂾂��̏�����
	void Init();//�V�[���`�F���W���ɂ����鏉����
	void Update();//�A�v�f
	void Draw();//���f���̕`��
	double GetDT() { return dt; }
	bool SetFlag(bool poseFlag) { return this->poseFlag = poseFlag; }
private:
	Sprite* timeSprite = nullptr;//�~
	Sprite* timeSprite3 = nullptr;//�~
	Sprite* timeSprite2 = nullptr;//�o�[
	std::array<Sprite*,2> TimeNum = {};
	//�^�C�}�[�n
	float TimeRot = 0;
	int TimeCount = 0;
	float TR;
	double start;
	double end;
	double dt;
	double total;
	double SetTime;
	bool poseFlag = false;
	int tSC = 0;//1�̈ʃJ�E���g
	int tC = 0;//10�̈ʃJ�E���g
};

