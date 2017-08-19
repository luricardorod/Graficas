#pragma once
#include "CVector4D.h"

float floatRandom();

int RandomBetween(int minValue, int maxValue);

CVector4D Circumcircle(CVector4D & p0, CVector4D & p1, CVector4D & p2, float & radius);

CVector4D proyectLeftOverDer(CVector4D & thisVec, CVector4D & proyectVect);

float Clamp(float min, float max, float value);

float lerp(float v0, float v1, float t);

float fade(float t);

int BasicRandom();

float BoxMuller(float m, float s);