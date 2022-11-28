#pragma once
#include"Sprite.h"
#include"Audio.h"
/// <summary>
/// �|�[�Y�@�\(�Q�[���V�[������̈ڐA)
/// </summary>
class Pose
{
public:
	void Initialize(Audio* audio);//��񂾂��̏�����
	void Init();//�V�[���`�F���W���ɂ����鏉����
	void Update();//�A�v�f
	void Draw();//���f���̕`��
	bool GetPFlag() { return PoseFlag; }
	bool GetTFlag() { return TitleFlag; }
	bool GetJFlag() { return jFlag; }
private:

	Audio* audio = nullptr;
	SoundData sound1 = {};
	SoundData sound2 = {};
	Sprite* PoseSprite = nullptr;
	Sprite* TitleBackSprite = nullptr;
	Sprite* BackSprite = nullptr;
	Sprite* InfoSprite = nullptr;
	Sprite* PBSprite = nullptr;
	bool PoseFlag = false;//�Q�[�����f�t���O
	bool TitleFlag = false;//�^�C�g���ɖ߂�t���O
	int PS = 0;//�|�[�Y���̂��
	bool jFlag = false;//�W�����v
};

