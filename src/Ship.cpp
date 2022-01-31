#include "Ship.h"

Ship::Ship(const sf::Vector2u loc)
: _so(sf::ConvexShape(3))
{
    sf::Vector2f ipos = sf::Vector2f(loc.x, loc.y);
    sf::Vector2f verts[3] = {{0.0f, 0.0f}, {18.0f, 24.0f}, {36.0f, 0.0f}};   // isoceles triangle, side lengths: 30-30-36 pixels
    for(std::size_t i = 0; i < _so.getPointCount(); ++i)
        _so.setPoint(i, verts[i]);

    _so.setFillColor(sf::Color::Blue);                                                      // ship prefabs
    _so.setOutlineThickness(0.8f);
    _so.setOutlineColor(sf::Color::Green);

    _so.setOrigin({(verts[0].x + verts[1].x + verts[2].x) / 3.0f,                 // location of centroid (local coordinates)
                           (verts[0].y + verts[1].y + verts[2].y) / 3.0f});

    sf::Transform translator;
    translator.translate(ipos);
    for(std::size_t i = 0; i < _so.getPointCount(); ++i)                            // translates local coordinate verts into world coordinate _sverts
        _sverts[i] = translator.transformPoint(verts[i]);

    _so.setPosition(translator.transformPoint(_so.getOrigin()));               // position of centroid (world coordinates)
}

void Ship::updateShipData(const sf::Vector2u rwvp, const sf::Vector2f newVel, const float newRot){
    sf::Transform transformer;
    transformer.translate(newVel).rotate(newRot, _so.getPosition());

    sf::Vector2f bnds = sf::Vector2f(rwvp.x, rwvp.y);
    sf::Vector2f trcntr = transformer.transformPoint(_so.getPosition());

    if(trcntr.x < 0.0f || trcntr.x > bnds.x || trcntr.y < 0.0f || trcntr.y > bnds.y)
    {
       sf::Vector2f warp = {0.0f, 0.0f};

       if(getSpos().x < 0.0f) warp.x = bnds.x;                       // determines where the centroid is out of bounds in order to calculate warp
       if(getSpos().x > bnds.x) warp.x = -bnds.x;
       if(getSpos().y < 0.0f) warp.y = bnds.y;
       if(getSpos().y > bnds.y) warp.y = -bnds.y;

       for(std::size_t i = 0; i < _so.getPointCount(); ++i) _sverts[i] += warp;     // move vertices
        _so.move(warp);                                                                                   // move graphics
    }

    _so.move(newVel);                                                      // these update what you see on the screen
    _so.rotate(newRot);

    for(std::size_t i = 0; i < _so.getPointCount(); ++i)        // these update _sverts for the next computation
        _sverts[i] = transformer.transformPoint(_sverts[i]);
}

Ship::~Ship(){}
