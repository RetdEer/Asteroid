#include <ctime>
#include <vector>
#include <algorithm>

#include "Ship.h"
#include "Asteroid.h"

// Project #1: Asteroid Game

constexpr int maxAsteroids = 16;                                 // you can increase this value for more of a challenge
int numAsteroids = 1, wavesSurvived = -1;                        // initial number of asteroids, number of waves survived

bool checkCollisionBetweenShipAndAsteroid(const Ship& ship, const std::unique_ptr<Asteroid>& a);

int main(){
    sf::RenderWindow rw(sf::VideoMode(800.0f, 800.0f), "Asteroid", sf::Style::Titlebar | sf::Style::Close);
    Ship player(rw.getSize() / 2u);

    srand(time(NULL));                                            // Seeds the random number generator, important before calling rand()
    std::vector<std::unique_ptr<Asteroid>> asteroids = {};

    while(rw.isOpen() && player.isStillAlive()){
        sf::Event e;

        while(rw.pollEvent(e))
            if(e.type == sf::Event::Closed) rw.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))      // rotate counter-clockwise
            player.updateShipData(rw.getSize(), {0.0f, 0.0f}, -0.1f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    // rotate clockwise
            player.updateShipData(rw.getSize(), {0.0f, 0.0f}, 0.1f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){       // vector of centroid and the ship's nose
            sf::Vector2f normdVec = player.getSverts()[1] - player.getSpos();
            player.updateShipData(rw.getSize(), 0.1f * GenMath::norm(normdVec));
        }

        if(asteroids.empty()){                                 // if all the asteroids have despawned, spawn some more!
            for(int i = 0; i < numAsteroids; ++i)
                asteroids.push_back(std::make_unique<Asteroid>(rw.getSize()));

            numAsteroids = (numAsteroids >= maxAsteroids ? maxAsteroids : (numAsteroids + 1));
            wavesSurvived += 1;
        }
        else{                                                  // otherwise update all remaining asteroids
            for(auto& a : asteroids)
                a->updateAsteroidData(rw.getSize());           // remove then erase out of bound asteroid(s)

            asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
                                    [](const std::unique_ptr<Asteroid>& a){return !a->isInView();}),
                                    asteroids.end());
        }

        // AABB check first in order to reduce the number of SAT checks

        for(const auto& a : asteroids){
            if(a->getApos().x + a->getRadius() > player.getSo().getGlobalBounds().left &&
               a->getApos().x - a->getRadius() < player.getSo().getGlobalBounds().left + player.getSo().getGlobalBounds().width &&
               a->getApos().y + a->getRadius() > player.getSo().getGlobalBounds().top &&
               a->getApos().y - a->getRadius() < player.getSo().getGlobalBounds().top + player.getSo().getGlobalBounds().height){
                    player.setIsAlive(!checkCollisionBetweenShipAndAsteroid(player, a));
            }
        }

        if(!player.isStillAlive()){                                                 // R.I.P.
            std::cout << "BOOM!! Your ship was destroyed!\n";
            std::cout << "You survived " << wavesSurvived << " wave(s)!\n";
        }

        rw.clear();                                                                 // clear the screen, draw new frame, then display it
        rw.draw(player.getSo());
        for(const auto& a : asteroids) rw.draw(a->getAo());
        rw.display();
    }

    std::cin.get();
    return 0;
}

// Code block translated into C++ from https://gamedevelopment.tutsplus.com/tutorials/collision-detection-using-the-separating-axis-theorem--gamedev-169

bool checkCollisionBetweenShipAndAsteroid(const Ship& ship, const std::unique_ptr<Asteroid>& a){   // Seperating Axis Theorem applied with a triangle and a circle
    sf::Vector2f delta, vert;
    float max_ast = -INFINITY;    // dot products can be negative so we need to guarantee max_ast will always be greater than the first one
    sf::Vector2f shipToAst = a->getAo().getPosition() - ship.getSpos();
    sf::Vector2f normShipToAst = GenMath::norm(shipToAst);

    for(std::size_t i = 0; i < ship.getSo().getPointCount(); ++i){
        vert = ship.getSverts()[i];
        delta = vert - ship.getSo().getPosition();
        float proj = GenMath::dot(delta, normShipToAst);
        max_ast = std::max(max_ast, proj);
    }

    if(GenMath::mag(shipToAst) - max_ast - a->getRadius() > 0.0f && GenMath::mag(shipToAst) > 0.0f) return false;
    else return true;
}


