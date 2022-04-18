#include "FbxLoader.h"
#include <cassert>

const std::string FbxLoader::baseDirectory = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
    static FbxLoader instance;
    return &instance;
}

void FbxLoader::Initialize(ID3D12Device* dev)
{
    //再初期化チェック
    assert(fbxManager == nullptr);
    //引数からメンバ変数に代入
    this->dev = dev;
    //fbxマネージャの生成
    fbxManager = FbxManager::Create();
    //fbxマネージャの入出力設定
    FbxIOSettings* ios = FbxIOSettings::Create(fbxManager, IOSROOT);
    fbxManager->SetIOSettings(ios);
    //fbxインポータの生成
    fbxImporter = FbxImporter::Create(fbxManager, "");
}

void FbxLoader::Finalize()
{
    //各種fbxインスタンスの破棄
    fbxImporter->Destroy();
    fbxManager->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
    //モデル名と同じ名前のフォルダから読み込む
    const string directoryPath = baseDirectory + modelName + "/";
    //拡張子.fbxを付加
    const string fileName = modelName + ".fbx";
    //連結してフルパスを得る
    const string fullpath = directoryPath + fileName;
    //ファイル名を指定してfbxファイルを読み込む
    if (!fbxImporter->Initialize(fullpath.c_str(), -1, fbxManager->GetIOSettings())) {
        assert(0);
    }
    //シーン生成
    FbxScene* fbxScene = FbxScene::Create(fbxManager, "fbxScene");
    //ファイルからロードしたfbx情報をシーンにインポート
    fbxImporter->Import(fbxScene);
}
void FbxLoader::ParseNodeRecursive(FbxModel* fbxModel, FbxNode* fbxNode)
{
    //ノード名を取得
    string name = fbxNode->GetName();
    //モデルにノードを追加(ToDo)
    //Fbxノードの情報を解析してノードに記録(ToDo)
    //Fbxノードのメッシュ情報を解析(ToDo)

    //子ノードに対して再帰呼び出し
    for (int i = 0; i < fbxNode->GetChildCount(); i++) {
        ParseNodeRecursive(fbxModel, fbxNode->GetChild(i));
    }
}
