#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "FbxModel.h"

class FbxLoader
{
private://エイリアス
	//std::を省略
	using string = std::string;
public:

	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dev">D3D12デバイス</param>
	void Initialize(ID3D12Device* dev);
	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();
	/// <summary>
	/// ファイルからFBXモデル読み込み
	/// </summary>
	/// <param name="modelName">モデル名</param>
	void LoadModelFromFile(const string&modelName);
	void ParseNodeRecursive(FbxModel* fbxModel, FbxNode* fbxNode);
public://定数

	static const string baseDirectory;
private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;

	ID3D12Device* dev = nullptr;
	//fbxマネージャ
	FbxManager* fbxManager = nullptr;
	//fbxインポータ
	FbxImporter* fbxImporter = nullptr;

};