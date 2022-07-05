#pragma once
#include"Object3d.h"
#include"Model.h"
/// <summary>
/// ステージに配置されているオブジェクトのクラス
/// </summary>
class GameObject
{
public:
	GameObject();
	~GameObject();
	void Initialize();
	void Init();
	void Update();
	void Draw();
	Object3d* cube;
	Model* modelCube;
};

