#ifndef ASTEROID_H
#define ASTEROID_H

#include <cstdlib>
#include <ctime>

#include "GenMath.h"

// Asteroid Class, all you need is the bounds to spawn them in... Asteroids are randomly generated

class Asteroid
{
    public:
        Asteroid(const sf::Vector2u rwvp);
        void updateAsteroidData(const sf::Vector2u rwvp);

        const sf::CircleShape& getAo() const {return _ao;}
        const sf::Vector2f& getApos() const {return _apos;}
        float getRadius() const {return _ao.getRadius();}

        constexpr bool isInView() const {return _inView;}
        virtual ~Asteroid();

    private:
        sf::CircleShape _ao;
        sf::Vector2f _apos, _avel;
        bool _inView = true;
};

#endif
