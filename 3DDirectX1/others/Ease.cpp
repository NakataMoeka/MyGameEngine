#include "Ease.h"
using namespace DirectX;

//t‚ÍŠÔ‚Å‚Í‚È‚­ŠÔ‚ÌŠ„‡

const XMFLOAT2 Eas::lerp(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	float x, y = 0;

	x = start.x * (1.0f - t) + end.x * t;
	y = start.y * (1.0f - t) + end.y * t;


	return XMFLOAT2({ x, y });
}


const  XMFLOAT3 Eas::lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	x = start.x * (1.0f - t) + end.x * t;
	y = start.y * (1.0f - t) + end.y * t;
	z = start.z * (1.0f - t) + end.z * t;

	return XMFLOAT3({ x, y, z });
}
const XMFLOAT2 Eas::easeIn(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	float x, y = 0;

	//t*t‚ğ

	x = start.x * (1.0f - t * t) + end.x * (t * t);
	y = start.y * (1.0f - t * t) + end.y * (t * t);
	return XMFLOAT2({ x, y });
}
const XMFLOAT3 Eas::easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	//t*t‚ğ

	x = start.x * (1.0f - t * t) + end.x * (t * t);
	y = start.y * (1.0f - t * t) + end.y * (t * t);
	z = start.z * (1.0f - t * t) + end.z * (t * t);

	return XMFLOAT3({ x, y, z });
}