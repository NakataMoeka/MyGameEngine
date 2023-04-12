#pragma once
#pragma once
#include <windows.h>
#include <tchar.h>
#include <sstream>

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
class FPS final
{
public:
	//������s
	void Start();
	//FPS�����̎��s
	void Ran();
	//�C���X�^���X�̎擾
	static FPS* GetInstance();
	float GetFPS() { return fps; }
	//�R�s�[�R���X�g���N�^�A������Z�q������
	FPS(const FPS& obj) = delete;
	FPS& operator=(const FPS& obj) = delete;
private:
	FPS() {};
	~FPS() {};

	const float MIN_FREAM_TIME = 1.0f / 60.0f;
	float frameTime = 0;
	LARGE_INTEGER timeStart={};
	LARGE_INTEGER timeEnd={};
	LARGE_INTEGER timeFreq={};
	
	float fps = 0;
};

