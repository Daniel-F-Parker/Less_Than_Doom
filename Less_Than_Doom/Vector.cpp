#include "Vector.h"
#include <math.h>
//Vector 2


V2 operator+(V2 val1, V2 val2)
{
	V2 result;
	result.x = val1.x + val2.x;
	result.y = val1.y + val2.y;

	return result;
}
V2 operator-(V2 val1)
{
	V2 result;
	result.x = -val1.x;
	result.y = -val1.y;

	return result;
}
V2 operator-(V2 val1, V2 val2)
{
	V2 result;
	result.x = val1.x - val2.x;
	result.y = val1.y - val2.y;

	return result;
}
V2 operator*(float val1, V2 val2)
{
	V2 result;
	result.x = val1 * val2.x;
	result.y = val1 * val2.y;

	return result;
}
V2 operator*(V2 val1, float val2)
{
	V2 result;
	result.x = val1.x * val2;
	result.y = val1.y * val2;

	return result;
}

V2 &operator*=(V2 &val1, float val2)
{
	val1 = val2 * val1;

	return val1;
}
V2 &operator+=(V2 &val1, V2 val2)
{
	val1 = val2 + val1;

	return val1;
}

float DotProduct(V2 val1, V2 val2)
{
	float result = val1.x*val2.x + val1.y*val2.y;
	return result;
}

float MagnitudeSqrd(V2 val)
{
	float result = DotProduct(val, val);
	return result;
}

float Magnitude(V2 val)
{
	float result = sqrtf(MagnitudeSqrd(val));
	return result;
}

V3 operator+(V3 val1, V3 val2)
{
	V3 result;
	result.x = val1.x + val2.x;
	result.y = val1.y + val2.y;
	result.z = val1.z + val2.z;

	return result;
}
V3 operator-(V3 val1)
{
	V3 result;
	result.x = -val1.x;
	result.y = -val1.y;
	result.z = -val1.z;

	return result;
}
V3 operator-(V3 val1, V3 val2)
{
	V3 result;
	result.x = val1.x - val2.x;
	result.y = val1.y - val2.y;
	result.z = val1.z - val2.z;

	return result;
}
V3 operator*(float val1, V3 val2)
{
	V3 result;
	result.x = val1 * val2.x;
	result.y = val1 * val2.y;
	result.z = val1 * val2.z;

	return result;
}
V3 operator*(V3 val1, float val2)
{
	V3 result;
	result.x = val1.x * val2;
	result.y = val1.y * val2;
	result.z = val1.z * val2;

	return result;
}
V3 &operator*=(V3 &val1, float val2)
{
	val1 = val2 * val1;

	return val1;
}
V3 &operator+=(V3 &val1, V3 val2)
{
	val1 = val2 + val1;

	return val1;
}

float DotProduct(V3 val1, V3 val2)
{
	float result = val1.x*val2.x + val1.y*val2.y + val1.z*val2.z;
	return result;
}

float MagnitudeSqrd(V3 val)
{
	float result = DotProduct(val, val);
	return result;
}

Rectangle RectMinMax(V2 min, V2 max)
{
	Rectangle result;
	result.min = min;
	result.max = max;
	return result;
}

Rectangle RectCentreHalfWidth(V2 centre, V2 halfDim)
{
	Rectangle result;
	result.min = centre - halfDim;
	result.max = centre + halfDim;
	return result;
}

Rectangle RectCentreFullWidth(V2 centre, V2 dim)
{
	Rectangle result = RectCentreHalfWidth(centre, 0.5*dim);

	return result;
}

V2 GetMinCorner(Rectangle rec)
{
	return rec.min;
}

V2 GetMaxCorner(Rectangle rec)
{
	return rec.max;
}

V2 GetCentre(Rectangle rec)
{
	return (0.5f*(rec.min + rec.max));
}

bool IsInBounds(Rectangle rec, V2 test)
{
	bool result = ((test.x >= rec.min.x)
		&& (test.y >= rec.min.y)
		&& (test.x < rec.max.x)
		&& (test.y < rec.max.y));

	return result;
}