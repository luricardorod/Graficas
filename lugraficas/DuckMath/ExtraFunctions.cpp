#include "ExtraFunctions.h"

float floatRandom()
{
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

int RandomBetween(int minValue, int maxValue)
{
	return rand() % (maxValue - minValue + 1) + minValue;
}

CVector4D Circumcircle(CVector4D & p0, CVector4D & p1, CVector4D & p2, float & radius)
{
	radius = 0.0f;
	float dA, dB, dC, aux1, aux2, aux3, div;

	dA = p0.Dot(p0);
	dB = p1.Dot(p1);
	dC = p2.Dot(p2);

	aux1 = (dA*(p2.z - p1.z) + dB*(p0.z - p2.z) + dC*(p1.z - p0.z));
	aux2 = (dA*(p2.y - p1.y) + dB*(p0.y - p2.y) + dC*(p1.y - p0.y));
	aux3 = -(dA*(p2.x - p1.x) + dB*(p0.x - p2.x) + dC*(p1.x - p0.x));
	div = (2 * (p0.x*(p2.z - p1.z) + p1.x*(p0.z - p2.z) + p2.x*(p1.z - p0.z)));

	if (div == 0.0f)
		return CVector4D(0.0f, 0.0f, 0.0f, 0.0f);

	CVector4D center(aux1, aux2, aux3, div);
	center = center / div;

	radius = (center - p0).Magnitude();

	return center;
}

CVector4D proyectLeftOverDer(CVector4D & thisVec, CVector4D & proyectVect)
{
	CVector4D vecResult = proyectVect*(proyectVect.Dot(thisVec)) / (proyectVect.Dot(proyectVect));
	return vecResult;
}

float Clamp(float min, float max, float value)
{
	if (value > max)
		return max;
	if (value < min)
		return min;
	return value;
}

float lerp(float minValue, float maxValue, float lerpProportion)
{
	return minValue + lerpProportion * (maxValue - minValue);
}

float fade(float t)
{
	// 6t^5 - 15t^4 + 10t^3
	float gradeA = 6.0f * powf(t, 5.0f);
	float gradeB = 15.0f * powf(t, 4.0f);
	float gradeC = 10.0f * powf(t, 3.0f);
	return gradeA - gradeB + gradeC;
}

int BasicRandom()
{
	static int BaiscRandom_seed = 12345;
	static int BaiscRandom_m = 67890;
	static int BaiscRandom_a = 10293;
	static int BaiscRandom_c = 84756;

	BaiscRandom_seed = (BaiscRandom_a * BaiscRandom_seed + BaiscRandom_c) % BaiscRandom_m;
	return BaiscRandom_seed;
};

float BoxMuller(float m, float s)
{
	float x1, x2, w, y1;
	static float y2;

	static int use_last = 0;

	if (use_last)
	{
		y1 = y2;
		//Reutilizar el otro valor
		use_last = 0;
	}
	else
	{
		do
		{
			x1 = 2.0f * floatRandom() - 1.0f;
			x2 = 2.0f * floatRandom() - 1.0f;
			w = x1 * x1 + x2 * x2;
		} while (w >= 1.0);

		w = sqrtf((-2.0f * logf(w)) / w);
		y1 = x1 * w;
		y2 = x2 * w;
		use_last = 1;
	}

	return(m + y1 * s);
}