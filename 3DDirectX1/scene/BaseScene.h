#pragma once
class SceneManager;

class BaseScene
{
public:
	virtual ~BaseScene() = default;
	/// <summary>
	/// 最初に1回限りで行われる初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// シーン変わるごとに行われる初期化
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 背景画像描画
	/// </summary>
	virtual void DrawBG() = 0;
	/// <summary>
	/// オブジェクト描画
	/// </summary>
	virtual void Draw() = 0;
	/// <summary>
	/// 前景画像描画
	/// </summary>
	virtual void DrawFront() = 0;
};

#pragma once
