#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>


using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib, "d3dcompiler.lib")
class Sprite {

	private: 

	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:


	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT2 uv;  // uv座標
	};

	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};
	//静的メンバ関数
	static bool StaticInitialize(ID3D12Device* dev, int window_width, int window_height);
	//描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	//描画後処理
	static void PostDraw();
	//スプライト生成
	static Sprite* CreateSprite(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1,1,1,1 }, XMFLOAT2 anchorpoint = { 0.0f,0.0f }, bool isFlipX = false, bool isFlipY = false);
	//テクスチャ読み込み
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);


	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	//初期化
	bool Initialize();
	//回転の設定
	void SetRotation(float rotation);
	//座標の設定
	void SetPosition(XMFLOAT2 position);
	//サイズの設定
	void SetSize(XMFLOAT2 size);
	//色の設定
	void SetColor(XMFLOAT4 color);
	//アンカーポイントの設定
	void SetAnchorPoint(XMFLOAT2 anchorpoint);
	//左右反転の設定
	void SetIsFlipX(bool isFlipX);
	//上下反転の設定
	void SetIsFlipY(bool isFlipY);
	//テクスチャの範囲の設定
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);
	//描画
	void Draw();
private: 



	void TransferVertices();

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
	//スプライト幅、高さ
	XMFLOAT2 size = { 100.0f,100.0f };
	//アンカーポイント
	XMFLOAT2 anchorpoint = { 0,0 };
	//ワールド変換行列
	XMMATRIX matWorld{};
	//色
	XMFLOAT4 color = { 1,1,1,1 };
	//左右反転
	bool isFlipX = false;
	//上下反転
	bool isFlipY = false;
	//テクスチャ始点
	XMFLOAT2 texBase = { 0,0 };
	//テクスチャ幅、高さ
	XMFLOAT2 texSize = { 100.0f,100.0f };

};
