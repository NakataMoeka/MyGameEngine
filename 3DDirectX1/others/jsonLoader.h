#pragma once

#include <string>
#include <vector>
#include <DirectXMath.h>
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

};