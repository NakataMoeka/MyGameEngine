#pragma once
#include"Sprite.h"
#include<array>
/// <summary>
/// �T�C�Y�\���p�̃N���X
/// </summary>
class SphereSize
{
public:
	void Initialize();//1��݂̂̏�����
	void Init();//�V�[���J�n���ɂ��鏉����
	void InitStage(int maxNum);
	void Update();
	void Draw();
	int SetTsize(int Tsize) { return this->Tsize = Tsize; }
	int GetTsize() { return Tsize; }
	int GetTcount() { return TCount; }
private:
	std::array < Sprite*, 10>Number = {};//�����B8�Ȃ̂�cm��m�̈�̈ʂƏ\�̈ʂ����邽��&�ڕW�T�C�Y�p
	std::array < Sprite*, 4> Meters = {};//�ڕW�T�C�Y�ƌ��݂̃T�C�Y�p��2��
	std::array < Sprite*, 2> Centimeter = {};//��L�Ɠ���
	int Tsize = 1;
	int TCount = 0;
	int tSC = 0;//cm��1�̈ʃJ�E���g
	int tC = 0;//cm��10�̈ʃJ�E���g
	int tSM = 0;//m��1�̈�
	int tM = 0;//m��10�̈�
	int tMM = 0;//m��100�̈�

};

