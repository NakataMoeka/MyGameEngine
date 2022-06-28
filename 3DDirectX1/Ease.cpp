#include "Ease.h"
using namespace DirectX;

//tÇÕéûä‘Ç≈ÇÕÇ»Ç≠éûä‘ÇÃäÑçá

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

	//t*tÇ

	x = start.x * (1.0f - t * t) + end.x * (t * t);
	y = start.y * (1.0f - t * t) + end.y * (t * t);
	return XMFLOAT2({ x, y });
}
const XMFLOAT3 Eas::easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	//t*tÇ

	x = start.x * (1.0f - t * t) + end.x * (t * t);
	y = start.y * (1.0f - t * t) + end.y * (t * t);
	z = start.z * (1.0f - t * t) + end.z * (t * t);

	return XMFLOAT3({ x, y, z });
}

const XMFLOAT2 Eas::easeOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	float x, y = 0;
	x = start.x * (1.0f - (t * (2 - t))) + end.x * (t * (2 - t));
	y = start.y * (1.0f - (t * (2 - t))) + end.y * (t * (2 - t));
	return XMFLOAT2({ x,y });
}

const XMFLOAT3 Eas::easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	x = start.x * (1.0f - (t * (2 - t))) + end.x * (t * (2 - t));
	y = start.y * (1.0f - (t * (2 - t))) + end.y * (t * (2 - t));
	z = start.z * (1.0f - (t * (2 - t))) + end.z * (t * (2 - t));
	return XMFLOAT3({x,y,z});
}

const XMFLOAT2 Eas::easeInOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	float x, y = 0;
	x = start.x * (1.0f - (t * t * (3 - 2 * t))) + end.x * (t * t * (3 - 2 * t));
	y = start.y * (1.0f - (t * t * (3 - 2 * t))) + end.y * (t * t * (3 - 2 * t));
	return XMFLOAT2({ x,y });
}

const XMFLOAT3 Eas::easeInOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	x = start.x * (1.0f - (t * t * (3 - 2 * t))) + end.x * (t * t * (3 - 2 * t));
	y = start.y * (1.0f - (t * t * (3 - 2 * t))) + end.y * (t * t * (3 - 2 * t));
	z = start.z * (1.0f - (t * t * (3 - 2 * t))) + end.z * (t * t * (3 - 2 * t));
	return XMFLOAT3({x,y,z});
}

const XMFLOAT2 Eas::easeInCubic(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{

	float x, y = 0;

	//t*tÇ

	x = start.x * (1.0f - t * t * t) + end.x * (t * t * t);
	y = start.y * (1.0f - t * t * t) + end.y * (t * t * t);

	return XMFLOAT2({ x, y });
}


const XMFLOAT3 Eas::easeInCubic(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	float x, y, z = 0;

	//t*tÇ

	x = start.x * (1.0f - t * t * t) + end.x * (t * t * t);
	y = start.y * (1.0f - t * t * t) + end.y * (t * t * t);
	z = start.z * (1.0f - t * t * t) + end.z * (t * t * t);

	return XMFLOAT3({ x, y, z });
}


