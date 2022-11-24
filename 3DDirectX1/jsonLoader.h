#pragma once
#include<json.hpp>
#include <string>
#include <DirectXMath.h>
#include <vector>
#include"Model.h"
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
public:
	/// <summary>
	/// �t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileName">�t�@�C���̖��O</param>
	void jsonLoad(const std::string& fileName);
	//���f���f�[�^�R���e�i
	std::vector<Model*>models;
};