#pragma once
#include<json.hpp>

#include <DirectXMath.h>
#include <vector>
#include"Model.h"
#include<map>
#include"Object3d.h"
struct LevelData {

	struct ObjectData {
		// �t�@�C����
		std::string fileName;
		// ���s�ړ�
		DirectX::XMVECTOR translation;
		// ��]�p
		DirectX::XMVECTOR rotation;
		// �X�P�[�����O
		DirectX::XMVECTOR scaling;
	};

	// �`��p�I�u�W�F�N�g�z��
	std::vector<ObjectData> objects;

};
class json_Loader
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	/// <summary>
	/// �t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C���̖��O</param>
	static LevelData* jsonLoad(const std::string& file_Name);
	//���f���f�[�^�R���e�i
	static std::map<std::string, Model> models;
	std::vector<Object3d*> objects;
};