#ifndef SHIP_H
#define SHIP_H

#include "GenMath.h"

// Aka the Player Class, you only need the bounds to spawn it in. Always spawns in the center of the screen.

class Ship
{
    public:
        Ship(const sf::Vector2u loc = {0u, 0u});
        void updateShipData(const sf::Vector2u rwvp, const sf::Vector2f newVel = {0.0f, 0.0f}, const float newRot = 0.0f);

        const sf::ConvexShape& getSo() const {return _so;}
        const sf::Vector2f& getSpos() const {return _so.getPosition();}
        const sf::Vector2f * getSverts() const {return _sverts;}

        constexpr bool isStillAlive() const {return _isAlive;}
        void setIsAlive(const bool isAlive){_isAlive = isAlive;}
        virtual ~Ship();

    private:
        sf::ConvexShape _so;
        float _srot = 0.0f;
        sf::Vector2f _sverts[3];
        bool _isAlive = true;
};

#endif
