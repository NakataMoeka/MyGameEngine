#include"Collision.h"
using namespace DirectX;

void Collision::ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point, const Triangle& triangle, DirectX::XMVECTOR* closest)
{
	// pointがp0の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	XMVECTOR p0_p2 = triangle.p2 - triangle.p0;
	XMVECTOR p0_pt = point - triangle.p0;

	float d1 = XMVector3Dot(p0_p1, p0_pt).m128_f32[0];
	float d2 = XMVector3Dot(p0_p2, p0_pt).m128_f32[0];

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0が最近傍
		*closest = triangle.p0;
		return;
	}

	// pointがp1の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p1_pt = point - triangle.p1;

	float d3 = XMVector3Dot(p0_p1, p1_pt).m128_f32[0];
	float d4 = XMVector3Dot(p0_p2, p1_pt).m128_f32[0];

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1が最近傍
		*closest = triangle.p1;
		return;
	}

	// pointがp0_p1の辺領域の中にあるかどうかチェックし、あればpointのp0_p1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// pointがp2の外側の頂点領域の中にあるかどうかチェック
	XMVECTOR p2_pt = point - triangle.p2;

	float d5 = XMVector3Dot(p0_p1, p2_pt).m128_f32[0];
	float d6 = XMVector3Dot(p0_p2, p2_pt).m128_f32[0];
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// pointがp0_p2の辺領域の中にあるかどうかチェックし、あればpointのp0_p2上に対する射影を返す
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// pointがp1_p2の辺領域の中にあるかどうかチェックし、あればpointのp1_p2上に対する射影を返す
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	// pointは面領域の中にある。closestを重心座標を用いて計算する
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Sphere2(const Sphere& sphereA, const Sphere& sphereB, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
	// 中心点の距離の２乗 <= 半径の和の２乗　なら交差
	float dist = XMVector3LengthSq(sphereA.center - sphereB.center).m128_f32[0];

	float radius2 = sphereA.radius + sphereB.radius;
	radius2 *= radius2;

	if (dist <= radius2) {
		if (inter) {
			// Aの半径が0の時座標はBの中心　Bの半径が0の時座標はAの中心　となるよう補完
			float t = sphereB.radius / (sphereA.radius + sphereB.radius);
			*inter = XMVectorLerp(sphereA.center, sphereB.center, t);
		}
		// 押し出すベクトルを計算
		if (reject) {
			float rejectLen = sphereA.radius + sphereB.radius - sqrtf(dist);
			*reject = XMVector3Normalize(sphereA.center - sphereB.center);
			*reject *= rejectLen;
		}
		return true;
	}

	return false;
}

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR* inter)
{
	// 座標系の原点から球の中心座標への距離から
	// 平面の原点距離を減算することで、平面と球の中心との距離が出る
	float dist = XMVector3Dot(sphere.center, plane.normal).m128_f32[0] - plane.distance;
	// 距離の絶対値が半径より大きければ当たっていない
	if (fabsf(dist) > sphere.radius)	return false;

	// 擬似交点を計算
	if (inter)
	{
		// 平面上の再接近点を、疑似交点とする
		*inter = -dist * plane.normal + sphere.center;                                                                                              +sphere.center;
	}

	return true;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, DirectX::XMVECTOR* inter, DirectX::XMVECTOR* reject)
{
	XMVECTOR p;
	// 球の中心に対する最近接点である三角形上にある点pを見つける
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);
	// 点pと球の中心の差分ベクトル
	XMVECTOR v = p - sphere.center;
	// 距離の二乗を求める
	//（同じベクトル同士の内積は三平方の定理のルート内部の式と一致する）
	float distanceSquare = XMVector3Dot(v, v).m128_f32[0];
	// 球と三角形の距離が半径以下なら当たっていない
	if (distanceSquare > sphere.radius * sphere.radius)	return false;
	// 擬似交点を計算
	if (inter) {
		// 三角形上の最近接点pを疑似交点とする
		*inter = p;
	}
	// 押し出すベクトルを計算
	if (reject) {
		float ds = XMVector3Dot(sphere.center, triangle.normal).m128_f32[0];
		float dt = XMVector3Dot(triangle.p0, triangle.normal).m128_f32[0];
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}
	return true;
}

