#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Model.h"

#include "Camera.h"
#include "LightGroup.h"
#include "CollisionInfo.h"
class BaseCollider;
class Object3d
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:

	// �p�C�v���C���Z�b�g
	struct PipelineSet
	{
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// �R�c�ϊ��s��
		XMFLOAT4 color;
		XMMATRIX viewproj;//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;//���[���h�s��
		XMFLOAT3 cameraPos;//�J�������W(���[���h���W)
	
	};

	Object3d() = default;

	virtual ~Object3d();

	static void StaticInitialize(ID3D12Device* dev, Camera* camera = nullptr);

	void CreateGraphicsPipeline(const wchar_t* ps, const wchar_t* vs);

	static void SetCamera(Camera* camera) {
		Object3d::camera = camera;
	}
	static void SetLight(LightGroup* lightGroup) {
		Object3d::lightGroup = lightGroup;
	}

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	static Object3d* Create(Model* model);


	virtual bool Initialize();

	void Quaternion();

	void UpdateWorldMatrix();

	virtual void Update();

	virtual void Draw();

	const XMMATRIX& GetMatWorld() { return matWorld; }

	void SetCollider(BaseCollider* collider);//�R���C�_�[�̒ǉ�

	void RemoveCollider();//�R���C�_�[����

	virtual void OnCollision(const CollisionInfo& info) {}

	void transformParent();//�y�A�����g�p�֐�

	//GetterSetter
	XMFLOAT3 GetWorldPosition();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	const XMVECTOR& GetRotation() { return rotation; }
	void SetRotation(XMVECTOR rotation) { this->rotation = rotation; }
	const XMFLOAT3& GetScale() { return scale; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }
	void SetColor(XMFLOAT4 color) { this->color = color; }
	// ���f���Ƃ̘A�g
	void SetModel(Model* model) { this->model = model; };
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }
	void SetParent(Object3d* parent) { this->parent = parent; }
	XMMATRIX GetMatRot() { return matRot; }
	XMMATRIX GetMatTrans() { return matTrans; }
	inline Model* GetModel() { return model; }
	BaseCollider* GetCollider() { return collider; }
	void SetParentFlag(bool pFlag) { this->parentFlag = pFlag; }
	void SetColFlag(bool cFlag) { this->ColFlag = cFlag; }
	bool GetParentFlag() { return parentFlag; }
	bool GetColFlag() { return ColFlag; }
	// �R���C�_�[
	BaseCollider* collider = nullptr;
protected:
	const char* name = nullptr;
	// �f�o�C�X
	static ID3D12Device* dev;

	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;

	// �p�C�v���C��
	PipelineSet pipelineSet;

	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@

	// �F
	XMFLOAT4 color = { 1,1,1,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMVECTOR rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// �e�I�u�W�F�N�g
	Object3d* parent = nullptr;

	Model* model = nullptr;
	XMMATRIX matWorld_parent, matTransV, matRotV, matScaleV, matWorld_Invers;
	XMMATRIX matScale, matRot, matTrans;
	XMVECTOR rotV;
	// �J����
	static Camera* camera;
	static LightGroup* lightGroup;
	// �r���{�[�h
	bool isBillboard = false;

	bool parentFlag = false;//�y�A�����g���Ă��邩�̃t���O
	bool ColFlag = false;//�������Ă��邩�t���O
};

