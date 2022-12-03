#include "Camera.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "DebugText.h"
using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;

	//�r���[�s��̌v�Z
	UpdateViewMatrix();

	// �ˉe�s��̌v�Z
	UpdateProjectionMatrix();

	// �r���[�v���W�F�N�V�����̍���
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	if (viewDirty || projectionDirty) {
		// �Čv�Z�K�v�Ȃ�
		if (viewDirty) {
			// �r���[�s��X�V
			UpdateViewMatrix();
			viewDirty = false;
		}

		// �Čv�Z�K�v�Ȃ�
		if (projectionDirty) {
			// �r���[�s��X�V
			UpdateProjectionMatrix();
			projectionDirty = false;
		}
		// �r���[�v���W�F�N�V�����̍���
		matViewProjection = matView * matProjection;
	}
}

void Camera::FollowCamera(XMFLOAT3 position, XMFLOAT3 d, float angleX, float angleY)
{
	XMVECTOR v0 = { d.x,d.y,d.z };
	//angle���W�A������y���܂��ɉ�]�B���a��-100
	XMMATRIX rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleY));
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleX));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR PTarget = { position.x,position.y,position.z };
	XMVECTOR v3 = PTarget + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	FTarget = { PTarget.m128_f32[0], PTarget.m128_f32[1],PTarget.m128_f32[2] };
	FEye = f;
	SetEye(FEye);
	SetTarget(FTarget);

}



void Camera::UpdateViewMatrix()

{
	// �r���[�s��̍X�V
	//matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	XMVECTOR upVector = XMLoadFloat3(&up);
	//�J����Z��
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	//0�x�N�g�����ƌ�������܂�Ȃ��̂ŏ��O
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	//�x�N�g���𐳋K��
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);
	//�J����X��
	XMVECTOR cameraAxisX;
	//X���͏������Z���̊O�ςŋ��܂�
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	//�x�N�g���𐳋K��
	cameraAxisX = XMVector3Normalize(cameraAxisX);
	//�J����Y��(�����)
	XMVECTOR cameraAxisY;
	//Y����Z����X���̊O�ςŋ��܂�
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
	//�J������]�s��
	XMMATRIX matCameraRot;
#pragma region �J�������W�n->���[���h���W�n�̕ϊ��s��
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma endregion
	//�]�u�ɂ��t�s��(�t��])���v�Z
	matView = XMMatrixTranspose(matCameraRot);
	//���_���W��-1�����������W
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	//�J�����̈ʒu���烏�[���h�̌��_�ւ̃x�N�g��(�J�������W�n)
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);
	//��̃x�N�g���ɂ܂Ƃ߂�
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	matView.r[3] = translation;
#pragma region �S�����r���{�[�h�s��̌v�Z
	matBillboard.r[0] = cameraAxisX;
	matBillboard.r[1] = cameraAxisY;
	matBillboard.r[2] = cameraAxisZ;
	matBillboard.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma endregion
#pragma region Y�����r���{�[�h�s��̌v�Z
	//�J����X��,Y��,Z��
	XMVECTOR ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;
	//X���͋���
	ybillCameraAxisX = cameraAxisX;
	//Y���̓��[���h���W�n��Y��
	ybillCameraAxisY = XMVector3Normalize(upVector);
	//Z����X����Y���̊O�ςŋ��܂�
	ybillCameraAxisZ = XMVector3Cross(ybillCameraAxisX, ybillCameraAxisY);
	//Y�����r���{�[�h�z��
	matBillboardY.r[0] = ybillCameraAxisX;
	matBillboardY.r[1] = ybillCameraAxisY;
	matBillboardY.r[2] = ybillCameraAxisZ;
	matBillboardY.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma endregion 
}

void Camera::UpdateProjectionMatrix()
{
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		aspectRatio,
		0.1f, 1000.0f
	);
}

void Camera::CameraCollision()
{
	sphere.radius = 10;
	sphere.center = XMVectorSet(eye.x, eye.y, eye.z, 1);
	class PlayerQueryCallback : public QueryCallback
	{
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};
		bool QcolFlag = false;
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
				DebugText::GetInstance()->Printf(100, 40, 3.0f, { 1,1,1,1 }, "OP");
				QcolFlag = true;
			}

			return true;
		}

		Sphere* sphere = nullptr;
		DirectX::XMVECTOR move = { };
	};

	PlayerQueryCallback callback(&sphere);
	// ���ƒn�`�̌�����S����

	CollisionManager::GetInstance()->QuerySphere(sphere, &callback, COLLISION_ATTR_LANDSHAPE);

	// �����ɂ��r�˕�������
	eye.x += callback.move.m128_f32[0];
	eye.y += callback.move.m128_f32[1];
	eye.z += callback.move.m128_f32[2];
	if (callback.QcolFlag == true) {
		colFlag = true;
	}
	else {
		colFlag = false;
	}
}

void Camera::SetCameraCollider()
{
	colFlag = false;
	sphere.radius = 10;
	sphere.center = XMVectorSet(eye.x, eye.y, eye.z, 1);
}

void Camera::MoveEyeVector(const XMFLOAT3& move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);

}

void Camera::MoveEyeVector(const XMVECTOR& move)
{
	// ���_���W���ړ����A���f
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.m128_f32[0];
	eye_moved.y += move.m128_f32[1];
	eye_moved.z += move.m128_f32[2];

	SetEye(eye_moved);
}

void Camera::MoveVector(const XMFLOAT3& move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}


void Camera::MoveVector(const XMVECTOR& move)
{
	// ���_�ƒ����_���W���ړ����A���f
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.m128_f32[0];
	eye_moved.y += move.m128_f32[1];
	eye_moved.z += move.m128_f32[2];

	target_moved.x += move.m128_f32[0];
	target_moved.y += move.m128_f32[1];
	target_moved.z += move.m128_f32[2];

	SetEye(eye_moved);
	SetTarget(target_moved);
}