bool Collision::CheckRay2Plane(const Ray& lay, const Plane& plane, float* distance, DirectX::XMVECTOR* inter)
{
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値

	float d1 = XMVector3Dot(plane.normal, lay.dir).m128_f32[0];
	// 裏面には当たらない
	if (d1 > -epsilon) {
		return false;
	}

	float d2 = XMVector3Dot(plane.normal, lay.start).m128_f32[0];
	float t = (plane.distance - d2) / d1;

	if (t < 0) return false;

	// 距離を書き込む
	if (distance) {
		*distance = t;
	}

	// 交点を計算
	if (inter) {
		*inter = lay.start + t * lay.dir;
	}

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& lay, const Triangle& triangle, float* distance, DirectX::XMVECTOR* inter)
{
	// 三角形が乗っている平面を算出
	Plane plane;
	XMVECTOR interPlane;
	plane.normal = triangle.normal;
	plane.distance = XMVector3Dot(triangle.normal, triangle.p0).m128_f32[0];
	// レイと平面が当たっていなければ、当たっていない	
	if (!CheckRay2Plane(lay, plane, distance, &interPlane)) {
		return false;
	}
	// レイと平面が当たっていたので、距離と交点が書き込まれた

	// レイと平面の交点が三角形の内側にあるか判定
	const float epsilon = 1.0e-5f;	// 誤差吸収用の微小な値
	XMVECTOR m;
	// 辺p0_p1について
	XMVECTOR pt_p0 = triangle.p0 - interPlane;
	XMVECTOR p0_p1 = triangle.p1 - triangle.p0;
	m = XMVector3Cross(pt_p0, p0_p1);
	// 辺の外側
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	// 辺p1_p2について
	XMVECTOR pt_p1 = triangle.p1 - interPlane;
	XMVECTOR p1_p2 = triangle.p2 - triangle.p1;
	m = XMVector3Cross(pt_p1, p1_p2);
	// 辺の外側
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	// 辺p2_p0について
	XMVECTOR pt_p2 = triangle.p2 - interPlane;
	XMVECTOR p2_p0 = triangle.p0 - triangle.p2;
	m = XMVector3Cross(pt_p2, p2_p0);
	// 辺の外側
	if (XMVector3Dot(m, triangle.normal).m128_f32[0] < -epsilon) {
		return false;
	}

	if (inter) {
		*inter = interPlane;
	}

	// 内側なので、当たっている
	return true;
}

