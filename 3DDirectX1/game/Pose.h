#pragma once
#include"Sprite.h"
#include"Audio.h"
#include <memory>
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
	std::unique_ptr<Sprite> PoseSprite = nullptr;
	std::unique_ptr<Sprite> TitleBackSprite = nullptr;
	std::unique_ptr<Sprite> BackSprite = nullptr;
	std::unique_ptr<Sprite> InfoSprite = nullptr;
	std::unique_ptr<Sprite> PBSprite = nullptr;
	bool PoseFlag = false;//�Q�[�����f�t���O
	bool TitleFlag = false;//�^�C�g���ɖ߂�t���O
	int PS = 0;//�|�[�Y���̂��
	bool jFlag = false;//�W�����v
};

