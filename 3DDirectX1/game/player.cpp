#include "player.h"
#include"input.h"
#include <cassert>
#include "SphereCollider.h"
#include "SphereColliderFbx.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "FbxLoader.h"
#include "FbxObject.h"
#include"DebugText.h"
using namespace DirectX;
Player::Player()
{
}
Player::~Player()
{
	safe_delete(playerObj);
	safe_delete(SphereObj);
}
void Player::Initialize()
{
	model = FbxLoader::GetInstance()->LoadModelFromFile("Player");
	playerObj = new FbxObject3d();
	playerObj->Initialize();
	playerObj->SetModel(model);
	playerObj->LoadAnimation();
	model2 = Model::Create("bullet", true);
	SphereObj = Object3d::Create(model2);
	//Create�̌�ɏ����Ȃ���client.h��InternalRelease()�ŃG���[���N����//Create�̌�ɏ����Ȃ���client.h��InternalRelease()�ŃG���[���N����
	SphereObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Sprite::LoadTexture(2, L"Resources/dash.png");

	dashSprite = std::unique_ptr<Sprite>(Sprite::CreateSprite(2, { 0,0 }));

}

void Player::Init()
{

	dashMoveFlag = false;
	dashFlag = false;
	PlayerWalkCount = 0;
	CountWalk = 0;
	speedUD = 0.0f;
	speedLR = 0.0f;
	r = 3.0f;
	dash = 1.5f;
	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);
	pFlag = false;
	sphereZV = 0;
	sphereY = 2;
	walkFlag = true;
	TWCount = 0;
	moveUDFlag = false;
	moveLRFlag = false;

	JumpFlag = false;
	onGround = true;
	spherePos = { 0,3,-40 };
	playerAngle = { 0,0,0 };
	sphereAngle = { 0,0,0,0 };
	sphereSize = { 0.8f,0.8f,0.8f };
	// �R���C�_�[�̒ǉ�
	SphereObj->SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	SphereObj->GetCollider()->SetAttribute(COLLISION_ATTR_ALLIES);
	SphereObj->SetParentFlag(false);
	playerObj->SetCollider(new SphereColliderFbx(XMVECTOR({ 0,1.0f,0,0 }), 1.0f));
	playerObj->GetCollider()->SetAttribute(COLLISION_ATTR_SPHERE);
	//playerObj->SetParentFlag(false);
	SphereObj->Quaternion();
	SphereObj->Update();


}

void Player::stageInit(int stageNo)
{
	this->stageNum = stageNo;
	//�v���C���[�̏����ʒu���߂�
	if (stageNo == 0) {
		playerPos = { 0,0,-40 };
	}
	else if (stageNo == 1) {
		playerPos = { 0,35,-40 };
	}
	else if (stageNo == 2) {
		playerPos = { 0,0,-40 };
	}
	playerObj->SetPosition(playerPos);
	playerObj->Update();
}


