#include "player.h"
#include"input.h"
#include <cassert>
#include "SphereCollider.h"
#include "SphereColliderFbx.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "FbxLoader.h"
#include "FbxObject.h"
using namespace DirectX;
Player::Player()
{
}
Player::~Player()
{
}
void Player::Initialize()
{
	model = FbxLoader::GetInstance()->LoadModelFromFile("Player");
	playerObj = new FbxObject3d();
	playerObj->Initialize();
	playerObj->SetModel(model);
	playerObj->LoadAnimation();
	model2 = Model::Create("bullet", false);
	SphereObj = Object3d::Create(model2);
	//Create�̌�ɏ����Ȃ���client.h��InternalRelease()�ŃG���[���N����//Create�̌�ɏ����Ȃ���client.h��InternalRelease()�ŃG���[���N����
	SphereObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Sprite::LoadTexture(2, L"Resources/dash.png");
	Sprite::LoadTexture(3, L"Resources/UI/sizeUI.png");
	Sprite::LoadTexture(4, L"Resources/UI/chikyuu.png");
	Sprite::LoadTexture(5, L"Resources/UI/Player.png");
	dashSprite = Sprite::CreateSprite(2, { 0,0 });
	sizeSprite = Sprite::CreateSprite(3, { 100,100 });
	earthSprite = Sprite::CreateSprite(4, { 1000,500 });
	playerSprite = Sprite::CreateSprite(5, { 1100,530 });
}

void Player::Init()
{
	for (int i = 0; i < OBJNumber; i++) {
		colFlag[i] = false;
	}
	dashMoveFlag = false;
	dashFlag = false;
	PlayerWalkCount = 0;
	CountWalk = 0;
	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);


	spherePos = { 0,3,-40 };
	playerPos = { 0,50,-40 };

	playerAngle = { 0,0,0 };
	sphereAngle = { 0,0,0,0 };
	sphereSize = { 1,1,1 };
	// �R���C�_�[�̒ǉ�
	float radius = 3.0f;
	SphereObj->SetCollider(new SphereCollider(XMVECTOR({ 0,3,0,0 }), radius));
	SphereObj->GetCollider()->SetAttribute(COLLISION_ATTR_ALLIES);

	playerObj->SetCollider(new SphereColliderFbx(XMVECTOR({ 0,0.6f,0,0 }), 0.6f));
	playerObj->GetCollider()->SetAttribute(COLLISION_ATTR_ALLIES);

	SphereObj->Quaternion();
	SphereObj->Update();
	playerObj->Update();

}


void Player::Move()
{
	XMVECTOR moveUD = { 0,0,0.5,0 };//�O������p�̈ړ��x�N�g��
	XMVECTOR moveLR = { 0.5,0,0,0 };//���E�����̈ړ��p�x�N�g��
	XMVECTOR moveAngle = { 0,1,0,0 };//�p�x�̃x�N�g��
	XMVECTOR moveAngleX = { 10,0,0,0 };//�p�x�̃x�N�g��
	XMVECTOR moveAngleZ = { 0,0,10,0 };//�p�x�̃x�N�g��
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.y));//y ���𒆐S�ɉ�]����}�g���b�N�X���쐬
	moveUD = XMVector3TransformNormal(moveUD, matRot);
	moveLR = XMVector3TransformNormal(moveLR, matRot);
	moveAngle = XMVector3TransformNormal(moveAngle, matRot);
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
	if (dashMoveFlag == false) {
		if (Input::GetInstance()->PushKey(DIK_W))
		{
			playerPos.x += moveUD.m128_f32[0];
			playerPos.z += moveUD.m128_f32[2];
			spherePos.x += moveUD.m128_f32[0];
			spherePos.z += moveUD.m128_f32[2];

			sphereAngle.m128_f32[0] += 10;

		}
		else if (Input::GetInstance()->PushKey(DIK_S))
		{
			playerPos.x -= moveUD.m128_f32[0];
			playerPos.z -= moveUD.m128_f32[2];
			spherePos.x -= moveUD.m128_f32[0];
			spherePos.z -= moveUD.m128_f32[2];

			sphereAngle.m128_f32[0] -= 10;

		}
		else if (Input::GetInstance()->PushKey(DIK_D))
		{
			playerPos.x += moveLR.m128_f32[0];
			playerPos.z += moveLR.m128_f32[2];
			spherePos.x += moveLR.m128_f32[0];
			spherePos.z += moveLR.m128_f32[2];

			sphereAngle.m128_f32[2] += 10;

		}
		else if (Input::GetInstance()->PushKey(DIK_A))
		{
			playerPos.x -= moveLR.m128_f32[0];
			playerPos.z -= moveLR.m128_f32[2];
			spherePos.x -= moveLR.m128_f32[0];
			spherePos.z -= moveLR.m128_f32[2];

			sphereAngle.m128_f32[2] -= 10;
		}
	}
		if (Input::GetInstance()->PushKey(DIK_W) ||
			Input::GetInstance()->PushKey(DIK_S) ||
			Input::GetInstance()->PushKey(DIK_A) ||
			Input::GetInstance()->PushKey(DIK_D))
		{

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
			
			if (JumpFlag == false) {
				playerObj->PlayAnimation(1);
			}

		}
		else {
			playerObj->Stop();
		}
	
	//if (JumpFlag == true) {
	//	playerObj->PlayAnimation(0);
	//}

	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);

	playerObj->Update();
	//��]��Ǐ]��������
}

