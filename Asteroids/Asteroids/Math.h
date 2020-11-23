#ifndef _MATH_H_
#define _MATH_H_

#include <SFML/Graphics.hpp>

static constexpr float PI = 3.14159265358979323846f;

class VectorMath
{
public:
	static float Angle(const sf::Vector2f& a, const sf::Vector2f& b);
	static float DotProduct(const sf::Vector2f& a, const sf::Vector2f& b);
	static float CrossProduct(const sf::Vector2f& a, const sf::Vector2f& b);
	static float Len(const sf::Vector2f& vector);
	static sf::Vector2f Normalize(const sf::Vector2f& vector);
};

#endif