bool Collision::CheckRay2Sphere(const Ray& lay, const Sphere& sphere, float* distance, DirectX::XMVECTOR* inter)
{
	XMVECTOR m = lay.start - sphere.center;
	float b = XMVector3Dot(m, lay.dir).m128_f32[0];
	float c = XMVector3Dot(m, m).m128_f32[0] - sphere.radius * sphere.radius;
	// layの始点がsphereの外側にあり(c > 0)、layがsphereから離れていく方向を
	// 差している場合(b > 0)、当たらない
	if (c > 0.0f && b > 0.0f) {
		return false;
	}

	float discr = b * b - c;
	// 負の判別式はレイが球を外れていることに一致
	if (discr < 0.0f) {
		return false;
	}

	// レイは球と交差している。
	// 交差する最小の値tを計算
	float t = -b - sqrtf(discr);
	// tが負である場合、レイは球の内側から開始しているのでtをゼロにクランプ
	if (t < 0) t = 0.0f;

	if (distance) {
		*distance = t;
	}

	if (inter) {
		*inter = lay.start + t * lay.dir;
	}

	return true;
}


	//球と球の当たり判定
	bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
	{
		//２つの球の中心座標を結ぶベクトルを求める
		XMVECTOR vec = sphereA.center - sphereB.center;

		//ベクトルの長さの２乗（２点間の距離の２乗）を求める
		float sqLength = vec.m128_f32[0] * vec.m128_f32[0] + vec.m128_f32[1] * vec.m128_f32[1] + vec.m128_f32[2] * vec.m128_f32[2];

		//2つの球の半径の合計を求める
		float r = sphereA.radius + sphereB.radius;

		//２点間の距離の２乗＜半径の合計の２乗なら２つの球は交差している
		return  sqLength < r* r;
	}


	bool Collision::CheckSphere2Box(const Sphere& sphere, const Box& box)
	{
		float sqDistance = 0.0f;
		float pos;

		pos = sphere.center.m128_f32[0];
		if (pos < box.minPosition.m128_f32[0])
		{
			sqDistance += (box.minPosition.m128_f32[0] - pos) * (box.minPosition.m128_f32[0] - pos);
		}
		else if (pos > box.maxPosition.m128_f32[0])
		{
			sqDistance += (box.maxPosition.m128_f32[0] - pos) * (box.maxPosition.m128_f32[0] - pos);
		}

		//y軸方向の距離の２乗を加算
		pos = sphere.center.m128_f32[1];
		if (pos < box.minPosition.m128_f32[1])
		{
			sqDistance += (box.minPosition.m128_f32[1] - pos) * (box.minPosition.m128_f32[1] - pos);
		}
		else if (pos > box.maxPosition.m128_f32[1])
		{
			sqDistance += (box.maxPosition.m128_f32[1] - pos) * (box.maxPosition.m128_f32[1] - pos);
		}
		pos = sphere.center.m128_f32[2];
		//z軸方向の距離の２乗を加算
		if (pos < box.minPosition.m128_f32[2])
		{
			sqDistance += (box.minPosition.m128_f32[2] - pos) * (box.minPosition.m128_f32[2] - pos);
		}
		else if (pos > box.maxPosition.m128_f32[2])
		{
			sqDistance += (box.maxPosition.m128_f32[2] - pos) * (box.maxPosition.m128_f32[2] - pos);
		}

		return sqDistance < sphere.radius* sphere.radius;
	}

	bool Collision::CheckSphere2OBB(Sphere& sphere, OBB& obb)
	{
		XMVECTOR Vec{ 0, 0, 0,0 };   // 最終的に長さを求めるベクトル

 // 各軸についてはみ出た部分のベクトルを算出
		for (int i = 0; i < 3; i++)
		{
			float L = obb.GetLen_W(i);
			if (L <= 0) continue;  // L=0は計算できない
			float s = ((sphere.center.m128_f32[0] - obb.GetPos_W().m128_f32[0]) * obb.GetDirect(i).m128_f32[0]) + ((sphere.center.m128_f32[1] - obb.GetPos_W().m128_f32[1]) * obb.GetDirect(i).m128_f32[1]) + ((sphere.center.m128_f32[2] - obb.GetPos_W().m128_f32[2]) * obb.GetDirect(i).m128_f32[2]) / L;

			// sの値から、はみ出した部分があればそのベクトルを加算
			s = fabsf(s);
			if (s > 1)
				Vec += (1 - s) * L * obb.GetDirect(i);   // はみ出した部分のベクトル算出
		}

		float length = (Vec.m128_f32[0] * Vec.m128_f32[0]) + (Vec.m128_f32[1] * Vec.m128_f32[1]) + (Vec.m128_f32[2] * Vec.m128_f32[2]);   // 長さを出力
		return length < sphere.radius* sphere.radius;
	}

	bool Collision::CheckOBB2OBB(OBB& obbA, OBB& obbB)
	{
		// 各方向ベクトルの確保
		// （N***:標準化方向ベクトル）
		XMVECTOR NAe1 = obbA.GetDirect(0), Ae1 = NAe1 * obbA.GetLen_W(0);
		XMVECTOR NAe2 = obbA.GetDirect(1), Ae2 = NAe2 * obbA.GetLen_W(1);
		XMVECTOR NAe3 = obbA.GetDirect(2), Ae3 = NAe3 * obbA.GetLen_W(2);
		XMVECTOR NBe1 = obbB.GetDirect(0), Be1 = NBe1 * obbB.GetLen_W(0);
		XMVECTOR NBe2 = obbB.GetDirect(1), Be2 = NBe2 * obbB.GetLen_W(1);
		XMVECTOR NBe3 = obbB.GetDirect(2), Be3 = NBe3 * obbB.GetLen_W(2);
		XMVECTOR Interval = obbA.GetPos_W() - obbB.GetPos_W();

		// 分離軸 : Ae1
		float rA = sqrtf((Ae1.m128_f32[0] * Ae1.m128_f32[0]) + (Ae1.m128_f32[1] * Ae1.m128_f32[1]) + (Ae1.m128_f32[2] * Ae1.m128_f32[2]));
		float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
		float L = fabsf((Interval.m128_f32[0] * NAe1.m128_f32[0]) + (Interval.m128_f32[1] * NAe1.m128_f32[1]) + (Interval.m128_f32[2] * NAe1.m128_f32[2]));
		if (L > rA + rB)
			return false; // 衝突していない

		// 分離軸 : Ae2
		rA = sqrtf((Ae2.m128_f32[0] * Ae2.m128_f32[0]) + (Ae2.m128_f32[1] * Ae2.m128_f32[1]) + (Ae2.m128_f32[2] * Ae2.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
		L = fabsf((Interval.m128_f32[0] * NAe2.m128_f32[0]) + (Interval.m128_f32[1] * NAe2.m128_f32[1]) + (Interval.m128_f32[2] * NAe2.m128_f32[2]));
		if (L > rA + rB)
			return false; // 衝突していない

		// 分離軸 : Ae3
		rA = sqrtf((Ae3.m128_f32[0] * Ae3.m128_f32[0]) + (Ae3.m128_f32[1] * Ae3.m128_f32[1]) + (Ae3.m128_f32[2] * Ae3.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
		L = fabsf((Interval.m128_f32[0] * NAe3.m128_f32[0]) + (Interval.m128_f32[1] * NAe3.m128_f32[1]) + (Interval.m128_f32[2] * NAe3.m128_f32[2]));
		if (L > rA + rB)
			return false; // 衝突していない

		// 分離軸 : Be1
		rA = sqrtf((Be1.m128_f32[0] * Be1.m128_f32[0]) + (Be1.m128_f32[1] * Be1.m128_f32[1]) + (Be1.m128_f32[2] * Be1.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&Be1, &Ae1, &Ae2, &Ae3);
		L = fabsf((Interval.m128_f32[0] * Be1.m128_f32[0]) + (Interval.m128_f32[1] * Be1.m128_f32[1]) + (Interval.m128_f32[2] * Be1.m128_f32[2]));
		if (L > rA + rB)
			return false; // 衝突していない

		// 分離軸 : Be2
		rA = sqrtf((Be2.m128_f32[0] * Be2.m128_f32[0]) + (Be2.m128_f32[1] * Be2.m128_f32[1]) + (Be2.m128_f32[2] * Be2.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&Be2, &Ae1, &Ae2, &Ae3);
		L = fabsf((Interval.m128_f32[0] * Be2.m128_f32[0]) + (Interval.m128_f32[1] * Be2.m128_f32[1]) + (Interval.m128_f32[2] * Be2.m128_f32[2]));
		if (L > rA + rB)
			return false; // 衝突していない

		// 分離軸 : Be3
		rA = sqrtf((Be3.m128_f32[0] * Be3.m128_f32[0]) + (Be3.m128_f32[1] * Be3.m128_f32[1]) + (Be3.m128_f32[2] * Be3.m128_f32[2]));
		rB = LenSegOnSeparateAxis(&Be3, &Ae1, &Ae2, &Ae3);
		L = fabsf((Interval.m128_f32[0] * Be3.m128_f32[0]) + (Interval.m128_f32[1] * Be3.m128_f32[1]) + (Interval.m128_f32[2] * Be3.m128_f32[2]));
		if (L > rA + rB)
			return false; // 衝突していない

		// 分離軸 : C11
		XMVECTOR Cross;
		Cross=XMVector3Cross( NAe1, NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C12
		Cross = XMVector3Cross(NAe1, NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C13
		Cross = XMVector3Cross(NAe1, NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C21
		Cross = XMVector3Cross(NAe2, NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C22
		Cross = XMVector3Cross(NAe2, NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C23
		Cross = XMVector3Cross(NAe2, NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C31
		Cross = XMVector3Cross(NAe3, NBe1);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C32
		Cross = XMVector3Cross(NAe3, NBe2);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離軸 : C33
		Cross = XMVector3Cross(NAe3, NBe3);
		rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
		rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
		L = fabsf((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
		if (L > rA + rB)
			return false;

		// 分離平面が存在しないので「衝突している」
		return true;
	}

	float Collision::LenSegOnSeparateAxis(DirectX::XMVECTOR* Sep, DirectX::XMVECTOR* e1, DirectX::XMVECTOR* e2, DirectX::XMVECTOR* e3)
	{
		// 3つの内積の絶対値の和で投影線分長を計算
		// 分離軸Sepは標準化されていること
	
		float fr1 = fabsf((Sep->m128_f32[0] * e1->m128_f32[0]) + (Sep->m128_f32[1] * e1->m128_f32[1]) + (Sep->m128_f32[2] * e1->m128_f32[2]));
		
		float fr2 = fabsf((Sep->m128_f32[0] * e2->m128_f32[0]) + (Sep->m128_f32[1] * e2->m128_f32[1]) + (Sep->m128_f32[2] * e2->m128_f32[2]));
		
		float fr3 = e3 ? (fabsf((Sep->m128_f32[0] * e3->m128_f32[0]) + (Sep->m128_f32[1] * e3->m128_f32[1]) + (Sep->m128_f32[2] * e3->m128_f32[2]))) : 0;
		return fr1 + fr2 + fr3;
	}



	
