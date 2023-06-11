#pragma once
#include"Sprite.h"
#include<array>
#include <memory>
/// <summary>
/// �`���[�g���A���N���X
/// </summary>
class Tutorial
{
public:
	//1�����̏�����������(�I�u�W�F�N�g�̓Ǎ��Ȃ�)
	void Initialize();
	//�J��Ԃ��s��������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	int GetTCount() { return TutorialCount; }
	int SetTCount(int TutorialCount) { return this->TutorialCount=TutorialCount; }
	bool SetCountFlag(bool countFlag) { return this->countFlag = countFlag; }
	bool GetEndFlag() { return endFlag; }
	bool GetMoveFlag() { return moveFlag; }
	bool GetColFlag() { return colFlag; }
	bool SetColFlag( bool col) { return colFlag=col; }
	int SetWalkCount(int wcount) { return walkCount = wcount; }
private:
	std::array < std::unique_ptr<Sprite>, 7> TutorialSprite = {};
	std::unique_ptr<Sprite> TutorialUI = nullptr;
	int TutorialCount = 0;//�������̕\���J�E���g
	bool countFlag = false;//��������i�߂邱�Ƃ��ł���̂��̃t���O
	bool colFlag = false;//�������邩�ۂ�
	bool endFlag = false;//�`���[�g���A���I���t���O
	bool moveFlag = false;//�����邩�̃t���O
	int walkCount = 0;//��������
};

