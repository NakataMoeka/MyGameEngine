#pragma once
#include"Framework.h"
#include "SceneManager.h"
class SceneManager;
class NMGame :public Framework
{
public:
	// ������
	void Initialize() override;
	//�I��
	void Finalize() override;
	// ���t���[������
	void Update() override;
	// �`��
	void Draw() override;
private:
	SceneManager* gameScene = nullptr;

};

