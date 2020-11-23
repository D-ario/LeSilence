#include "Math.h"

float VectorMath::DotProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return (a.x * b.x) + (a.y * b.y);
}

float VectorMath::CrossProduct(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return (a.x * b.y) - (a.y * b.x);
}

float VectorMath::Len(const sf::Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f VectorMath::Normalize(const sf::Vector2f& vector)
{
	float invertLen = 1.0f / VectorMath::Len(vector);

	if (invertLen == 0)
	{
		invertLen = 1;
	}

	return sf::Vector2f(vector.x * invertLen, vector.y * invertLen);
}

float VectorMath::Angle(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float len = VectorMath::Len(a) * VectorMath::Len(b);
	float cos = 0.0f;

	if (len != 0.0f)
	{
		cos = VectorMath::DotProduct(a, b) / len;
	}

	float cross = VectorMath::CrossProduct(a, b);
	float sign = 1.0f;

	if (cross < 0.0f)
	{
		sign = -1.0f;
	}
	else if (cross > 0.0f)
	{
		sign = 1.0f;
	}
	else
	{
		sign = cos;
	}

	float angle = sign * acos(cos);

	return angle * 180.0f / PI; // To degree
}
