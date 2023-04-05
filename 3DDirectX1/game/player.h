#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
#include "FbxObject.h"
#include<array>
#include <memory>
/// <summary>
/// �v���C���[�֘A�̃N���X
/// </summary>
class Player
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	Player();
	~Player();
	void Initialize();//��񂾂��̏�����
	void Init();//�V�[���`�F���W���ɂ����鏉����
	void stageInit(int stageNo);
	void Update();//�A�v�f
	void Draw();//���f���̕`��
	void DrawSprite();//�摜�̕`��
	void RC();//�R���C�_�[���������

	//GetterSetter
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	XMFLOAT3 GetPlayerAngle() { return playerAngle; }
	float GetRadius() { return radius; }
	Sphere GetSphere() { return sphere; }
	Object3d* GetObject3d() { return SphereObj; }
	XMFLOAT3 SetSphereSize(XMFLOAT3 sphereSize) { return this->sphereSize = sphereSize; }
	float SetSpherePos(float spherePos) { return this->spherePos.y = spherePos; }
	XMFLOAT3 SetPlayerPos(XMFLOAT3 playerPos) { return this->playerPos = playerPos; }
	float GetTsize() { return Tsize; }
	float SetTsize(float tsize) { return this->Tsize = tsize; }
	bool SetWalkFlag(bool walkFlag) { return this->walkFlag = walkFlag; }
	bool SetPFlag(bool pFlag) { return this->pFlag = pFlag; }

	float SetSZV(float szv) { return this->sphereZV = szv; }
	float SetSY(float sy) { return this->sphereY = sy; }
	float SetRadius(float r) { return this->radius = r; }
	int GetTWCount() { return TWCount; }
private://Update()�ɂ܂Ƃ߂����
	void Move();//�ړ�
	XMFLOAT3 vec(XMFLOAT3 pos, XMVECTOR vec);
	void Ball();//�{�[���֌W
	void Jump();//�W�����v
	void Dash();//�_�b�V��
private://�ϐ�
	//�v���C���[�̃��f��
	FbxObject3d* playerObj = nullptr;
	FbxModel* model = nullptr;
	//���̃��f��
	Object3d* SphereObj = nullptr;
	Model* model2 = nullptr;
	Object3d* SphereObj2 = nullptr;
	Model* model3 = nullptr;
	//�W����
	std::unique_ptr<Sprite> dashSprite = nullptr;


	//�ʒu�T�C�Y�p�x
	XMFLOAT3 playerPos = { 0,0,0 };
	XMFLOAT3 spherePos = { 0,0,0 };
	XMFLOAT3 playerAngle = { 0,0,0 };
	XMVECTOR sphereAngle = { 0,0,0,0 };
	XMFLOAT3 sphereSize = { 1,1,1 };

	Sphere sphere;//�����蔻��̂��

	float Tsize = 1;//���̃T�C�Y(����ɕ\������Ă�����)
	float r = 3;
	float radius = 3.0f;
	//�ړ�
	float speedUD = 0;
	float speedLR = 0;
	bool moveUDFlag = false;
	bool moveLRFlag = false;
	//����z��
	float sphereZV = 0;//���Ƃ̋���z��
	float sphereY = 0;//��y������
	//�_�b�V���֘A�̕ϐ�
	bool dashFlag = false;
	float dash = 1.5f;
	float dashSpeed = 2.0f;
	int dashCoolTime = 0;
	const int dashCoolTimeMax = 20;
	int dashTime = 0;
	//const int dashTimeMax = 20;
	float fade = 1;
	//�W�����v���n�ʂƂ̓����蔻��n
	bool JumpFlag = false;
	bool onGround = true;
	// �����x�N�g��
	DirectX::XMVECTOR fallV = {};

	bool onGround2 = true;
	// �����x�N�g��
	DirectX::XMVECTOR fallV2 = {};

	static const int OBJNumber = 100;

	//bool colFlag[OBJNumber][OBJNumber] = {};

	float PlayerWalkCount = 0;
	float CountWalk = 0;
	bool pFlag = false;//�|�[�Y�p�̃t���O
	bool walkFlag = true;//�`���[�g���A���p�̕����邩����t���O
	int TWCount = 0;//�`���[�g���A���̈ړ��J�E���g
	int stageNum = 0;
};