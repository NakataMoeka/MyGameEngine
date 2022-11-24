#include "jsonLoader.h"
#include <fstream>
#include<cassert>
#include <json.hpp>

using namespace DirectX;

using namespace std;
LevelData* json_Loader::jsonLoad(const std::string& file_Name)
{
	//json
//�A�����ăt���p�X�𓾂�
	const std::string fullpath = std::string("Resources/") + file_Name + ".json";
	std::ifstream file;
	file.open(fullpath);
	if (file.fail()) {
		assert(0);
	}
	//json����𓀂����f�[�^
	nlohmann::json deserialized;
	//��
	file >> deserialized;
	//���������x���f�[�^�t�@�C�����`�F�b�N
	//�f�[�^�����������̃`�F�b�N
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	//"name"�𕶎���Ƃ��Ď擾
	std::string name = deserialized["name"].get<std::string>();
	//���������x���f�[�^�t�@�C�����`�F�b�N
	assert(name.compare("scene") == 0);
	//���x���f�[�^�i�[�p�C���X�^���X�𐶐�
	LevelData* levelData = new LevelData();

	// "objects"�̑S�I�u�W�F�N�g�𑖍�
	for (nlohmann::json& object : deserialized["objects"]) {
		assert(object.contains("type"));
		std::string type = object["type"].get<std::string>();
		//MESH
		if (type.compare("MESH") == 0) {
			//�v�f�ǉ�
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//���ǉ������v�f�̎Q�Ƃ𓾂�
			LevelData::ObjectData& objectData = levelData->objects.back();
			if (object.contains("file_name")) {
				//�t�@�C����
				objectData.fileName = object["file_name"];
				// �g�����X�t�H�[���̃p�����[�^�ǂݍ���
				nlohmann::json& transform = object["transform"];
				// ���s�ړ�
				objectData.translation.m128_f32[0] = (float)transform["translation"][1];
				objectData.translation.m128_f32[1] = (float)transform["translation"][2];
				objectData.translation.m128_f32[2] = -(float)transform["translation"][0];
				objectData.translation.m128_f32[3] = 1.0f;
				//��]�p
				objectData.rotation.m128_f32[0] = -(float)transform["rotation"][1];
				objectData.rotation.m128_f32[1] = -(float)transform["rotation"][2];
				objectData.rotation.m128_f32[2] = (float)transform["rotation"][0];
				objectData.rotation.m128_f32[3] = 0.0f;
				//��]�p
				objectData.scaling.m128_f32[0] = (float)transform["scaling"][1];
				objectData.scaling.m128_f32[1] = (float)transform["scaling"][2];
				objectData.scaling.m128_f32[2] = (float)transform["scaling"][0];
				objectData.scaling.m128_f32[3] = 0.0f;


			}
			// TODO: �I�u�W�F�N�g�������ċA�֐��ɂ܂Ƃ߁A�ċA�ďo���Ŏ}�𑖍�����
			if (object.contains("children"))
			{
			}
		}

	}

	return levelData;
}
