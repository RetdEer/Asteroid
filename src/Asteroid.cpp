#include "Asteroid.h"

Asteroid::Asteroid(const sf::Vector2u rwvp)
{
    sf::Vector2f bnds = sf::Vector2f(rwvp.x, rwvp.y);

    using namespace GenMath;

    int axis = genNumInRange(0, 3);                                 // 0 -> top, 1-> bottom, 2 -> left, 3 -> right

    _ao.setRadius(genNumInRange(20, 60));                           // radius of asteroids [20.0f, 60.0f]
    _ao.setFillColor(sf::Color(genNumInRange(0, 255),
                                           genNumInRange(0, 255),
                                           genNumInRange(0, 255))); // RGB from [0, 255]

    _ao.setOutlineThickness(genNumInRange(150, 300) * 0.01f);       // outline thickness from [1.5f, 3.0f]
    _ao.setOrigin(_ao.getRadius(), _ao.getRadius());                // set origin to the center of the circle

    switch(axis){
        case 0:
            _avel = {genNumInRange(-8, 8) * 0.01f, genNumInRange(2, 10) * 0.01f}; // {[-0.08f, 0.08f], [0.02f, 0.10f]}
            _apos = {(float)genNumInRange(100, 700), -_ao.getRadius()};           // [100.0f, 700.0f]
            break;
        case 1:
            _avel = {genNumInRange(-8, 8) * 0.01f, genNumInRange(2, 10) * -0.01f}; // {[-0.08f, 0.08f], [-0.10f, -0.02f]}
            _apos = {(float)genNumInRange(100, 700), bnds.y + _ao.getRadius()};    // [100.0f, 700.0f]
            break;
        case 2:
            _avel = {genNumInRange(2, 10) * 0.01f, genNumInRange(-8, 8) * 0.01f};  // {[0.02f, 0.10f], [-0.08f, 0.08f]}
            _apos = {-_ao.getRadius(), (float)genNumInRange(100, 700)};            // [100.0f, 700.0f]
            break;
        case 3:
            _avel = {genNumInRange(2, 10) * -0.01f, genNumInRange(-8, 8) * 0.01f}; // {[-0.10f, -0.02f], [-0.08f, 0.08f]}
            _apos = {bnds.x + _ao.getRadius(), (float)genNumInRange(100, 700)};    // [100.0f, 700.0f]
            break;
        default:
            std::terminate();                                                      // Oops!
            break;
    }

    _ao.setPosition(_apos);
}

void Asteroid::updateAsteroidData(const sf::Vector2u rwvp){
    sf::Rect<float> bnds(-_ao.getRadius(), -_ao.getRadius(), (float)rwvp.x + (2 * _ao.getRadius()), (float)rwvp.y + (2 * _ao.getRadius()));
    if(!GenMath::isBoundedBy(_ao.getPosition(), bnds))         // if the asteroid is no longer in the viewport, flag it for deletion
        _inView = false;
    else{                                                      // else update internals and graphics
        _apos += _avel;
        _ao.move(_avel);
    }
}

Asteroid::~Asteroid(){}
