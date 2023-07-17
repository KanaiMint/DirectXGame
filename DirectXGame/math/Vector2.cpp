#include "Vector2.h"



float Vector2::Length(const Vector2& v, const Vector2& v2) {
	float tmp;
	float dx = v2.x - v.x;
	float dy = v2.y - v.y;
	tmp = sqrtf((dx * dx) + (dy * dy));

	return tmp;
}
