#include "jsonLoader.h"
#include <fstream>
#include<cassert>
#include <json.hpp>

using namespace DirectX;

using namespace std;
LevelData* json_Loader::jsonLoad(const std::string& file_Name)
{
	//json
//連結してフルパスを得る
	const std::string fullpath = std::string("Resources/") + file_Name + ".json";
	std::ifstream file;
	file.open(fullpath);
	if (file.fail()) {
		assert(0);
	}
	//jsonから解凍したデータ
	nlohmann::json deserialized;
	//解凍
	file >> deserialized;
	//正しいレベルデータファイルかチェック
	//データが正しいかのチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	//"name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	//正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);
	//レベルデータ格納用インスタンスを生成
	LevelData* levelData = new LevelData();

	// "objects"の全オブジェクトを走査
	for (nlohmann::json& object : deserialized["objects"]) {
		assert(object.contains("type"));
		std::string type = object["type"].get<std::string>();
		//MESH
		if (type.compare("MESH") == 0) {
			//要素追加
			levelData->objects.emplace_back(LevelData::ObjectData{});
			//今追加した要素の参照を得る
			LevelData::ObjectData& objectData = levelData->objects.back();
			if (object.contains("file_name")) {
				//ファイル名
				objectData.fileName = object["file_name"];
				// トランスフォームのパラメータ読み込み
				nlohmann::json& transform = object["transform"];
				// 平行移動
				objectData.translation.m128_f32[0] = (float)transform["translation"][1];
				objectData.translation.m128_f32[1] = (float)transform["translation"][2];
				objectData.translation.m128_f32[2] = -(float)transform["translation"][0];
				objectData.translation.m128_f32[3] = 1.0f;
				//回転角
				objectData.rotation.m128_f32[0] = -(float)transform["rotation"][1];
				objectData.rotation.m128_f32[1] = -(float)transform["rotation"][2];
				objectData.rotation.m128_f32[2] = (float)transform["rotation"][0];
				objectData.rotation.m128_f32[3] = 0.0f;
				//回転角
				objectData.scaling.m128_f32[0] = (float)transform["scaling"][1];
				objectData.scaling.m128_f32[1] = (float)transform["scaling"][2];
				objectData.scaling.m128_f32[2] = (float)transform["scaling"][0];
				objectData.scaling.m128_f32[3] = 0.0f;


			}
			// TODO: オブジェクト走査を再帰関数にまとめ、再帰呼出しで枝を走査する
			if (object.contains("children"))
			{
			}
		}

	}

	return levelData;
}
