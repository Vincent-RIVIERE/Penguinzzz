#include "Map.hpp"
#include <fstream>
#include <iostream>

Map::Map(int n){
    std::ifstream file;
    switch(n){
        case 1:
            file.open("map1.txt");
            this->x_size = 1000;
            this->y_size = 700;
            break;
        case 2:
            file.open("map2.txt");
            this->x_size = 1000;
            this->y_size = 700;
            break;
    }
    std::string data;
    file >> data;
    this->map = (int**)malloc(this->x_size*sizeof(int*));
    for(int i = 0; i < this->x_size; i++){
        map[i] = (int*)malloc(this->y_size*sizeof(int));
    }
    int i = this->x_size*this->y_size-1;
    for(int y = 0; y < this->y_size; y++){
        for(int x = 0; x < this->x_size; x++){
            if(data[i]=='1'){
                this->map[x][y]=1;
            } else {
                this->map[x][y]=0;
            }
            i--;
        }
    }
    this->ground.setPrimitiveType(sf::Points);
}

void Map::reset(){
    this->ground.resize(0);
    this->air.resize(0);
    for(int y = 0; y < this->y_size; y++){
        for(int x = 0; x < this->x_size; x++){
            if(this->map[x][y]==1){
                sf::Vertex pix(sf::Vector2f(x,y),sf::Color::Green);
                this->ground.append(pix);
            } else if(this->map[x][y]==0){
                sf::Vertex pix(sf::Vector2f(x,y),sf::Color::Cyan);
                this->air.append(pix);
            }
        }
    }
    this->changed = false;
}

void Map::setChangeState(){
    this->changed = true;
}

int** Map::getMap(){
    return this->map;
}

sf::VertexArray Map::getGround(){
    return this->ground;
}

sf::VertexArray Map::getAir(){
    return this->air;
}

bool Map::wereChanged(){
    return this->changed;
}

int Map::getXsize(){
    return this->x_size;
}

int Map::getYsize(){
    return this->y_size;
}