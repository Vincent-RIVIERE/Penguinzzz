#include <SFML/Graphics.hpp>
#include "Obstacle.hpp"

#ifndef MAP_HPP
#define MAP_HPP

class Map {
    public:
        Map(int n);
        void reset();
        void setChangeState();
        int** getMap();
        sf::VertexArray getGround();
        sf::VertexArray getAir();
        bool wereChanged();
        int getXsize();
        int getYsize();
    private:
        int **map;
        int x_size;
        int y_size;
        sf::VertexArray ground;
        sf::VertexArray air;
        std::vector<Obstacle> obstacles;
        bool changed;
};

#endif