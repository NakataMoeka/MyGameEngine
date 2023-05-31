#pragma once
class SceneManager;

class BaseScene
{
public:
	virtual ~BaseScene() = default;
	/// <summary>
	/// �ŏ���1�����ōs���鏉����
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �V�[���ς�邲�Ƃɍs���鏉����
	/// </summary>
	virtual void Init() = 0;
	virtual void InitTH() = 0;
	virtual void InitStageNum(int num) = 0;
	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// �w�i�摜�`��
	/// </summary>
	virtual void DrawBG() = 0;
	/// <summary>
	/// �I�u�W�F�N�g�`��
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// �O�i�摜�`��
	/// </summary>
	virtual void DrawFront() = 0;

	virtual void Finalize() = 0;
	
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }
	virtual bool GetSCangeFlag() = 0;
protected:
	SceneManager* sceneManager_ = nullptr;
};
