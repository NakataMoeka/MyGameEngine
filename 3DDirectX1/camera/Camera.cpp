#include "Camera.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "DebugText.h"
using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;

	//ビュー行列の計算
	UpdateViewMatrix();

	// 射影行列の計算
	UpdateProjectionMatrix();

	// ビュープロジェクションの合成
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	if (viewDirty || projectionDirty) {
		// 再計算必要なら
		if (viewDirty) {
			// ビュー行列更新
			UpdateViewMatrix();
			viewDirty = false;
		}

		// 再計算必要なら
		if (projectionDirty) {
			// ビュー行列更新
			UpdateProjectionMatrix();
			projectionDirty = false;
		}
		// ビュープロジェクションの合成
		matViewProjection = matView * matProjection;
	}
}

void Camera::FollowCamera(XMFLOAT3 position, XMFLOAT3 d, float angleX, float angleY)
{
	XMVECTOR v0 = { d.x,d.y,d.z };
	//angleラジアンだけy軸まわりに回転。半径は-100
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
	// 視点座標
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	// 注視点座標
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	// （仮の）上方向
	XMVECTOR upVector = XMLoadFloat3(&up);

	// カメラZ軸（視線方向）
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	// 0ベクトルだと向きが定まらないので除外
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	// ベクトルを正規化
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	// カメラのX軸（右方向）
	XMVECTOR cameraAxisX;
	// X軸は上方向→Z軸の外積で求まる
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	// ベクトルを正規化
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	// カメラのY軸（上方向）
	XMVECTOR cameraAxisY;
	// Y軸はZ軸→X軸の外積で求まる
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);

	// ここまでで直交した3方向のベクトルが揃う
	//（ワールド座標系でのカメラの右方向、上方向、前方向）	

	// カメラ回転行列
	XMMATRIX matCameraRot;
	// カメラ座標系→ワールド座標系の変換行列
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
	// 転置により逆行列（逆回転）を計算
	matView = XMMatrixTranspose(matCameraRot);

	// 視点座標に-1を掛けた座標
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	// カメラの位置からワールド原点へのベクトル（カメラ座標系）
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);	// X成分
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);	// Y成分
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);	// Z成分
	// 一つのベクトルにまとめる
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	// ビュー行列に平行移動成分を設定
	matView.r[3] = translation;

#pragma region 全方向ビルボード行列の計算
	// ビルボード行列
	matBillboard.r[0] = cameraAxisX;
	matBillboard.r[1] = cameraAxisY;
	matBillboard.r[2] = cameraAxisZ;
	matBillboard.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma region

#pragma region Y軸回りビルボード行列の計算
	// カメラX軸、Y軸、Z軸
	XMVECTOR ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;

	// X軸は共通
	ybillCameraAxisX = cameraAxisX;
	// Y軸はワールド座標系のY軸
	ybillCameraAxisY = XMVector3Normalize(upVector);
	// Z軸はX軸→Y軸の外積で求まる
	ybillCameraAxisZ = XMVector3Cross(ybillCameraAxisX, ybillCameraAxisY);

	// Y軸回りビルボード行列
	matBillboardY.r[0] = ybillCameraAxisX;
	matBillboardY.r[1] = ybillCameraAxisY;
	matBillboardY.r[2] = ybillCameraAxisZ;
	matBillboardY.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma endregion
}

void Camera::UpdateProjectionMatrix()
{
	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		aspectRatio,
		0.1f, 1000.0f
	);
}

void Camera::CameraCollision(XMFLOAT3 position, XMFLOAT3 angle)
{

	//sphere.radius = 1;
	//sphere.center = XMVectorSet(eye.x, eye.y, eye.z, 1);
	//class PlayerQueryCallback : public QueryCallback
	//{
	//public:
	//	PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};
	//	bool QcolFlag = false;
	//	// 衝突時コールバック関数
	//	bool OnQueryHit(const QueryHit& info) {

	//		const XMVECTOR up = { 0,1,0,0 };

	//		XMVECTOR rejectDir = XMVector3Normalize(info.reject);
	//		float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

	//		// 地面判定しきい値
	//		const float threshold = cosf(XMConvertToRadians(30.0f));

	//		if (-threshold < cos && cos < threshold) {
	//			sphere->center += info.reject;
	//			move += info.reject;
	//			QcolFlag = true;
	//		
	//		}

	//		return true;
	//	}

	//	Sphere* sphere = nullptr;
	//	DirectX::XMVECTOR move = { };
	//};

	//PlayerQueryCallback callback(&sphere);
	//// 球と地形の交差を全検索

	//CollisionManager::GetInstance()->QuerySphere(sphere, &callback, COLLISION_ATTR_LANDSHAPE);

	//// 交差による排斥分動かす
	//eye.x += callback.move.m128_f32[0];
	//eye.y += callback.move.m128_f32[1];
	//eye.z += callback.move.m128_f32[2];
	//if (callback.QcolFlag == true) {
	//	colFlag = true;
	//}
	//else {
	//	colFlag = false;
	//}
	//target = position;
	Ray ray;
	ray.start = { target.x,target.y,target.z ,1 };
	XMVECTOR cd = { eye.x - target.x,eye.y - target.y,eye.z - target.z,0 };
	//XMVECTOR cd = { 0,0,-1,0 };

	cd = XMVector3Normalize(cd);
	ray.dir = cd;
	/*DebugText::GetInstance()->Printf(100, 300, 3.0f, { 1,1,1,1 }, "%f,%f,%f",
		ray.dir.m128_f32[0], ray.dir.m128_f32[1],ray.dir.m128_f32[2]);
	*/RaycastHit raycastHit;
	//DebugText::GetInstance()->Printf(100, 400, 3.0f, { 1,1,1,1 }, "%f,%f,%f",
	//	ray.start.m128_f32[0], ray.start.m128_f32[1], ray.start.m128_f32[2]);
	//
	if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, 5.0f)) {
		distance = raycastHit.distance;
		ccFlag = true;
	}
	else {
		ccFlag = false;
	}
	//if(distance>0&&distance<=9.0f){
	//	ccFlag = true;
	//}
	//else {
	//	ccFlag = false;
	//}
	//DebugText::GetInstance()->Printf(100, 200, 3.0f, { 1,1,1,1 }, "%f", raycastHit.distance);
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
	// 視点座標を移動し、反映
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
	// 視点と注視点座標を移動し、反映
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



