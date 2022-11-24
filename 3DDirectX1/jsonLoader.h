#pragma once
#include<json.hpp>
#include <string>
#include <DirectXMath.h>
#include <vector>
#include"Model.h"
struct LevelData {

	struct ObjectData {
		// ファイル名
		std::string fileName;
		// 平行移動
		DirectX::XMVECTOR translation;
		// 回転角
		DirectX::XMVECTOR rotation;
		// スケーリング
		DirectX::XMVECTOR scaling;
	};

	// 描画用オブジェクト配列
	std::vector<ObjectData> objects;

};
class json_Loader
{
public:
	/// <summary>
	/// ファイル読み込み
	/// </summary>
	/// <param name="fileName">ファイルの名前</param>
	void jsonLoad(const std::string& fileName);
	//モデルデータコンテナ
	std::vector<Model*>models;
};