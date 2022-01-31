#include "GenMath.h"

float GenMath::mag(const sf::Vector2f v){                               // magnitude of a vector
    return std::sqrt(v.x * v.x + v.y * v.y);
}

float GenMath::dot(const sf::Vector2f v1, const sf::Vector2f v2){       // dot product of two vectors
    return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f GenMath::perp(const sf::Vector2f v){                        // perpendicular vector between two points
    return {-v.y, v.x};
}

sf::Vector2f GenMath::norm(const sf::Vector2f v){                        // normalizes a vector given its two endpoints
    return {v.x / mag(v), v.y / mag(v)};
}

int GenMath::genNumInRange(const int minInt, const int maxInt){          // returns random number in range minInt -> maxInt inclusive
    return minInt + (std::rand() % (maxInt - minInt + 1));
}

bool GenMath::isBoundedBy(const sf::Vector2f p, const sf::Rect<float>& bnds){ // checks if point is in a bounding rectangle, it's basically Rect::contain() except the bounds are inclusive
    if(p.x >= bnds.left && p.y >= bnds.top && p.x <= bnds.left + bnds.width && p.y <= bnds.top + bnds.height) return true;
    else return false;
}
