#include "Ease.h"
using namespace DirectX;

//t‚ÍŠÔ‚Å‚Í‚È‚­ŠÔ‚ÌŠ„‡


const XMFLOAT2 Eas::lerp(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	XMFLOAT2 num;

	num.x = start.x * (1.0f - t) + end.x * t;
	num.y = start.y * (1.0f - t) + end.y * t;


	return num;
}


const  XMFLOAT3 Eas::lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	XMFLOAT3 num;

	num.x = start.x * (1.0f - t) + end.x * t;
	num.y = start.y * (1.0f - t) + end.y * t;
	num.z = start.z * (1.0f - t) + end.z * t;

	return num;
}
const XMFLOAT2 Eas::easeIn(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	XMFLOAT2 num;

	//t*t‚ğ

	num.x = start.x * (1.0f - t * t) + end.x * (t * t);
	num.y = start.y * (1.0f - t * t) + end.y * (t * t);
	return num;
}
const XMFLOAT3 Eas::easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	XMFLOAT3 num;

	//t*t‚ğ

	num.x = start.x * (1.0f - t * t) + end.x * (t * t);
	num.y = start.y * (1.0f - t * t) + end.y * (t * t);
	num.z = start.z * (1.0f - t * t) + end.z * (t * t);

	return num;
}

const XMFLOAT2 Eas::easeOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	XMFLOAT2 num;
	num.x = start.x * (1.0f - (t * (2 - t))) + end.x * (t * (2 - t));
	num.y = start.y * (1.0f - (t * (2 - t))) + end.y * (t * (2 - t));
	return num;
}

const XMFLOAT3 Eas::easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	XMFLOAT3 num;

	num.x = start.x * (1.0f - (t * (2 - t))) + end.x * (t * (2 - t));
	num.y = start.y * (1.0f - (t * (2 - t))) + end.y * (t * (2 - t));
	num.z = start.z * (1.0f - (t * (2 - t))) + end.z * (t * (2 - t));
	return num;
}

const XMFLOAT2 Eas::easeInOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t)
{
	XMFLOAT2 num;
	num.x = start.x * (1.0f - (t * t * (3 - 2 * t))) + end.x * (t * t * (3 - 2 * t));
	num.y = start.y * (1.0f - (t * t * (3 - 2 * t))) + end.y * (t * t * (3 - 2 * t));
	return num;
}

const XMFLOAT3 Eas::easeInOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t)
{
	XMFLOAT3 num;

	num.x = start.x * (1.0f - (t * t * (3 - 2 * t))) + end.x * (t * t * (3 - 2 * t));
	num.y = start.y * (1.0f - (t * t * (3 - 2 * t))) + end.y * (t * t * (3 - 2 * t));
	num.z = start.z * (1.0f - (t * t * (3 - 2 * t))) + end.z * (t * t * (3 - 2 * t));
	return num;
}

float Eas::easeInCubic(float x)
{
	return x * x * x;
}

float Eas::easeOutCubic(float x)
{
	return 1 - pow(1 - x, 3);
}

float Eas::easeInQuad(float x)
{
	return x * x;
}

float Eas::easeOutQuad(float x)
{
	return 1 - (1 - x) * (1 - x);
}

float Eas::easeOutBounce(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}

float Eas::easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float Eas::ease(const float& start, const float& end, float t, float d, int i)
{
	float x = t / d;
	float subtraction = end - start;
	float num{};
	float v = 0;
	if (i == 1) { v = easeInCubic(x); }
	if (i == 2) { v = easeOutCubic(x); }
	if (i == 3) { v = easeInQuad(x); }
	if (i == 4) { v = easeOutQuad(x); }
	if (i == 5) { v = easeOutBounce(x); }
	if (i == 6) { v = easeInBounce(x); }
	num = subtraction * v + start;
	return num;
}

XMFLOAT2 Eas::ease(const XMFLOAT2& start, const XMFLOAT2& end, float t, float d, int i)
{
	float x = t / d;
	XMFLOAT2 subtraction = { end.x - start.x,end.y - start.y };
	XMFLOAT2 num{};
	float v = 0;
	if (i == 1) { v = easeInCubic(x); }
	if (i == 2) { v = easeOutCubic(x); }
	if (i == 3) { v = easeInQuad(x); }
	if (i == 4) { v = easeOutQuad(x); }
	if (i == 5) { v = easeOutBounce(x); }
	num.x = subtraction.x * t + start.x;
	num.y = subtraction.y * v + start.y;
	return num;
}

XMFLOAT3 Eas::ease(const XMFLOAT3& start, const XMFLOAT3& end, float t, float d, int i)
{
	float x = t / d;
	XMFLOAT3 subtraction = { end.x - start.x,end.y - start.y,end.z - start.z };
	XMFLOAT3 num{};
	float v = 0;
	if (i == 1) { v = easeInCubic(x); }
	if (i == 2) { v = easeOutCubic(x); }
	if (i == 3) { v = easeInQuad(x); }
	if (i == 4) { v = easeOutQuad(x); }
	if (i == 5) { v = easeOutBounce(x); }
	if (i == 6) { v = easeInBounce(x); }
	num.x = subtraction.x * v + start.x;
	num.y = subtraction.y * v + start.y;
	num.z = subtraction.z * v + start.z;
	return num;
}



