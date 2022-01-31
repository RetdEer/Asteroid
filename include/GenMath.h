#ifndef GENMATH_H
#define GENMATH_H

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

// Common Vector/Math operations, the next step would be to templatize these functions...

namespace GenMath{
    float mag(const sf::Vector2f v);
    float dot(const sf::Vector2f v1, const sf::Vector2f v2);
    sf::Vector2f perp(const sf::Vector2f v);
    sf::Vector2f norm(const sf::Vector2f v);
    int genNumInRange(const int minInt, const int maxInt);
    bool isBoundedBy(const sf::Vector2f p, const sf::Rect<float>& bnds);
}

#endif
