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
const XMFLOAT3 Eas::easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	//t*t‚ð

	x = start.x * (1.0f - t * t) + end.x * (t * t);
	y = start.y * (1.0f - t * t) + end.y * (t * t);
	z = start.z * (1.0f - t * t) + end.z * (t * t);

	return XMFLOAT3({ x, y, z });
}