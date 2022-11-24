#pragma once
#include<json.hpp>

#include <DirectXMath.h>
#include <vector>
#include"Model.h"
#include<map>
#include"Object3d.h"
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
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	/// <summary>
	/// ファイル読み込み
	/// </summary>
	/// <param name="fileName">ファイルの名前</param>
	static LevelData* jsonLoad(const std::string& file_Name);
	//モデルデータコンテナ
	static std::map<std::string, Model> models;
	std::vector<Object3d*> objects;
};