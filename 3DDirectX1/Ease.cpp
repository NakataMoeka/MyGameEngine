#include "Ease.h"
using namespace DirectX;
const  XMFLOAT3 Eas::lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	x = start.x * (1.0f - t) + end.x * t;
	y = start.y * (1.0f - t) + end.y * t;
	z = start.z * (1.0f - t) + end.z * t;

	return XMFLOAT3({ x, y, z });
}
