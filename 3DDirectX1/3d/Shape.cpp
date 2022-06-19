#include "Shape.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

using namespace std;

ID3D12Device* Shape::dev = nullptr;
UINT Shape::descriptorHandleIncrementSize = 0;

bool Shape::StaticInitialize(ID3D12Device* dev)
{
	// nullptrチェック
	assert(dev);

	Shape::dev = dev;

	return true;
}

Shape* Shape::Create(float x, float y, float z) 
{
	// 3Dオブジェクトのインスタンスを生成
	Shape* model = new Shape();
	if (model == nullptr)
	{
		return nullptr;
	}
	// 初期化
	if (!model->Initialize(x,y,z))
	{
		delete model;
		assert(0);
		return nullptr;
	}
	
	

	return model;
}

bool Shape::InitializeDescriptorHeap()
{
	HRESULT result = S_FALSE;
	//設定構造体
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors = 1;

	result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));

	if (FAILED(result)) {
		assert(0);
		return false;
	}
	descriptorHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	return true;
}

bool Shape::LoadTexture(const wchar_t* filename)
{
	HRESULT result = S_FALSE;
	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	//WICテクスチャのロード
	result = LoadFromWICFile(
		filename,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		return result;
	}

	const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出
	// リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format, metadata.width,
		(UINT)metadata. height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// テクスチャ用バッファの生成
	result = dev->CreateCommittedResource(		//GPUリソースの生成
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,		//テクスチャ用設定
		nullptr,
		IID_PPV_ARGS(&texbuff));
	if (FAILED(result)) {
		return result;
	}
	//テクスチャバッファにデータ転送
	result = texbuff->WriteToSubresource(
		0,
		nullptr,		//全領域へコピー
		img->pixels,
		(UINT)img->rowPitch,
		(UINT)img->slicePitch
	);
	if (FAILED(result)) {
		return result;
	}


	// シェーダリソースビュー作成
	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	dev->CreateShaderResourceView(texbuff.Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		cpuDescHandleSRV
	);

	return true;
}



void Shape::CreateCube(float x, float y, float z)
{
	

	//前
	vertices.push_back({ {-x, -y, -z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {-x,  y, -z}, {}, {0.0f, 0.0f} });
	vertices.push_back({ { x, -y, -z}, {}, {1.0f, 1.0f} });
	vertices.push_back({ { x,  y, -z}, {}, {1.0f, 0.0f} });
	//後
	vertices.push_back({ {-x, -y, z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {-x,  y, z}, {}, {0.0f, 0.0f} });
	vertices.push_back({ { x, -y, z}, {}, {1.0f, 1.0f} });
	vertices.push_back({ { x,  y, z}, {}, {1.0f, 0.0f} });
	//左
	vertices.push_back({ {-x, -y, -z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {-x, -y,  z}, {}, {0.0f, 0.0f} });
	vertices.push_back({ {-x,  y, -z}, {}, {1.0f, 1.0f} });
	vertices.push_back({ {-x,  y,  z}, {}, {1.0f, 0.0f} });
	//右
	vertices.push_back({ {x, -y,  z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {x, -y, -z}, {}, {0.0f, 0.0f} });
	vertices.push_back({ {x, y, z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {x, y, -z}, {}, {0.0f, 1.0f} });
	//下
	vertices.push_back({ {-x, -y, -z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {-x, -y, z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {x, -y, -z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {x, -y, z}, {}, {0.0f, 1.0f} });
	//上
	vertices.push_back({ {-x, y, -z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {-x, y, z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {x, y, -z}, {}, {0.0f, 1.0f} });
	vertices.push_back({ {x, y, z}, {}, {0.0f, 1.0f} });

	/*インデックスデータ*/
	indices= {
		//前
		0,1,2,   
		2,1,3,   

		//後
		5,4,6,    
		5,6,7,    

		//左
		8,9,10,   
		10,9,11,  

		//右
		12,13,14,
		14,13,15, 

		//下
		16,17,18, 
		18,17,19, 

		//上
		22,21,23, 
	};

	CreateModel();
	InitializeDescriptorHeap();
	LoadTexture(L"Resources/white1x1.png");
}


bool Shape::Initialize(float x,float y, float z)
{
	// nullptrチェック
	assert(dev);


	CreateCube(x, y, z);
	return true;
}

void Shape::CreateModel()
{
	HRESULT result = S_FALSE;
	for (size_t i = 0; i < indices.size() / 3; i++)
	{//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		unsigned short indices0 = indices[i * 3 + 0];
		unsigned short indices1 = indices[i * 3 + 1];
		unsigned short indices2 = indices[i * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		XMVECTOR p0 = XMLoadFloat3(&vertices[indices0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[indices1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[indices2].pos);
		//p0→p1ベクトル、p0→p2ベクトルを計算（ベクトルの減算）
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);

		//外積は両方から垂直なベクトル
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//正規化（長さを１にする）
		normal = XMVector3Normalize(normal);
		//求めた法線を頂点データに代入
		XMStoreFloat3(&vertices[indices0].normal, normal);
		XMStoreFloat3(&vertices[indices1].normal, normal);
		XMStoreFloat3(&vertices[indices2].normal, normal);
	}

	//頂点データ全体のサイズ＝頂点データ一つ分のサイズ＊頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());

	//インデックスデータ全体のサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());

	////頂点バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff)
	);

	////インデックスバッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));

	VertexPosNormalUv* vertMap = nullptr;
	//GPU上のバッファに対応した仮想メモリを取得
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);

	//全頂点に対して
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertMap[i] = vertices[i];//座標コピー
	}

	//マップを解除
	vertBuff->Unmap(0, nullptr);

	//GPU上のバッファに対応した仮想メモリを取得
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);

	//全インデックスに対して
	for (size_t i = 0; i < indices.size(); i++)
	{
		indexMap[i] = indices[i];//インデックスをコピー
	}
	//繋がりを解除
	indexBuff->Unmap(0, nullptr);

	//頂点バッファビューの作成
	vbView.BufferLocation =vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(VertexPosNormalUv);

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

}



void Shape::Draw(ID3D12GraphicsCommandList* cmdList)
{
	// nullptrチェック
	assert(dev);

	// 頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// インデックスバッファの設定
	cmdList->IASetIndexBuffer(&ibView);

	// デスクリプタヒープの配列
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(1, constBuffB1->GetGPUVirtualAddress());
	//// シェーダリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(2, gpuDescHandleSRV);

	// 描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}