void Player::Move()
{

	XMVECTOR moveUD = { 0,0,speedUD,0 };//�O������p�̈ړ��x�N�g��
	XMVECTOR moveLR = { speedLR,0,0,0 };//���E�����̈ړ��p�x�N�g��
	XMVECTOR moveAngle = { 0,1,0,0 };//�p�x�̃x�N�g��
	XMVECTOR moveAngleZ = { 0,0,10,0 };//�p�x�̃x�N�g��
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.y));//y ���𒆐S�ɉ�]����}�g���b�N�X���쐬
	XMMATRIX matRot2 = XMMatrixRotationY(XMConvertToRadians(sphereAngle.m128_f32[1]));
	XMMATRIX matRot3 = XMMatrixRotationY(XMConvertToRadians(sphereAngle.m128_f32[0]));
	moveUD = XMVector3TransformNormal(moveUD, matRot2);
	moveLR = XMVector3TransformNormal(moveLR, matRot2);
	moveAngle = XMVector3TransformNormal(moveAngle, matRot);
	moveAngleZ = XMVector3TransformNormal(moveAngleZ, matRot3);

	//�p�x�ړ�
	if (Input::GetInstance()->PushKey(DIK_RIGHTARROW))
	{
		sphereAngle.m128_f32[1] += moveAngle.m128_f32[1];
		playerAngle.y += moveAngle.m128_f32[1];
	}
	else if (Input::GetInstance()->PushKey(DIK_LEFTARROW))
	{
		sphereAngle.m128_f32[1] -= moveAngle.m128_f32[1];
		playerAngle.y -= moveAngle.m128_f32[1];
	}
	//if (JumpFlag == false) {
	//�_�b�V�����Ă��Ȃ��Ƃ�
	if (dashMoveFlag == false) {
		//�ړ�
		playerPos = vec(playerPos, moveUD);
		spherePos = vec(spherePos, moveUD);
		playerPos = vec(playerPos, moveLR);
		spherePos = vec(spherePos, moveLR);
		if (Input::GetInstance()->PushKey(DIK_W))
		{
			//�O��̃X�s�[�h��0.2f�ɂȂ�܂�0.005f���Z
			if (speedUD < 0.2f) {
				speedUD += 0.005f;
			}
			sphereAngle.m128_f32[0] += 10;
		}
		else if (Input::GetInstance()->PushKey(DIK_S))
		{
			//�O��̃X�s�[�h��-0.2f�ɂȂ�܂�0.005f���Z
			if (speedUD > -0.2f) {
				speedUD -= 0.005f;
			}
			sphereAngle.m128_f32[0] -= 10;
		}
		else if (Input::GetInstance()->PushKey(DIK_D))
		{
			//���E�̃X�s�[�h��0.2f�ɂȂ�܂�0.005f���Z
			if (speedLR < 0.2f) {
				speedLR += 0.005f;
			}
			sphereAngle.m128_f32[2] += moveAngleZ.m128_f32[2];
		}
		else if (Input::GetInstance()->PushKey(DIK_A))
		{
			//���E�̃X�s�[�h��-0.2f�ɂȂ�܂�0.005f���Z
			if (speedLR > -0.2f) {
				speedLR -= 0.005f;
			}
			sphereAngle.m128_f32[2] -= moveAngleZ.m128_f32[2];
		}
	}
	//WASD�����Ă���Ƃ�
	if (Input::GetInstance()->PushKey(DIK_W) ||
		Input::GetInstance()->PushKey(DIK_S) ||
		Input::GetInstance()->PushKey(DIK_A) ||
		Input::GetInstance()->PushKey(DIK_D))
	{
		//UI�p
		if (CountWalk < 5) {
			CountWalk++;
		}
		if (CountWalk == 5) {
			if (PlayerWalkCount < 6) {
				PlayerWalkCount++;
			}
			if (PlayerWalkCount == 6) {
				PlayerWalkCount = 0;
			}
			CountWalk = 0;
		}
		if (stageNum == 0) {
			if (TWCount < 100) {
				TWCount++;
			}
		}
		//�ړ��A�j���[�V�����ɂ���
		playerObj->PlayAnimation(2, true);
	}
	//WASD�����ĂȂ��Ƃ�
	else {
		if (JumpFlag == false) {
			//�ҋ@�A�j���[�V�����ɂ���
			playerObj->PlayAnimation(1, true);
		}
		//0�ڎw���ď��X�ɃX�s�[�h���Ƃ�
		if (speedUD > 0) {
			speedUD -= 0.01f;
		}
		else if (speedUD < 0) {
			speedUD += 0.01f;
		}
		else {
			speedUD = 0.0f;
		}
		if (speedLR > 0) {
			speedLR -= 0.01f;
		}
		else if (speedLR < 0) {
			speedLR += 0.01f;
		}
		else {
			speedLR = 0.0f;
		}
	}
	if (JumpFlag == true) {
		//�W�����v�A�j���[�V�����ɂ���
		playerObj->PlayAnimation(0, false);
	}


	//��]��Ǐ]��������
}

XMFLOAT3 Player::vec(XMFLOAT3 pos, XMVECTOR vec)
{
	//�ړ��p�̃N���X
	pos.x += vec.m128_f32[0];
	pos.y += vec.m128_f32[1];
	pos.z += vec.m128_f32[2];
	return pos;
}



void Player::Ball()
{
	//�{�[���̒Ǐ]
#pragma region �J�����Ǐ]�Ƃقړ���
	XMVECTOR v0 = { 0,0,sphereZV,0 };
	//angle���W�A������y���܂��ɉ�]�B���a��-100
	XMMATRIX rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(sphereAngle.m128_f32[1]));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR bossTarget = { playerPos.x,playerPos.y,playerPos.z };
	XMVECTOR v3 = bossTarget + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	////�W�����v�����Ȃ�������Y���̒Ǐ]������
	spherePos.y = f.y + sphereY;
	spherePos.x = f.x;
	spherePos.z = f.z;

#pragma endregion
}

