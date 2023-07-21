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
	//
	enum STATE{
		JUMP,
		WALK,
		STAND
	};
public:
	Player();
	~Player();
	void Initialize();//��񂾂��̏�����
	void Init();//�V�[���`�F���W���ɂ����鏉����
	void stageInit(int stageNo);//�X�e�[�W���ς�邲�Ƃ̏�����
	void Update();//�A�v�f
	void Draw();//���f���̕`��
	void DrawSprite();//�摜�̕`��
	void RC();//�R���C�_�[���������

	//�Q�b�^�[
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	XMFLOAT3 GetPlayerAngle() { return playerAngle; }
	float GetRadius() { return radius; }
	Sphere GetSphere() { return sphere; }
	int GetTWCount() { return TWCount; }
	std::unique_ptr < Object3d>& GetObject3d() { return SphereObj; }
	//�Z�b�^�[
	XMFLOAT3 SetSphereSize(XMFLOAT3 sphereSize) { return this->sphereSize = sphereSize; }
	float SetSpherePos(float spherePos) { return this->spherePos.y = spherePos; }
	XMFLOAT3 SetPlayerPos(XMFLOAT3 playerPos) { return this->playerPos = playerPos; }
	bool SetWalkFlag(bool walkFlag) { return this->walkFlag = walkFlag; }
	bool SetPFlag(bool pFlag) { return this->pFlag = pFlag; }
	float SetSZV(float szv) { return this->sphereZV = szv; }
	float SetSY(float sy) { return this->sphereY = sy; }
	float SetRadius(float r) { return this->radius = r; }

private://Update()�ɂ܂Ƃ߂����
	void Move();//�ړ�
	XMFLOAT3 vec(XMFLOAT3 pos, XMVECTOR vec);
	XMVECTOR vecTrans(XMVECTOR vec, float rot, float speed,float xyz);
	void Ball();//�{�[���֌W
	void Jump();//�W�����v
	void terrainCol();//�n�`�Ƃ̔���
	void Dash();//�_�b�V��
private://�ϐ�
	//�v���C���[�̃��f��
	std::unique_ptr < FbxObject3d> playerObj = nullptr;
	std::unique_ptr < FbxModel> model = nullptr;
	//���̃��f��
	std::unique_ptr < Object3d> SphereObj = nullptr;
	std::unique_ptr < Model> model2 = nullptr;
	//�W����
	std::unique_ptr<Sprite> dashSprite = nullptr;
	STATE state_;
	//�ʒu�T�C�Y�p�x
	XMFLOAT3 playerPos = { 0,0,0 };
	XMFLOAT3 spherePos = { 0,0,0 };
	XMFLOAT3 playerAngle = { 0,0,0 };
	XMVECTOR sphereAngle = { 0,0,0,0 };
	XMFLOAT3 sphereSize = { 1,1,1 };

	Sphere sphere;//�����蔻��̂��
	float r = 2;
	float radius = 3.0f;
	//�ړ�
	XMVECTOR moveUD = { 0,0,0,0 };//�O��ړ��p�x�N�g��
	XMVECTOR moveLR = { 0,0,0,0 };//���E�ړ��p�x�N�g��
	XMVECTOR moveAngle = { 0,0,0,0 };//�p�x�x�N�g��
	float speedUD = 0;//�O��ړ��X�s�[�h
	float speedLR = 0;//���E�ړ��X�s�[�h
	float sphereZV = 0;//���Ƃ̋���z��
	float sphereY = 0;//��y������
	//�_�b�V���֘A�̕ϐ�
	bool dashFlag = false;
	float dash = 1.5f;
	int dashCoolTime = 0;//�N�[���^�C��
	const int dashCoolTimeMax = 20;//�N�[���^�C���ő�l
	float fade = 1;
	//�W�����v���n�ʂƂ̓����蔻��n
	bool JumpFlag = false;
	bool onGround = true;
	// �����x�N�g��
	DirectX::XMVECTOR fallV = {};
	bool pFlag = false;//�|�[�Y�p�̃t���O
	//�`���[�g���A���֘A
	bool walkFlag = true;//�`���[�g���A���p�̕����邩����t���O
	int TWCount = 0;//�`���[�g���A���̈ړ��J�E���g
	int stageNum = 0;//�X�e�[�W��
};