void Player::Ball()
{
#pragma region �J�����Ǐ]�Ƃقړ���
	XMVECTOR v0 = { 0,0,15,0 };
	//angle���W�A������y���܂��ɉ�]�B���a��-100
	XMMATRIX rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(sphereAngle.m128_f32[1]));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR bossTarget = { playerPos.x,playerPos.y,playerPos.z };
	XMVECTOR v3 = bossTarget + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	////�W�����v�����Ȃ�������Y���̒Ǐ]������
	if (JumpFlag == false) {
		spherePos.y = f.y + 4;
	}
	//if (moveFlag == false) {
	spherePos.x = f.x;
	spherePos.z = f.z;
	//}

#pragma endregion
}

void Player::Jump()
{
	// ��������
	if (!onGround) {
		// �����������x
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// ����
		fallV.m128_f32[1] = max(fallV.m128_f32[1] + fallAcc, fallVYMin);
		// �ړ�
		playerPos.x += fallV.m128_f32[0];
		playerPos.y += fallV.m128_f32[1];
		playerPos.z += fallV.m128_f32[2];
	}
	//�W�����v����
	else if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		onGround = false;
		JumpFlag = true;
		const float jumpVYFist = 1.0f;
		fallV = { 0, jumpVYFist, 0, 0 };
	}
	playerObj->UpdateWorldMatrix();
	playerObj->GetCollider()->Update();
	SphereColliderFbx* sphereCollider = dynamic_cast<SphereColliderFbx*>(playerObj->GetCollider());
	assert(sphereCollider);
	SphereCollider* sphereCollider2 = dynamic_cast<SphereCollider*>(SphereObj->GetCollider());
	assert(sphereCollider2);
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
			const float threshold = cosf(XMConvertToRadians(60.0f));

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
	// ���ƒn�`�̌�����S����

	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_LANDSHAPE);
	
	// �����ɂ��r�˕�������
	playerPos.x += callback.move.m128_f32[0];
	playerPos.y += callback.move.m128_f32[1];
	playerPos.z += callback.move.m128_f32[2];
	// �����ɂ��r�˕�������
	spherePos.x += callback.move.m128_f32[0];
	spherePos.y += callback.move.m128_f32[1];
	spherePos.z += callback.move.m128_f32[2];


	PlayerQueryCallback callback2(sphereCollider2);
	// ���ƒn�`�̌�����S����
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider2, &callback2, COLLISION_ATTR_LANDSHAPE);
	
	for (int i = 0; i < OBJNumber; i++) {
		if (colFlag[i] == true) {
			CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISION_ATTR_OBJECT);
			CollisionManager::GetInstance()->QuerySphere(*sphereCollider2, &callback2, COLLISION_ATTR_OBJECT);
		}
	}

	// �����ɂ��r�˕�������
	playerPos.x += callback2.move.m128_f32[0];
	playerPos.y += callback2.move.m128_f32[1];
	playerPos.z += callback2.move.m128_f32[2];
	spherePos.x += callback2.move.m128_f32[0];
	spherePos.y += callback2.move.m128_f32[1];
	spherePos.z += callback2.move.m128_f32[2];


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
			playerPos.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
		}
		// �n�ʂ��Ȃ��̂ŗ���
		else {
			onGround = false;
			fallV = {};
		}
	}
	// �������
	else if (fallV.m128_f32[1] <= 0.0f) {
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f)) {
			// ���n
			onGround = true;
			playerPos.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
		}
	}

	//// ���̏�[���狅�̉��[�܂ł̃��C�L���X�g
	//Ray ray2;
	//ray2.start = sphereCollider2->center;
	//ray2.start.m128_f32[1] += sphereCollider2->GetRadius();
	//ray2.dir = { 0,-1.0,0,0 };
	//RaycastHit raycastHit2;
	//// �ڒn���
	//if (onGround2) {
	//	// �X���[�Y�ɍ������ׂ̋z������
	//	const float adsDistance2 = 0.2f;
	//	// �ڒn���ێ�
	//	if (CollisionManager::GetInstance()->Raycast(ray2, COLLISION_ATTR_LANDSHAPE, &raycastHit2, sphereCollider2->GetRadius() * 2.0f + adsDistance2)) {
	//		onGround2 = true;
	//		//���̏������L�������-nan(ind)���ďo�ĉ�ʂ�OBJ���\������Ȃ�
	//		//��������(Update�̏��Ԃ���������)
	//		spherePos.y -= (raycastHit2.distance - sphereCollider2->GetRadius() * 2.0f);
	//		SphereObj->SetPosition(spherePos);
	//		SphereObj->Update();
	//	}
	//	// �n�ʂ��Ȃ��̂ŗ���
	//	else {
	//		onGround2 = false;
	//		fallV2 = {};
	//	}
	//}
	//// �������
	//else if (fallV2.m128_f32[1] <= 0.0f) {
	//	if (CollisionManager::GetInstance()->Raycast(ray2, COLLISION_ATTR_LANDSHAPE, &raycastHit2, sphereCollider2->GetRadius() * 2.0f)) {
	//		// ���n
	//		onGround2 = true;
	//		spherePos.y -= (raycastHit2.distance - sphereCollider2->GetRadius() * 2.0f);
	//		SphereObj->SetPosition(spherePos);
	//		SphereObj->Update();
	//	}
	//}
	//SphereObj->Update();
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
	if (Input::GetInstance()->TriggerKey(DIK_UPARROW) && Input::GetInstance()->PushKey(DIK_W) && dashFlag == false)
	{
		dashTime = dashTimeMax;
		fade = 1;
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
		XMVECTOR movedash = { 0,0,1.5,0 };//�_�b�V���p�̈ړ��x�N�g��

		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.y));//y ���𒆐S�ɉ�]����}�g���b�N�X���쐬
		movedash = XMVector3TransformNormal(movedash, matRot);

		playerPos.x += movedash.m128_f32[0];
		playerPos.z += movedash.m128_f32[2];
		spherePos.x += movedash.m128_f32[0];
		spherePos.z += movedash.m128_f32[2];
		if (fade > 0) {
			fade -= 0.05f;
		}
	}

}


void Player::Update()
{
	Move();
	Jump();
	Ball();
	Dash();

	sizeSprite->SetAnchorPoint({ 0.5, 0.5 });

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
	playerSprite->SetSize({ 140,200 });
	playerSprite->SetTextureRect({ 0 + 580 * PlayerWalkCount,0 }, { 580,810 });
}



void Player::Draw()
{
	playerObj->Draw();
	SphereObj->Draw();

}

void Player::DrawSprite()
{
	sizeSprite->Draw();
	if (dashFlag == true) {
		dashSprite->Draw();
	}
	earthSprite->Draw();
	playerSprite->Draw();
}

void Player::RC()
{
	SphereObj->RemoveCollider();
	playerObj->RemoveCollider();
}
