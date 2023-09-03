#pragma once
#include"Object3d.h"
#include"Model.h"
#include "DirectXMath.h"
class GObject
{
private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	void Initialize(Model* modell);
	void Init(XMFLOAT3 pos, XMFLOAT3 size, XMVECTOR rot ,float y,float radius);
	void Update(XMVECTOR rot,bool move);
	void RC();
	void Draw();
	Object3d* GetOBJ3d();
	XMMATRIX GetMatWorld();
private:
	Object3d* obj = nullptr;
	std::unique_ptr < Model> model = nullptr;
};

