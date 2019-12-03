#pragma once
struct V2
{
	float x;
	float y;
};

union V3
{
	struct
	{
		float x;
		float y;
		float z;
	};
	struct
	{
		float r;
		float g;
		float b;
	};
};

union V4
{
	struct
	{
		float x;
		float y;
		float z;
		float v;
	};
	struct
	{
		float r;
		float g;
		float b;
		float a;
	};
};

struct Rectangle
{
	V2 min;
	V2 max;
};

//V2
V2 operator+(V2 val1, V2 val2);

V2 operator-(V2 val1);

V2 operator-(V2 val1, V2 val2);

V2 operator*(float val1, V2 val2);

V2 operator*(V2 val1, float val2);

V2 &operator*=(V2 &val1, float val2);

V2 &operator+=(V2 &val1, V2 val2);

float DotProduct(V2 val1, V2 val2);

float MagnitudeSqrd(V2 val);

float Magnitude(V2 val);

//V3
V3 operator+(V3 val1, V3 val2);

V3 operator-(V3 val1);

V3 operator-(V3 val1, V3 val2);

V3 operator*(float val1, V3 val2);

V3 operator*(V3 val1, float val2);

V3 &operator*=(V3 &val1, float val2);

V3 &operator+=(V3 &val1, V3 val2);

float DotProduct(V3 val1, V3 val2);

float MagnitudeSqrd(V3 val);

//Rectangle
Rectangle RectMinMax(V2 min, V2 max);

Rectangle RectCentreHalfWidth(V2 centre, V2 halfDim);

Rectangle RectCentreFullWidth(V2 centre, V2 dim);

V2 GetMinCorner(Rectangle rec);

V2 GetMaxCorner(Rectangle rec);

V2 GetCentre(Rectangle rec);

bool IsInBounds(Rectangle rec, V2 test);