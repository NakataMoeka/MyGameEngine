#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Camera.h"
class Draw2D
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 頂点データ構造体
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

public: // 静的メンバ関数

	static bool StaticInitialize(ID3D12Device* dev ,int window_width, int window_height);

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Draw2D* Create();

private: // 静的メンバ変数

	//静的メンバ変数
	//テクスチャの最大枚数
	static const int spriteSRVCount = 512; //テクスチャの最大枚数
	//頂点数
	static const int vertNum = 4;
	//デバイス
	static ID3D12Device* dev;
	//デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	//コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;
	//デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	//テクスチャバッファ
	static ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	//射影行列
	static XMMATRIX matProjection;

	//メンバ変数
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//テクスチャ番号
	UINT texNumber = 0;
	//Z軸の回転角
	float rotation = 0.0f;
	//ローカル座標
	XMFLOAT2 position = {};
	XMFLOAT2 position2 = {};
	//スプライト幅、高さ
	XMFLOAT2 size = { 100.0f,100.0f };
	//ワールド変換行列
	XMMATRIX matWorld{};
	//色
	XMFLOAT4 color = { 1,1,1,1 };

private:// 静的メンバ関数
	
	void GraphicsPipline();
	

public: // メンバ関数
	bool Initialize();

	void CreateModel(XMFLOAT2 startPos, XMFLOAT2 endPos);

	void Update();


	void Draw();

	float GetAngle(XMFLOAT2 startPos, XMFLOAT2 endPos);
	const XMFLOAT2& GetPosition() { return position; }

	void SetPosition(XMFLOAT2 position) { this->position = position; }

};

