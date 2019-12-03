#pragma once
#include "Vector.h"
struct Tile
{
	Rectangle rect;
	int state;
};

struct Line
{
	V2 begin;
	V2 end;
};