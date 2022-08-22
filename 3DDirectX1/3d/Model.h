#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Mesh.h"
/// <summary>
/// OBJ用のモデルクラス
/// </summary>
class Model
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
	~Model();

	static void StaticInitialize(ID3D12Device* dev);

	static Model* Create(const std::string& modelname, bool smoothing = false);

	void Initialize(const std::string& modelname, bool smoothing);
	
	// 描画
	void Draw(ID3D12GraphicsCommandList* cmdList);

	inline const std::vector<Mesh*>& GetMeshes() { return meshes; }


private:


	void LoadTextures();
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	void LoadModel(const std::string& modelname, bool smoothing);
	
	void AddMaterial(Material* material);
	
	void CreateDescriptorHeap();

	static const std::string baseDirectory;
	// デバイス
	static ID3D12Device* dev;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// 名前
	std::string name;
	// メッシュコンテナ
	std::vector<Mesh*> meshes;
	// マテリアルコンテナ
	std::unordered_map<std::string, Material*> materials;
	// デフォルトマテリアル
	Material* defaultMaterial = nullptr;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
};