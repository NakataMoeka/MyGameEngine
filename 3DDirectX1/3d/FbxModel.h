#pragma once
#include <string>

struct Node
{

};
//Fbx用のモデルクラス
class FbxModel
{
public:
	//フレンドクラス
	friend class FbxLoader;
private:
	//モデル名
	std::string name;
};