#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "FbxModel.h"

#include "Camera.h"
class FbxObject3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:


	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};


	static void StaticInitialize(ID3D12Device* dev, Camera* camera = nullptr);

	static void CreateGraphicsPipeline();

	static void SetDev(ID3D12Device* dev){
		FbxObject3d::dev = dev;
	}
	static void SetCamera(Camera* camera) {
		FbxObject3d::camera = camera;
	}

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	void Initialize();

	void Update();

	void Draw();

	const XMFLOAT3& GetPosition() { return position; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }

	const XMFLOAT3& GetRotation() { return rotation; }

	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	// モデルとの連携
	void SetModel(FbxModel* fbxModel) { this->fbxModel = fbxModel; };



	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }

protected:
	ComPtr<ID3D12Resource> constBuffTransform;
private:

	// デバイス
	static ID3D12Device* dev;

	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;

	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;



	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
	//XMFLOAT4 color = { 1,0,0,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	FbxObject3d* parent = nullptr;

	FbxModel* fbxModel = nullptr;

	// カメラ
	static Camera* camera;
	// ビルボード
	bool isBillboard = false;
};