void Player::Jump()
{
	// ��������
	if (!onGround) {
		if (JumpFlag == true) {
			// �����������x
			const float fallAcc = -0.01f;
			const float fallVYMin = -0.5f;
			// ����
			fallV.m128_f32[1] = max(fallV.m128_f32[1] + fallAcc, fallVYMin);
			// �ړ�
			playerPos = vec(playerPos, fallV);
		}
	}
	//�W�����v����
	else if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		if (dashFlag == false && walkFlag == true && pFlag == false) {
			onGround = false;
			JumpFlag = true;
			const float jumpVYFist = 0.5f;
			fallV = { 0, jumpVYFist, 0, 0 };
		}
	}
	playerObj->UpdateWorldMatrix();
	playerObj->GetCollider()->Update();
	SphereColliderFbx* sphereCollider = dynamic_cast<SphereColliderFbx*>(playerObj->GetCollider());
	assert(sphereCollider);
	SphereCollider* sphereCollider2 = dynamic_cast<SphereCollider*>(SphereObj->GetCollider());
	assert(sphereCollider2);
	//�r��
	// �N�G���[�R�[���o�b�N�N���X
	class PlayerQueryCallback : public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};
		// �Փˎ��R�[���o�b�N�֐�
		bool OnQueryHit(const QueryHit& info) {

			const XMVECTOR up = { 0,1,0,0 };

			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

			// �n�ʔ��肵�����l
			const float threshold = cosf(XMConvertToRadians(40.0f));

			if (-threshold < cos && cos < threshold) {
				sphere->center += info.reject;
				move += info.reject;

			}
			return true;
		}

		Sphere* sphere = nullptr;
		DirectX::XMVECTOR move = { };
	};

	PlayerQueryCallback callback(sphereCollider);
	PlayerQueryCallback callback2(sphereCollider2);
	// ���ƒn�`�̌�����S����
	//DebugText::GetInstance()->Printf(100, 40, 3.0f, { 1,1,1,1 }, "%d",JumpFlag);
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_LANDSHAPE);
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider2, &callback2, COLLISION_ATTR_LANDSHAPE);

	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_OBJECT);
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider2, &callback2, COLLISION_ATTR_OBJECT);


	// �����ɂ��r�˕�������
	playerPos = vec(playerPos, callback.move);
	spherePos = vec(spherePos, callback.move);
	playerPos = vec(playerPos, callback2.move);
	spherePos = vec(spherePos, callback2.move);
	// ���̏�[���狅�̉��[�܂ł̃��C�L���X�g
	Ray ray;
	ray.start = sphereCollider->center;
	ray.start.m128_f32[1] += sphereCollider->GetRadius();
	ray.dir = { 0,-1,0,0 };
	RaycastHit raycastHit;

	// �ڒn���
	if (onGround) {
		// �X���[�Y�ɍ������ׂ̋z������
		const float adsDistance = 0.2f;
		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistance)) {
			onGround = true;
			JumpFlag = false;
			playerPos.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
		}
		// �n�ʂ��Ȃ��̂ŗ���
		else {
			onGround = false;
			fallV = {};
			JumpFlag = true;
		}
	}
	// �������
	else if (fallV.m128_f32[1] <= 0.0f) {
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f)) {
			// ���n
			onGround = true;
			JumpFlag = false;
			playerPos.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
		}
	}

}


void Player::Dash()
{
	dashCoolTime--;
	if (dashCoolTime <= 0 && dashTime <= 0)
	{
		dashCoolTime = 0;
		dashFlag = false;
		dashMoveFlag = false;
	}
	//�W�����v���Ă��Ȃ��Ƃ��Ƀ_�b�V���ł���
	if (JumpFlag == false) {
		if (Input::GetInstance()->TriggerKey(DIK_UPARROW) && Input::GetInstance()->PushKey(DIK_W) && dashFlag == false)
		{
			dashTime = dashTimeMax;
			fade = 1;
			dash = 1.5f;
			dashFlag = true;
			dashMoveFlag = true;
		}

		if (dashTime > 0)
		{
			dashTime--;
			if (dashTime <= 0)
			{
				dashCoolTime = dashCoolTimeMax;
			}
			XMVECTOR movedash = { 0,0,dash,0 };//�_�b�V���p�̈ړ��x�N�g��

			XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.y));//y ���𒆐S�ɉ�]����}�g���b�N�X���쐬
			movedash = XMVector3TransformNormal(movedash, matRot);
			playerPos = vec(playerPos, movedash);
			spherePos = vec(spherePos, movedash);
			if (fade > 0) {
				fade -= 0.05f;
			}
			if (dash > 0) {
				dash -= 0.1f;
			}
		}
	}
}


void Player::Update()
{
	SphereObj->SetParentFlag(false);
	if (walkFlag == true) {
		Move();
		Dash();
	}
	else {
		//�����Ă��Ȃ��Ƃ��ҋ@�A�j���[�V����
		playerObj->PlayAnimation(1, true);
	}
	Ball();
	Jump();
	//�ʒu�ȂǃZ�b�g�n
	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);

	SphereObj->SetPosition(spherePos);
	SphereObj->SetScale(sphereSize);
	SphereObj->SetRotation(sphereAngle);
	SphereObj->Quaternion();
	SphereObj->Update();
	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerAngle);
	playerObj->SetScale({ 0.05f,0.05f,0.05f });
	playerObj->Update();

	dashSprite->SetColor({ 1, 1, 1, fade });
}



void Player::Draw()
{
	playerObj->Draw();
	SphereObj->Draw();

}

void Player::DrawSprite()
{
	//sizeSprite->Draw();
	if (dashFlag == true) {
		dashSprite->Draw();
	}

}

void Player::RC()
{
	SphereObj->RemoveCollider();
	playerObj->RemoveCollider();
}
